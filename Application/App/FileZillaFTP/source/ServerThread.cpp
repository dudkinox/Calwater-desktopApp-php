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

// ServerThread.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "iputils.h"
#include "ServerThread.h"
#include "ControlSocket.h"
#include "transfersocket.h"
#include "Options.h"
#include "version.h"
#include "Permissions.h"
#include "ExternalIpCheck.h"
#include "autobanmanager.h"
#include "hash_thread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

std::map<int, t_socketdata> CServerThread::m_userids;
CCriticalSectionWrapper CServerThread::m_GlobalThreadsync;
std::map<CStdString, int> CServerThread::m_userIPs;
std::list<CServerThread*> CServerThread::m_sInstanceList;
std::map<CStdString, int> CServerThread::m_antiHammerInfo;
CHashThread* CServerThread::m_hashThread = 0;

/////////////////////////////////////////////////////////////////////////////
// CServerThread

CServerThread::CServerThread(int nNotificationMessageId)
{
	m_nNotificationMessageId = nNotificationMessageId;
	m_pOptions = 0;
	m_pAutoBanManager = 0;
}

CServerThread::~CServerThread()
{
}

BOOL CServerThread::InitInstance()
{
	BOOL res = TRUE;
	WSADATA wsaData;
	
	WORD wVersionRequested = MAKEWORD(1, 1);
	int nResult = WSAStartup(wVersionRequested, &wsaData);
	if (nResult != 0)
		res=FALSE;
	else if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		res=FALSE;
	}
	
	m_timerid = SetTimer(0, 0, 1000, 0);
	m_nRateTimer = SetTimer(0, 0, 100, 0);

	// Reduce anti hammer value twice an hour
	m_antiHammerTimer = SetTimer(0, 0, 1800 * 1000, 0);

	m_bQuit = FALSE;
	m_nRecvCount = 0;
	m_nSendCount = 0;
	m_pOptions = new COptions;
	m_pAutoBanManager = new CAutoBanManager(m_pOptions);
	m_pPermissions = new CPermissions;

	EnterCritSection(m_GlobalThreadsync);
	if (m_sInstanceList.empty())
		m_bIsMaster = TRUE;
	else
		m_bIsMaster = FALSE;
	m_sInstanceList.push_back(this);
	LeaveCritSection(m_GlobalThreadsync);

	m_nLoopCount = 0;

	EnterCritSection(m_threadsync);
	if (!m_bIsMaster)
		m_pExternalIpCheck = NULL;
	else
	{
		m_pExternalIpCheck = new CExternalIpCheck(this);
		m_hashThread = new CHashThread();
	}
	LeaveCritSection(m_threadsync);

	m_throttled = 0;

	return TRUE;
}

