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

// Server.cpp: Implementierung der Klasse CServer.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Server.h"
#include "Options.h"
#include "ServerThread.h"
#include "ListenSocket.h"
#include "AdminListenSocket.h"
#include "AdminInterface.h"
#include "AdminSocket.h"
#include "Permissions.h"
#include "FileLogger.h"
#include "version.h"
#include "defs.h"
#include "iputils.h"
#include "autobanmanager.h"

#ifndef MB_SERVICE_NOTIFICATION
#define MB_SERVICE_NOTIFICATION          0x00040000L
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CServer::CServer()
{
	m_hWnd=0;
	m_pOptions = NULL;
	m_pAdminInterface = new CAdminInterface(this);
	m_nServerState = 0;
	m_bQuit = FALSE;

	m_nSendCount = m_nRecvCount = 0;
	m_nTimerID = 0;
	m_nBanTimerID = 0;

	// Since this thread has to handle notifications, increase it's priority
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);

	m_pAutoBanManager = 0;
}

CServer::~CServer()
{
	for (std::list<CListenSocket*>::iterator iter = m_ListenSocketList.begin(); iter != m_ListenSocketList.end(); iter++)
		delete *iter;
	m_ListenSocketList.clear();
	
	for (std::list<CAdminListenSocket*>::iterator adminIter = m_AdminListenSocketList.begin(); adminIter != m_AdminListenSocketList.end(); adminIter++)
		delete *adminIter;
	m_AdminListenSocketList.clear();

	delete m_pAdminInterface;

	delete m_pAutoBanManager;
	delete m_pFileLogger;
	delete m_pOptions;

	//Destroy window
	if (m_hWnd)
	{
		hMainWnd = 0;
		DestroyWindow(m_hWnd);
		m_hWnd = 0;
	}
}

bool CServer::Create()
{
	//Create window
	WNDCLASSEX wndclass; 
	wndclass.cbSize=sizeof wndclass; 
	wndclass.style=0; 
	wndclass.lpfnWndProc=WindowProc; 
	wndclass.cbClsExtra=0; 
	wndclass.cbWndExtra=0; 
	wndclass.hInstance=GetModuleHandle(0); 
	wndclass.hIcon=0; 
	wndclass.hCursor=0; 
	wndclass.hbrBackground=0; 
	wndclass.lpszMenuName=0; 
	wndclass.lpszClassName=_T("FileZilla Server Helper Window"); 
	wndclass.hIconSm=0; 
	
	RegisterClassEx(&wndclass);
	
	m_hWnd = CreateWindow(_T("FileZilla Server Helper Window"), _T("FileZilla Server Helper Window"), 0, 0, 0, 0, 0, 0, 0, 0, GetModuleHandle(0));
	if (!m_hWnd)
		return false;
	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG)this);

	hMainWnd = m_hWnd;

	m_pOptions = new COptions;
	m_pFileLogger = new CFileLogger(m_pOptions);
	m_pAutoBanManager = new CAutoBanManager(m_pOptions);
	
	//Create the threads
	int num = (int)m_pOptions->GetOptionVal(OPTION_THREADNUM);
	for (int i = 0; i < num; i++)
	{
		int index = GetNextThreadNotificationID();
		CServerThread *pThread = new CServerThread(WM_FILEZILLA_SERVERMSG + index);
		m_ThreadNotificationIDs[index] = pThread;
		if (pThread->Create(THREAD_PRIORITY_NORMAL, CREATE_SUSPENDED))
		{
			pThread->ResumeThread();
			m_ThreadArray.push_back(pThread);
		}
	}
	
	m_pFileLogger->Log(GetVersionString() + _T(" started"));
	m_pFileLogger->Log(_T("Initializing Server."));

	m_nTimerID = SetTimer(m_hWnd, 1234, 10000, NULL);
	ASSERT(m_nTimerID);

	m_nBanTimerID = SetTimer(m_hWnd, 1235, 60000, NULL);
	ASSERT(m_nBanTimerID);

	if (CreateListenSocket())
	{
		m_nServerState = STATE_ONLINE;
		ShowStatus(_T("Server online."), 0);
	}
	else
		ShowStatus(_T("Server not online."), 1);

	CreateAdminListenSocket();

	return true;
}

HWND CServer::GetHwnd()
{
	return m_hWnd;
}

