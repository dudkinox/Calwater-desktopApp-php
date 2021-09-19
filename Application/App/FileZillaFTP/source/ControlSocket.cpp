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

// ControlSocket.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ControlSocket.h"
#include "transfersocket.h"
#include "ServerThread.h"
#include "Options.h"
#include "Permissions.h"
#include "AsyncGssSocketLayer.h"
#include "AsyncSslSocketLayer.h"
#include <math.h>
#include "iputils.h"
#include "autobanmanager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlSocket

std::map<CStdString, int> CControlSocket::m_UserCount;
CCriticalSectionWrapper CControlSocket::m_Sync;

CControlSocket::CControlSocket(CServerThread *pOwner)
	: m_hash_algorithm(CHashThread::SHA1)
{
	m_status.loggedon = FALSE;
	m_status.hammerValue = 0;
	m_transferstatus.socket = NULL;
	m_transferstatus.ip = _T("");
	m_transferstatus.port = -1;
	m_transferstatus.pasv = -1;
	m_transferstatus.rest = 0;
	m_transferstatus.type = -1;
	m_transferstatus.family = AF_UNSPEC;
	m_bWaitGoOffline = FALSE;
	GetSystemTime(&m_LastTransferTime);
	GetSystemTime(&m_LastCmdTime);
	GetSystemTime(&m_LoginTime);
	m_bQuitCommand = FALSE;

	ASSERT(pOwner);
	m_pOwner = pOwner;

	m_nTelnetSkip = 0;
	m_nRecvBufferPos = 0;

	m_pSendBuffer = NULL;
	m_nSendBufferLen = 0;

	m_pGssLayer = NULL;
	m_pSslLayer = NULL;

	for (int i = 0; i < 2; i++)
	{
		m_SlQuotas[i].bContinue = false;
		m_SlQuotas[i].nBytesAllowedToTransfer = -1;
		m_SlQuotas[i].nTransferred = 0;
		m_SlQuotas[i].bBypassed = true;
	}

	m_transferMode = mode_stream;

	m_zlibLevel = 8;

	m_antiHammeringWaitTime = 0;
	m_bProtP = false;

	m_useUTF8 = true;

	for (int i = 0; i < 3; i++)
		m_facts[i] = true;
	m_facts[fact_perm] = false;

	m_shutdown = false;

	m_hash_id = 0;
}

CControlSocket::~CControlSocket()
{
	if (m_status.loggedon)
	{
		DecUserCount(m_status.user);
		m_pOwner->DecIpCount(m_status.ip);
		m_status.loggedon = FALSE;
	}
	t_connop *op = new t_connop;
	op->data = 0;
	op->op = USERCONTROL_CONNOP_REMOVE;
	op->userid = m_userid;
	m_pOwner->SendNotification(FSM_CONNECTIONDATA, (LPARAM)op);
	if (m_transferstatus.socket)
		delete m_transferstatus.socket;
	m_transferstatus.socket=0;

	delete [] m_pSendBuffer;
	m_nSendBufferLen = 0;

	RemoveAllLayers();
	delete m_pGssLayer;
	delete m_pSslLayer;
}

/////////////////////////////////////////////////////////////////////////////
// Member-Funktion CControlSocket

#define BUFFERSIZE 500
void CControlSocket::OnReceive(int nErrorCode)
{
	if (m_antiHammeringWaitTime)
	{
		if (nErrorCode)
		{
			//Control connection has been closed
			Close();
			SendStatus(_T("disconnected."), 0);
			m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_DELSOCKET, m_userid);
		}
		return;
	}

	int len = BUFFERSIZE;
	int nLimit = GetSpeedLimit(upload);
	if (!nLimit)
	{
		ParseCommand();
		return;
	}
	if (len > nLimit && nLimit != -1)
		len = nLimit;

	unsigned char *buffer = new unsigned char[BUFFERSIZE];
	int numread = Receive(buffer, len);
	if (numread != SOCKET_ERROR && numread)
	{
		if (nLimit != -1)
			m_SlQuotas[upload].nTransferred += numread;

		m_pOwner->IncRecvCount(numread);
		//Parse all received bytes
		for (int i = 0; i<numread; i++)
		{
			if (!m_nRecvBufferPos)
			{
				//Remove telnet characters
				if (m_nTelnetSkip)
				{
					if (buffer[i] < 240)
						m_nTelnetSkip = 0;
					else
						continue;
				}
				else if (buffer[i] == 255)
				{
					m_nTelnetSkip = 1;
					continue;
				}
			}

			//Check for line endings
			if ((buffer[i] == '\r')||(buffer[i] == 0)||(buffer[i] == '\n'))
			{
				//If input buffer is not empty...
				if (m_nRecvBufferPos)
				{
					m_RecvBuffer[m_nRecvBufferPos] = 0;
					m_RecvLineBuffer.push_back(m_RecvBuffer);
					m_nRecvBufferPos = 0;

					//Signal that there is a new command waiting to be processed.
					GetSystemTime(&m_LastCmdTime);
				}
			}
			else
				//The command may only be 2000 chars long. This ensures that a malicious user can't
				//send extremely large commands to fill the memory of the server
				if (m_nRecvBufferPos < 2000)
					m_RecvBuffer[m_nRecvBufferPos++] = buffer[i];
		}
	}
	else
	{
		if (!numread || GetLastError() != WSAEWOULDBLOCK)
		{
			//Control connection has been closed
			Close();
			SendStatus(_T("disconnected."), 0);
			m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_DELSOCKET, m_userid);

			delete [] buffer;
			return;
		}
	}

	ParseCommand();

	delete [] buffer;
}

BOOL CControlSocket::GetCommand(CStdString &command, CStdString &args)
{
	//Get first command from input buffer
	CStdStringA str;
	if (m_RecvLineBuffer.empty())
		return FALSE;
	str = m_RecvLineBuffer.front();
	m_RecvLineBuffer.pop_front();

	//Output command in status window
	CStdString str2;
	if (m_useUTF8)
	{
#ifdef _UNICODE
	str2 = ConvFromNetwork(str);
#else
	str2 = ConvToLocal(ConvFromNetwork(str));
#endif
	}
	else
	{
#ifdef _UNICODE
	str2 = ConvFromLocal(str);
#else
	str2 = str;
#endif
	}
	
	//Hide passwords if the server admin wants to.
	if (!str2.Left(5).CompareNoCase(_T("PASS ")))
	{	if (m_pOwner->m_pOptions->GetOptionVal(OPTION_LOGSHOWPASS))
			SendStatus(str2, 2);
		else
		{
			CStdString msg = str2;
			for (int i = 5; i < msg.GetLength(); i++)
				msg[i] = '*';
			SendStatus(msg, 2);
		}
	}
	else
		SendStatus(str2, 2);

	//Split command and arguments
	int pos = str2.Find(_T(" "));
	if (pos != -1)
	{
		command = str2.Left(pos);
		if (pos == str2.GetLength() - 1)
			args = _T("");
		else
		{
			args = str2.Mid(pos + 1);
			if (args == _T(""))
			{
				Send(_T("501 Syntax error, failed to decode string"));
				return FALSE;
			}
		}
	}
	else
	{
		args = _T("");
		command = str2;
	}
	if (command == _T(""))
		return FALSE;
	command.MakeUpper();
	return TRUE;
}

void CControlSocket::SendStatus(LPCTSTR status, int type)
{
	t_statusmsg *msg = new t_statusmsg;
	_tcscpy(msg->ip, m_RemoteIP);
	GetLocalTime(&msg->time);
	if (!m_status.loggedon)
	{
		msg->user = new TCHAR[16];
		_tcscpy(msg->user, _T("(not logged in)"));
	}
	else
	{
		msg->user = new TCHAR[_tcslen(m_status.user) + 1];
		_tcscpy(msg->user, m_status.user);
	}
	msg->userid = m_userid;
	msg->type = type;
	msg->status = new TCHAR[_tcslen(status) + 1];
	_tcscpy(msg->status, status);
	m_pOwner->SendNotification(FSM_STATUSMESSAGE, (LPARAM)msg);
}

BOOL CControlSocket::Send(LPCTSTR str, bool sendStatus /*=true*/)
{
	if (sendStatus)
		SendStatus(str, 3);

	char* buffer;
	int len;
	if (m_useUTF8)
	{
		char* utf8 = ConvToNetwork(str);
		if (!utf8)
		{
			Close();
			SendStatus(_T("Failed to convert reply to UTF-8"), 1);
			m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_DELSOCKET, m_userid);

			return false;
		}

		buffer = new char[strlen(utf8) + 3];
		strcpy(buffer, utf8);
		strcat(buffer, "\r\n");
		len = strlen(buffer);
		delete [] utf8;
	}
	else
	{
		CStdStringA local = ConvToLocal(str);
		if (local == "")
		{
			Close();
			SendStatus(_T("Failed to convert reply to local charset"), 1);
			m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_DELSOCKET, m_userid);

			return false;
		}

		buffer = new char[strlen(local) + 3];
		strcpy(buffer, local);
		strcat(buffer, "\r\n");
		len = strlen(buffer);
	}


	//Add line to back of send buffer if it's not empty
	if (m_pSendBuffer)
	{
		char *tmp = m_pSendBuffer;
		m_pSendBuffer = new char[m_nSendBufferLen + len];
		memcpy(m_pSendBuffer, tmp, m_nSendBufferLen);
		memcpy(m_pSendBuffer+m_nSendBufferLen, buffer, len);
		delete [] tmp;
		m_nSendBufferLen += len;
		delete [] buffer;
		return TRUE;
	}

	int nLimit = GetSpeedLimit(download);
	if (!nLimit)
	{
		if (!m_pSendBuffer)
		{
			m_pSendBuffer = buffer;
			m_nSendBufferLen = len;
		}
		else
		{
			char *tmp = m_pSendBuffer;
			m_pSendBuffer = new char[m_nSendBufferLen + len];
			memcpy(m_pSendBuffer, tmp, m_nSendBufferLen);
			memcpy(m_pSendBuffer+m_nSendBufferLen, buffer, len);
			delete [] tmp;
			m_nSendBufferLen += len;
			delete [] buffer;
		}
		return TRUE;
	}
	int numsend = nLimit;
	if (numsend == -1 || len < numsend)
		numsend = len;

	int res = CAsyncSocketEx::Send(buffer, numsend);
	if (res==SOCKET_ERROR && GetLastError() == WSAEWOULDBLOCK)
	{
		res = 0;
	}
	else if (!res || res==SOCKET_ERROR)
	{
		delete [] buffer;
		Close();
		SendStatus(_T("could not send reply, disconnected."), 0);
		m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_DELSOCKET, m_userid);
		return FALSE;
	}

	if (nLimit != -1)
		m_SlQuotas[download].nTransferred += res;

	if (res != len)
	{
		if (!m_pSendBuffer)
		{
			m_pSendBuffer = new char[len-res];
			memcpy(m_pSendBuffer, buffer+res, len-res);
			m_nSendBufferLen = len-res;
		}
		else
		{
			char *tmp = m_pSendBuffer;
			m_pSendBuffer = new char[m_nSendBufferLen + len - res];
			memcpy(m_pSendBuffer, tmp, m_nSendBufferLen);
			memcpy(m_pSendBuffer+m_nSendBufferLen, buffer+res, len-res);
			delete [] tmp;
			m_nSendBufferLen += len-res;
		}
		TriggerEvent(FD_WRITE);
	}
	delete [] buffer;

	m_pOwner->IncSendCount(res);
	return TRUE;
}

void CControlSocket::OnClose(int nErrorCode)
{
	Close();
	SendStatus(_T("disconnected."), 0);
	m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_DELSOCKET, m_userid);
	CAsyncSocketEx::OnClose(nErrorCode);
}

#define COMMAND_USER	0
#define COMMAND_PASS	1
#define COMMAND_QUIT	2
#define COMMAND_CWD		3
#define COMMAND_PWD		4
#define COMMAND_PORT	5
#define COMMAND_PASV	6
#define COMMAND_TYPE	7
#define COMMAND_LIST	8
#define COMMAND_REST	9
#define COMMAND_CDUP	10
#define COMMAND_RETR	11
#define COMMAND_STOR	12
#define COMMAND_SIZE	13
#define COMMAND_DELE	14
#define COMMAND_RMD		15
#define COMMAND_MKD		16
#define COMMAND_RNFR	17
#define COMMAND_RNTO	18
#define COMMAND_ABOR	19
#define COMMAND_SYST	20
#define COMMAND_NOOP	21
#define COMMAND_APPE	22
#define COMMAND_NLST	23
#define COMMAND_MDTM	24
#define COMMAND_XPWD	25
#define COMMAND_XCUP	26
#define COMMAND_XMKD	27
#define COMMAND_XRMD	28
#define COMMAND_NOP		29
#define COMMAND_EPSV	30
#define COMMAND_EPRT	31
#define COMMAND_AUTH	32
#define COMMAND_ADAT	33
#define COMMAND_PBSZ	34
#define COMMAND_PROT	35
#define COMMAND_FEAT	36
#define COMMAND_MODE	37
#define COMMAND_OPTS	38
#define COMMAND_HELP	39
#define COMMAND_ALLO	40
#define COMMAND_MLST	41
#define COMMAND_MLSD	42
#define COMMAND_SITE	43
#define COMMAND_PASVSMC	44 // some bugged SMC routers convert incoming PASV into P@SW
#define COMMAND_STRU	45
#define COMMAND_CLNT	46
#define COMMAND_MFMT	47
#define COMMAND_HASH	48

typedef struct
{
	int nID;
	TCHAR command[5];
	BOOL bHasargs;
	BOOL bValidBeforeLogon;
} t_command;

