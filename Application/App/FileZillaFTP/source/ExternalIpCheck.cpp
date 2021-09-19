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

#include "stdafx.h"
#include "ExternalIpCheck.h"
#include "ServerThread.h"
#include "Options.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

#define TIMERINTERVAL 30

CExternalIpCheck::CExternalIpCheck(CServerThread *pOwner)
{
	ASSERT(pOwner);
	m_pOwner = pOwner;

	m_bActive = FALSE;
	m_nRetryCount = 0;
	m_nTimerID = SetTimer(0, 0, TIMERINTERVAL * 1000, 0);
	m_bTriggerUpdateCalled = FALSE;
	m_nFailedConnections = 0;
	m_nElapsedSeconds = 0;
	
	if (!m_pOwner->m_pOptions->GetOptionVal(OPTION_CUSTOMPASVIPTYPE))
		return;
	
	if (m_pOwner->m_pOptions->GetOptionVal(OPTION_CUSTOMPASVIPTYPE) == 2)
		Start();
	else if (m_pOwner->m_pOptions->GetOptionVal(OPTION_CUSTOMPASVIPTYPE) == 1)
	{
		CStdString hostname = m_pOwner->m_pOptions->GetOption(OPTION_CUSTOMPASVIP);
		SOCKADDR_IN sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		
		sockAddr.sin_family = AF_INET;
#ifdef _UNICODE
		sockAddr.sin_addr.s_addr = inet_addr(ConvToLocal(hostname));
#else
		sockAddr.sin_addr.s_addr = inet_addr(hostname);
#endif
		
		if (sockAddr.sin_addr.s_addr == INADDR_NONE)
		{
			LPHOSTENT lphost;
#ifdef _UNICODE
			lphost = gethostbyname(ConvToLocal(hostname));
#else
			lphost = gethostbyname(hostname);
#endif
			if (lphost != NULL)

				sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
			else
			{
				Close();
				m_nRetryCount++;
				m_bActive = FALSE;
				return;
			}
		}
		
		const char *ip = inet_ntoa(sockAddr.sin_addr);
		
		if (!ip)
			return;
		
#ifdef _UNICODE
		m_IP = ConvFromLocal(ip);
#else
		m_IP = ip;
#endif
	}
}

CExternalIpCheck::~CExternalIpCheck()
{
	Close();
}

void CExternalIpCheck::OnReceive(int nErrorCode)
{
	if (!m_bActive)
		return;

	if (nErrorCode)
	{
		m_bActive = FALSE;
		Close();
		m_nRetryCount++;
		return;
	}
	char buffer[1000];
	int len = Receive(buffer, 999);

	if (len == SOCKET_ERROR)
	{
		if (GetLastError() == WSAEWOULDBLOCK)
			return;
	
		Close();
		m_nRetryCount++;
		m_bActive = FALSE;
		return;
	}

	buffer[len] = 0;
	char *p = strstr(buffer, "\r\n\r\n");
	if (!p)
		p = strstr(buffer, "\n\n");

	if (!p)
	{
		Close();
		m_nRetryCount++;
		m_bActive = FALSE;
		return;
	}
	
	
	while (*p && (*p == '\n' || *p == '\r'))
		p++;

	if (!*p)
	{
		Close();
		m_nRetryCount++;
		m_bActive = FALSE;
		return;
	}

	char * ip = p;
	while (*p && *p != '\n' && *p != '\r')
		p++;
	*p = 0;
	
	SOCKADDR_IN sockAddr;
	memset(&sockAddr,0,sizeof(sockAddr));
	
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(ip);
	
	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(ip);
		if (lphost != NULL)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
			Close();
			m_nRetryCount++;
			m_bActive = FALSE;
			return;
		}
	}
	
	ip = inet_ntoa(sockAddr.sin_addr);

	if (!ip)
	{		
		Close();
		m_nRetryCount++;
		m_bActive = FALSE;
		return;
	}
	
#ifdef _UNICODE
	m_IP = ConvFromLocal(ip);
#else
	m_IP = ip;
#endif

	m_nFailedConnections = 0;

	Close();
	m_nRetryCount = 0;
	m_bActive = FALSE;
}

void CExternalIpCheck::OnConnect(int nErrorCode)
{
	if (!m_bActive)
		return;

	if (nErrorCode)
	{
		m_bActive = FALSE;
		Close();
		m_nRetryCount++;
		return;
	}
	
	CStdStringA address = "GET " + m_pOwner->m_pOptions->GetOption(OPTION_CUSTOMPASVIPSERVER) + " HTTP/1.0\r\nUser-Agent: FileZilla Server\r\n\r\n";
	const char *buffer = address;
	int len = strlen(buffer);
	if (Send(buffer, len) != len)
	{
		m_bActive = FALSE;
		Close();
		m_nRetryCount++;
	}

	OnReceive(0);
}