DWORD CServerThread::ExitInstance()
{
	ASSERT(m_pPermissions);
	delete m_pPermissions;
	m_pPermissions=0;
	delete m_pAutoBanManager;
	m_pAutoBanManager = 0;
	delete m_pOptions;
	m_pOptions=0;
	KillTimer(0, m_timerid);
	KillTimer(0, m_nRateTimer);
	WSACleanup();
	m_hashThread->Stop(this);

	if (m_bIsMaster)
	{
		EnterCritSection(m_threadsync);
		delete m_pExternalIpCheck;
		m_pExternalIpCheck = NULL;
		LeaveCritSection(m_threadsync);
	}

	EnterCritSection(m_GlobalThreadsync);
	m_sInstanceList.remove(this);
	if (!m_sInstanceList.empty())
		m_sInstanceList.front()->m_bIsMaster = TRUE;
	else
	{
		delete m_hashThread;
		m_hashThread = 0;
	}
	LeaveCritSection(m_GlobalThreadsync);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CServerThread 

const int CServerThread::GetNumConnections()
{
	EnterCritSection(m_threadsync);
	int num = m_LocalUserIDs.size();
	LeaveCritSection(m_threadsync);
	return num;
}

void CServerThread::AddSocket(SOCKET sockethandle, bool ssl)
{
	PostThreadMessage(WM_FILEZILLA_THREADMSG, ssl ? FTM_NEWSOCKET_SSL : FTM_NEWSOCKET, (LPARAM)sockethandle);
}

#define IDMAX 1000000000
int CServerThread::CalcUserID()
{
	if (m_userids.size() >= IDMAX)
		return -1;
	static int curid=0;
	curid++;
	if (curid==IDMAX)
		curid=1;
	while (m_userids.find(curid) != m_userids.end())
	{
		curid++;
		if (curid == IDMAX)
			curid=1;
	}
	return curid;
}

void CServerThread::AddNewSocket(SOCKET sockethandle, bool ssl)
{
	CControlSocket *socket = new CControlSocket(this);
	if (!socket->Attach(sockethandle))
	{
		socket->SendStatus(_T("Failed to attach socket."), 1);
		closesocket(sockethandle);
		return;
	}

	CStdString ip;
	UINT port = 0;
	if (socket->GetPeerName(ip, port))
	{
		if (socket->GetFamily() == AF_INET6)
			ip = GetIPV6ShortForm(ip);
		socket->m_RemoteIP = ip;
	}
	else
	{
		socket->m_RemoteIP = _T("ip unknown");
		socket->m_userid = 0;
		socket->SendStatus(_T("Can't get remote IP, disconnected"), 1);
		socket->Close();
		delete socket;
		return;
	}
	EnterCritSection(m_GlobalThreadsync);
	int userid = CalcUserID();
	if (userid == -1)
	{
		LeaveCritSection(m_GlobalThreadsync);
		socket->m_userid = 0;
		socket->SendStatus(_T("Refusing connection, server too busy!"), 1);
		socket->Send(_T("421 Server too busy, closing connection. Please retry later!"));
		socket->Close();
		delete socket;
		return;
	}
	socket->m_userid = userid;
	t_socketdata data;
	data.pSocket = socket;
	data.pThread = this;
	m_userids[userid] = data;

	// Check if remote IP is blocked due to hammering
	std::map<CStdString, int>::const_iterator iter = m_antiHammerInfo.find(ip);
	if (iter != m_antiHammerInfo.end() && iter->second > 10)
		socket->AntiHammerIncrease(25); // ~6 secs delay
	LeaveCritSection(m_GlobalThreadsync);
	EnterCritSection(m_threadsync);
	m_LocalUserIDs[userid] = socket;
	LeaveCritSection(m_threadsync);

	t_connectiondata_add *conndata = new t_connectiondata_add;
	t_connop *op = new t_connop;
	op->data = conndata;
	op->op = USERCONTROL_CONNOP_ADD;
	op->userid = userid;
	conndata->pThread = this;

	conndata->port = port;
	_tcscpy(conndata->ip, socket->m_RemoteIP);

	SendNotification(FSM_CONNECTIONDATA, (LPARAM)op);

	if (ssl && !socket->InitImplicitSsl())
		return;

	socket->AsyncSelect(FD_READ|FD_WRITE|FD_CLOSE);
	socket->SendStatus(_T("Connected, sending welcome message..."), 0);

	CStdString msg;
	if (m_pOptions->GetOptionVal(OPTION_ENABLE_HASH))
		msg = _T("EXPERIMANTAL BUILD\nNOT FOR PRODUCTION USE\n\nImplementing draft-bryan-ftp-hash-06");
	else
		msg = m_pOptions->GetOption(OPTION_WELCOMEMESSAGE);
	if (m_RawWelcomeMessage != msg)
	{
		m_RawWelcomeMessage = msg;
		m_ParsedWelcomeMessage.clear();

		msg.Replace(_T("%%"), _T("\001"));
		msg.Replace(_T("%v"), GetVersionString());
		msg.Replace(_T("\001"), _T("%"));

		ASSERT(msg != _T(""));
		int oldpos = 0;
		msg.Replace(_T("\r\n"), _T("\n"));
		int pos = msg.Find(_T("\n"));
		CStdString line;
		while (pos != -1)
		{
			ASSERT(pos);
			m_ParsedWelcomeMessage.push_back(_T("220-") +  msg.Mid(oldpos, pos-oldpos) );
			oldpos = pos + 1;
			pos = msg.Find(_T("\n"), oldpos);
		}

		line = msg.Mid(oldpos);
		if (line != _T(""))
			m_ParsedWelcomeMessage.push_back(_T("220 ") + line);		
		else
		{
			m_ParsedWelcomeMessage.back()[3] = 0;
		}
	}

	bool hideStatus = m_pOptions->GetOptionVal(OPTION_WELCOMEMESSAGE_HIDE) != 0;
	ASSERT(!m_ParsedWelcomeMessage.empty());
	for (std::list<CStdString>::iterator iter = m_ParsedWelcomeMessage.begin(); iter != m_ParsedWelcomeMessage.end(); iter++)
		if (!socket->Send(*iter, !hideStatus))
			break;
}

int CServerThread::OnThreadMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg == WM_FILEZILLA_THREADMSG)
	{
		if (wParam == FTM_NEWSOCKET) //Add a new socket to this thread
			AddNewSocket((SOCKET)lParam, false);
		else if (wParam == FTM_NEWSOCKET_SSL) //Add a new socket to this thread
			AddNewSocket((SOCKET)lParam, true);
		else if (wParam==FTM_DELSOCKET) //Remove a socket from this thread
		{
			CControlSocket *socket=GetControlSocket(lParam);
			EnterCritSection(m_threadsync);
			if (m_LocalUserIDs.find(lParam)!=m_LocalUserIDs.end())
				m_LocalUserIDs.erase(m_LocalUserIDs.find(lParam));
			LeaveCritSection(m_threadsync);
			if (socket)
			{
				socket->Close();
				EnterCritSection(m_GlobalThreadsync);
				if (m_userids.find(lParam)!=m_userids.end())
					m_userids.erase(m_userids.find(lParam));
				LeaveCritSection(m_GlobalThreadsync);
				delete socket;
			}
			EnterCritSection(m_threadsync);
			if (m_bQuit)
			{
				int count=m_LocalUserIDs.size();
				LeaveCritSection(m_threadsync);
				if (!count)
					SendNotification(FSM_THREADCANQUIT, (LPARAM)this);
			}
			else
				LeaveCritSection(m_threadsync);
		}
		else if (wParam==FTM_COMMAND)
		{ //Process a command sent from a client
			CControlSocket *socket=GetControlSocket(lParam);
			if (socket)
				socket->ParseCommand();
		}
		else if (wParam==FTM_TRANSFERMSG)
		{
			CControlSocket *socket=GetControlSocket(lParam);
			if (socket)
				socket->ProcessTransferMsg();
		}
		else if (wParam==FTM_GOOFFLINE)
		{
			EnterCritSection(m_threadsync);
			m_bQuit = TRUE;
			int count = m_LocalUserIDs.size();
			if (!count)
			{
				LeaveCritSection(m_threadsync);
				SendNotification(FSM_THREADCANQUIT, (LPARAM)this);
				return 0;
			}
			if (lParam==2)
			{
				LeaveCritSection(m_threadsync);
				return 0;
			}
			for (std::map<int, CControlSocket *>::iterator iter=m_LocalUserIDs.begin(); iter!=m_LocalUserIDs.end(); iter++)
			{
				switch (lParam)
				{
				case 2:
					iter->second->WaitGoOffline(false);
					break;
				case 0:
				default:
					iter->second->ForceClose(0);
					break;
				case 1:
					iter->second->WaitGoOffline(true);
					break;
				}
			}
			LeaveCritSection(m_threadsync);
		}
		else if (wParam == FTM_CONTROL)
			ProcessControlMessage((t_controlmessage *)lParam);
		else if (wParam == FTM_HASHRESULT)
		{
			CHashThread::_algorithm alg;
			CStdString hash;
			CStdString file;
			int hash_res = GetHashThread().GetResult(lParam, alg, hash, file);
			EnterCritSection(m_threadsync);

			for (std::map<int, CControlSocket *>::iterator iter = m_LocalUserIDs.begin(); iter != m_LocalUserIDs.end(); iter++)
			{
				iter->second->ProcessHashResult(lParam, hash_res, alg, hash, file);
			}
			LeaveCritSection(m_threadsync);
		}
	}
	else if (Msg == WM_TIMER)
		OnTimer(wParam, lParam);
	return 0;
}