static const t_command commands[]={	COMMAND_USER, _T("USER"), TRUE,	 TRUE,
									COMMAND_PASS, _T("PASS"), FALSE, TRUE,
									COMMAND_QUIT, _T("QUIT"), FALSE, TRUE,
									COMMAND_CWD,  _T("CWD"),  FALSE, FALSE,
									COMMAND_PWD,  _T("PWD"),  FALSE, FALSE,
									COMMAND_PORT, _T("PORT"), TRUE,  FALSE,
									COMMAND_PASV, _T("PASV"), FALSE, FALSE,
									COMMAND_TYPE, _T("TYPE"), TRUE,  FALSE,
									COMMAND_LIST, _T("LIST"), FALSE, FALSE,
									COMMAND_REST, _T("REST"), TRUE,  FALSE,
									COMMAND_CDUP, _T("CDUP"), FALSE, FALSE,
									COMMAND_RETR, _T("RETR"), TRUE,  FALSE,
									COMMAND_STOR, _T("STOR"), TRUE,  FALSE,
									COMMAND_SIZE, _T("SIZE"), TRUE,  FALSE,
									COMMAND_DELE, _T("DELE"), TRUE,  FALSE,
									COMMAND_RMD,  _T("RMD"),  TRUE,  FALSE,
									COMMAND_MKD,  _T("MKD"),  TRUE,  FALSE,
									COMMAND_RNFR, _T("RNFR"), TRUE,  FALSE,
									COMMAND_RNTO, _T("RNTO"), TRUE,  FALSE,
									COMMAND_ABOR, _T("ABOR"), FALSE, FALSE,
									COMMAND_SYST, _T("SYST"), FALSE, TRUE,
									COMMAND_NOOP, _T("NOOP"), FALSE, FALSE,
									COMMAND_APPE, _T("APPE"), TRUE,  FALSE,
									COMMAND_NLST, _T("NLST"), FALSE, FALSE,
									COMMAND_MDTM, _T("MDTM"), TRUE,  FALSE,
									COMMAND_XPWD, _T("XPWD"), FALSE, FALSE,
									COMMAND_XCUP, _T("XCUP"), FALSE, FALSE,
									COMMAND_XMKD, _T("XMKD"), TRUE,  FALSE,
									COMMAND_XRMD, _T("XRMD"), TRUE,  FALSE,
									COMMAND_NOP,  _T("NOP"),  FALSE, FALSE,
									COMMAND_EPSV, _T("EPSV"), FALSE, FALSE,
									COMMAND_EPRT, _T("EPRT"), TRUE,  FALSE,
									COMMAND_AUTH, _T("AUTH"), TRUE,  TRUE,
									COMMAND_ADAT, _T("ADAT"), TRUE,  TRUE,
									COMMAND_PBSZ, _T("PBSZ"), TRUE,  TRUE,
									COMMAND_PROT, _T("PROT"), TRUE,  TRUE,
									COMMAND_FEAT, _T("FEAT"), FALSE, TRUE,
									COMMAND_MODE, _T("MODE"), TRUE,  FALSE,
									COMMAND_OPTS, _T("OPTS"), TRUE,  FALSE,
									COMMAND_HELP, _T("HELP"), FALSE, TRUE,
									COMMAND_ALLO, _T("ALLO"), FALSE, FALSE,
									COMMAND_MLST, _T("MLST"), FALSE, FALSE,
									COMMAND_MLSD, _T("MLSD"), FALSE, FALSE,
									COMMAND_SITE, _T("SITE"), TRUE,  TRUE,
									COMMAND_PASVSMC, _T("P@SW"), FALSE, FALSE,
									COMMAND_STRU, _T("STRU"), TRUE, FALSE,
									COMMAND_CLNT, _T("CLNT"), TRUE, TRUE,
									COMMAND_MFMT, _T("MFMT"), TRUE, FALSE,
									COMMAND_HASH, _T("HASH"), TRUE, FALSE
						};