void CExternalIpCheck::OnTimer()
{
	if (m_nElapsedSeconds <= 1000000)
		m_nElapsedSeconds += TIMERINTERVAL;

	if (!m_pOwner->m_pOptions->GetOptionVal(OPTION_CUSTOMPASVIPTYPE))
	{
		m_nRetryCount = 0;
		Close();
		m_bActive = FALSE;
		return;
	}
	else if (m_pOwner->m_pOptions->GetOptionVal(OPTION_CUSTOMPASVIPTYPE) == 1)
	{
		m_nRetryCount = 0;
		Close();
		m_bActive = FALSE;

		CStdString hostname = m_pOwner->m_pOptions->GetOption(OPTION_CUSTOMPASVIP);
		SOCKADDR_IN sockAddr;
		memset(&sockAddr,0,sizeof(sockAddr));
		
		sockAddr.sin_family = AF_INET;
#ifdef _UNICODE
		sockAddr.sin_addr.s_addr = inet_addr(ConvToLocal(hostname));
#else
		sockAddr.sin_addr.s_addr = inet_addr(hostname);
#endif
		
		if (sockAddr.sin_addr.s_addr == INADDR_NONE)
		{
			LPHOSTENT lphost;
#ifdef _UNICODE
			lphost = gethostbyname(ConvToLocal(hostname));
#else
			lphost = gethostbyname(hostname);
#endif
			if (lphost != NULL)
				sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
			else
			{
				Close();
				m_nRetryCount++;
				m_bActive = FALSE;
				return;
			}
		}
		
		const char *ip = inet_ntoa(sockAddr.sin_addr);
		
		if (!ip)
			return;
	
#ifdef _UNICODE
		m_IP = ConvFromLocal(ip);
#else
		m_IP = ip;
#endif
		m_nFailedConnections = 0;
		return;
	}

	if (!m_bActive && m_nRetryCount)
	{
		if (m_nElapsedSeconds > 60 && m_nRetryCount < 5)
		{
			Start();
			return;
		}
		else if (m_nElapsedSeconds > 300 && m_nRetryCount < 10)
		{
			Start();
			return;
		}
		else if (m_nElapsedSeconds > 900 && m_nRetryCount < 20)
		{
			Start();
			return;
		}
		else if (m_nElapsedSeconds > 3600)
		{
			Start();
			return;
		}
	}
	else if (m_bActive)
	{
		if (m_nElapsedSeconds > 30)
		{
			m_bActive = FALSE;
			Close();
			m_nRetryCount++;
			m_nElapsedSeconds = 0;
		}
	}
	else
	{
		if (m_nElapsedSeconds > 300 && m_bTriggerUpdateCalled)
			Start();
		else if (m_nElapsedSeconds > 3600)
			Start();
	}
}

void CExternalIpCheck::OnClose(int nErrorCode)
{
	if (m_bActive)
	{
		m_bActive = FALSE;
		Close();
		m_nRetryCount++;
	}
}

void CExternalIpCheck::Start()
{
	if (m_bActive)
		return;

	CStdString address = m_pOwner->m_pOptions->GetOption(OPTION_CUSTOMPASVIPSERVER);
	if (address.Left(7) == _T("http://"))
		address = address.Mid(7);
	int pos = address.Find('/');
	if (pos != -1)
		address = address.Left(pos);
	if (address == _T(""))
		return;

	m_bTriggerUpdateCalled = FALSE;

	m_nElapsedSeconds = 0;
	Create();

	BOOL res = Connect(address, 80);
	if (res == SOCKET_ERROR && GetLastError() != WSAEWOULDBLOCK)
		m_nRetryCount++;
	else
		m_bActive = TRUE;
}

void CExternalIpCheck::TriggerUpdate()
{
	if (m_bActive)
		return;

	m_bTriggerUpdateCalled = TRUE;
	if (m_nFailedConnections < 100000)
		m_nFailedConnections++;
}

CStdString CExternalIpCheck::GetIP(const CStdString& localIP)
{
	if (!m_pOwner->m_pOptions->GetOptionVal(OPTION_CUSTOMPASVIPTYPE))
		return _T("");

	CStdString ip;
	switch (m_pOwner->m_pOptions->GetOptionVal(OPTION_CUSTOMPASVIPTYPE))
	{
	case 0:
		return _T("");
	case 2:
		if (!m_bActive && !m_nRetryCount && localIP != _T(""))
		{
			if (localIP == m_IP)
				m_nElapsedSeconds = 0;
		}
	case 1:
		ip = m_IP;
		
		break;
	}
	
	return ip;
}