void CServerThread::OnTimer(WPARAM wParam,LPARAM lParam)
{
	if (wParam == m_timerid)
	{
		EnterCritSection(m_threadsync);
		
		/* 
		 * Check timeouts and collect transfer file offsets.
		 * Do both in the same loop to save performance.
		 */

		/*
		 * Maximum memory required for file offsets:
		 * 2 unused prefix bytes, will be filled by CServer,
		 * This avoids buffer copying.
		 * For each connection 4 bytes for the userid
		 * and 8 for the offset.
		 * We do not need to store the number of elements, this
		 * information can be calculated from the length if neccessary.
		 */
		int bufferLen = 2 + m_LocalUserIDs.size() * 12;
		unsigned char* buffer = new unsigned char[bufferLen];
		unsigned char* p = buffer + 2;
		for (std::map<int, CControlSocket *>::iterator iter = m_LocalUserIDs.begin(); iter != m_LocalUserIDs.end(); iter++)
		{
			CControlSocket* pSocket = iter->second;
			CTransferSocket* pTransferSocket = pSocket->GetTransferSocket();
			if (pTransferSocket && pTransferSocket->WasActiveSinceCheck())
			{
				memcpy(p, &iter->first, 4);
				p += 4;
				__int64 offset = pTransferSocket->GetCurrentFileOffset();
				memcpy(p, &offset, 8);
				p += 8;
			}
			iter->second->CheckForTimeout();
		}
		
		if ((p - buffer) <= 2)
			delete [] buffer;
		else
		{
			t_connectiondata_transferoffsets* conndata = new t_connectiondata_transferoffsets;
			conndata->pData = buffer;
			conndata->len = p - buffer;
			t_connop* op = new t_connop;
			op->data = conndata;
			op->op = USERCONTROL_CONNOP_TRANSFEROFFSETS;
			SendNotification(FSM_CONNECTIONDATA, (LPARAM)op);
		}

		LeaveCritSection(m_threadsync);

		// Check if master thread has changed
		if (m_bIsMaster && !m_pExternalIpCheck)
		{
			EnterCritSection(m_threadsync);
			m_pExternalIpCheck = new CExternalIpCheck(this);
			LeaveCritSection(m_threadsync);
		}
	}
	else if (wParam==m_nRateTimer)
	{
		if (m_nSendCount)
		{	
			SendNotification(FSM_SEND, m_nSendCount);
			m_nSendCount = 0;
		}
		if (m_nRecvCount)
		{	
			SendNotification(FSM_RECV, m_nRecvCount);
			m_nRecvCount = 0;
		}

		if (m_bIsMaster)
		{
			EnterCritSection(m_GlobalThreadsync);

			std::list<CServerThread *>::iterator iter;

			//Only update the speed limits from the rule set every 2 seconds to improve performance
			if (!m_nLoopCount)
			{
				m_lastLimits[download] = m_pOptions->GetCurrentSpeedLimit(download);
				m_lastLimits[upload] = m_pOptions->GetCurrentSpeedLimit(upload);
			}
			++m_nLoopCount %= 20;

			// Gather transfer statistics if a speed limit is set
			if (m_lastLimits[download] != -1 || m_lastLimits[upload] != -1)
				for (iter = m_sInstanceList.begin(); iter != m_sInstanceList.end(); iter++)
				{
					CServerThread *pThread = *iter;
					EnterCritSection(pThread->m_threadsync);
					pThread->GatherTransferedBytes();
					LeaveCritSection(pThread->m_threadsync);
				}

			for (int i = 0; i < 2; i++)
			{
				int limit = m_lastLimits[i];

				if (limit == -1)
				{
					for (iter = m_sInstanceList.begin(); iter != m_sInstanceList.end(); iter++)
					{
						CServerThread *pThread = *iter;
						EnterCritSection(pThread->m_threadsync);
						pThread->m_SlQuotas[i].nBytesAllowedToTransfer = -1;
						pThread->m_SlQuotas[i].nTransferred = 0;
						LeaveCritSection(pThread->m_threadsync);
					}
					continue;
				}

				limit *= 100;
				
				int nRemaining = limit;
				int nThreadLimit = limit / m_sInstanceList.size();
				
				std::list<CServerThread *> fullUsageList;
				
				for (iter = m_sInstanceList.begin(); iter != m_sInstanceList.end(); iter++)
				{
					CServerThread *pThread = *iter;
					EnterCritSection(pThread->m_threadsync);
					int r = pThread->m_SlQuotas[i].nBytesAllowedToTransfer - pThread->m_SlQuotas[i].nTransferred;
					if ( r > 0 && pThread->m_SlQuotas[i].nBytesAllowedToTransfer <= nThreadLimit)
					{
						pThread->m_SlQuotas[i].nBytesAllowedToTransfer = nThreadLimit;
						nRemaining -= pThread->m_SlQuotas[i].nTransferred;
						pThread->m_SlQuotas[i].nTransferred = 0;
					}
					else if (r > 0 && pThread->m_SlQuotas[i].nTransferred < nThreadLimit)
					{
						pThread->m_SlQuotas[i].nBytesAllowedToTransfer = nThreadLimit;
						nRemaining -= pThread->m_SlQuotas[i].nTransferred;
						pThread->m_SlQuotas[i].nTransferred = 0;
					}
					else
					{
						fullUsageList.push_back(pThread);
						// Don't unlock thread here, do it later
						continue;
					}
					LeaveCritSection(pThread->m_threadsync);
				}
				
				// fullUsageList now contains all threads which did use up its assigned quota
				std::list<CServerThread *> fullUsageList2;
				if (!fullUsageList.empty())
				{
					nThreadLimit = nRemaining / fullUsageList.size();
					for (iter = fullUsageList.begin(); iter != fullUsageList.end(); iter++)
					{	
						CServerThread *pThread = *iter;

						// Thread has already been locked
						int r = pThread->m_SlQuotas[i].nBytesAllowedToTransfer - pThread->m_SlQuotas[i].nTransferred;
						if (r > 0)
						{
							if (pThread->m_SlQuotas[i].nTransferred > nThreadLimit)
								pThread->m_SlQuotas[i].nBytesAllowedToTransfer = nThreadLimit;
							else
								pThread->m_SlQuotas[i].nBytesAllowedToTransfer = pThread->m_SlQuotas[i].nTransferred;
							pThread->m_SlQuotas[i].nTransferred = 0;
							nRemaining -= pThread->m_SlQuotas[i].nBytesAllowedToTransfer;
						}
						else
						{
							fullUsageList2.push_back(pThread);
							// Don't unlock thread here either, do it later
							continue;
						}
						LeaveCritSection(pThread->m_threadsync);
					}
					
					if (!fullUsageList2.empty())
					{
						nThreadLimit = nRemaining / fullUsageList2.size();
						for (iter = fullUsageList2.begin(); iter != fullUsageList2.end(); iter++)
						{	
							CServerThread *pThread = *iter;
							pThread->m_SlQuotas[i].nTransferred = 0;
							pThread->m_SlQuotas[i].nBytesAllowedToTransfer = nThreadLimit;

							// Finally unlock threads
							LeaveCritSection(pThread->m_threadsync);
						}
					}
				}
			}
			
			LeaveCritSection(m_GlobalThreadsync);
		}
		ProcessNewSlQuota();
	}
	else if (m_pExternalIpCheck && wParam == m_pExternalIpCheck->GetTimerID())
	{
		EnterCritSection(m_threadsync);
		m_pExternalIpCheck->OnTimer();
		LeaveCritSection(m_threadsync);
	}
	else if (wParam == m_antiHammerTimer && m_bIsMaster)
		AntiHammerDecrease();
}