void CControlSocket::ParseCommand()
{
	if (m_antiHammeringWaitTime)
		return;

	//Get command
	CStdString command;
	CStdString args;
	if (!GetCommand(command, args))
		return;

	//Check if command is valid
	int nCommandID = -1;
	for (int i = 0; i < (sizeof(commands)/sizeof(t_command)); i++)
	{
		if (command == commands[i].command)
		{
			//Does the command needs an argument?
			if (commands[i].bHasargs && (args == _T("")))
			{
				Send(_T("501 Syntax error"));
				if (!m_RecvLineBuffer.empty())
					m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_COMMAND, m_userid);
				return;
			}
			//Can it be issued before logon?
			else if (!m_status.loggedon && !commands[i].bValidBeforeLogon)
			{
				Send(_T("530 Please log in with USER and PASS first."));
				if (!m_RecvLineBuffer.empty())
					m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_COMMAND, m_userid);
				return;
			}
			nCommandID = commands[i].nID;
			break;
		}
	}
	//Command not recognized
	if (nCommandID == -1)
	{
		Send(_T("500 Syntax error, command unrecognized."));
		if (!m_RecvLineBuffer.empty())
			m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_COMMAND, m_userid);
		return;
	}

	//Now process the commands
	switch (nCommandID)
	{
	case COMMAND_USER:
		{
			AntiHammerIncrease();

			if (m_status.loggedon)
			{
				GetSystemTime(&m_LoginTime);
				DecUserCount(m_status.user);
				m_pOwner->DecIpCount(m_status.ip);
				t_connop *op = new t_connop;
				op->op = USERCONTROL_CONNOP_CHANGEUSER;
				t_connectiondata_changeuser *conndata = new t_connectiondata_changeuser;
				op->data = conndata;
				op->userid = m_userid;
				m_pOwner->SendNotification(FSM_CONNECTIONDATA, (LPARAM)op);

				m_status.loggedon = FALSE;
				m_CurrentServerDir = _T("");
			}
			if (m_pOwner->m_pOptions->GetOptionVal(OPTION_ENABLESSL) && m_pOwner->m_pOptions->GetOptionVal(OPTION_ALLOWEXPLICITSSL) &&
				m_pOwner->m_pOptions->GetOptionVal(OPTION_SSLFORCEEXPLICIT) && !m_pSslLayer)
			{
				Send(_T("530 Have to use explicit SSL/TLS before logging on."));
				break;
			}
			RenName = _T("");
			args.MakeLower();
			m_status.user = args;
			if (m_pGssLayer && m_pGssLayer->AuthSuccessful())
			{
				char sendme[4096];

#ifdef _UNICODE
				int res = m_pGssLayer->ProcessCommand("USER", ConvToLocal(args), sendme);
#else
				int res = m_pGssLayer->ProcessCommand("USER", args, sendme);
#endif
				if (res != -1)
				{
					if (DoUserLogin(0, true))
					{
#ifdef _UNICODE
						Send(ConvFromLocal(sendme));
#else
						Send(sendme);
#endif
					}
					else
						m_status.user = _T("");
				}
				break;
			}
			if (!m_pSslLayer)
			{
				CUser user;
				if (m_pOwner->m_pPermissions->CheckUserLogin(m_status.user, _T(""), user, true) && user.ForceSsl())
				{
					m_status.user = _T("");
					Send(_T("530 SSL required"));
					break;
				}
			}
			Send(_T("331 Password required for ") + args);
		}
		break;
	case COMMAND_PASS:
		AntiHammerIncrease();

		if (m_status.loggedon)
			Send(_T("503 Bad sequence of commands."));
		else if (m_pGssLayer && m_pGssLayer->AuthSuccessful())
		{
			char sendme[4096];
#ifdef _UNICODE
			int res = m_pGssLayer->ProcessCommand("PASS", ConvToLocal(m_status.user), ConvToLocal(args), sendme);
#else
			int res = m_pGssLayer->ProcessCommand("PASS", m_status.user, args, sendme);
#endif

			if (res != -1)
			{
				if (DoUserLogin(_T(""), true))
#ifdef _UNICODE
                    Send(ConvFromLocal(sendme));
#else
                    Send(sendme);
#endif
			}
		}
		else if (DoUserLogin(args))
			Send(_T("230 Logged on"));
		break;
	case COMMAND_QUIT:
		m_bQuitCommand = TRUE;
		if (!m_transferstatus.socket || !m_transferstatus.socket->InitCalled())
		{
			Send(_T("221 Goodbye"));
			if (m_pSslLayer)
			{
				if (ShutDown() || WSAGetLastError() != WSAEWOULDBLOCK)
					ForceClose(5);
			}
			else if (CanQuit())
				ForceClose(5);
		}
		break;
	case COMMAND_CWD:
		{
			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send(_T("501 Syntax error"));
				break;
			}

			if (args == _T(""))
			{
				CStdString str;
				str.Format(_T("250 Broken client detected, missing argument to CWD. \"%s\" is current directory."), m_CurrentServerDir);
				Send(str);
				break;
			}

			int res = m_pOwner->m_pPermissions->ChangeCurrentDir(m_status.user, m_CurrentServerDir, args);
			if (!res)
			{
				CStdString str;
				str.Format(_T("250 CWD successful. \"%s\" is current directory."), m_CurrentServerDir);
				Send(str);
			}
			else if (res & PERMISSION_DENIED)
			{
				CStdString str;
				str.Format(_T("550 CWD failed. \"%s\": Permission denied."), args);
				Send(str);
			}
			else if (res & PERMISSION_INVALIDNAME)
			{
				CStdString str;
				str.Format(_T("550 CWD failed. \"%s\": Filename invalid."), args);
				Send(str);
			}
			else if (res)
			{
				CStdString str;
				str.Format(_T("550 CWD failed. \"%s\": directory not found."), args);
				Send(str);
			}
		}
		break;
	case COMMAND_PWD:
	case COMMAND_XPWD:
		{
			CStdString str;
			str.Format(_T("257 \"%s\" is current directory."), m_CurrentServerDir);
			Send(str);
		}
		break;
	case COMMAND_PORT:
		{
			if (GetFamily() != AF_INET)
			{
				Send(_T("500 You are connected using IPv6. PORT is only for IPv4. You have to use the EPRT command instead."));
				break;
			}

			if (m_transferstatus.socket)
			{
				SendTransferinfoNotification();
				delete m_transferstatus.socket;
				m_transferstatus.socket = 0;
			}
			int count = 0;
			int pos = 0;
			//Convert commas to dots
			args.Replace(_T(","), _T("."));
			while (1)
			{
				pos = args.Find(_T("."), pos);
				if (pos != -1)
					count++;
				else
					break;
				pos++;
			}
			if (count != 5)
			{
				Send(_T("501 Syntax error"));
				m_transferstatus.pasv = -1;
				break;
			}
			CStdString ip;
			int port = 0;
			int i = args.ReverseFind('.');
			port = _ttoi(args.Right(args.GetLength() - (i + 1))); //get ls byte of server socket
			args = args.Left(i);
			i = args.ReverseFind('.');
			port += 256 * _ttoi(args.Right(args.GetLength() - (i + 1))); // add ms byte to server socket
			ip = args.Left(i);

#ifdef _UNICODE
			int res = inet_addr(ConvToLocal(ip));
#else
			int res = inet_addr(ip);
#endif
			if (res == INADDR_NONE)
			{
				// Fix: Convert IP in PORT command to int and back to string (strips
				// leading zeros) because some FTP clients prepend zeros to it.
				// inet_addr() thinks this is an octal number and will return INADDR_NONE
				// if 8 or 9 are encountered.
				CStdString decIP;
				ip += _T(".");
				int pos = ip.Find('.');
				while (pos != -1)
				{
					CStdString tmp;
					tmp.Format(_T("%d."), _ttoi(ip.Left(pos)));
					decIP += tmp;

					ip = ip.Mid(pos + 1);
					pos = ip.Find('.');
				}

				ip = decIP.Left(decIP.GetLength() - 1);
#ifdef _UNICODE
				res = inet_addr(ConvToLocal(ip));
#else
				res = inet_addr(ip);
#endif
			}

			if (res == INADDR_NONE || port < 1 || port > 65535)
 			{
				Send(_T("501 Syntax error"));
				m_transferstatus.pasv = -1;
				break;
			}

			if (m_pOwner->m_pOptions->GetOptionVal(OPTION_ACTIVE_IGNORELOCAL))
			{
				CStdString peerAddr;
				UINT peerPort = 0;
				if (GetPeerName(peerAddr, peerPort))
				{
					if (!IsRoutableAddress(ip) && IsRoutableAddress(peerAddr))
						ip = peerAddr;
				}
			}

			m_transferstatus.ip = ip;
			m_transferstatus.port = port;
			m_transferstatus.pasv = 0;
			m_transferstatus.family = AF_INET;
			Send(_T("200 Port command successful"));
			break;
		}
	case COMMAND_PASV:
	case COMMAND_PASVSMC:
		{
			if (GetFamily() != AF_INET)
			{
				Send(_T("500 You are connected using IPv6. PASV is only for IPv4. You have to use the EPSV command instead."));
				break;
			}

			if (m_transferstatus.socket)
			{
				SendTransferinfoNotification();
				delete m_transferstatus.socket;
			}
			m_transferstatus.family = AF_INET;
			m_transferstatus.socket = new CTransferSocket(this);

			unsigned int retries = 3;
			unsigned int port = 0;

			CStdString pasvIP = GetPassiveIP();
			if (pasvIP == _T(""))
			{
				delete m_transferstatus.socket;
				m_transferstatus.socket = NULL;
				Send(_T("421 Can't create socket"));
				m_transferstatus.pasv = -1;
				break;
			}

			while (retries > 0)
			{
				if (m_pOwner->m_pOptions->GetOptionVal(OPTION_USECUSTOMPASVPORT))
				{
					static UINT customPort = 0;
					unsigned int minPort = (unsigned int)m_pOwner->m_pOptions->GetOptionVal(OPTION_CUSTOMPASVMINPORT);
					unsigned int maxPort = (unsigned int)m_pOwner->m_pOptions->GetOptionVal(OPTION_CUSTOMPASVMAXPORT);
					if (minPort > maxPort) {
						unsigned int temp = minPort;
						minPort = maxPort;
						maxPort = temp;
					}
					if (customPort < minPort || customPort > maxPort) {
						customPort = minPort;
					}
					port = customPort;

					++customPort;
				} else {
					port = 0;
				}
				if (m_transferstatus.socket->Create(port, SOCK_STREAM, FD_ACCEPT))
					break;
				--retries;
			}
			if (retries <= 0) {
				delete m_transferstatus.socket;
				m_transferstatus.socket = NULL;
				Send(_T("421 Can't create socket"));
				m_transferstatus.pasv = -1;
				break;
			}

			if (m_pGssLayer && m_pGssLayer->AuthSuccessful())
				m_transferstatus.socket->UseGSS(m_pGssLayer);

			if (m_pSslLayer && m_bProtP)
				m_transferstatus.socket->UseSSL(m_pSslLayer->GetContext());

			if (!m_transferstatus.socket->Listen())
			{
				delete m_transferstatus.socket;
				m_transferstatus.socket = NULL;
				Send(_T("421 Can't create socket"));
				m_transferstatus.pasv = -1;
				break;
			}

			//Now retrieve the port
			CStdString dummy;
			if (m_transferstatus.socket->GetSockName(dummy, port))
			{
				//Reformat the ip
				pasvIP.Replace(_T("."), _T(","));
				//Put the answer together
				CStdString str;
				if (nCommandID == COMMAND_PASVSMC)
					str.Format(_T("227 Warning: Router with P@SW bug detected. Entering Passive Mode (%s,%d,%d)"), pasvIP, port / 256, port % 256);
				else
					str.Format(_T("227 Entering Passive Mode (%s,%d,%d)"), pasvIP, port / 256, port % 256);
				Send(str);
				m_transferstatus.pasv = 1;
			}
			else
			{
				delete m_transferstatus.socket;
				m_transferstatus.socket = NULL;
				Send(_T("421 Can't create socket"));
				m_transferstatus.pasv = -1;
				break;
			}
			
			break;
		}
	case COMMAND_TYPE:
		{
			args.MakeUpper();
			if (args[0] != 'I' && args[0] != 'A' && args != _T("L 8"))
			{
				Send(_T("501 Unsupported type. Supported types are I, A and L 8"));
				break;
			}
			m_transferstatus.type = (args[0] == 'A') ? 1 : 0;
			CStdString str;
			str.Format(_T("200 Type set to %s"), args);
			Send(str);
		}
		break;
	case COMMAND_LIST:
		if (m_transferstatus.pasv == -1)
		{
			Send(_T("503 Bad sequence of commands."));
			break;
		}
		if (!m_transferstatus.pasv && (m_transferstatus.ip == _T("") || m_transferstatus.port == -1))
		{
			Send(_T("503 Bad sequence of commands."));
			break;
		}
		if (m_pSslLayer && m_pOwner->m_pOptions->GetOptionVal(OPTION_FORCEPROTP) && !m_bProtP)
		{
			Send(_T("521 PROT P required"));
			break;
		}
		else
		{
			//Check args, currently only supported argument is the directory which will be listed.
			CStdString dirToList;
			args.TrimLeft(_T(" "));
			args.TrimRight(_T(" "));
			if (args != _T(""))
			{
				BOOL bBreak = FALSE;
				while (args[0] == '-') //No parameters supported
				{
					if (args.GetLength() < 2)
					{ //Dash without param
						Send(_T("501 Syntax error"));
						bBreak = TRUE;
						break;
					}

					int pos = args.Find(' ');
					CStdString params;
					if (pos != -1)
					{
						params = args.Left(1);
						params = params.Left(pos - 1);
						args = args.Mid(pos + 1);
						args.TrimLeft(_T(" "));
					}
					else
						args = _T("");
					while (params != _T(""))
					{
						//Some parameters are not support
						if (params[0] == 'R')
						{
							Send(_T("504 Command not implemented for that parameter"));
							bBreak = TRUE;
							break;
						}
						//Ignore other parameters
						params = params.Mid(1);
					}

					if (args == _T(""))
						break;
				}
				if (bBreak)
					break;
				if (args != _T(""))
				{
					//Unquote args
					if (!UnquoteArgs(args))
					{
						Send(_T("501 Syntax error"));
						break;
					}

					dirToList = args;
				}
			}

			t_dirlisting *pResult;
			CStdString physicalDir, logicalDir;
			int error = m_pOwner->m_pPermissions->GetDirectoryListing(m_status.user, m_CurrentServerDir, dirToList, pResult, physicalDir, logicalDir, CPermissions::AddLongListingEntry, m_useUTF8);
			if (error & PERMISSION_DENIED)
			{
				Send(_T("550 Permission denied."));
				ResetTransferstatus();
				break;
			}
			else if (error & PERMISSION_INVALIDNAME)
			{
				Send(_T("550 Filename invalid."));
				ResetTransferstatus();
				break;
			}
			else if (error)
			{
				Send(_T("550 Directory not found."));
				ResetTransferstatus();
				break;
			}

			if (!m_transferstatus.pasv)
			{
				if (m_transferstatus.socket)
				{
					SendTransferinfoNotification();
					delete m_transferstatus.socket;
				}
				CTransferSocket *transfersocket = new CTransferSocket(this);
				m_transferstatus.socket = transfersocket;
				transfersocket->Init(pResult, TRANSFERMODE_LIST);
				if (m_transferMode == mode_zlib)
				{
					if (!transfersocket->InitZLib(m_zlibLevel))
					{
						Send(_T("550 could not initialize zlib, please use MODE S instead"));
						ResetTransferstatus();
						break;
					}
				}

				if (!CreateTransferSocket(transfersocket))
					break;

				SendTransferinfoNotification(TRANSFERMODE_LIST, ConvToLocal(physicalDir), ConvToLocal(logicalDir));
				Send(_T("150 Opening data channel for directory list."));
			}
			else
			{
				if (!m_transferstatus.socket)
				{
					CPermissions::DestroyDirlisting(pResult);
					Send(_T("503 Bad sequence of commands."));
					break;
				}
				m_transferstatus.socket->Init(pResult, TRANSFERMODE_LIST);
				if (m_transferMode == mode_zlib)
				{
					if (!m_transferstatus.socket->InitZLib(m_zlibLevel))
					{
						Send(_T("550 could not initialize zlib, please use MODE S instead"));
						ResetTransferstatus();
						break;
					}
				}

				SendTransferinfoNotification(TRANSFERMODE_LIST, ConvToLocal(physicalDir), ConvToLocal(logicalDir));
				m_transferstatus.socket->PasvTransfer();
			}
		}
		break;
	case COMMAND_REST:
		{
			BOOL error = FALSE;
			for (int i = 0; i < args.GetLength(); i++)
				if (args[i] < '0' || args[i] > '9')
				{
					error = TRUE;
					break;
				}
			if (error)
			{
				Send(_T("501 Bad parameter. Numeric value required"));
				break;
			}
			m_transferstatus.rest = _ttoi64(args);
			CStdString str;
			str.Format(_T("350 Rest supported. Restarting at %I64d"), m_transferstatus.rest);
			Send(str);
		}
		break;
	case COMMAND_CDUP:
	case COMMAND_XCUP:
		{
			CStdString dir = _T("..");
			int res = m_pOwner->m_pPermissions->ChangeCurrentDir(m_status.user, m_CurrentServerDir, dir);
			if (!res)
			{
				CStdString str;
				str.Format(_T("200 CDUP successful. \"%s\" is current directory."), m_CurrentServerDir);
				Send(str);
			}
			else if (res & PERMISSION_DENIED)
				Send(_T("550 CDUP failed, permission denied."));
			else if (res & PERMISSION_INVALIDNAME)
				Send(_T("550 CDUP failed, filename invalid."));
			else if (res)
				Send(_T("550 CDUP failed, directory not found."));
		}
		break;
	case COMMAND_RETR:
		{
			if (m_transferstatus.pasv == -1)
			{
				Send(_T("503 Bad sequence of commands."));
				break;
			}
			if (!m_transferstatus.pasv && (m_transferstatus.ip == _T("") || m_transferstatus.port == -1))
			{
				Send(_T("503 Bad sequence of commands."));
				break;
			}
			if (m_pSslLayer && m_pOwner->m_pOptions->GetOptionVal(OPTION_FORCEPROTP) && !m_bProtP)
			{
				Send(_T("521 PROT P required"));
				break;
			}
			//Much more checks

			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send( _T("501 Syntax error") );
				break;
			}


			CStdString physicalFile, logicalFile;
			int error = m_pOwner->m_pPermissions->CheckFilePermissions(m_status.user, args, m_CurrentServerDir, FOP_READ, physicalFile, logicalFile);
			if (error & PERMISSION_DENIED)
			{
				Send(_T("550 Permission denied"));
				ResetTransferstatus();
			}
			else if (error & PERMISSION_INVALIDNAME)
			{
				Send(_T("550 Filename invalid."));
				ResetTransferstatus();
			}
			else if (error)
			{
				Send(_T("550 File not found"));
				ResetTransferstatus();
			}
			else
			{
				if (!m_transferstatus.pasv)
				{
					if (m_transferstatus.socket)
					{
						SendTransferinfoNotification();
						delete m_transferstatus.socket;
					}
					CTransferSocket *transfersocket = new CTransferSocket(this);
					m_transferstatus.socket = transfersocket;
					transfersocket->Init(physicalFile, TRANSFERMODE_SEND, m_transferstatus.rest);
					if (m_transferMode == mode_zlib)
					{
						if (!transfersocket->InitZLib(m_zlibLevel))
						{
							Send(_T("550 could not initialize zlib, please use MODE S instead"));
							ResetTransferstatus();
							break;
						}
					}

					if (!CreateTransferSocket(transfersocket))
						break;

					__int64 totalSize;
					if (!GetLength64(physicalFile, totalSize))
						totalSize = -1;
					SendTransferinfoNotification(TRANSFERMODE_SEND, physicalFile, logicalFile, m_transferstatus.rest, totalSize);

					Send(_T("150 Opening data channel for file transfer."));
				}
				else
				{
					if (!m_transferstatus.socket)
					{
						Send(_T("503 Bad sequence of commands."));
						break;
					}

					m_transferstatus.socket->Init(physicalFile, TRANSFERMODE_SEND, m_transferstatus.rest);
					if (m_transferMode == mode_zlib)
					{
						if (!m_transferstatus.socket->InitZLib(m_zlibLevel))
						{
							Send(_T("550 could not initialize zlib, please use MODE S instead"));
							ResetTransferstatus();
							break;
						}
					}

					__int64 totalSize;
					if (!GetLength64(physicalFile, totalSize))
						totalSize = -1;
					SendTransferinfoNotification(TRANSFERMODE_SEND, physicalFile, logicalFile, m_transferstatus.rest, totalSize);

					m_transferstatus.socket->PasvTransfer();
				}
				GetSystemTime(&m_LastTransferTime);
			}
			break;
		}
	case COMMAND_STOR:
		{
			if (m_transferstatus.pasv == -1)
			{
				Send(_T("503 Bad sequence of commands."));
				break;
			}
			if(!m_transferstatus.pasv && (m_transferstatus.ip == _T("") || m_transferstatus.port == -1))
			{
				Send(_T("503 Bad sequence of commands."));
				break;
			}
			if (m_pSslLayer && m_pOwner->m_pOptions->GetOptionVal(OPTION_FORCEPROTP) && !m_bProtP)
			{
				Send(_T("521 PROT P required"));
				break;
			}
			//Much more checks

			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send( _T("501 Syntax error") );
				break;
			}

			CStdString physicalFile, logicalFile;
			int error = m_pOwner->m_pPermissions->CheckFilePermissions(m_status.user, args, m_CurrentServerDir, m_transferstatus.rest ? FOP_APPEND : FOP_WRITE, physicalFile, logicalFile);
			if (error & PERMISSION_DENIED)
			{
				Send(_T("550 Permission denied"));
				ResetTransferstatus();
			}
			else if (error & PERMISSION_INVALIDNAME)
			{
				Send(_T("550 Filename invalid."));
				ResetTransferstatus();
			}
			else if (error)
			{
				Send(_T("550 Filename invalid"));
				ResetTransferstatus();
			}
			else
			{
				if (!m_transferstatus.pasv)
				{
					CTransferSocket *transfersocket = new CTransferSocket(this);
					transfersocket->Init(physicalFile, TRANSFERMODE_RECEIVE, m_transferstatus.rest);
					m_transferstatus.socket = transfersocket;
					if (m_transferMode == mode_zlib)
					{
						if (!transfersocket->InitZLib(m_zlibLevel))
						{
							Send(_T("550 could not initialize zlib, please use MODE S instead"));
							ResetTransferstatus();
							break;
						}
					}

					if (!CreateTransferSocket(transfersocket))
						break;

					SendTransferinfoNotification(TRANSFERMODE_RECEIVE, physicalFile, logicalFile, m_transferstatus.rest);
					Send(_T("150 Opening data channel for file transfer."));
				}
				else
				{
					if (!m_transferstatus.socket)
					{
						Send(_T("503 Bad sequence of commands."));
						break;
					}

					m_transferstatus.socket->Init(physicalFile, TRANSFERMODE_RECEIVE, m_transferstatus.rest);
                    if (m_transferMode == mode_zlib)
					{
						if (!m_transferstatus.socket->InitZLib(m_zlibLevel))
						{
							Send(_T("550 could not initialize zlib, please use MODE S instead"));
							ResetTransferstatus();
							break;
						}
					}
					SendTransferinfoNotification(TRANSFERMODE_RECEIVE, physicalFile, logicalFile, m_transferstatus.rest);
					m_transferstatus.socket->PasvTransfer();
				}
				GetSystemTime(&m_LastTransferTime);
			}
		}
		break;
	case COMMAND_SIZE:
		{
			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send( _T("501 Syntax error") );
				break;
			}

			CStdString physicalFile, logicalFile;
			int error = m_pOwner->m_pPermissions->CheckFilePermissions(m_status.user, args, m_CurrentServerDir, FOP_LIST, physicalFile, logicalFile);
			if (error & PERMISSION_DENIED)
				Send(_T("550 Permission denied"));
			else if (error & PERMISSION_INVALIDNAME)
				Send(_T("550 Filename invalid."));
			else if (error)
				Send(_T("550 File not found"));
			else
			{
				CStdString str;
				_int64 length;
				if (GetLength64(physicalFile, length))
					str.Format(_T("213 %I64d"), length);
				else
					str = _T("550 File not found");
				Send(str);
			}
		}
		break;
	case COMMAND_DELE:
		{
			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send(_T("501 Syntax error"));
				break;
			}

			CStdString physicalFile, logicalFile;
			int error = m_pOwner->m_pPermissions->CheckFilePermissions(m_status.user, args, m_CurrentServerDir, FOP_DELETE, physicalFile, logicalFile);
			if (error & PERMISSION_DENIED)
				Send(_T("550 Permission denied"));
			else if (error & PERMISSION_INVALIDNAME)
				Send(_T("550 Filename invalid."));
			else if (error)
				Send(_T("550 File not found"));
			else
			{
				bool success = DeleteFile(physicalFile) == TRUE;
				if (!success && GetLastError() == ERROR_ACCESS_DENIED)
				{
					DWORD attr = GetFileAttributes(physicalFile);
					if (attr != INVALID_FILE_ATTRIBUTES && attr & FILE_ATTRIBUTE_READONLY)
					{
						attr &= ~FILE_ATTRIBUTE_READONLY;
						SetFileAttributes(physicalFile, attr);

						success = DeleteFile(physicalFile) == TRUE;
					}
				}
				if (!success)
					Send(_T("500 Failed to delete the file."));
				else
					Send(_T("250 File deleted successfully"));
			}
		}
		break;
	case COMMAND_RMD:
	case COMMAND_XRMD:
		{
			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send( _T("501 Syntax error") );
				break;
			}

			CStdString physicalFile, logicalFile;
			int error = m_pOwner->m_pPermissions->CheckDirectoryPermissions(m_status.user, args, m_CurrentServerDir, DOP_DELETE, physicalFile, logicalFile);
			if (error & PERMISSION_DENIED)
				Send(_T("550 Permission denied"));
			else if (error & PERMISSION_INVALIDNAME)
				Send(_T("550 Filename invalid."));
			else if (error)
				Send(_T("550 Directory not found"));
			else
			{
				if (!RemoveDirectory(physicalFile))
				{
					if (GetLastError() == ERROR_DIR_NOT_EMPTY)
						Send(_T("550 Directory not empty."));
					else
						Send(_T("450 Internal error deleting the directory."));
				}
				else
					Send(_T("250 Directory deleted successfully"));
			}
		}
		break;
	case COMMAND_MKD:
	case COMMAND_XMKD:
		{
			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send( _T("501 Syntax error") );
				break;
			}

			CStdString physicalFile, logicalFile;
			int error = m_pOwner->m_pPermissions->CheckDirectoryPermissions(m_status.user, args, m_CurrentServerDir, DOP_CREATE, physicalFile, logicalFile);
			if (error & PERMISSION_DENIED)
				Send(_T("550 Can't create directory. Permission denied"));
			else if (error & PERMISSION_INVALIDNAME)
				Send(_T("550 Filename invalid."));
			else if (error & PERMISSION_DOESALREADYEXIST && (error & PERMISSION_FILENOTDIR)!=PERMISSION_FILENOTDIR)
				Send(_T("550 Directory already exists"));
			else if (error & PERMISSION_FILENOTDIR)
				Send(_T("550 File with same name already exists"));
			else if (error)
				Send(_T("550 Directoryname not valid"));
			else
			{
				CStdString str;
				BOOL res = FALSE;
				BOOL bReplySent = FALSE;
				physicalFile += _T("\\");
				while (physicalFile != _T(""))
				{
					CStdString piece = physicalFile.Left(physicalFile.Find('\\')+1);
					if (piece.Right(2) == _T(".\\"))
					{
						Send(_T("550 Directoryname not valid"));
						bReplySent = TRUE;
						break;
					}
					str += piece;
					physicalFile = physicalFile.Mid(physicalFile.Find('\\') + 1);
					res = CreateDirectory(str, 0);
				}
				if (!bReplySent)
					if (!res)//CreateDirectory(result+"\\",0))
					{
						int error = GetLastError();
						if (error == ERROR_ALREADY_EXISTS)
							Send(_T("550 Directory already exists"));
						else
							Send(_T("450 Internal error creating the directory."));
					}
					else
						Send(_T("257 \"") + logicalFile + _T("\" created successfully"));
			}
		}
		break;
	case COMMAND_RNFR:
		{
			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send( _T("501 Syntax error") );
				break;
			}

			RenName = _T("");

			CStdString physicalFile, logicalFile;
			int error = m_pOwner->m_pPermissions->CheckFilePermissions(m_status.user, args, m_CurrentServerDir, FOP_DELETE, physicalFile, logicalFile);
			if (!error)
			{
				RenName = physicalFile;
				bRenFile = TRUE;
				Send(_T("350 File exists, ready for destination name."));
				break;
			}
			else if (error & PERMISSION_DENIED)
				Send(_T("550 Permission denied"));
			else if (error & PERMISSION_INVALIDNAME)
				Send(_T("550 Filename invalid."));
			else
			{
				int error2 = m_pOwner->m_pPermissions->CheckDirectoryPermissions(m_status.user, args, m_CurrentServerDir, DOP_DELETE, physicalFile, logicalFile);
				if (!error2)
				{
					RenName = physicalFile;
					bRenFile = FALSE;
					Send(_T("350 Directory exists, ready for destination name."));
				}
				else if (error2 & PERMISSION_DENIED)
					Send(_T("550 Permission denied"));
				else if (error2 & PERMISSION_INVALIDNAME)
					Send(_T("550 Filename invalid."));
				else
					Send(_T("550 file/directory not found"));
				break;
			}
		}
		break;
	case COMMAND_RNTO:
		{
			if (RenName == _T(""))
			{
				Send(_T("503 Bad sequence of commands!"));
				break;
			}

			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send( _T("501 Syntax error") );
				break;
			}

			if (bRenFile)
			{
				CStdString physicalFile, logicalFile;
				int error = m_pOwner->m_pPermissions->CheckFilePermissions(m_status.user, args, m_CurrentServerDir, FOP_CREATENEW, physicalFile, logicalFile);
				if (error)
					RenName = _T("");
				if (error & PERMISSION_DENIED)
					Send(_T("550 Permission denied"));
				else if (error & PERMISSION_INVALIDNAME)
					Send(_T("553 Filename invalid."));
				else if (error & PERMISSION_DOESALREADYEXIST && (error & PERMISSION_DIRNOTFILE)!=PERMISSION_DIRNOTFILE)
					Send(_T("553 file exists"));
				else if (error)
					Send(_T("553 Filename invalid"));
				else
				{
					if (!MoveFile(RenName, physicalFile))
						Send(_T("450 Internal error renaming the file"));
					else
						Send(_T("250 file renamed successfully"));
				}
			}
			else
			{
				CStdString physicalFile, logicalFile;
				int error = m_pOwner->m_pPermissions->CheckDirectoryPermissions(m_status.user, args, m_CurrentServerDir, DOP_CREATE, physicalFile, logicalFile);
				if (error)
					RenName = _T("");
				if (error & PERMISSION_DENIED)
					Send(_T("550 Permission denied"));
				else if (error & PERMISSION_INVALIDNAME)
					Send(_T("550 Filename invalid."));
				else if (error & PERMISSION_DOESALREADYEXIST && (error & PERMISSION_FILENOTDIR)!=PERMISSION_FILENOTDIR)
					Send(_T("550 file exists"));
				else if (error)
					Send(_T("550 Filename invalid"));
				else
				{
					if (!MoveFile(RenName, physicalFile))
						Send(_T("450 Internal error renaming the file"));
					else
						Send(_T("250 file renamed successfully"));
				}
			}
		}
		break;
	case COMMAND_ABOR:
		{
			if (m_transferstatus.socket)
			{
				if (m_transferstatus.socket->Started())
					Send(_T("426 Connection closed; transfer aborted."));
			}
			Send(_T("226 ABOR command successful"));
			ResetTransferstatus();
		break;
		}
	case COMMAND_SYST:
		Send(_T("215 UNIX emulated by FileZilla"));
		break;
	case COMMAND_NOOP:
	case COMMAND_NOP:
		Send(_T("200 OK"));
		break;
	case COMMAND_APPE:
		{
			if (m_transferstatus.pasv == -1)
			{
				Send(_T("503 Bad sequence of commands."));
				break;
			}
			if (!m_transferstatus.pasv && (m_transferstatus.ip == _T("") || m_transferstatus.port == -1))
			{
				Send(_T("503 Bad sequence of commands."));
				break;
			}
			if (m_pSslLayer && m_pOwner->m_pOptions->GetOptionVal(OPTION_FORCEPROTP) && !m_bProtP)
			{
				Send(_T("521 PROT P required"));
				break;
			}
			//Much more checks

			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send( _T("501 Syntax error") );
				break;
			}

			CStdString physicalFile, logicalFile;
			int error = m_pOwner->m_pPermissions->CheckFilePermissions(m_status.user, args, m_CurrentServerDir, FOP_APPEND, physicalFile, logicalFile);
			if (error & PERMISSION_DENIED)
			{
				Send(_T("550 Permission denied"));
				ResetTransferstatus();
			}
			else if (error & PERMISSION_INVALIDNAME)
			{
				Send(_T("550 Filename invalid."));
				ResetTransferstatus();
			}
			else if (error)
			{
				Send(_T("550 Filename invalid"));
				ResetTransferstatus();
			}
			else
			{
				_int64 size = 0;
				if (!GetLength64(physicalFile, size))
					size = 0;

				m_transferstatus.rest = size;

				if (!m_transferstatus.pasv)
				{
					CTransferSocket *transfersocket = new CTransferSocket(this);
					transfersocket->Init(physicalFile, TRANSFERMODE_RECEIVE, m_transferstatus.rest);
					m_transferstatus.socket = transfersocket;
					if (m_transferMode == mode_zlib)
					{
						if (!transfersocket->InitZLib(m_zlibLevel))
						{
							Send(_T("550 could not initialize zlib, please use MODE S instead"));
							ResetTransferstatus();
							break;
						}
					}

					if (!CreateTransferSocket(transfersocket))
						break;

					SendTransferinfoNotification(TRANSFERMODE_RECEIVE, physicalFile, logicalFile, m_transferstatus.rest);

					CStdString str;
					str.Format(_T("150 Opening data channel for file transfer, restarting at offset %I64d"), size);
					Send(str);
				}
				else
				{
					if (!m_transferstatus.socket)
					{
						Send(_T("503 Bad sequence of commands."));
						break;
					}
					m_transferstatus.socket->Init(physicalFile, TRANSFERMODE_RECEIVE, m_transferstatus.rest);
					if (m_transferMode == mode_zlib)
					{
						if (!m_transferstatus.socket->InitZLib(m_zlibLevel))
						{
							Send(_T("550 could not initialize zlib, please use MODE S instead"));
							ResetTransferstatus();
							break;
						}
					}
					SendTransferinfoNotification(TRANSFERMODE_RECEIVE, physicalFile, logicalFile, m_transferstatus.rest);
					m_transferstatus.socket->PasvTransfer();
				}
				GetSystemTime(&m_LastTransferTime);
			}
		}
		break;
	case COMMAND_NLST:
		if (m_transferstatus.pasv == -1)
		{
			Send(_T("503 Bad sequence of commands."));
			break;
		}
		if (!m_transferstatus.pasv && (m_transferstatus.ip == _T("") || m_transferstatus.port == -1))
		{
			Send(_T("503 Bad sequence of commands."));
			break;
		}
		if (m_pSslLayer && m_pOwner->m_pOptions->GetOptionVal(OPTION_FORCEPROTP) && !m_bProtP)
		{
			Send(_T("521 PROT P required"));
			break;
		}
		//Much more checks
		else
		{
			//Check args, currently only supported argument is the directory which will be listed.
			if (args != _T(""))
			{
				BOOL bBreak = FALSE;
				while (args[0] == '-') //No parameters supported
				{
					if (args.GetLength() < 2)
					{ //Dash without param
						Send(_T("501 Syntax error"));
						bBreak = TRUE;
						break;
					}

					int pos = args.Find(' ');
					CStdString params;
					if (pos != -1)
					{
						params = args.Left(1);
						params = params.Left(pos-1);
						args = args.Mid(pos+1);
						args.TrimLeft(_T(" "));
					}
					else
						args = _T("");
					while (params != _T(""))
					{
						//Some parameters are not support
						if (params[0] == 'R')
						{
							Send(_T("504 Command not implemented for that parameter"));
							bBreak = TRUE;
							break;
						}
						//Ignore other parameters
						params = params.Mid(1);
					}

					if (args == _T(""))
						break;
				}
				if (bBreak)
					break;
				if (args != _T(""))
				{
					//Unquote args
					if (!UnquoteArgs(args))
					{
						Send( _T("501 Syntax error") );
						break;
					}
				}
			}

			t_dirlisting *pResult;
			CStdString physicalDir, logicalDir;
			int error = m_pOwner->m_pPermissions->GetDirectoryListing(m_status.user, m_CurrentServerDir, args, pResult, physicalDir, logicalDir, CPermissions::AddShortListingEntry, m_useUTF8);
			if (error & PERMISSION_DENIED)
			{
				Send(_T("550 Permission denied"));
				ResetTransferstatus();
			}
			else if (error & PERMISSION_INVALIDNAME)
			{
				Send(_T("550 Filename invalid."));
				ResetTransferstatus();
			}
			else if (error)
			{
				Send(_T("550 Directory not found"));
				ResetTransferstatus();
			}
			else
			{
				if (!m_transferstatus.pasv)
				{
					CTransferSocket *transfersocket = new CTransferSocket(this);
					m_transferstatus.socket = transfersocket;
					transfersocket->Init(pResult, TRANSFERMODE_NLST);
					if (m_transferMode == mode_zlib)
					{
						if (!transfersocket->InitZLib(m_zlibLevel))
						{
							Send(_T("550 could not initialize zlib, please use MODE S instead"));
							ResetTransferstatus();
							break;
						}
					}

					if (!CreateTransferSocket(transfersocket))
						break;

					SendTransferinfoNotification(TRANSFERMODE_LIST, physicalDir, logicalDir); // Use TRANSFERMODE_LIST instead of TRANSFERMODE_NLST.
					Send(_T("150 Opening data channel for directory list."));
				}
				else
				{
					if (!m_transferstatus.socket)
					{
						CPermissions::DestroyDirlisting(pResult);
						Send(_T("503 Bad sequence of commands."));
						break;
					}
					m_transferstatus.socket->Init(pResult, TRANSFERMODE_NLST );
					if (m_transferMode == mode_zlib)
					{
						if (!m_transferstatus.socket->InitZLib(m_zlibLevel))
						{
							Send(_T("550 could not initialize zlib, please use MODE S instead"));
							ResetTransferstatus();
							break;
						}
					}
					SendTransferinfoNotification(TRANSFERMODE_LIST, physicalDir, logicalDir); // Use TRANSFERMODE_LIST instead of TRANSFERMODE_NLST.
					m_transferstatus.socket->PasvTransfer();
				}
			}
		}
		break;
	case COMMAND_MDTM:
		{
			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send( _T("501 Syntax error") );
				break;
			}

			CStdString physicalFile, logicalFile;
			int error = m_pOwner->m_pPermissions->CheckFilePermissions(m_status.user, args, m_CurrentServerDir, FOP_LIST, physicalFile, logicalFile);
			if (error & PERMISSION_DENIED)
				Send(_T("550 Permission denied"));
			else if (error & PERMISSION_INVALIDNAME)
				Send(_T("550 Filename invalid."));
			else if (error & 2)
				Send(_T("550 File not found"));
			else
			{
				CFileStatus64 status;
				GetStatus64(physicalFile, status);
				CStdString str;
				SYSTEMTIME time;
				FileTimeToSystemTime(&status.m_mtime, &time);
				str.Format(_T("213 %04d%02d%02d%02d%02d%02d"),
							time.wYear,
							time.wMonth,
							time.wDay,
							time.wHour,
							time.wMinute,
							time.wSecond);
				Send(str);
			}
		}
		break;
	case COMMAND_EPSV:
		{
			if (m_transferstatus.socket)
			{
				SendTransferinfoNotification();
				delete m_transferstatus.socket;
			}
			m_transferstatus.family = (GetFamily() == AF_INET) ? 1 : 2;
			m_transferstatus.socket = new CTransferSocket(this);

			unsigned int port = 0;
			unsigned int retries = 3;
			while (retries > 0) {
				if (m_pOwner->m_pOptions->GetOptionVal(OPTION_USECUSTOMPASVPORT)) {
					static UINT customPort = 0;
					unsigned int minPort = (unsigned int)m_pOwner->m_pOptions->GetOptionVal(OPTION_CUSTOMPASVMINPORT);
					unsigned int maxPort = (unsigned int)m_pOwner->m_pOptions->GetOptionVal(OPTION_CUSTOMPASVMAXPORT);
					if (minPort > maxPort) {
						unsigned int temp = minPort;
						minPort = maxPort;
						maxPort = temp;
					}
					if (customPort < minPort || customPort > maxPort) {
						customPort = minPort;
					}
					port = customPort;
					++customPort;
				}
				if (m_transferstatus.socket->Create(port, SOCK_STREAM, FD_ACCEPT, 0, GetFamily()))
				{
					break;
				}
				--retries;
			}
			if (retries <= 0) {
				delete m_transferstatus.socket;
				m_transferstatus.socket=0;
				Send(_T("421 Can't create socket"));
				break;
			}

			if (m_pGssLayer && m_pGssLayer->AuthSuccessful())
				m_transferstatus.socket->UseGSS(m_pGssLayer);

			if (m_pSslLayer && m_bProtP)
				m_transferstatus.socket->UseSSL(m_pSslLayer->GetContext());

			if (!m_transferstatus.socket->Listen())
			{
				delete m_transferstatus.socket;
				m_transferstatus.socket=0;
				Send(_T("421 Can't create socket"));
				m_transferstatus.pasv = -1;
				break;
			}

			//Now retrieve the port
			CStdString dummy;
			if (m_transferstatus.socket->GetSockName(dummy, port))
			{
				//Put the answer together
				CStdString str;
				str.Format(_T("229 Entering Extended Passive Mode (|||%d|)"), port);
				Send(str);
				m_transferstatus.pasv=1;
			}
			else
			{
				delete m_transferstatus.socket;
				m_transferstatus.socket=0;
				Send(_T("421 Can't create socket"));
				m_transferstatus.pasv = -1;
			}
			break;
		}
	case COMMAND_EPRT:
		{
			if (m_transferstatus.socket)
			{
				SendTransferinfoNotification();
				delete m_transferstatus.socket;
				m_transferstatus.socket=0;
			}

			if (args[0] != '|')
			{
				Send(_T("501 Syntax error"));
				m_transferstatus.pasv = -1;
				break;
			}
			args = args.Mid(1);

			int pos = args.Find('|');
			if (pos < 1 || (pos>=(args.GetLength()-1)))
			{
				Send(_T("501 Syntax error"));
				m_transferstatus.pasv = -1;
				break;
			}
			int protocol = _ttoi(args.Left(pos));

			bool ipv6Allowed = m_pOwner->m_pOptions->GetOptionVal(OPTION_DISABLE_IPV6) == 0;
			if (protocol != 1 && (protocol != 2 || !ipv6Allowed))
			{
				if (ipv6Allowed)
					Send(_T("522 Extended Port Failure - unknown network protocol. Supported protocols: (1,2)"));
				else
					Send(_T("522 Extended Port Failure - unknown network protocol. Supported protocols: (1)"));
				m_transferstatus.pasv = -1;
				break;
			}
			args = args.Mid(pos + 1);

			pos = args.Find('|');
			if (pos < 1 || (pos>=(args.GetLength()-1)))
			{
				Send(_T("501 Syntax error"));
				m_transferstatus.pasv = -1;
				break;
			}
			CStdString ip = args.Left(pos);
			if (protocol == 1)
			{
#ifdef _UNICODE
				if (inet_addr(ConvToLocal(ip)) == INADDR_NONE)
#else
				if (inet_addr(ip) == INADDR_NONE)
#endif
				{
					Send(_T("501 Syntax error, not a valid IPv4 address"));
					m_transferstatus.pasv = -1;
					break;
				}
			}
			else
			{
				ip = GetIPV6LongForm(ip);
				if (ip.IsEmpty())
				{
					Send(_T("501 Syntax error, not a valid IPv6 address"));
					m_transferstatus.pasv = -1;
					break;
				}
			}
			args = args.Mid(pos + 1);

			pos = args.Find('|');
			if (pos < 1)
			{
				Send(_T("501 Syntax error"));
				m_transferstatus.pasv = -1;
				break;
			}
			int port = _ttoi(args.Left(pos));
			if (port < 1 || port > 65535)
			{
				Send(_T("501 Syntax error"));
				m_transferstatus.pasv = -1;
				break;
			}

			m_transferstatus.port = port;
			m_transferstatus.ip = ip;
			m_transferstatus.family = (protocol == 1) ? AF_INET : AF_INET6;

			m_transferstatus.pasv = 0;
			Send(_T("200 Port command successful"));
			break;
		}
	case COMMAND_AUTH:
		{
			if (m_nRecvBufferPos || m_RecvLineBuffer.size() ) {
				Send(_T("503 Bad sequence of commands. Received additional data after the AUTH command before this reply could be sent."));
				ForceClose(-1);
				break;
			}

			if (m_pGssLayer)
			{
				Send(_T("534 Authentication type already set to GSSAPI"));
				break;
			}
			else if (m_pSslLayer)
			{
				Send(_T("534 Authentication type already set to SSL"));
				break;
			}
			args.MakeUpper();

			if (args == _T("GSSAPI"))
			{
				if (!m_pOwner->m_pOptions->GetOptionVal(OPTION_USEGSS))
				{
					Send(_T("502 GSSAPI authentication not implemented"));
					break;
				}

				m_pGssLayer = new CAsyncGssSocketLayer;
				BOOL res = AddLayer(m_pGssLayer);
				if (res)
				{
					res = m_pGssLayer->InitGSS(FALSE, (BOOL)m_pOwner->m_pOptions->GetOptionVal(OPTION_GSSPROMPTPASSWORD));
					if (!res)
						SendStatus(_T("Unable to init GSS"), 1);
				}
				if (!res)
				{
					RemoveAllLayers();
					delete m_pGssLayer;
					m_pGssLayer = NULL;
					Send(_T("431 Could not initialize GSSAPI libraries"));
					break;
				}

				Send(_T("334 Using authentication type GSSAPI; ADAT must follow"));
			}
			else if (args == _T("SSL") || args == _T("TLS"))
			{
				if (m_pSslLayer)
				{
					Send(_T("503 Already using SSL/TLS"));
					break;
				}

				if (!m_pOwner->m_pOptions->GetOptionVal(OPTION_ENABLESSL) || !m_pOwner->m_pOptions->GetOptionVal(OPTION_ALLOWEXPLICITSSL))
				{
					Send(_T("502 SSL/TLS authentication not allowed"));
					break;
				}

				m_pSslLayer = new CAsyncSslSocketLayer;
				BOOL res = AddLayer(m_pSslLayer);

				if (res)
				{
					CString error;
#ifdef _UNICODE
					int res = m_pSslLayer->SetCertKeyFile(ConvToLocal(m_pOwner->m_pOptions->GetOption(OPTION_SSLCERTFILE)), ConvToLocal(m_pOwner->m_pOptions->GetOption(OPTION_SSLKEYFILE)), ConvToLocal(m_pOwner->m_pOptions->GetOption(OPTION_SSLKEYPASS)), &error);
#else
					int res = m_pSslLayer->SetCertKeyFile(m_pOwner->m_pOptions->GetOption(OPTION_SSLCERTFILE), m_pOwner->m_pOptions->GetOption(OPTION_SSLKEYFILE), m_pOwner->m_pOptions->GetOption(OPTION_SSLKEYPASS), &error);
#endif
					if (res == SSL_FAILURE_LOADDLLS)
						SendStatus(_T("Failed to load SSL libraries"), 1);
					else if (res == SSL_FAILURE_INITSSL)
						SendStatus(_T("Failed to initialize SSL libraries"), 1);
					else if (res == SSL_FAILURE_VERIFYCERT)
					{
						if (error != _T(""))
							SendStatus(error, 1);
						else
							SendStatus(_T("Failed to set certificate and private key"), 1);
					}
					if (res)
					{
						RemoveAllLayers();
						delete m_pSslLayer;
						m_pSslLayer = NULL;
						Send(_T("431 Could not initialize SSL connection"));
						break;
					}
				}

				if (res)
				{
					int code = m_pSslLayer->InitSSLConnection(false);
					if (code == SSL_FAILURE_LOADDLLS)
						SendStatus(_T("Failed to load SSL libraries"), 1);
					else if (code == SSL_FAILURE_INITSSL)
						SendStatus(_T("Failed to initialize SSL library"), 1);

					res = (code == 0);
				}

				if (res)
				{
					if (args == _T("SSL"))
					{
						SendStatus(_T("234 Using authentication type SSL"), 3);
						static const char* reply = "234 Using authentication type SSL\r\n";
						const int len = strlen(reply);
						res = (m_pSslLayer->SendRaw(reply, len) == len);
					}
					else // TLS
					{
						SendStatus(_T("234 Using authentication type TLS"), 3);
						static const char* reply = "234 Using authentication type TLS\r\n";
						const int len = strlen(reply);
						res = (m_pSslLayer->SendRaw(reply, len) == len);
					}
				}

				if (!res)
				{
					RemoveAllLayers();
					delete m_pSslLayer;
					m_pSslLayer = NULL;
					Send(_T("431 Could not initialize SSL connection"));
					break;
				}
			}
			else
			{
				Send(_T("504 Auth type not supported"));
				break;
			}

			break;
		}
	case COMMAND_ADAT:
		if (m_pGssLayer)
		{
			char sendme[4096];
#ifdef _UNICODE
			m_pGssLayer->ProcessCommand("ADAT", ConvToLocal(args), sendme);
			Send(ConvFromLocal(sendme));
#else
			m_pGssLayer->ProcessCommand("ADAT", args, sendme);
			Send(sendme);
#endif
			
		}
		else
			Send(_T("502 Command not implemented for this authentication type"));
		break;
	case COMMAND_PBSZ:
		if (m_pGssLayer)
		{
			char sendme[4096];
#ifdef _UNICODE
			m_pGssLayer->ProcessCommand("PBSZ", ConvToLocal(args), sendme);
			Send(ConvFromLocal(sendme));
#else
			m_pGssLayer->ProcessCommand("PBSZ", args, sendme);
			Send(sendme);
#endif
		}
		else if (m_pSslLayer)
			Send(_T("200 PBSZ=0"));
		else
			Send(_T("502 Command not implemented for this authentication type"));
		break;
	case COMMAND_PROT:
		if (m_pGssLayer)
		{
			char sendme[4096];

#ifdef _UNICODE
			m_pGssLayer->ProcessCommand("PROT", ConvToLocal(args), sendme);
			Send(ConvFromLocal(sendme));
#else
			m_pGssLayer->ProcessCommand("PROT", args, sendme);
			Send(sendme);
#endif
		}
		else if (m_pSslLayer)
		{
			args.MakeUpper();
			if (args == _T("C"))
			{
				if (m_pOwner->m_pOptions->GetOptionVal(OPTION_FORCEPROTP))
					Send(_T("534 This server requires an encrypted data connection with PROT P"));
				else
				{
					if (m_transferstatus.socket)
						m_transferstatus.socket->UseSSL(0);

					Send(_T("200 Protection level set to C"));
					m_bProtP = false;
				}
			}
			else if (args == _T("P"))
			{
				if (m_transferstatus.socket)
					m_transferstatus.socket->UseSSL(m_pSslLayer->GetContext());

				Send(_T("200 Protection level set to P"));
				m_bProtP = true;
			}
			else if (args == _T("S") || args == _T("E"))
				Send(_T("504 Protection level ") + args + _T(" not supported"));
			else
				Send(_T("504 Protection level ") + args + _T(" not recognized"));
		}
		else
			Send(_T("502 Command not implemented for this authentication type"));
		break;
	case COMMAND_FEAT:
		{
		if (!Send(_T("211-Features:")))
			break;
		if (!Send(_T(" MDTM")))
			break;
		if (!Send(_T(" REST STREAM")))
			break;
		if (!Send(_T(" SIZE")))
			break;
		if (m_pOwner->m_pOptions->GetOptionVal(OPTION_MODEZ_USE))
		{
			if (!Send(_T(" MODE Z")))
				break;
		}
		if (!Send(_T(" MLST type*;size*;modify*;")))
			break;
		if (!Send(_T(" MLSD")))
			break;
		if (m_pOwner->m_pOptions->GetOptionVal(OPTION_ENABLESSL) && (m_pOwner->m_pOptions->GetOptionVal(OPTION_ALLOWEXPLICITSSL) || m_pSslLayer))
		{
			if (!Send(_T(" AUTH SSL")))
				break;
			if (!Send(_T(" AUTH TLS")))
				break;
			if (!Send(_T(" PROT")))
				break;
			if (!Send(_T(" PBSZ")))
				break;
		}
		if (!Send(_T(" UTF8")))
			break;
		if (!Send(_T(" CLNT")))
			break;
		if (!Send(_T(" MFMT")))
			break;
		if (m_pOwner->m_pOptions->GetOptionVal(OPTION_ENABLE_HASH))
		{
			CStdString hash = _T(" HASH ");
			hash += _T("SHA-1");
			if (m_hash_algorithm == CHashThread::SHA1)
				hash += _T("*");
			hash += _T(";SHA-512");
			if (m_hash_algorithm == CHashThread::SHA512)
				hash += _T("*");
			hash += _T(";MD5");
			if (m_hash_algorithm == CHashThread::MD5)
				hash += _T("*");
			if (!Send(hash))
				break;
		}
		if (!Send(_T("211 End")))
			break;
		break;
		}
	case COMMAND_MODE:
		if (args == _T("S") || args == _T("s"))
		{
			m_transferMode = mode_stream;
			Send(_T("200 MODE set to S."));
		}
		else if (args == _T("Z") || args == _T("z"))
		{
			if (m_pOwner->m_pOptions->GetOptionVal(OPTION_MODEZ_USE) || m_transferMode == mode_zlib)
			{
				if (m_transferMode == mode_zlib || CheckIpForZlib())
				{
					m_transferMode = mode_zlib;
					Send(_T("200 MODE set to Z."));
				}
				else
					Send(_T("504 MODE Z not allowed from your IP"));
			}
			else
				Send(_T("504 MODE Z not enabled"));
		}
		else if (args == _T("C") || args == _T("c") || args == _T("B") || args == _T("b"))
			Send(_T("502 Unimplemented MODE type"));
		else
			Send(_T("504 Unknown MODE type"));
		break;
	case COMMAND_OPTS:
		args.MakeUpper();
		if (args.Left(13) == _T("MODE Z LEVEL "))
		{
			int level = _ttoi(args.Mid(13));
			if (m_zlibLevel == level || (level >= m_pOwner->m_pOptions->GetOptionVal(OPTION_MODEZ_LEVELMIN) && level <= m_pOwner->m_pOptions->GetOptionVal(OPTION_MODEZ_LEVELMAX)))
			{
				m_zlibLevel = level;
				CString str;
				str.Format(_T("200 MODE Z LEVEL set to %d"), level);
				Send(str);
			}
			else
				Send(_T("501 can't change MODE Z LEVEL do desired value"));
		}
		else if (args == _T("UTF8 ON"))
		{
			m_useUTF8 = true;
			Send(_T("200 UTF8 mode enabled"));
		}
		else if (args == _T("UTF8 OFF"))
		{
			m_useUTF8 = false;
			Send(_T("200 UTF8 mode disabled"));
		}
		else if (args.Left(4) == _T("MLST"))
			ParseMlstOpts(args.Mid(4));
		else if (args.Left(4) == _T("HASH"))
			ParseHashOpts(args.Mid(4));
		else
			Send(_T("501 Option not understood"));
		break;
	case COMMAND_HELP:
		if (args == _T(""))
		{
			Send(_T("214-The following commands are recognized:"));
			CString str;
			for (int i = 0; i < (sizeof(commands)/sizeof(t_command)); i++)
			{
				CString cmd = commands[i].command;
				while (cmd.GetLength() < 4)
					cmd += _T(" ");
				str += _T("   ") + cmd;
				if (!((i + 1) % 8))
				{
					Send(str);
					str = _T("");
				}
			}
			if (str != _T(""))
				Send(str);
			Send(_T("214 Have a nice day."));
		}
		else
		{
			args.MakeUpper();

			int i;
			for (i = 0; i < (sizeof(commands)/sizeof(t_command)); i++)
			{
				if (args == commands[i].command)
				{
					CStdString str;
					str.Format(_T("214 Command %s is supported by FileZilla Server"), args);
					Send(str);
					break;
				}
			}
			if (i == (sizeof(commands)/sizeof(t_command)))
			{
				CStdString str;
				str.Format(_T("502 Command %s is not recognized or supported by FileZilla Server"), args);
				Send(str);
			}
		}
		break;
	case COMMAND_ALLO:
		Send(_T("202 No storage allocation neccessary."));
		break;
	case COMMAND_MLST:
		{
			CStdString fact;
			CStdString logicalName;
			int res = m_pOwner->m_pPermissions->GetFact(m_status.user, m_CurrentServerDir, args, fact, logicalName, m_facts);
			if (res & PERMISSION_DENIED)
			{
				Send(_T("550 Permission denied."));
				break;
			}
			else if (res & PERMISSION_INVALIDNAME)
			{
				Send(_T("550 Filename invalid."));
				break;
			}
			else if (res)
			{
				Send(_T("550 File or directory not found."));
				break;
			}
			CStdString str;
			str.Format(_T("250-Listing %s"), logicalName);
			if (!Send(str))
				break;
			fact = _T(" ") + fact;
			if (!Send(fact))
				break;

			Send(_T("250 End"));
		}
		break;
	case COMMAND_MLSD:
		if (m_transferstatus.pasv == -1)
		{
			Send(_T("503 Bad sequence of commands."));
			break;
		}
		if (!m_transferstatus.pasv && (m_transferstatus.ip == _T("") || m_transferstatus.port == -1))
			Send(_T("503 Bad sequence of commands."));
		//Much more checks
		else
		{
			if (m_pSslLayer && m_pOwner->m_pOptions->GetOptionVal(OPTION_FORCEPROTP) && !m_bProtP)
			{
				Send(_T("521 PROT P required"));
				break;
			}
			if (args != _T(""))
			{
				//Unquote args
				if (!UnquoteArgs(args))
				{
					Send(_T("501 Syntax error"));
					break;
				}
			}

			t_dirlisting *pResult;
			CStdString physicalDir, logicalDir;
			int error = m_pOwner->m_pPermissions->GetDirectoryListing(m_status.user, m_CurrentServerDir, args, pResult, physicalDir, logicalDir, CPermissions::AddFactsListingEntry, m_useUTF8, m_facts);
			if (error & PERMISSION_DENIED)
			{
				Send(_T("550 Permission denied"));
				ResetTransferstatus();
			}
			else if (error & PERMISSION_INVALIDNAME)
			{
				Send(_T("550 Filename invalid."));
				ResetTransferstatus();
			}
			else if (error)
			{
				Send(_T("550 Directory not found"));
				ResetTransferstatus();
			}
			else
			{
				if (!m_transferstatus.pasv)
				{
					if (m_transferstatus.socket)
					{
						SendTransferinfoNotification();
						delete m_transferstatus.socket;
					}
					CTransferSocket *transfersocket = new CTransferSocket(this);
					m_transferstatus.socket = transfersocket;
					transfersocket->Init(pResult, TRANSFERMODE_LIST);
					if (m_transferMode == mode_zlib)
					{
						if (!transfersocket->InitZLib(m_zlibLevel))
						{
							Send(_T("550 could not initialize zlib, please use MODE S instead"));
							ResetTransferstatus();
							break;
						}
					}

					if (!CreateTransferSocket(transfersocket))
						break;

					SendTransferinfoNotification(TRANSFERMODE_LIST, physicalDir, logicalDir);
					Send(_T("150 Opening data channel for directory list."));
				}
				else
				{
					if (!m_transferstatus.socket)
					{
						CPermissions::DestroyDirlisting(pResult);
						Send(_T("503 Bad sequence of commands."));
						break;
					}
					m_transferstatus.socket->Init(pResult, TRANSFERMODE_LIST );
					if (m_transferMode == mode_zlib)
					{
						if (!m_transferstatus.socket->InitZLib(m_zlibLevel))
						{
							Send(_T("550 could not initialize zlib, please use MODE S instead"));
							ResetTransferstatus();
							break;
						}
					}

					SendTransferinfoNotification(TRANSFERMODE_LIST, physicalDir, logicalDir);
					m_transferstatus.socket->PasvTransfer();
				}
			}

		}
		break;
	case COMMAND_SITE:
		{
			CStdString cmd;

			args.MakeUpper();
			
			int pos = args.Find(' ');
			if (pos != -1)
			{
				cmd = args.Left(pos);
				args = args.Mid(pos + 1);
				args.TrimLeft(_T(" "));
			}
			else
			{
				cmd = args;
				args = _T("");
			}

			if (cmd == _T("NAMEFMT"))
			{
				if (args == _T("") || args == _T("1"))
					Send(_T("200 Now using naming format \"1\""));
				else
					Send(_T("504 Naming format not implemented"));
				break;
			}
			else
			{
				Send(_T("504 Command not implemented for that parameter"));
				break;
			}
			break;
		}
	case COMMAND_STRU:
		args.MakeUpper();
		if (args == _T("F"))
			Send(_T("200 Using file structure 'File'"));
		else
			Send(_T("504 Command not implemented for that parameter"));
		break;
	case COMMAND_CLNT:
		Send(_T("200 Don't care"));
		break;
	case COMMAND_MFMT:
		{
			int pos = args.find(' ');
			if (pos < 1)
			{
				Send(_T("501 Syntax error"));
				break;
			}

			CStdString timeval = args.Left(pos);
			args = args.Mid(pos + 1);

			if (timeval.GetLength() < 14)
			{
				Send( _T("501 Syntax error") );
				break;
			}

			bool numbersOnly = true;
			for (int i = 0; i < 14; i++)
			{
				if (timeval[i] < '0' || timeval[i] > '9')
				{
					numbersOnly = false;
					break;
				}
			}
			if (!numbersOnly)
			{
				Send( _T("501 Syntax error") );
				break;
			}

			int year = (timeval[0] - '0') * 1000 +
					(timeval[1] - '0') * 100 +
					(timeval[2] - '0') * 10 +
					timeval[3] - '0';

			int month = (timeval[4] - '0') * 10 + timeval[5] - '0';
			int day = (timeval[6] - '0') * 10 + timeval[7] - '0';
			int hour = (timeval[8] - '0') * 10 + timeval[9] - '0';
			int minute = (timeval[10] - '0') * 10 + timeval[11] - '0';
			int second = (timeval[12] - '0') * 10 + timeval[13] - '0';

			if (year < 1000 || month < 1 || month > 12 || day < 1 || day > 31 || hour > 23 ||
				minute > 59 || second > 59)
			{
				Send( _T("501 Not a valid date") );
				break;
			}

			SYSTEMTIME st = {0};
			st.wYear = year;
			st.wMonth = month;
			st.wDay = day;
			st.wHour = hour;
			st.wMinute = minute;
			st.wSecond = second;

			FILETIME ft;
			if (!SystemTimeToFileTime(&st, &ft))
			{
				Send( _T("501 Not a valid date") );
				break;
			}

			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send( _T("501 Syntax error") );
				break;
			}

			if (args == _T(""))
			{
				Send( _T("501 Syntax error") );
				break;
			}

			CStdString physicalFile, logicalFile;
			int error = m_pOwner->m_pPermissions->CheckFilePermissions(m_status.user, args, m_CurrentServerDir, FOP_LIST, physicalFile, logicalFile);
			if (error & PERMISSION_DENIED)
				Send(_T("550 Permission denied"));
			else if (error & PERMISSION_INVALIDNAME)
				Send(_T("550 Filename invalid."));
			else if (error & 2)
				Send(_T("550 File not found"));
			else
			{
				HANDLE hFile = CreateFile(physicalFile, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0);
				if (hFile == INVALID_HANDLE_VALUE)
					Send(_T("550 Cannot access file"));
				else
				{
					if (!SetFileTime(hFile, 0, 0, &ft))
						Send(_T("550 Failed to set file modification time"));
					else
						Send(_T("213 modify=") + timeval.Left(14) + _T("; ") + logicalFile);

					CloseHandle(hFile);
				}
			}
		}
		break;
	case COMMAND_HASH:
		{
			if (!m_pOwner->m_pOptions->GetOptionVal(OPTION_ENABLE_HASH))
			{
				Send(_T("500 Syntax error, command unrecognized."));
				break;
			}

			//Unquote args
			if (!UnquoteArgs(args))
			{
				Send( _T("501 Syntax error") );
				break;
			}

			CStdString physicalFile, logicalFile;
			int error = m_pOwner->m_pPermissions->CheckFilePermissions(m_status.user, args, m_CurrentServerDir, FOP_READ, physicalFile, logicalFile);
			if (error & PERMISSION_DENIED)
			{
				Send(_T("550 Permission denied"));
				ResetTransferstatus();
			}
			else if (error & PERMISSION_INVALIDNAME)
			{
				Send(_T("550 Filename invalid."));
				ResetTransferstatus();
			}
			else if (error)
			{
				Send(_T("550 File not found"));
				ResetTransferstatus();
			}
			else
			{
				int hash_res = m_pOwner->GetHashThread().Hash(physicalFile, m_hash_algorithm, m_hash_id, m_pOwner);
				if (hash_res == CHashThread::BUSY)
					Send(_T("450 Another hash operation is already in progress."));
				else if (hash_res != CHashThread::PENDING)
					Send(_T("550 Failed to hash file"));
			}
		}
		break;
	default:
		Send(_T("502 Command not implemented."));
	}

	if (!m_RecvLineBuffer.empty())
		m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_COMMAND, m_userid);

	return;
}