LRESULT CALLBACK CServer::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CServer *pServer=(CServer *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (message == WM_CLOSE)
	{
		pServer->OnClose();
		return 0;
	}
	else if (hWnd && message == WM_DESTROY)
	{
		ASSERT( hWnd == pServer->m_hWnd);
		HANDLE *handle = new HANDLE[pServer->m_ThreadArray.size()];
		unsigned int i = 0;
		std::list<CServerThread *>::iterator iter;
		for (iter = pServer->m_ThreadArray.begin(); iter != pServer->m_ThreadArray.end(); iter++, i++)
		{
			handle[i]=(*iter)->m_hThread;
			(*iter)->PostThreadMessage(WM_QUIT, 0, 0);
		}
		for (i=0; i<pServer->m_ThreadArray.size(); i++)
		{
			int res=WaitForSingleObject(handle[i],INFINITE);
			if (res==WAIT_FAILED)
				res=GetLastError();
		}
		delete [] handle;
		handle = new HANDLE[pServer->m_ClosedThreads.size()];
		i=0;
		for (iter = pServer->m_ClosedThreads.begin(); iter != pServer->m_ClosedThreads.end(); iter++, i++)
		{
			handle[i]=(*iter)->m_hThread;
			(*iter)->PostThreadMessage(WM_QUIT, 0, 0);
		}
		for (i = 0; i < pServer->m_ClosedThreads.size(); i++)
		{
			int res=WaitForSingleObject(handle[i],INFINITE);
			if (res==WAIT_FAILED)
				res=GetLastError();
		}
		delete [] handle;
		for (std::list<CAdminListenSocket*>::iterator iter2 = pServer->m_AdminListenSocketList.begin(); iter2!=pServer->m_AdminListenSocketList.end(); iter2++)
		{
			(*iter2)->Close();
			delete *iter2;
		}
		pServer->m_AdminListenSocketList.clear();
		delete pServer->m_pAdminInterface;
		pServer->m_pAdminInterface = NULL;
		delete pServer->m_pOptions;
		pServer->m_pOptions = NULL;
		if (pServer->m_nTimerID)
		{
			KillTimer(pServer->m_hWnd, pServer->m_nTimerID);
			pServer->m_nTimerID = 0;
		}
		PostQuitMessage(0);
		return 0;
	}
	else if (message == WM_TIMER)
		pServer->OnTimer(wParam);
	else if (message == WM_FILEZILLA_RELOADCONFIG)
	{
		COptions options;
		options.ReloadConfig();
		CPermissions perm;
		perm.ReloadConfig();
	}
	else if (message >= WM_FILEZILLA_SERVERMSG)
	{
		UINT index = message - WM_FILEZILLA_SERVERMSG;
		if (index >= pServer->m_ThreadNotificationIDs.size())
			return 0;

		CServerThread *pThread = pServer->m_ThreadNotificationIDs[index];
		if (pThread)
		{
			std::list<CServerThread::t_Notification> notifications;
			pThread->GetNotifications(notifications);
			for (std::list<CServerThread::t_Notification>::const_iterator iter = notifications.begin(); iter != notifications.end(); iter++)
				if (pServer->OnServerMessage(pThread, iter->wParam, iter->lParam) != 0)
					break;
		}
		return 0;
	}
	
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CServer::OnServerMessage(CServerThread* pThread, WPARAM wParam, LPARAM lParam)
{
	if (wParam == FSM_STATUSMESSAGE)
	{
		t_statusmsg *msg = reinterpret_cast<t_statusmsg *>(lParam);
		if (!msg)
			return 0;

		CStdString str;

		FILETIME fFileTime;
		SystemTimeToFileTime(&msg->time, &fFileTime);
		
		str.Format(_T("(%06d)- %s (%s)> %s"), msg->userid, (LPCTSTR)msg->user, (LPCTSTR)msg->ip, (LPCTSTR)msg->status);
		ShowStatus(fFileTime.dwHighDateTime, fFileTime.dwLowDateTime, str, msg->type);
		delete [] msg->status;
		delete [] msg->user;
		delete msg;
	}
	else if (wParam == FSM_CONNECTIONDATA)
	{
		t_connop *pConnOp = reinterpret_cast<t_connop*>(lParam);
		if (!pConnOp)
			return 0;
		
		int len;
		unsigned char *buffer;

		switch (pConnOp->op)
		{
		case USERCONTROL_CONNOP_ADD:
			{
				t_connectiondata_add* pData = (t_connectiondata_add*)pConnOp->data;
				t_connectiondata data;
				data.userid = pConnOp->userid;
				data.pThread = pThread;
				_tcsncpy(data.ip, pData->ip, 40);
				data.port = pData->port;
				data.transferMode = 0;
				data.currentOffset = 0;
				data.totalSize = -1;

				m_UsersList[pConnOp->userid] = data;

				char* utf8 = ConvToNetwork(pData->ip);
				int iplen = strlen(utf8);
				len = 2 + 4 + 2 + iplen + 4;
				buffer = new unsigned char[len];
				buffer[2 + 4] = iplen / 256;
				buffer[2 + 4 + 1] = iplen % 256;		
				memcpy(buffer + 2 + 4 + 2, utf8, iplen);
				delete [] utf8;
				memcpy(buffer + 2 + 4 + 2 + iplen, &pData->port, 4);

				delete pData;
			}
			break;
		case USERCONTROL_CONNOP_CHANGEUSER:
			{
				t_connectiondata_changeuser* pData = (t_connectiondata_changeuser*)pConnOp->data;
				m_UsersList[pConnOp->userid].user = pData->user;
			
				char* utf8 = ConvToNetwork(pData->user);
				if (!utf8)
				{
					buffer = new unsigned char[2 + 2 + 4 + 2];
					buffer[2 + 4] = 0;
					buffer[2 + 4 + 1] = 0;
					len = 8;
				}
				else
				{
					int userlen = strlen(utf8);
					len = 2 + 4 + 2 + userlen;
					buffer = new unsigned char[len];
					buffer[2 + 4] = userlen / 256;
					buffer[2 + 4 + 1] = userlen % 256;		
					memcpy(buffer + 2 + 4 + 2, utf8, userlen);
					delete [] utf8;
				}

				delete pData;
			}
			break;
		case USERCONTROL_CONNOP_REMOVE:
			{
				std::map<int, t_connectiondata>::iterator iter = m_UsersList.find(pConnOp->userid);
				if (iter != m_UsersList.end())
					m_UsersList.erase(iter);

				len = 6;
				buffer = new unsigned char[len];
			}
			break;
		case USERCONTROL_CONNOP_TRANSFERINIT:
			{
				t_connectiondata_transferinfo* pData = (t_connectiondata_transferinfo*)pConnOp->data;
				t_connectiondata& data = m_UsersList[pConnOp->userid];
				data.transferMode = pData->transferMode;
				data.physicalFile = pData->physicalFile;
				data.logicalFile = pData->logicalFile;
				data.currentOffset = pData->startOffset;
				data.totalSize = pData->totalSize;

				if (data.transferMode)
				{
					char* physicalFile = ConvToNetwork(pData->physicalFile);
					int physicalFileLen = physicalFile ? strlen(physicalFile) : 0;
					char* logicalFile = ConvToNetwork(pData->logicalFile);
					int logicalFileLen = logicalFile ? strlen(logicalFile) : 0;
					len = 2 + 4 + 1 + 2 + physicalFileLen + 2 + logicalFileLen;
					if (data.currentOffset != 0)
						len += 8;
					if (data.totalSize != -1)
						len += 8;

					buffer = new unsigned char[len];
					unsigned char *p = buffer + 6;
					*p = data.transferMode;
					
					// Bit 5 and 6 indicate presence of currentOffset and totalSize.
					if (data.currentOffset != 0)
						*p |= 0x20;
					if (data.totalSize != -1)
						*p |= 0x40;
					p++;
					
					*p++ = physicalFileLen / 256;
					*p++ = physicalFileLen % 256;		
					if (physicalFile)
					{
						memcpy(p, physicalFile, physicalFileLen);
						delete [] physicalFile;
					}
					p += physicalFileLen;

                    *p++ = logicalFileLen / 256;
					*p++ = logicalFileLen % 256;		
					if (logicalFile)
					{
						memcpy(p, logicalFile, logicalFileLen);
						delete [] logicalFile;
					}
					p += logicalFileLen;

					if (data.currentOffset != 0)
					{
						memcpy(p, &data.currentOffset, 8);
						p += 8;
					}
					if (data.totalSize != -1)
					{
						memcpy(p, &data.totalSize, 8);
						p += 8;
					}
				}
				else
				{
					len = 2 + 4 + 1;
					buffer = new unsigned char[len];
					buffer[2 + 4] = 0;
				}
				delete pData;
			}
			break;
		case USERCONTROL_CONNOP_TRANSFEROFFSETS:
			{
				t_connectiondata_transferoffsets* pData = (t_connectiondata_transferoffsets*)pConnOp->data;
				buffer = pData->pData;
				len = pData->len;

				unsigned char* p = buffer + 2;
				int* userid;
				__int64* offset;
				while ((p - buffer + 12) <= len)
				{
					userid = (int*)p;
					offset = (__int64*)(p + 4);
					t_connectiondata& data = m_UsersList[*userid];
					data.currentOffset = *offset;

					p += 12;					
				}
				delete pData;
			}
			break;
		}
		buffer[0] = USERCONTROL_CONNOP;
		buffer[1] = pConnOp->op;
		if (pConnOp->op != USERCONTROL_CONNOP_TRANSFEROFFSETS)
			memcpy(buffer + 2, &pConnOp->userid, 4);
		
		m_pAdminInterface->SendCommand(2, 3, buffer, len);
		delete [] buffer;
		delete pConnOp;
	}
	else if (wParam == FSM_THREADCANQUIT)
	{
		std::list<CServerThread *>::iterator iter;
		for (iter = m_ThreadArray.begin(); iter != m_ThreadArray.end(); iter++)
		{
			if (*iter == pThread)
			{
				HANDLE handle=pThread->m_hThread;
				pThread->PostThreadMessage(WM_QUIT, 0, 0);
				int res=WaitForSingleObject(handle, INFINITE);
				if (res==WAIT_FAILED)
					res=GetLastError();
				m_ThreadArray.erase(iter);
				FreeThreadNotificationID(pThread);
				if (!m_ThreadArray.size() && !m_ClosedThreads.size())
				{
					m_nServerState &= ~(STATE_ONLINE | STATE_MASK_GOOFFLINE);
					SendState();
					if (!m_bQuit)
						ShowStatus(_T("Server offline."), 1);
					else
					{
						hMainWnd = 0;
						DestroyWindow(m_hWnd);
						m_hWnd = 0;
					}
				}
				return -1;
			}
		}
		for (iter = m_ClosedThreads.begin(); iter != m_ClosedThreads.end(); iter++)
		{
			if (*iter == pThread)
			{
				HANDLE handle = pThread->m_hThread;
				pThread->PostThreadMessage(WM_QUIT, 0, 0);
				int res = WaitForSingleObject(handle, INFINITE);
				if (res == WAIT_FAILED)
					res = GetLastError();
				m_ClosedThreads.erase(iter);
				FreeThreadNotificationID(pThread);
				if (!m_ThreadArray.size() && !m_ClosedThreads.size())
				{
					m_nServerState &= ~(STATE_ONLINE | STATE_MASK_GOOFFLINE);
					SendState();
					if (!m_bQuit)
						ShowStatus(_T("Server offline."), 1);
					else
					{
						hMainWnd = 0;
						DestroyWindow(m_hWnd);
						m_hWnd = 0;
					}
				}
				return -1;
			}
			
		}
	}
	else if (wParam == FSM_SEND)
	{
		char buffer[5];
		buffer[0] = 1;
		memcpy(buffer+1, &lParam, 4);
		m_pAdminInterface->SendCommand(2, 7, buffer, 5);
		m_nSendCount += lParam;
	}
	else if (wParam == FSM_RECV)
	{
		char buffer[5];
		buffer[0] = 0;
		memcpy(buffer+1, &lParam, 4);
		m_pAdminInterface->SendCommand(2, 7, buffer, 5);
		m_nRecvCount += lParam;
	}
	return 0;
}


void CServer::OnClose()
{
	for (std::list<CListenSocket*>::iterator listIter = m_ListenSocketList.begin(); listIter != m_ListenSocketList.end(); listIter++)
	{
		(*listIter)->Close();
		delete *listIter;
	}
	m_ListenSocketList.clear();

	m_bQuit = TRUE;

	if (!m_ThreadArray.size() && !m_ClosedThreads.size())
	{
		hMainWnd = 0;
		DestroyWindow(m_hWnd);
		m_hWnd = 0;
		return;
	}

	std::list<CServerThread *>::iterator iter;
	for (iter = m_ThreadArray.begin(); iter != m_ThreadArray.end(); iter++)
	{
		VERIFY((*iter)->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_GOOFFLINE, 0));
	}
	for (iter = m_ClosedThreads.begin(); iter != m_ClosedThreads.end(); iter++)
	{
		VERIFY((*iter)->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_GOOFFLINE, 0));
	}
}