const int CServerThread::GetGlobalNumConnections()
{
	EnterCritSection(m_GlobalThreadsync);
	int num=m_userids.size();
	LeaveCritSection(m_GlobalThreadsync);
	return num;
}

CControlSocket * CServerThread::GetControlSocket(int userid)
{
	CControlSocket *ret=0;
	EnterCritSection(m_threadsync);
	std::map<int, CControlSocket *>::iterator iter=m_LocalUserIDs.find(userid);
	if (iter!=m_LocalUserIDs.end())
		ret=iter->second;
	LeaveCritSection(m_threadsync);
	return ret;
}

void CServerThread::ProcessControlMessage(t_controlmessage *msg)
{
	if (msg->command == USERCONTROL_KICK)
	{
		CControlSocket *socket = GetControlSocket(msg->socketid);
		if (socket)
			socket->ForceClose(4);
	}
	delete msg;
}

BOOL CServerThread::IsReady()
{
	return !m_bQuit;
}

int CServerThread::GetIpCount(const CStdString &ip) const
{
	int count=0;
	EnterCritSection(m_GlobalThreadsync);
	std::map<CStdString, int>::iterator iter=m_userIPs.find(ip);
	if (iter!=m_userIPs.end())
		count=iter->second;
	LeaveCritSection(m_GlobalThreadsync);
	return count;
}