void CControlSocket::ProcessTransferMsg()
{
	if (!m_transferstatus.socket)
		return;
	int status = m_transferstatus.socket->GetStatus();

	GetSystemTime(&m_LastCmdTime);
	if (m_transferstatus.socket)
		if (m_transferstatus.socket->GetMode()==TRANSFERMODE_SEND || m_transferstatus.socket->GetMode()==TRANSFERMODE_RECEIVE)
			GetSystemTime(&m_LastTransferTime);

	if (status == 2 && m_transferstatus.pasv && m_transferstatus.usedResolvedIP)
		m_pOwner->ExternalIPFailed();
	
	int mode = m_transferstatus.socket->GetMode();
	_int64 zlibBytesIn = 0;
	_int64 zlibBytesOut = 0;
	if (m_transferMode == mode_zlib)
		m_transferstatus.socket->GetZlibStats(zlibBytesIn, zlibBytesOut);
	ResetTransferstatus();

	if (!status)
	{
		if ((mode == TRANSFERMODE_LIST || mode == TRANSFERMODE_NLST || mode == TRANSFERMODE_SEND) && zlibBytesIn && zlibBytesOut)
		{
			if (zlibBytesIn >= zlibBytesOut)
			{
				CString str;
				_int64 percent = 10000 - (zlibBytesOut * 10000 / zlibBytesIn);
				str.Format(_T("226 Transfer OK, compression saved %I64d of %I64d bytes (%I64d.%02I64d%%)"), zlibBytesIn - zlibBytesOut, zlibBytesIn, percent / 100, percent % 100);
				Send(str);
			}
			else
			{
				CString str;
				_int64 percent = (zlibBytesOut * 10000 / zlibBytesIn) - 10000;
				str.Format(_T("226 Transfer OK, unfortunately compression did increase the transfer size by %I64d bytes to %I64d bytes (%I64d.%02I64d%%)"), zlibBytesOut - zlibBytesIn, zlibBytesOut, percent / 100, percent % 100);
				Send(str);
			}
		}
		else if (mode == TRANSFERMODE_RECEIVE && zlibBytesIn && zlibBytesOut)
		{
			if (zlibBytesOut >= zlibBytesIn)
			{
				CString str;
				_int64 percent = 10000 - (zlibBytesIn * 10000 / zlibBytesOut);
				str.Format(_T("226 Transfer OK, compression saved %I64d of %I64d bytes (%I64d.%02I64d%%)"), zlibBytesOut - zlibBytesIn, zlibBytesOut, percent / 100, percent % 100);
				Send(str);
			}
			else
			{
				CString str;
				_int64 percent = (zlibBytesIn * 10000 / zlibBytesOut) - 10000;
				str.Format(_T("226 Transfer OK, unfortunately compression did increase the transfer size by %I64d bytes to %I64d bytes (%I64d.%02I64d%%)"), zlibBytesIn - zlibBytesOut, zlibBytesIn, percent / 100, percent % 100);
				Send(str);
			}
		}
		else
			Send(_T("226 Transfer OK"));
	}
	else if (status==1)
		Send(_T("426 Connection closed; transfer aborted."));
	else if (status==2)
		Send(_T("425 Can't open data connection."));
	else if (status==3)
		Send(_T("550 can't access file."));
	else if (status==4)
	{
		Send(_T("426 Connection timed out, aborting transfer"));
		ForceClose(1);
		return;
	}
	else if (status==5)
		Send(_T("425 Can't open data connection"));
	else if (status==6)
		Send(_T("450 zlib error"));
	if (status>=0 && m_bWaitGoOffline)
		ForceClose(0);
	else if (m_bQuitCommand)
	{
		Send(_T("221 Goodbye"));
		if (CanQuit())
			ForceClose(5);
	}
}