BOOL CServer::ProcessCommand(CAdminSocket *pAdminSocket, int nID, unsigned char *pData, int nDataLength)
{
	switch (nID)
	{
	case 2:
		if (!nDataLength)
		{
			unsigned char buffer[2];
			buffer[0] = m_nServerState / 256;
			buffer[1] = m_nServerState % 256;
			pAdminSocket->SendCommand(1, 2, buffer, 2);
		}
		else if (nDataLength == 2)
		{
			ToggleActive(*pData * 256 + pData[1]);
			unsigned char buffer[2];
			buffer[0] = m_nServerState / 256;
			buffer[1] = m_nServerState % 256;
			pAdminSocket->SendCommand(1, 2, buffer, 2);
		}
		else
			pAdminSocket->SendCommand(1, 1, "\001Protocol error: Unexpected data length", strlen("\001Protocol error: Unexpected data length") + 1);
		break;
	case 3:
		if (!nDataLength)
			pAdminSocket->SendCommand(1, 1, "\001Protocol error: Unexpected data length", strlen("\001Protocol error: Unexpected data length") + 1);
		else if (*pData == USERCONTROL_GETLIST)
		{
			int len = 3;
			std::map<int, t_connectiondata>::iterator iter;
			for (iter = m_UsersList.begin(); iter != m_UsersList.end(); iter++)
			{
				const t_connectiondata& data = iter->second;
				char* ip = ConvToNetwork(data.ip);
				char* user = ConvToNetwork(data.user);
				len += 4 + (ip ? strlen(ip) : 0) + 2 + 4 + (user ? strlen(user) : 0) + 2 + 
					   1;
				delete [] ip;
				delete [] user;
				if (data.transferMode)
				{
					char* physicalFile = ConvToNetwork(data.physicalFile);
					char* logicalFile = ConvToNetwork(data.logicalFile);
					len += 2 + (physicalFile ? strlen(physicalFile) : 0) + 2 + (logicalFile ? strlen(logicalFile) : 0);
					delete [] physicalFile;
					delete [] logicalFile;

					if (data.currentOffset != 0)
						len += 8;
					if (data.totalSize != -1)
						len += 8;
				}
			}
			unsigned char *buffer = new unsigned char[len];
			buffer[0] = USERCONTROL_GETLIST;
			buffer[1] = m_UsersList.size() / 256;
			buffer[2] = m_UsersList.size() % 256;
			unsigned char *p = buffer + 3;
			for (iter = m_UsersList.begin(); iter != m_UsersList.end(); iter++)
			{
				const t_connectiondata& data = iter->second;
				char* ip = ConvToNetwork(data.ip);
				char* user = ConvToNetwork(data.user);
				int ipLen = ip ? strlen(ip) : 0;
				int userLen = user ? strlen(user) : 0;

				memcpy(p, &data.userid, 4);
				p+=4;
				*p++ = ipLen / 256;
				*p++ = ipLen % 256;
				if (ip)
				{
					memcpy(p, ip, ipLen);
					p += ipLen;
					delete [] ip;
				}

				memcpy(p, &data.port, 4);
				p += 4;

				*p++ = userLen / 256;
				*p++ = userLen % 256;
				if (user)
				{
					memcpy(p, user, userLen);
					p += userLen;
					delete [] user;
				}

				*p = data.transferMode;
				if (data.transferMode)
				{
					// Bit 5 and 6 indicate presence of currentOffset and totalSize.
					if (data.currentOffset != 0)
						*p |= 0x20;
					if (data.totalSize != -1)
						*p |= 0x40;
					p++;

					char* physicalFile = ConvToNetwork(data.physicalFile);
					if (physicalFile)
					{
						int physicalLen = strlen(physicalFile);
						*p++ = physicalLen / 256;
						*p++ = physicalLen % 256;
						memcpy(p, physicalFile, physicalLen);
						delete [] physicalFile;
						p += physicalLen;
					}
					else
					{
						*p++ = 0;
						*p++ = 0;
					}

					
					char* logicalFile = ConvToNetwork(data.logicalFile);
					if (logicalFile)
					{
						int logicalLen = strlen(logicalFile);
						*p++ = logicalLen / 256;
						*p++ = logicalLen % 256;
						memcpy(p, logicalFile, logicalLen);
						delete [] logicalFile;
						p += logicalLen;
					}
					else
					{
						*p++ = 0;
						*p++ = 0;
					}

					if (data.currentOffset != 0)
					{
						memcpy(p, &data.currentOffset, 8);
						p += 8;
					}
					if (data.totalSize != -1)
					{
						memcpy(p, &data.totalSize, 8);
						p += 8;
					}
				}
				else
					p++;
			}
			m_pAdminInterface->SendCommand(1, 3, buffer, len);			
			delete [] buffer;
		}
		else if (*pData == USERCONTROL_KICK || *pData == USERCONTROL_BAN)
		{
			if (nDataLength != 5)
				pAdminSocket->SendCommand(1, 1, "\001Protocol error: Unexpected data length", strlen("\001Protocol error: Unexpected data length")+1);
			else
			{
				int nUserID;
				memcpy(&nUserID, pData+1, 4);
				
				std::map<int, t_connectiondata>::iterator iter = m_UsersList.find(nUserID);
				if (iter!=m_UsersList.end())
				{
					if (*pData == USERCONTROL_BAN)
					{
						// Get the list of IP filter rules.
						CStdString ips = m_pOptions->GetOption(OPTION_IPFILTER_DISALLOWED);
						if (ips != _T(""))
							ips += _T(" ");

						USES_CONVERSION;

						int pos = ips.Find(' ');
						while (pos != -1)
						{
							CStdString blockedIP = ips.Left(pos);
							ips = ips.Mid(pos + 1);
							pos = ips.Find(' ');

							if (MatchesFilter(blockedIP, iter->second.ip))
								break;
						}
						if (pos == -1)
						{
							ips = m_pOptions->GetOption(OPTION_IPFILTER_DISALLOWED);
							if (ips != _T(""))
								ips += _T(" ");
							ips += iter->second.ip;
							m_pOptions->SetOption(OPTION_IPFILTER_DISALLOWED, ips);
						}
					}	
					t_controlmessage *msg=new t_controlmessage;
					msg->command=USERCONTROL_KICK;
					msg->socketid=nUserID;
					iter->second.pThread->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_CONTROL, (LPARAM)msg);
					char buffer[2];
					buffer[0] = *pData;
					buffer[1] = 0;
					pAdminSocket->SendCommand(1, 3, &buffer, 2);
				}
				else
				{
					char buffer[2];
					buffer[0] = USERCONTROL_KICK;
					buffer[1] = 1;
					pAdminSocket->SendCommand(1, 3, &buffer, 2);
				}
			}
		}
		else
			pAdminSocket->SendCommand(1, 1, "\001Protocol error: Invalid data", strlen("\001Protocol error: Invalid data")+1);
		break;
	case 5:
		if (!nDataLength)
		{
			char *pBuffer = NULL;
			DWORD nBufferLength = 0;
			if (m_pOptions && m_pOptions->GetAsCommand(&pBuffer, &nBufferLength))
			{
				pAdminSocket->SendCommand(1, 5, pBuffer, nBufferLength);
				delete [] pBuffer;
			}
		}
		else if (m_pOptions)
		{
			if (nDataLength < 2)
				pAdminSocket->SendCommand(1, 1, "\001Protocol error: Unexpected data length", strlen("\001Protocol error: Unexpected data length")+1);
			else
			{
				CStdString listenPorts = m_pOptions->GetOption(OPTION_SERVERPORT);
				CStdString listenPortsSsl = m_pOptions->GetOption(OPTION_SSLPORTS);
				bool enableSsl = m_pOptions->GetOptionVal(OPTION_ENABLESSL) != 0;
				int nAdminListenPort = (int)m_pOptions->GetOptionVal(OPTION_ADMINPORT);
				CStdString adminIpBindings = m_pOptions->GetOption(OPTION_ADMINIPBINDINGS);
				
				CStdString peerIP;
				UINT port = 0;
				bool bLocal = false;
				if (!pAdminSocket->GetPeerName(peerIP, port))
					return FALSE;
				else
					bLocal = IsLocalhost(peerIP);

				if (!m_pOptions->ParseOptionsCommand(pData, nDataLength, bLocal))
				{
					pAdminSocket->SendCommand(1, 1, "\001Protocol error: Invalid data, could not import settings.", strlen("\001Protocol error: Invalid data, could not import settings.")+1);
					char buffer = 1;
					pAdminSocket->SendCommand(1, 5, &buffer, 1);
					break;
				}

				char buffer = 0;
				pAdminSocket->SendCommand(1, 5, &buffer, 1);

				unsigned int threadnum = (int)m_pOptions->GetOptionVal(OPTION_THREADNUM);
				if (m_nServerState & STATE_ONLINE)
				{
					if (threadnum > m_ThreadArray.size())
					{
						int newthreads = threadnum - m_ThreadArray.size();
						for (int i = 0; i < newthreads; i++)
						{
							int index = GetNextThreadNotificationID();
							CServerThread *pThread = new CServerThread(WM_FILEZILLA_SERVERMSG + index);
							m_ThreadNotificationIDs[index] = pThread;
							if (pThread->Create(THREAD_PRIORITY_NORMAL, CREATE_SUSPENDED))
							{
								pThread->ResumeThread();
								m_ThreadArray.push_back(pThread);
							}
						}
						CStdString str;
						str.Format(_T("Number of threads increased to %d."), threadnum);
						ShowStatus(str, 0);
					}
					else if (threadnum < m_ThreadArray.size())
					{
						CStdString str;
						str.Format(_T("Decreasing number of threads to %d."), threadnum);
						ShowStatus(str, 0);
						unsigned int i=0;
						std::list<CServerThread *> newList;
						for (std::list<CServerThread *>::iterator iter=m_ThreadArray.begin(); iter!=m_ThreadArray.end(); iter++,i++)
							if (i>=threadnum)
							{
								(*iter)->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_GOOFFLINE, 2);
								m_ClosedThreads.push_back(*iter);
							}
							else
								newList.push_back(*iter);
						m_ThreadArray.clear();
						m_ThreadArray = newList;
					}
				}
				if (listenPorts != m_pOptions->GetOption(OPTION_SERVERPORT) ||
					enableSsl != (m_pOptions->GetOptionVal(OPTION_ENABLESSL) != 0) ||
					(m_pOptions->GetOptionVal(OPTION_ENABLESSL) && listenPortsSsl != m_pOptions->GetOption(OPTION_SSLPORTS)))
				{
					if (!m_ListenSocketList.empty())
					{
						ShowStatus(_T("Closing all listening sockets"), 0);
						for (std::list<CListenSocket*>::iterator listIter = m_ListenSocketList.begin(); listIter != m_ListenSocketList.end(); listIter++)
						{
							(*listIter)->Close();
							delete *listIter;
						}
						m_ListenSocketList.clear();

						if (!CreateListenSocket())
						{
							ShowStatus(_T("Failed to create a listen socket on any of the specified ports. Server is not online!"), 1);
                            m_nServerState &= ~STATE_ONLINE;
						}
						else
						{
							ShowStatus(_T("Listen socket port changed"), 0);
							if (!(m_nServerState & STATE_MASK_GOOFFLINE))
								m_nServerState |= STATE_ONLINE;
						}
						SendState();
					}
				}
				if (nAdminListenPort != m_pOptions->GetOptionVal(OPTION_ADMINPORT) || adminIpBindings!=m_pOptions->GetOption(OPTION_ADMINIPBINDINGS))
				{
					if (nAdminListenPort == m_pOptions->GetOptionVal(OPTION_ADMINPORT))
					{
						for (std::list<CAdminListenSocket*>::iterator iter = m_AdminListenSocketList.begin(); iter!=m_AdminListenSocketList.end(); iter++)
						{
							(*iter)->Close();
							delete *iter;
						}
						m_AdminListenSocketList.clear();
					}
					CAdminListenSocket *pSocket = new CAdminListenSocket(m_pAdminInterface);
					if (!pSocket->Create((int)m_pOptions->GetOptionVal(OPTION_ADMINPORT), SOCK_STREAM, FD_ACCEPT, (m_pOptions->GetOption(OPTION_ADMINIPBINDINGS) != _T("*")) ? _T("127.0.0.1") : NULL))
					{
						delete pSocket;
						CStdString str;
						str.Format(_T("Failed to change admin listen port to %I64d."), m_pOptions->GetOptionVal(OPTION_ADMINPORT));
						m_pOptions->SetOption(OPTION_ADMINPORT, nAdminListenPort);
						ShowStatus(str, 1);
					}
					else
					{
						pSocket->Listen();
						for (std::list<CAdminListenSocket*>::iterator iter = m_AdminListenSocketList.begin(); iter!=m_AdminListenSocketList.end(); iter++)
						{
							(*iter)->Close();
							delete *iter;
						}
						m_AdminListenSocketList.clear();

						m_AdminListenSocketList.push_back(pSocket);
						if (nAdminListenPort != m_pOptions->GetOptionVal(OPTION_ADMINPORT))
						{
							CStdString str;
							str.Format(_T("Admin listen port changed to %I64d."), m_pOptions->GetOptionVal(OPTION_ADMINPORT));
							ShowStatus(str, 0);
						}

						if (m_pOptions->GetOption(OPTION_ADMINIPBINDINGS) != _T("*"))
						{
							BOOL bError = FALSE;
							CStdString str = _T("Failed to bind the admin interface to the following IPs:");
							CStdString ipBindings = m_pOptions->GetOption(OPTION_ADMINIPBINDINGS);

							if (ipBindings != _T(""))
								ipBindings += _T(" ");
							while (ipBindings != _T(""))
							{
								int pos = ipBindings.Find(' ');
								if (pos == -1)
									break;
								CStdString ip = ipBindings.Left(pos);
								ipBindings = ipBindings.Mid(pos+1);
								CAdminListenSocket *pAdminListenSocket = new CAdminListenSocket(m_pAdminInterface);

								int family;
								if (ip.Find(':') != -1)
									family = AF_INET6;
								else
									family = AF_INET;

								if (!pAdminListenSocket->Create((int)m_pOptions->GetOptionVal(OPTION_ADMINPORT), SOCK_STREAM, FD_ACCEPT, ip, family) || !pAdminListenSocket->Listen())
								{
									bError = TRUE;
									str += _T(" ") + ip;
									delete pAdminListenSocket;
								}
								else
									m_AdminListenSocketList.push_back(pAdminListenSocket);
							}
							if (bError)
								ShowStatus(str, 1);
						}
						if (adminIpBindings != m_pOptions->GetOption(OPTION_ADMINIPBINDINGS))
							ShowStatus(_T("Admin interface IP bindings changed"), 0);
					}
	
				}
			}
		}
		break;
	case 6:
		if (!nDataLength)
		{
			char *pBuffer = NULL;
			DWORD nBufferLength = 0;
			CPermissions permissions;
			permissions.GetAsCommand(&pBuffer, &nBufferLength);
			pAdminSocket->SendCommand(1, 6, pBuffer, nBufferLength);
			delete [] pBuffer;
		}
		else
		{
			if (nDataLength < 2)
				pAdminSocket->SendCommand(1, 1, "\001Protocol error: Unexpected data length", strlen("\001Protocol error: Unexpected data length")+1);
			else
			{
				CPermissions permissions;
				if (!permissions.ParseUsersCommand(pData, nDataLength))
				{
					pAdminSocket->SendCommand(1, 1, "\001Protocol error: Invalid data, could not import account settings.", strlen("\001Protocol error: Invalid data, could not import account settings.")+1);
					char buffer = 1;
					pAdminSocket->SendCommand(1, 6, &buffer, 1);
					break;
				}
				char buffer = 0;
				pAdminSocket->SendCommand(1, 6, &buffer, 1);
			}
		}
		break;
	case 8:
		pAdminSocket->SendCommand(1, 8, NULL, 0);
		break;
	default:
		{
			CStdStringA str;
			str.Format("\001Protocol error: Unknown command (%d).", nID);
			pAdminSocket->SendCommand(1, 1, str.c_str(), str.GetLength());
		}
		break;
	}

	return TRUE;
}