void CServerThread::IncIpCount(const CStdString &ip)
{
	int count;
	EnterCritSection(m_GlobalThreadsync);
	std::map<CStdString, int>::iterator iter=m_userIPs.find(ip);
	if (iter!=m_userIPs.end())
		count=iter->second++;
	else
		m_userIPs[ip]=1;
	LeaveCritSection(m_GlobalThreadsync);
}

void CServerThread::DecIpCount(const CStdString &ip)
{
	EnterCritSection(m_GlobalThreadsync);
	std::map<CStdString, int>::iterator iter=m_userIPs.find(ip);
	ASSERT(iter!=m_userIPs.end());
	if (iter==m_userIPs.end())
	{
		LeaveCritSection(m_GlobalThreadsync);
		return;
	}
	else
	{
		ASSERT(iter->second);
		if (iter->second)
			iter->second--;
	}
	LeaveCritSection(m_GlobalThreadsync);
}

void CServerThread::IncSendCount(int count)
{
	m_nSendCount += count;
}

void CServerThread::IncRecvCount(int count)
{
	m_nRecvCount += count;
}

void CServerThread::ProcessNewSlQuota()
{
	EnterCritSection(m_threadsync);

	std::map<int, CControlSocket *>::iterator iter;

	for (int i = 0; i < 2; i++)
	{
		if (m_SlQuotas[i].nBytesAllowedToTransfer == -1)
		{
			for (iter = m_LocalUserIDs.begin(); iter != m_LocalUserIDs.end(); iter++)
			{
				CControlSocket *pControlSocket = iter->second;
				pControlSocket->m_SlQuotas[i].nBytesAllowedToTransfer = -1;
				pControlSocket->m_SlQuotas[i].nTransferred = 0;
			}
			continue;
		}
	
		int nRemaining = m_SlQuotas[i].nBytesAllowedToTransfer;
		int nThreadLimit = nRemaining / m_sInstanceList.size();
			
		std::list<CControlSocket *> fullUsageList;
		
		for (iter = m_LocalUserIDs.begin(); iter != m_LocalUserIDs.end(); iter++)
		{
			CControlSocket *pControlSocket = iter->second;
			int r = pControlSocket->m_SlQuotas[i].nBytesAllowedToTransfer - pControlSocket->m_SlQuotas[i].nTransferred;
			if (pControlSocket->m_SlQuotas[i].nBytesAllowedToTransfer == -1)
			{
				pControlSocket->m_SlQuotas[i].nBytesAllowedToTransfer = nThreadLimit;
				pControlSocket->m_SlQuotas[i].nTransferred = 0;
			}
			else if (r > 0 && pControlSocket->m_SlQuotas[i].nBytesAllowedToTransfer <= nThreadLimit)
			{
				pControlSocket->m_SlQuotas[i].nBytesAllowedToTransfer = nThreadLimit;
				nRemaining -= pControlSocket->m_SlQuotas[i].nTransferred;
				pControlSocket->m_SlQuotas[i].nTransferred = 0;
			}
			else if (r > 0 && pControlSocket->m_SlQuotas[i].nTransferred < nThreadLimit)
			{
				pControlSocket->m_SlQuotas[i].nBytesAllowedToTransfer = nThreadLimit;
				nRemaining -= pControlSocket->m_SlQuotas[i].nTransferred;
				pControlSocket->m_SlQuotas[i].nTransferred = 0;
			}
			else
			{
				fullUsageList.push_back(pControlSocket);
				continue;
			}
		}
		
		std::list<CControlSocket *> fullUsageList2;
		if (!fullUsageList.empty())
		{
			std::list<CControlSocket *>::iterator iter;
			
			nThreadLimit = nRemaining / fullUsageList.size();
			for (iter = fullUsageList.begin(); iter != fullUsageList.end(); iter++)
			{	
				CControlSocket *pControlSocket = *iter;
				int r = pControlSocket->m_SlQuotas[i].nBytesAllowedToTransfer - pControlSocket->m_SlQuotas[i].nTransferred;
				if (r)
				{
					if (pControlSocket->m_SlQuotas[i].nTransferred > nThreadLimit)
						pControlSocket->m_SlQuotas[i].nBytesAllowedToTransfer = nThreadLimit;
					else
						pControlSocket->m_SlQuotas[i].nBytesAllowedToTransfer = pControlSocket->m_SlQuotas[i].nTransferred;
					pControlSocket->m_SlQuotas[i].nTransferred = 0;
					nRemaining -= pControlSocket->m_SlQuotas[i].nBytesAllowedToTransfer;
				}
				else
				{
					fullUsageList2.push_back(pControlSocket);
					continue;
				}
			}
			
			if (!fullUsageList2.empty())
			{
				nThreadLimit = nRemaining / fullUsageList2.size();
				for (iter = fullUsageList2.begin(); iter != fullUsageList2.end(); iter++)
				{	
					CControlSocket *pControlSocket = *iter;
					pControlSocket->m_SlQuotas[i].nTransferred = 0;
					pControlSocket->m_SlQuotas[i].nBytesAllowedToTransfer = nThreadLimit;
				}
			}
		}
	}
	
	for (iter = m_LocalUserIDs.begin(); iter != m_LocalUserIDs.end(); iter++)
	{
		CControlSocket *pControlSocket = iter->second;
		pControlSocket->Continue();
	}

	LeaveCritSection(m_threadsync);
}

