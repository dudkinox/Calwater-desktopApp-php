// FileZilla Server - a Windows ftp server

// Copyright (C) 2002-2004 - Tim Kosse <tim.kosse@gmx.de>

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// AdminSocket.cpp: Implementierung der Klasse CAdminSocket.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AdminSocket.h"
#include "AdminInterface.h"
#include "OptionTypes.h"
#include "misc\md5.h"
#include "iputils.h"
#include "Options.h"
#include "version.h"

#define BUFSIZE 4096

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CAdminSocket::CAdminSocket(CAdminInterface *pAdminInterface)
{
	ASSERT(pAdminInterface);
	m_pAdminInterface = pAdminInterface;
	m_bStillNeedAuth = TRUE;

	m_pRecvBuffer = new unsigned char[BUFSIZE];
	m_nRecvBufferLen = BUFSIZE;
	m_nRecvBufferPos = 0;
	
	SYSTEMTIME sTime;
	GetSystemTime(&sTime);
	VERIFY(SystemTimeToFileTime(&sTime, &m_LastRecvTime));
}

CAdminSocket::~CAdminSocket()
{
	for (std::list<t_data>::iterator iter=m_SendBuffer.begin(); iter!=m_SendBuffer.end(); iter++)
		delete [] iter->pData;

	delete [] m_pRecvBuffer;
}

BOOL CAdminSocket::Init()
{
	char *buffer = new char[100];
	char *p = buffer;
	strcpy(buffer, "FZS");
	p += 3;

	*p++ = 0;
	*p++ = 4;
	memcpy(p, &SERVER_VERSION, 4);
	p += 4;
	
	*p++ = 0;
	*p++ = 4;

	memcpy(p, &PROTOCOL_VERSION, 4);
	p+=4;

	COptions options;
	CStdString pass = options.GetOption(OPTION_ADMINPASS);
	CStdString peerAddress;
	UINT port = 0;
	if (GetPeerName(peerAddress, port) && IsLocalhost(peerAddress) && pass == _T(""))
	{
		BOOL res = Send(buffer, p-buffer) == p - buffer;
		delete [] buffer;
		if (!res)
		{
			Close();
			return FALSE;
		}
		return FinishLogon();		
	}
	else
	{
		*p++ = 0;
		
		DWORD len = 20;
		memcpy(p, &len, 4);
		p += 4;

		*p++ = 0;
		*p++ = 8;
		
		int i;
		for (i = 0; i < 8; i++)
		{
			m_Nonce1[i] = (rand()*256)/(RAND_MAX+1);
			*p++ = m_Nonce1[i];
		}
		
		*p++ = 0;
		*p++ = 8;
		
		for (i = 0; i < 8; i++)
		{
			m_Nonce2[i] = (rand()*256)/(RAND_MAX+1);
			*p++ = m_Nonce2[i];
		}
	}

	int res = Send(buffer, p-buffer) == p-buffer;
	delete [] buffer;
	return res;
}

BOOL CAdminSocket::SendCommand(int nType, int nID, const void *pData, int nDataLength)
{
	if (m_bStillNeedAuth)
		return TRUE;

	t_data data;
	data.pData = new unsigned char[nDataLength + 5];
	*data.pData = nType;
	*data.pData |= nID << 2;
	data.dwOffset = 0;
	memcpy(data.pData + 1, &nDataLength, 4);
	if (pData)
		memcpy(data.pData+5, pData, nDataLength);

	data.dwLength = nDataLength + 5;

	m_SendBuffer.push_back(data);
	
	do
	{
		data = m_SendBuffer.front();
		m_SendBuffer.pop_front();
		int nSent = Send(data.pData + data.dwOffset, data.dwLength - data.dwOffset);
		if (!nSent)
			return FALSE;
		if (nSent == SOCKET_ERROR)
		{
			if (WSAGetLastError()!=WSAEWOULDBLOCK)
				return FALSE;
			m_SendBuffer.push_front(data);
			return TRUE;
		}
		
		if ((unsigned int)nSent < (data.dwLength-data.dwOffset))
		{
			data.dwOffset += nSent;
			m_SendBuffer.push_front(data);
		}
		else
		{
			delete [] data.pData;

			SYSTEMTIME sTime;
			GetSystemTime(&sTime);
			VERIFY(SystemTimeToFileTime(&sTime, &m_LastRecvTime));
		}
	} while (!m_SendBuffer.empty());

	return TRUE;
}