BOOL CServer::ToggleActive(int nServerState)
{
	if (nServerState & STATE_GOOFFLINE_NOW)
	{
		if (m_nServerState & STATE_MASK_GOOFFLINE)
			return FALSE;

		for (std::list<CListenSocket*>::iterator listenIter = m_ListenSocketList.begin(); listenIter != m_ListenSocketList.end(); listenIter++)
		{
			(*listenIter)->Close();
			delete *listenIter;
		}
		m_ListenSocketList.clear();
		for (std::list<CServerThread *>::iterator iter = m_ClosedThreads.begin(); iter != m_ClosedThreads.end(); iter++)
			(*iter)->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_GOOFFLINE, 0);
		for (std::list<CServerThread *>::iterator iter = m_ThreadArray.begin(); iter != m_ThreadArray.end(); iter++)
		{
			(*iter)->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_GOOFFLINE, 0);
			m_ClosedThreads.push_back(*iter);
		}
		m_ThreadArray.clear();
		m_nServerState &= ~STATE_ONLINE;
		if (!m_ClosedThreads.empty())
			m_nServerState |= STATE_GOOFFLINE_NOW;
	}
	else if (nServerState & STATE_GOOFFLINE_LOGOUT)
	{
		if (m_nServerState & STATE_MASK_GOOFFLINE)
			return FALSE;

		for (std::list<CListenSocket*>::iterator listenIter = m_ListenSocketList.begin(); listenIter != m_ListenSocketList.end(); listenIter++)
		{
			(*listenIter)->Close();
			delete *listenIter;
		}
		m_ListenSocketList.clear();
		for (std::list<CServerThread *>::iterator iter = m_ClosedThreads.begin(); iter != m_ClosedThreads.end(); iter++)
			(*iter)->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_GOOFFLINE, 2);
		for (std::list<CServerThread *>::iterator iter=m_ThreadArray.begin(); iter!=m_ThreadArray.end(); iter++)
		{
			(*iter)->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_GOOFFLINE, 2);			
			m_ClosedThreads.push_back(*iter);
		}
		m_ThreadArray.clear();
		m_nServerState &= ~STATE_ONLINE;
		if (!m_ClosedThreads.empty())
			m_nServerState = m_nServerState |= STATE_GOOFFLINE_LOGOUT;
	}
	else if (nServerState & STATE_GOOFFLINE_WAITTRANSFER)
	{
		if (m_nServerState & STATE_MASK_GOOFFLINE)
			return FALSE;

		for (std::list<CListenSocket*>::iterator listenIter = m_ListenSocketList.begin(); listenIter != m_ListenSocketList.end(); listenIter++)
		{
			(*listenIter)->Close();
			delete *listenIter;
		}
		m_ListenSocketList.clear();
		for (std::list<CServerThread *>::iterator iter = m_ClosedThreads.begin(); iter != m_ClosedThreads.end(); iter++)
			(*iter)->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_GOOFFLINE, 1);
		for (std::list<CServerThread *>::iterator iter=m_ThreadArray.begin(); iter!=m_ThreadArray.end(); iter++)
		{
			(*iter)->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_GOOFFLINE, 1);			
			m_ClosedThreads.push_back(*iter);
		}
		m_ThreadArray.clear();
		m_nServerState &= ~STATE_ONLINE;
		if (!m_ClosedThreads.empty())
			m_nServerState = m_nServerState |= STATE_GOOFFLINE_WAITTRANSFER;
	}
	else if (nServerState & STATE_ONLINE)
	{
		if (m_ListenSocketList.empty())
		{
			if (!CreateListenSocket())
			{
				ShowStatus(_T("Failed to create a listen socket on any of the specified ports. Server is not online!"), 1);
				return true;
			}
		}

		if (!m_ListenSocketList.empty())
		{
			ShowStatus(_T("Server online"), 0);
			int i = 0;
			int num = (m_pOptions ? (int)m_pOptions->GetOptionVal(OPTION_THREADNUM) : 2);

			//Recreate the threads
			for (i = m_ThreadArray.size(); i < num; i++)
			{
				int index = GetNextThreadNotificationID();
				CServerThread *pThread = new CServerThread(WM_FILEZILLA_SERVERMSG + index);
				m_ThreadNotificationIDs[index] = pThread;
				if (pThread->Create(THREAD_PRIORITY_NORMAL, CREATE_SUSPENDED))
				{
					m_ThreadArray.push_back(pThread);
					pThread->ResumeThread();
				}
			}
		}
		for (std::list<CListenSocket *>::iterator iter = m_ListenSocketList.begin(); iter != m_ListenSocketList.end(); iter++)
			(*iter)->m_bLocked = nServerState & STATE_LOCKED;

		// Set closing threads to "wait until logout" mode.
		for (std::list<CServerThread *>::iterator iter = m_ClosedThreads.begin(); iter != m_ClosedThreads.end(); iter++)
			(*iter)->PostThreadMessage(WM_FILEZILLA_THREADMSG, FTM_GOOFFLINE, 2);

		m_nServerState = (m_ListenSocketList.empty() ? 0 : STATE_ONLINE) + (nServerState & STATE_LOCKED);
	}

	SendState();
	return TRUE;
}