void CServerThread::GatherTransferedBytes()
{
	EnterCritSection(m_threadsync);
	for (std::map<int, CControlSocket *>::iterator iter = m_LocalUserIDs.begin(); iter != m_LocalUserIDs.end(); iter++)
	{
		for (int i = 0; i < 2; i++)
		{
			if (iter->second->m_SlQuotas[i].nBytesAllowedToTransfer != -1)
				if (iter->second->m_SlQuotas[i].bBypassed)
					iter->second->m_SlQuotas[i].nTransferred = 0;
				else
					m_SlQuotas[i].nTransferred += iter->second->m_SlQuotas[i].nTransferred;

			iter->second->m_SlQuotas[i].bBypassed = false;
		}
	}
	LeaveCritSection(m_threadsync);
}

CStdString CServerThread::GetExternalIP(const CStdString& localIP)
{
	CStdString ip;
	EnterCritSection(m_threadsync);
	if (m_pExternalIpCheck)
	{
		ip = m_pExternalIpCheck->GetIP(localIP);
		LeaveCritSection(m_threadsync);
	}
	else
	{
		LeaveCritSection(m_threadsync);
		EnterCritSection(m_GlobalThreadsync);
		CServerThread *pThread = m_sInstanceList.front();
		EnterCritSection(pThread->m_threadsync);
		if (pThread != this && pThread->m_pExternalIpCheck)
			ip = pThread->m_pExternalIpCheck->GetIP(localIP);
		LeaveCritSection(pThread->m_threadsync);
		LeaveCritSection(m_GlobalThreadsync);
	}

	return ip;
}