void CAdminSocket::OnReceive(int nErrorCode)
{
	if (nErrorCode)
	{
		Close();
		m_pAdminInterface->Remove(this);
		return;
	}
	int numread = Receive(m_pRecvBuffer + m_nRecvBufferPos, m_nRecvBufferLen - m_nRecvBufferPos);
	if (numread > 0)
	{
		SYSTEMTIME sTime;
		GetSystemTime(&sTime);
		VERIFY(SystemTimeToFileTime(&sTime, &m_LastRecvTime));

		m_nRecvBufferPos += numread;
		if (m_nRecvBufferLen-m_nRecvBufferPos < (BUFSIZE/4))
		{
			unsigned char *tmp=m_pRecvBuffer;
			m_nRecvBufferLen *= 2;
			m_pRecvBuffer = new unsigned char[m_nRecvBufferLen];
			memcpy(m_pRecvBuffer, tmp, m_nRecvBufferPos);
			delete [] tmp;
		}
		int parseResult;
		while ((parseResult = ParseRecvBuffer()) > 0);

		if (parseResult == -1)
			return;
	}
	if (numread == 0)
	{
		if (ParseRecvBuffer() == -1)
			return;
		Close();
		m_pAdminInterface->Remove(this);
		return;
	}
	else if (numread == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			if (ParseRecvBuffer() == -1)
				return;
			Close();
			m_pAdminInterface->Remove(this);
			return;
		}
	}
	while (ParseRecvBuffer() > 0);
}

void CAdminSocket::OnSend(int nErrorCode)
{
	if (nErrorCode)
	{
		Close();
		m_pAdminInterface->Remove(this);
		return;
	}

	while (!m_SendBuffer.empty())
	{
		t_data data=m_SendBuffer.front();
		m_SendBuffer.pop_front();
		int nSent = Send(data.pData+data.dwOffset, data.dwLength-data.dwOffset);
		if (!nSent)
		{
			Close();
			m_pAdminInterface->Remove(this);
			return;
		}
		if (nSent == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				Close();
				m_pAdminInterface->Remove(this);
			}
			m_SendBuffer.push_front(data);
			return;
		}
		
		if ((unsigned int)nSent<(data.dwLength-data.dwOffset))
		{
			data.dwOffset+=nSent;
			m_SendBuffer.push_front(data);
		}
		else
			delete [] data.pData;
	}
}