void CServer::ShowStatus(LPCTSTR msg, int nType)
{
	char* utf8 = ConvToNetwork(msg);
	if (!utf8)
		return;

	char *pBuffer = new char[strlen(utf8) + 1];
	*pBuffer = nType;
	memcpy(pBuffer + 1, utf8, strlen(utf8));
	if (m_pAdminInterface)
		m_pAdminInterface->SendCommand(2, 1, pBuffer, strlen(utf8) + 1);
	delete [] pBuffer;
	delete [] utf8;

	if (m_pFileLogger)
		m_pFileLogger->Log(msg);
}

void CServer::ShowStatus(DWORD eventDateHigh, DWORD eventDateLow, LPCTSTR msg, int nType)
{
	char* utf8 = ConvToNetwork(msg);
	if (!utf8)
		return;
	if (!*utf8)
	{
		delete [] utf8;
		return;
	}

	unsigned int utf8len = strlen(utf8);
	char *pBuffer = new char[utf8len + 1 + 8];
	*pBuffer = nType;
	memcpy(pBuffer + 1, &eventDateHigh, 8);
	memcpy(pBuffer + 5, &eventDateLow, 4);
	memcpy(pBuffer + 1 + 8, utf8, utf8len);
	if (m_pAdminInterface)
		m_pAdminInterface->SendCommand(2, 4, pBuffer, utf8len + 1 + 8);
	delete [] pBuffer;
	delete [] utf8;

	//Log string
	if (m_pFileLogger)
	{
		FILETIME fFileTime;
		SYSTEMTIME sFileTime;
		fFileTime.dwHighDateTime = eventDateHigh;
		fFileTime.dwLowDateTime = eventDateLow;
		FileTimeToSystemTime(&fFileTime, &sFileTime);
		TCHAR text[80];
		if (!GetDateFormat(
			LOCALE_USER_DEFAULT,               // locale for which date is to be formatted
			DATE_SHORTDATE,             // flags specifying function options
			&sFileTime,  // date to be formatted
			0,          // date format string
			text,          // buffer for storing formatted string
			80                // size of buffer
			))
			return;
		
		CStdString text2 = _T(" ");
		text2 += text;
		
		if (!GetTimeFormat(
			LOCALE_USER_DEFAULT,               // locale for which date is to be formatted
			TIME_FORCE24HOURFORMAT,             // flags specifying function options
			&sFileTime,  // date to be formatted
			0,          // date format string
			text,          // buffer for storing formatted string
			80                // size of buffer
			))
			return;

		text2 += _T(" ");
		text2 += text;
		CStdString str = msg;
		int pos = str.Find(_T("-"));
		if (pos!=-1)
		{
			str.Insert(pos, text2 + _T(" "));
		}
		m_pFileLogger->Log(str);
	}
}