CTransferSocket* CControlSocket::GetTransferSocket()
{
	return m_transferstatus.socket;
}

void CControlSocket::ForceClose(int nReason)
{
	if (m_transferstatus.socket)
	{
		// Don't call SendTransferInfoNotification, since connection
		// does get removed real soon.
		m_transferstatus.socket->Close();
		delete m_transferstatus.socket;
		m_transferstatus.socket = 0;
	}
	if (m_shutdown && nReason == 1)
	{
		Close();
		m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_DELSOCKET, m_userid);
		return;
	}

	if (!nReason)
		Send(_T("421 Server is going offline"));
	else if (nReason == 1)
		Send(_T("421 Connection timed out."));
	else if (nReason == 2)
		Send(_T("421 No-transfer-time exceeded. Closing control connection."));
	else if (nReason == 3)
		Send(_T("421 Login time exceeded. Closing control connection."));
	else if (nReason == 4)
		Send(_T("421 Kicked by Administrator"));
	else if (nReason == 5)
	{
		// 221 Goodbye
	}
	SendStatus(_T("disconnected."), 0);
	m_shutdown = true;
	int res = ShutDown();
	if (m_pSslLayer)
	{
		if (!res && GetLastError() == WSAEWOULDBLOCK)
			return;
	}
	Close();
	m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_DELSOCKET, m_userid);
}