int CAdminSocket::ParseRecvBuffer()
{
	if (m_nRecvBufferPos<5)
		return 0;

	if ((m_pRecvBuffer[0]&0x03) != 0)
	{
		SendCommand(_T("Protocol error: Unknown command type, closing connection."), 1);
		Close();
		m_pAdminInterface->Remove(this);
		return -1;
	}
	else
	{
		DWORD len;
		memcpy(&len, m_pRecvBuffer+1, 4);
		if (len > 0xFFFFFF)
		{
			SendCommand(_T("Protocol error: Invalid data length, closing connection."), 1);
			Close();
			m_pAdminInterface->Remove(this);
			return -1;
		}
		if (m_nRecvBufferPos < len+5)
			return 0;
		else
		{
			int nID = (m_pRecvBuffer[0]&0x7C) >> 2;
			if (m_bStillNeedAuth)
			{
				if (nID)
				{
					SendCommand(_T("Protocol error: Not authenticated, closing connection."), 1);
					Close();
					m_pAdminInterface->Remove(this);
					return -1;
				}
				if (len != 16)
				{
					SendCommand(_T("Protocol error: Auth data len invalid, closing connection."), 1);
					Close();
					m_pAdminInterface->Remove(this);
					return -1;
				}
				MD5 md5;
				md5.update(m_Nonce1, 8);
				COptions options;
				CStdString pass = options.GetOption(OPTION_ADMINPASS);
				if (pass.GetLength() < 6)
				{
					SendCommand(_T("Protocol error: Server misconfigured, admin password not set correctly"), 1);
					Close();
					m_pAdminInterface->Remove(this);
					return -1;
				}
				char* utf8 = ConvToNetwork(pass);
				if (!utf8)
				{
					SendCommand(_T("Failed to convert password to UTF-8"), 1);
					Close();
					m_pAdminInterface->Remove(this);
					return -1;
				}
				md5.update((unsigned char *)utf8, strlen(utf8));
				delete [] utf8;
				md5.update(m_Nonce2, 8);
				md5.finalize();
				unsigned char *digest = md5.raw_digest();
				if (memcmp(m_pRecvBuffer + 5, digest, 16))
				{
					delete [] digest;
					SendCommand(_T("Protocol error: Auth failed, closing connection."), 1);
					Close();
					m_pAdminInterface->Remove(this);
					return -1;
				}
				delete [] digest;

				FinishLogon();
			}
			else
				m_pAdminInterface->ProcessCommand(this, nID, m_pRecvBuffer+5, len);
			memmove(m_pRecvBuffer, m_pRecvBuffer+len+5, m_nRecvBufferPos-len-5);
			m_nRecvBufferPos-=len+5;
		}
	}
	return 1;
}

BOOL CAdminSocket::SendCommand(LPCTSTR pszCommand, int nTextType)
{
	DWORD nDataLength;
	const char *utf8 = 0;

	if (!pszCommand)
		nDataLength = 0;
	else
	{
		utf8 = ConvToNetwork(pszCommand);
		nDataLength = strlen(utf8) + 1;
	}

	t_data data;
	data.pData = new unsigned char[nDataLength + 5];
	*data.pData = 2;
	*data.pData |= 1 << 2;
	data.dwOffset = 0;
	memcpy(data.pData + 1, &nDataLength, 4);
	*(data.pData+5) = nTextType;
	if (utf8)
		memcpy(reinterpret_cast<char *>(data.pData+6), utf8, nDataLength - 1);
	delete [] utf8;

	data.dwLength = nDataLength + 5;

	m_SendBuffer.push_back(data);
	
	do 
	{
		data = m_SendBuffer.front();
		m_SendBuffer.pop_front();
		int nSent = Send(data.pData + data.dwOffset, data.dwLength - data.dwOffset);
		if (!nSent)
			return FALSE;
		if (nSent == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
				return FALSE;
			m_SendBuffer.push_front(data);
			return TRUE;
		}
		
		if ((unsigned int)nSent < (data.dwLength - data.dwOffset))
		{
			data.dwOffset += nSent;
			m_SendBuffer.push_front(data);
		}
		else
			delete [] data.pData;
	} while (!m_SendBuffer.empty());

	return TRUE;
}

BOOL CAdminSocket::CheckForTimeout()
{
	SYSTEMTIME sTime;
	FILETIME fTime;
	GetSystemTime(&sTime);
	VERIFY(SystemTimeToFileTime(&sTime, &fTime));
	
	_int64 LastRecvTime = ((_int64)m_LastRecvTime.dwHighDateTime << 32) + m_LastRecvTime.dwLowDateTime;
	_int64 CurTime = ((_int64)fTime.dwHighDateTime << 32) + fTime.dwLowDateTime;

	if ((CurTime - LastRecvTime) > 600000000) // 60 seconds
		return TRUE;

	return FALSE;
}

BOOL CAdminSocket::FinishLogon()
{
	m_bStillNeedAuth = FALSE;

	//Logon successful
	if (!SendCommand(1, 0, NULL, 0))
		return FALSE;
	return TRUE;
}