void CServer::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == m_nBanTimerID)
	{
		if (m_pAutoBanManager)
			m_pAutoBanManager->PurgeOutdated();
		return;
	}

	m_pAdminInterface->CheckForTimeout();
	m_pFileLogger->CheckLogFile();
}

int CServer::DoCreateAdminListenSocket(UINT port, LPCTSTR addr, int family)
{
	CAdminListenSocket *pAdminListenSocket = new CAdminListenSocket(m_pAdminInterface);
	if (!pAdminListenSocket->Create(port, SOCK_STREAM, FD_ACCEPT, addr, family))
	{
		delete pAdminListenSocket;
		return 0;
	}

	if (!pAdminListenSocket->Listen())
	{
		delete pAdminListenSocket;
		return 0;
	}

	if (!port)
	{
		CStdString ip;
		BOOL bResult = pAdminListenSocket->GetSockName(ip, port);
		if (!bResult)
		{
			delete pAdminListenSocket;
			return 0;
		}
	}
	
	m_AdminListenSocketList.push_back(pAdminListenSocket);
	return port;
}

BOOL CServer::CreateAdminListenSocket()
{
	CStdString ipBindings = (m_pOptions ? m_pOptions->GetOption(OPTION_ADMINIPBINDINGS) : _T(""));
	int nAdminPort = (m_pOptions ? (int)m_pOptions->GetOptionVal(OPTION_ADMINPORT) : 14147);

	CStdString error;

	if (!DoCreateAdminListenSocket(nAdminPort, (ipBindings != _T("*")) ? _T("127.0.0.1") : NULL, AF_INET))
	{
		int p = DoCreateAdminListenSocket(nAdminPort, _T("127.0.0.1"), AF_INET);
		if (!p)
		{
			CStdString str;
			str.Format(_T("Failed to create listen socket for admin interface on port %d for IPv4, the IPv4 admin interface has been disabled."), nAdminPort);
			ShowStatus(str, 1);
			error += _T("\n") + str;
		}
		else
		{
			CStdString str;
			str.Format(_T("Failed to create listen socket for admin interface on port %d for IPv4, for this session the IPv4 admin interface is available on port %u."), p);
			ShowStatus(str, 1);
			error += _T("\n") + str;
		}
	}

	if (!m_pOptions->GetOptionVal(OPTION_DISABLE_IPV6))
	{
		if (!DoCreateAdminListenSocket(nAdminPort, (ipBindings != _T("*")) ? _T("::1") : NULL, AF_INET6))
		{
			int p = DoCreateAdminListenSocket(nAdminPort, _T("127.0.0.1"), AF_INET6);
			if (!p)
			{
				CStdString str;
				str.Format(_T("Failed to create listen socket for admin interface on port %d for IPv6, the IPv6 admin interface has been disabled."), nAdminPort);
				ShowStatus(str, 1);
				error += _T("\n") + str;
			}
			else
			{
				CStdString str;
				str.Format(_T("Failed to create listen socket for admin interface on port %d for IPv6, for this session the IPv6 admin interface is available on port %u."), p);
				ShowStatus(str, 1);
				error += _T("\n") + str;
			}
		}
	}

	if (ipBindings != _T("*"))
	{
		if (ipBindings != _T(""))
			ipBindings += _T(" ");
		while (ipBindings != _T(""))
		{
			int pos = ipBindings.Find(' ');
			if (pos == -1)
				break;
			CStdString ip = ipBindings.Left(pos);
			ipBindings = ipBindings.Mid(pos+1);
			CAdminListenSocket *pAdminListenSocket = new CAdminListenSocket(m_pAdminInterface);

			int family;
			if (ip.Find(':') != -1)
				family = AF_INET6;
			else
				family = AF_INET;

			if (!pAdminListenSocket->Create(nAdminPort, SOCK_STREAM, FD_ACCEPT, ip, family) || !pAdminListenSocket->Listen())
			{
				delete pAdminListenSocket;
				error += _T("\n") + ip;
			}
			else
				m_AdminListenSocketList.push_back(pAdminListenSocket);
		}
	}

	/* Disabled since appareantly MessageBox freezes the server on Windows Server 2003.
	if (!error.IsEmpty())
	{
		error = _T("Failed to bind the admin interface to the following addresses:") + error;
		MessageBox(0, error, _T("FileZilla Server Error"), MB_ICONEXCLAMATION | MB_SERVICE_NOTIFICATION);
	}*/

	return !m_AdminListenSocketList.empty();
}