void CControlSocket::IncUserCount(const CStdString &user)
{
	int curcount=GetUserCount(user)+1;
	EnterCritSection(m_Sync);
	m_UserCount[user]=curcount;
	LeaveCritSection(m_Sync);
}

void CControlSocket::DecUserCount(const CStdString &user)
{
	int curcount=GetUserCount(user)-1;
	if (curcount<0)
		return;
	EnterCritSection(m_Sync);
	m_UserCount[user]=curcount;
	LeaveCritSection(m_Sync);
}

int CControlSocket::GetUserCount(const CStdString &user)
{
	EnterCritSection(m_Sync);
	int count=0;
	std::map<CStdString, int>::iterator iter = m_UserCount.find(user);
	if (iter!=m_UserCount.end())
		count = iter->second;
	LeaveCritSection(m_Sync);
	return count;
}

void CControlSocket::CheckForTimeout()
{
	if (m_antiHammeringWaitTime)
	{
		m_antiHammeringWaitTime -= 1000;
		if (m_antiHammeringWaitTime <= 0)
		{
			m_antiHammeringWaitTime = 0;
			TriggerEvent(FD_FORCEREAD);
		}
	}
	if (m_status.hammerValue > 0)
		m_status.hammerValue--;

	if (m_transferstatus.socket)
	{
		if (m_transferstatus.socket->CheckForTimeout())
			return;
	}
	_int64 timeout;
	if (m_shutdown)
		timeout = 3;
	else
		timeout = m_pOwner->m_pOptions->GetOptionVal(OPTION_TIMEOUT);
	if (!timeout)
		return;
	SYSTEMTIME sCurrentTime;
	GetSystemTime(&sCurrentTime);
	FILETIME fCurrentTime;
	SystemTimeToFileTime(&sCurrentTime, &fCurrentTime);
	FILETIME fLastTime;
	SystemTimeToFileTime(&m_LastCmdTime, &fLastTime);
	_int64 elapsed = ((_int64)(fCurrentTime.dwHighDateTime - fLastTime.dwHighDateTime) << 32) + fCurrentTime.dwLowDateTime - fLastTime.dwLowDateTime;
	if (elapsed > (timeout*10000000))
	{
		ForceClose(1);
		return;
	}
	if (m_status.loggedon)
	{ //Transfer timeout
		_int64 nNoTransferTimeout=m_pOwner->m_pOptions->GetOptionVal(OPTION_NOTRANSFERTIMEOUT);
		if (!nNoTransferTimeout)
			return;
		SystemTimeToFileTime(&m_LastTransferTime, &fLastTime);
		elapsed = ((_int64)(fCurrentTime.dwHighDateTime - fLastTime.dwHighDateTime) << 32) + fCurrentTime.dwLowDateTime - fLastTime.dwLowDateTime;
		if (elapsed>(nNoTransferTimeout*10000000))
		{
			ForceClose(2);
			return;
		}
	}
	else
	{ //Login timeout
		_int64 nLoginTimeout=m_pOwner->m_pOptions->GetOptionVal(OPTION_LOGINTIMEOUT);
		if (!nLoginTimeout)
			return;
		SystemTimeToFileTime(&m_LoginTime, &fLastTime);
		elapsed = ((_int64)(fCurrentTime.dwHighDateTime - fLastTime.dwHighDateTime) << 32) + fCurrentTime.dwLowDateTime - fLastTime.dwLowDateTime;
		if (elapsed>(nLoginTimeout*10000000))
		{
			ForceClose(3);
			return;
		}
	}
}