void CServerThread::ExternalIPFailed()
{
	CStdString ip;
	EnterCritSection(m_threadsync);
	if (m_pExternalIpCheck)
	{
		m_pExternalIpCheck->TriggerUpdate();
		LeaveCritSection(m_threadsync);
	}
	else
	{
		LeaveCritSection(m_threadsync);
		EnterCritSection(m_GlobalThreadsync);
		CServerThread *pThread = m_sInstanceList.front();
		EnterCritSection(pThread->m_threadsync);
		if (pThread != this && pThread->m_pExternalIpCheck)
			pThread->m_pExternalIpCheck->TriggerUpdate();
		LeaveCritSection(pThread->m_threadsync);
		LeaveCritSection(m_GlobalThreadsync);
	}
}

void CServerThread::SendNotification(WPARAM wParam, LPARAM lParam)
{
	EnterCritSection(m_threadsync);
	t_Notification notification;
	notification.wParam = wParam;
	notification.lParam = lParam;

	if (m_pendingNotifications.empty())
		PostMessage(hMainWnd, m_nNotificationMessageId, 0, 0);

	m_pendingNotifications.push_back(notification);

	// Check if main thread can't handle number of notifications fast enough, throttle thread if neccessary
	if (m_pendingNotifications.size() > 200 && m_throttled < 3)
	{
		SetPriority(THREAD_PRIORITY_IDLE);
		m_throttled = 3;
	}
	else if (m_pendingNotifications.size() > 150 && m_throttled < 2)
	{
		SetPriority(THREAD_PRIORITY_LOWEST);
		m_throttled = 2;
	}
	else if (m_pendingNotifications.size() > 100 && !m_throttled)
	{
		SetPriority(THREAD_PRIORITY_BELOW_NORMAL);
		m_throttled = 1;
	}
	
	LeaveCritSection(m_threadsync);
}