BOOL CServer::CreateListenSocket()
{
	CStdString ports = (m_pOptions ? m_pOptions->GetOption(OPTION_SERVERPORT) : _T("21"));
	bool ssl = false;
	
	if (ports == _T("") && m_pOptions && m_pOptions->GetOptionVal(OPTION_ENABLESSL))
	{
		ports = m_pOptions->GetOption(OPTION_SSLPORTS);
		ssl = true;
	}

	if (ports == _T(""))
	{
		ShowStatus(_T("No listen ports set in settings"), 1);
		return false;
	}

	ports += _T(" ");
	int pos = ports.Find(' ');
	while (pos > 0)
	{
		CStdString ipBindings = (m_pOptions ? m_pOptions->GetOption(OPTION_IPBINDINGS) : _T("*"));
		if (ipBindings == _T(""))
			ipBindings = _T("*");
		int nPort = _ttoi(ports.Left(pos));
		ports = ports.Mid(pos + 1);
		pos = ports.Find(' ');

		CStdString str;
		str.Format(_T("Creating listen socket on port %d..."), nPort);
		ShowStatus(str, 0);
		if (ipBindings == _T("*"))
		{
			CListenSocket *pListenSocket = new CListenSocket(this, ssl);
			pListenSocket->m_pThreadList = &m_ThreadArray;
	
			if (!pListenSocket->Create(nPort, SOCK_STREAM, FD_ACCEPT, NULL, AF_INET) || !pListenSocket->Listen())
			{
				delete pListenSocket;
				pListenSocket = NULL;
				str.Format(_T("Failed to create listen socket on port %d for IPv4"), nPort);
				ShowStatus(str, 1);
			}
			else
				m_ListenSocketList.push_back(pListenSocket);

			if (!m_pOptions->GetOptionVal(OPTION_DISABLE_IPV6))
			{
				CListenSocket *pListenSocket = new CListenSocket(this, ssl);
				pListenSocket->m_pThreadList = &m_ThreadArray;
		
				if (!pListenSocket->Create(nPort, SOCK_STREAM, FD_ACCEPT, NULL, AF_INET6) || !pListenSocket->Listen())
				{
					delete pListenSocket;
					pListenSocket = NULL;
					str.Format(_T("Failed to create listen socket on port %d for IPv6"), nPort);
					ShowStatus(str, 1);
				}
				else
					m_ListenSocketList.push_back(pListenSocket);
			}
		}
		else
		{
			BOOL bError = FALSE;
			CStdString str;
			str.Format(_T("Failed to bind the listen socket on port %d to the following IPs:"), nPort);
			ipBindings += _T(" ");
			while (ipBindings != _T(""))
			{
				int pos = ipBindings.Find(' ');
				if (pos == -1)
					break;
				CStdString ip = ipBindings.Left(pos);
				ipBindings = ipBindings.Mid(pos + 1);
				CListenSocket *pListenSocket = new CListenSocket(this, ssl);
				pListenSocket->m_pThreadList = &m_ThreadArray;
				
				int family;
				if (ip.Find(':') != -1)
					family = AF_INET6;
				else
					family = AF_INET;

				if (!pListenSocket->Create(nPort, SOCK_STREAM, FD_ACCEPT, ip, family) || !pListenSocket->Listen())
				{
					delete pListenSocket;
					bError = TRUE;
					str += _T(" ") + ip;
				}
				else
					m_ListenSocketList.push_back(pListenSocket);
			}
			if (bError)
				ShowStatus(str, 1);
		}

		if (pos < 1 && !ssl && m_pOptions && m_pOptions->GetOptionVal(OPTION_ENABLESSL))
		{
			// Now create the ssl ports
			ports = m_pOptions->GetOption(OPTION_SSLPORTS);
			ports += _T(" ");
			pos = ports.Find(' ');
			ssl = true;
		}
	}

	return !m_ListenSocketList.empty();
}

unsigned int CServer::GetNextThreadNotificationID()
{
	for (unsigned int i = 0; i < m_ThreadNotificationIDs.size(); i++)
		if (!m_ThreadNotificationIDs[i])
			return i;

	m_ThreadNotificationIDs.push_back(0);
	return m_ThreadNotificationIDs.size() - 1;
}

void CServer::FreeThreadNotificationID(CServerThread *pThread)
{
	for (unsigned int i = 0; i < m_ThreadNotificationIDs.size(); i++)
		if (m_ThreadNotificationIDs[i] == pThread)
		{
			m_ThreadNotificationIDs[i] = 0;
			break;
		}

}

void CServer::SendState()
{
	if (!m_pAdminInterface)
		return;

	// Send state to interface
	unsigned char buffer[2];
	buffer[0] = m_nServerState / 256;
	buffer[1] = m_nServerState % 256;
	m_pAdminInterface->SendCommand(2, 2, buffer, 2);
}