void CControlSocket::WaitGoOffline(bool wait /*=true*/)
{
	if (!wait)
	{
		m_bWaitGoOffline = FALSE;
		return;
	}

	if (m_transferstatus.socket)
	{
		if (!m_transferstatus.socket->Started())
			ForceClose(0);
		else
			m_bWaitGoOffline=TRUE;
	}
	else
		ForceClose(0);

}

void CControlSocket::ResetTransferstatus()
{
	if (m_transferstatus.socket)
	{
		SendTransferinfoNotification();
		delete m_transferstatus.socket;
	}
	m_transferstatus.socket = 0;
	m_transferstatus.ip = _T("");
	m_transferstatus.port = -1;
	m_transferstatus.pasv = -1;
	m_transferstatus.rest = 0;
}

BOOL CControlSocket::UnquoteArgs(CStdString &args)
{
	args.TrimLeft( _T(" ") );
	args.TrimRight( _T(" ") );
	int pos1 = args.Find('"');
	int pos2 = args.ReverseFind('"');
	if (pos1 == -1 && pos2 == -1)
		return TRUE;
	if (pos1 || pos2 != (args.GetLength()-1) || pos1 >= (pos2-1))
		return FALSE;
	args = args.Mid(1, args.GetLength() - 2);
	return TRUE;
}

void CControlSocket::OnSend(int nErrorCode)
{
	if (m_nSendBufferLen && m_pSendBuffer)
	{
		int nLimit = GetSpeedLimit(download);
		if (!nLimit)
			return;
		int numsend = nLimit;
		if (nLimit == -1 || nLimit > m_nSendBufferLen)
			numsend = m_nSendBufferLen;


		int numsent = CAsyncSocketEx::Send(m_pSendBuffer, numsend);

		if (numsent==SOCKET_ERROR && GetLastError() == WSAEWOULDBLOCK)
			return;
		if (!numsent || numsent == SOCKET_ERROR)
		{
			Close();
			SendStatus(_T("could not send reply, disconnected."), 0);
			m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_DELSOCKET, m_userid);

			delete [] m_pSendBuffer;
			m_pSendBuffer = NULL;
			m_nSendBufferLen = 0;

			return;
		}

		if (nLimit != -1)
			m_SlQuotas[download].nTransferred += numsent;

		if (numsent == m_nSendBufferLen)
		{
			delete [] m_pSendBuffer;
			m_pSendBuffer = NULL;
			m_nSendBufferLen = 0;
		}
		else
		{
			char *tmp = m_pSendBuffer;
			m_pSendBuffer = new char[m_nSendBufferLen-numsent];
			memcpy(m_pSendBuffer, tmp+numsent, m_nSendBufferLen-numsent);
			delete [] tmp;
			m_nSendBufferLen -= numsent;
			TriggerEvent(FD_WRITE);
		}
	}
}

BOOL CControlSocket::DoUserLogin(LPCTSTR password, bool skipPass /*=false*/)
{
	CUser user;
	if (!m_pOwner->m_pPermissions->CheckUserLogin(m_status.user, password, user, skipPass))
	{
		AntiHammerIncrease(2);
		m_pOwner->AntiHammerIncrease(m_RemoteIP);

		if (m_pOwner->m_pAutoBanManager->RegisterAttempt(m_RemoteIP))
		{
			Send(_T("421 Temporarily banned for too many failed login attempts"));
			ForceClose(-1);
			return FALSE;
		}

		Send(_T("530 Login or password incorrect!"));
		return FALSE;
	}

	if (!user.IsEnabled())
	{
		Send(_T("530 Not logged in, user account has been disabled"));
		ForceClose(-1);
		return FALSE;
	}
	if (!user.BypassUserLimit())
	{
		int nMaxUsers = (int)m_pOwner->m_pOptions->GetOptionVal(OPTION_MAXUSERS);
		if (m_pOwner->GetGlobalNumConnections()>nMaxUsers&&nMaxUsers)
		{
			SendStatus(_T("Refusing connection. Reason: Max. connection count reached."), 1);
			Send(_T("421 Too many users are connected, please try again later."));
			ForceClose(-1);
			return FALSE;
		}
	}
	if (user.GetUserLimit() && GetUserCount(m_status.user)>=user.GetUserLimit())
	{
			CStdString str;
			str.Format(_T("Refusing connection. Reason: Max. connection count reached for the user \"%s\"."), m_status.user);
			SendStatus(str,1);
			Send(_T("421 Too many users logged in for this account. Try again later."));
			ForceClose(-1);
			return FALSE;
	}

	CStdString peerIP;
	UINT port = 0;

	BOOL bResult = GetPeerName(peerIP, port);
	if (bResult)
	{
		if (!user.AccessAllowed(peerIP))
		{
			Send(_T("521 This user is not allowed to connect from this IP"));
			ForceClose(-1);
			return FALSE;
		}
	}
	else
	{
		SendStatus(_T("Could not get peer name"), 1);
		Send(_T("421 Refusing connection. Could not get peer name."));
		ForceClose(-1);
		return FALSE;
	}

	int count = m_pOwner->GetIpCount(peerIP);
	if (user.GetIpLimit() && count >= user.GetIpLimit())
	{
		CStdString str;
		if (count==1)
			str.Format(_T("Refusing connection. Reason: No more connections allowed from this IP. (%s already connected once)"), peerIP.c_str());
		else
			str.Format(_T("Refusing connection. Reason: No more connections allowed from this IP. (%s already connected %d times)"), peerIP.c_str(), count);
		SendStatus(str, 1);
		Send(_T("421 Refusing connection. No more connections allowed from your IP."));
		ForceClose(-1);
		return FALSE;
	}

	m_CurrentServerDir = m_pOwner->m_pPermissions->GetHomeDir(m_status.user);
	if (m_CurrentServerDir == _T(""))
	{
		Send(_T("550 Could not get home dir!"));
		ForceClose(-1);
		return FALSE;
	}

	m_status.ip = peerIP;

	count = GetUserCount(user.user);
	if (user.GetUserLimit() && count >= user.GetUserLimit())
	{
		CStdString str;
		str.Format(_T("Refusing connection. Reason: Maximum connection count (%d) reached for this user"), user.GetUserLimit());
		SendStatus(str, 1);
		str.Format(_T("421 Refusing connection. Maximum connection count reached for the user '%s'"), user.user);
		Send(str);
		ForceClose(-1);
		return FALSE;
	}

	m_pOwner->IncIpCount(peerIP);
	IncUserCount(m_status.user);
	m_status.loggedon = TRUE;

	GetSystemTime(&m_LastTransferTime);

	m_pOwner->m_pPermissions->AutoCreateDirs(m_status.user);

	t_connectiondata_changeuser *conndata = new t_connectiondata_changeuser;
	t_connop *op = new t_connop;
	op->data = conndata;
	op->op = USERCONTROL_CONNOP_CHANGEUSER;
	op->userid = m_userid;
	conndata->user = m_status.user;

	m_pOwner->SendNotification(FSM_CONNECTIONDATA, (LPARAM)op);

	return TRUE;
}

void CControlSocket::Continue()
{
	if (m_SlQuotas[download].bContinue)
	{
		TriggerEvent(FD_WRITE);
		if (m_transferstatus.socket && m_transferstatus.socket->Started())
			m_transferstatus.socket->TriggerEvent(FD_WRITE);
		m_SlQuotas[download].bContinue = false;
	}

	if (m_SlQuotas[upload].bContinue)
	{
		TriggerEvent(FD_READ);
		if (m_transferstatus.socket && m_transferstatus.socket->Started())
			m_transferstatus.socket->TriggerEvent(FD_READ);
		m_SlQuotas[upload].bContinue = false;
	}
}