void CServerThread::GetNotifications(std::list<CServerThread::t_Notification>& list)
{
	EnterCritSection(m_threadsync);

	m_pendingNotifications.swap(list);

	if (m_throttled)
		SetPriority(THREAD_PRIORITY_NORMAL);

	LeaveCritSection(m_threadsync);
}

void CServerThread::AntiHammerIncrease(const CStdString& ip)
{
	EnterCritSection(m_GlobalThreadsync);

	std::map<CStdString, int>::iterator iter = m_antiHammerInfo.find(ip);
	if (iter != m_antiHammerInfo.end())
	{
		if (iter->second < 20)
			iter->second++;
		LeaveCritSection(m_GlobalThreadsync);
		return;
	}
	if (m_antiHammerInfo.size() >= 1000)
	{
		std::map<CStdString, int>::iterator best = m_antiHammerInfo.begin();
		for (iter = m_antiHammerInfo.begin(); iter != m_antiHammerInfo.end(); iter++)
		{
			if (iter->second < best->second)
				best = iter;
		}
		m_antiHammerInfo.erase(best);
	}
	m_antiHammerInfo.insert(std::make_pair(ip, 1));

	LeaveCritSection(m_GlobalThreadsync);
}

void CServerThread::AntiHammerDecrease()
{
	EnterCritSection(m_GlobalThreadsync);

	std::map<CStdString, int>::iterator iter = m_antiHammerInfo.begin();
	while (iter != m_antiHammerInfo.end())
	{
		if (iter->second > 1)
		{
			--(iter->second);
			++iter;
		}
		else
			m_antiHammerInfo.erase(iter++);
	}
	
	LeaveCritSection(m_GlobalThreadsync);
}

CHashThread& CServerThread::GetHashThread()
{
	return *m_hashThread;
}