int CControlSocket::GetSpeedLimit(sltype mode)
{
	CUser user;
	int nLimit = -1;
	if (m_status.loggedon && m_pOwner->m_pPermissions->GetUser(m_status.user, user))
	{
		nLimit = user.GetCurrentSpeedLimit(mode);
	}
	if (nLimit > 0)
	{
		nLimit *= 100;
		if (m_SlQuotas[mode].nTransferred >= nLimit)
		{
			m_SlQuotas[mode].bContinue = TRUE;
			return 0;
		}
		else
			nLimit -= m_SlQuotas[mode].nTransferred;
	}
	else
		nLimit = -1;
	if (user.BypassServerSpeedLimit(mode))
		m_SlQuotas[mode].bBypassed = TRUE;
	else if (m_SlQuotas[mode].nBytesAllowedToTransfer != -1)
	{
		if (nLimit == -1 || nLimit > (m_SlQuotas[mode].nBytesAllowedToTransfer - m_SlQuotas[mode].nTransferred))
			nLimit = m_SlQuotas[mode].nBytesAllowedToTransfer - m_SlQuotas[mode].nTransferred;
	}

	if (!nLimit)
		m_SlQuotas[mode].bContinue = TRUE;

	return nLimit;
}

BOOL CControlSocket::CreateTransferSocket(CTransferSocket *pTransferSocket)
{
	/* Create socket
	 * First try control connection port - 1, if that fails try
	 * control connection port + 1. If that fails as well, let
	 * the OS decide.
	 */
	bool bFallback = false;
	BOOL bCreated = FALSE;

	// Fix: Formerly, the data connection would always be opened using the server's default (primary) IP.
	// This would cause Windows Firewall to freak out if control connection was opened on a secondary IP.
	// When using Active FTP behind Windows Firewall, no connection could be made. This fix ensures the data
	// socket is on the same IP as the control socket.
	CStdString controlIP;
	UINT controlPort = 0;
	BOOL bResult = this->GetSockName(controlIP, controlPort);

	if (bResult)
	{
		// Try create control conn. port - 1
		if (controlPort > 1)
			if (pTransferSocket->Create(controlPort - 1, SOCK_STREAM, FD_CONNECT, controlIP, m_transferstatus.family, true))
				bCreated = TRUE;
	}
	if (!bCreated)
	{
creation_fallback:
		bFallback = true;
		// Let the OS find a valid port
		if (!pTransferSocket->Create(0, SOCK_STREAM, FD_CONNECT, controlIP, m_transferstatus.family, true))
		{
			// Give up
			Send(_T("421 Can't create socket"));
			ResetTransferstatus();
			return FALSE;
		}
	}
	if (m_pGssLayer && m_pGssLayer->AuthSuccessful())
		m_transferstatus.socket->UseGSS(m_pGssLayer);

	if (pTransferSocket->Connect(m_transferstatus.ip, m_transferstatus.port) == 0)
	{
		if (!bFallback && GetLastError() == WSAEADDRINUSE)
		{
			pTransferSocket->Close();
			goto creation_fallback;
		}

		if (GetLastError() != WSAEWOULDBLOCK)
		{
			Send(_T("425 Can't open data connection"));
			ResetTransferstatus();
			return FALSE;
		}
	}

	if (m_pSslLayer && m_bProtP)
		pTransferSocket->UseSSL(m_pSslLayer->GetContext());

	return TRUE;
}

bool CControlSocket::CheckIpForZlib()
{
	CStdString peerIP;
	UINT port = 0;
	BOOL bResult = GetPeerName(peerIP, port);
	if (!bResult)
		return false;

	if (!m_pOwner->m_pOptions->GetOptionVal(OPTION_MODEZ_ALLOWLOCAL) && !IsRoutableAddress(peerIP))
		return false;

	CStdString ips = m_pOwner->m_pOptions->GetOption(OPTION_MODEZ_DISALLOWED_IPS);
	ips += " ";

	int pos = ips.Find(' ');
	while (pos != -1)
	{
		CStdString blockedIP = ips.Left(pos);
		ips = ips.Mid(pos + 1);
		pos = ips.Find(' ');

		if (MatchesFilter(blockedIP, peerIP))
			return false;
	}

	return true;
}

void CControlSocket::AntiHammerIncrease(int amount /*=1*/)
{
	if (m_status.hammerValue < 8000)
		m_status.hammerValue += amount * 200;

	if (m_status.hammerValue > 2000)
		m_antiHammeringWaitTime += 1000 * (int)pow(1.3, (m_status.hammerValue / 400) - 5);
}

void CControlSocket::SendTransferinfoNotification(const char transfermode, const CStdString& physicalFile, const CStdString& logicalFile, __int64 startOffset, __int64 totalSize)
{
	t_connop *op = new t_connop;
	op->op = USERCONTROL_CONNOP_TRANSFERINIT;
	op->userid = m_userid;

	t_connectiondata_transferinfo *conndata = new t_connectiondata_transferinfo;
	conndata->transferMode = transfermode;
	conndata->physicalFile = physicalFile;
	conndata->logicalFile = logicalFile;
	conndata->startOffset = startOffset;
	conndata->totalSize = totalSize;
	op->data = conndata;

	m_pOwner->SendNotification(FSM_CONNECTIONDATA, (LPARAM)op);
}

int CControlSocket::OnLayerCallback(std::list<t_callbackMsg>& callbacks)
{
	for (std::list<t_callbackMsg>::iterator iter = callbacks.begin(); iter != callbacks.end(); iter++)
	{
		if (m_pSslLayer && iter->pLayer == m_pSslLayer)
		{
			if (iter->nType == LAYERCALLBACK_LAYERSPECIFIC && iter->nParam1 == SSL_INFO && iter->nParam2 == SSL_INFO_ESTABLISHED)
				SendStatus(_T("SSL connection established"), 0);
			else if (iter->nType == LAYERCALLBACK_LAYERSPECIFIC && iter->nParam1 == SSL_INFO && iter->nParam2 == SSL_INFO_SHUTDOWNCOMPLETE)
			{
				if (m_shutdown)
				{
					delete [] iter->str;
					Close();
					m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_DELSOCKET, m_userid);
					return 0;
				}
				if (!m_bQuitCommand)
				{
					delete [] iter->str;
					continue;
				}

				do
				{
					delete [] iter->str;
					iter++;
				} while (iter != callbacks.end());

				ForceClose(5);

				return 0;
			}
		}
		else if (iter->nType == LAYERCALLBACK_LAYERSPECIFIC && iter->nParam1 == SSL_VERBOSE_WARNING)
		{
			if (iter->str)
			{
				CStdString str = "SSL warning: ";
				str += iter->str;

				SendStatus(str, 1);
			}
		}
		delete [] iter->str;
	}
	return 0;//CAsyncSocketEx::OnLayerCallback(pLayer, nType, nParam1, nParam2);
}

bool CControlSocket::InitImplicitSsl()
{
	m_pSslLayer = new CAsyncSslSocketLayer;
	int res = AddLayer(m_pSslLayer) ? 1 : 0;
	if (!res)
	{
		delete m_pSslLayer;
		m_pSslLayer = 0;
		return false;
	}

	CString error;
#ifdef _UNICODE
	res = m_pSslLayer->SetCertKeyFile(ConvToLocal(m_pOwner->m_pOptions->GetOption(OPTION_SSLCERTFILE)), ConvToLocal(m_pOwner->m_pOptions->GetOption(OPTION_SSLKEYFILE)), ConvToLocal(m_pOwner->m_pOptions->GetOption(OPTION_SSLKEYPASS)), &error);
#else
	res = m_pSslLayer->SetCertKeyFile(m_pOwner->m_pOptions->GetOption(OPTION_SSLCERTFILE), m_pOwner->m_pOptions->GetOption(OPTION_SSLKEYFILE), m_pOwner->m_pOptions->GetOption(OPTION_SSLKEYPASS), &error);
#endif
	if (res == SSL_FAILURE_LOADDLLS)
		SendStatus(_T("Failed to load SSL libraries"), 1);
	else if (res == SSL_FAILURE_INITSSL)
		SendStatus(_T("Failed to initialize SSL libraries"), 1);
	else if (res == SSL_FAILURE_VERIFYCERT)
	{
		if (error != _T(""))
			SendStatus(error, 1);
		else
			SendStatus(_T("Failed to set certificate and private key"), 1);
	}
	if (res)
	{
		RemoveAllLayers();
		delete m_pSslLayer;
		m_pSslLayer = NULL;
		Send(_T("431 Could not initialize SSL connection"), 1);
		return false;
	}

	int code = m_pSslLayer->InitSSLConnection(false);
	if (code == SSL_FAILURE_LOADDLLS)
		SendStatus(_T("Failed to load SSL libraries"), 1);
	else if (code == SSL_FAILURE_INITSSL)
		SendStatus(_T("Failed to initialize SSL library"), 1);

	if (!code)
		return true;

	RemoveAllLayers();
	delete m_pSslLayer;
	m_pSslLayer = NULL;
	Send(_T("431 Could not initialize SSL connection"));

	//Close socket
	Close();
	SendStatus(_T("disconnected."), 0);
	m_pOwner->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_DELSOCKET, m_userid);

	return false;
}

bool CControlSocket::CanQuit()
{
	if (m_pSslLayer)
		return false;
	return true;
}

CStdString CControlSocket::GetPassiveIP()
{
	//Get the ip of the control socket
	CStdString localIP;
	UINT localPort;
	BOOL bValidSockAddr = GetSockName(localIP, localPort);

	//Get peer ip
	CStdString peerIP;
	UINT peerPort = 0;
	BOOL bResult = GetPeerName(peerIP, peerPort);
	if (bResult)
	{
		if (m_pOwner->m_pOptions->GetOptionVal(OPTION_NOEXTERNALIPONLOCAL) && !IsRoutableAddress(peerIP))
		{
			// Remote IP address from an unroutable subnet
			
			// Inside a NAT-in-NAT environment, two different unroutable address ranges are used.
			// If remote address comes from a different unroutable subnet, don't use local
			// address.
			// Note that in a NAT-in-NAT environment, the external IP address specified will either
			// be the worldwide one or the NAT one. Either external or single-NATed users won't be able
			// to use passive mode.
			m_transferstatus.usedResolvedIP = false;

			if (!bValidSockAddr)
				return _T("");
			return localIP;
		}
	}

	if (m_pOwner->m_pOptions->GetOptionVal(OPTION_CUSTOMPASVIPTYPE))
	{
		CStdString pasvIP = m_pOwner->GetExternalIP(localIP);
		if (pasvIP != _T("") && pasvIP != localIP)
		{
			m_transferstatus.usedResolvedIP = true;
			return pasvIP;
		}
	}

	m_transferstatus.usedResolvedIP = false;

	if (!bValidSockAddr)
		return _T("");

	return localIP;
}

void CControlSocket::ParseMlstOpts(CStdString args)
{
	if (args == _T(""))
	{
		for (int i = 0; i < 4; i++)
			m_facts[i] = false;
		Send(_T("200 MLST OPTS"));
		return;
	}
	if (args[0] != ' ')
	{
		Send(_T("501 Invalid MLST options"));
		return;
	}
	args = args.Mid(1);
	if (args.Find(' ') != -1)
	{
		Send(_T("501 Invalid MLST options"));
		return;
	}

	bool facts[4] = {0};
	while (args != _T(""))
	{
		int pos = args.Find(';');
		if (pos < 1)
		{
			Send(_T("501 Invalid MLST options"));
			return;
		}

		CStdString fact = args.Left(pos);
		args = args.Mid(pos + 1);

		if (fact == _T("TYPE"))
			facts[fact_type] = true;
		else if (fact == _T("SIZE"))
			facts[fact_size] = true;
		else if (fact == _T("MODIFY"))
			facts[fact_modify] = true;
		//else if (fact == _T("PERM"))
		//	facts[fact_perm] = true;
	}

	for (int i = 0; i < 4; i++)
		m_facts[i] = facts[i];

	CStdString factstr;
	if (facts[fact_type])
		factstr += _T("type;");
	if (facts[fact_size])
		factstr += _T("size;");
	if (facts[fact_modify])
		factstr += _T("modify;");
	if (facts[fact_perm])
		factstr += _T("perm;");
	
	CStdString result = _T("200 MLST OPTS");
	if (factstr != _T(""))
		result += _T(" ") + factstr;

	Send(result);
}

void CControlSocket::ParseHashOpts(CStdString args)
{
	if (args == _T(""))
	{
		switch (m_hash_algorithm)
		{
		case CHashThread::MD5:
			Send(_T("200 MD5"));
			break;
		case CHashThread::SHA512:
			Send(_T("200 SHA-512"));
			break;
		default:
			Send(_T("200 SHA-1"));
			break;
		}
		return;
	}
	if (args[0] != ' ')
	{
		Send(_T("501 Invalid HASH options"));
		return;
	}
	args = args.Mid(1);
	if (args.Find(' ') != -1)
	{
		Send(_T("501 Invalid HASH options"));
		return;
	}

	if (args == _T("SHA-1"))
	{
		m_hash_algorithm = CHashThread::SHA1;
		Send(_T("200 Hash algorithm set to SHA-1"));
	}
	else if (args == _T("SHA-512"))
	{
		m_hash_algorithm = CHashThread::SHA512;
		Send(_T("200 Hash algorithm set to SHA-512"));
	}
	else if (args == _T("MD5"))
	{
		m_hash_algorithm = CHashThread::MD5;
		Send(_T("200 Hash algorithm set to MD5"));
	}
	else
		Send(_T("501 Unknown algorithm"));
}

void CControlSocket::ProcessHashResult(int hash_id, int res, CHashThread::_algorithm alg, const CStdString& hash, const CStdString& file)
{
	if (hash_id != m_hash_id)
		return;
	
	m_hash_id = 0;

	if (res == CHashThread::BUSY)
		Send(_T("450 Another hash operation is already in progress."));
	else if (res == CHashThread::FAILURE_OPEN)
		Send(_T("550 Failed to open file"));
	else if (res == CHashThread::FAILURE_READ)
		Send(_T("550 Could not read from file"));
	else
	{
		CStdString algname;
		switch (alg)
		{
		case CHashThread::SHA1:
			algname = "SHA-1";
			break;
		case CHashThread::SHA512:
			algname = "SHA-512";
			break;
		case CHashThread::MD5:
			algname = "MD5";
			break;
		}
		Send(_T("213 ") + algname + _T(" ") + hash + _T(" ") + file);
	}
}
