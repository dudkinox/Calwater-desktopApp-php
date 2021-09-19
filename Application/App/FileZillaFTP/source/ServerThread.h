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

#if !defined(AFX_SERVERTHREAD_H__4F566540_62DF_4338_85DE_EC699EB6640C__INCLUDED_)
#define AFX_SERVERTHREAD_H__4F566540_62DF_4338_85DE_EC699EB6640C__INCLUDED_

#include "Thread.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerThread.h : Header-Datei
//

class CControlSocket;
class CServerThread;
class COptions;
class CPermissions;
class t_user;
class CExternalIpCheck;
class CAutoBanManager;
class CHashThread;

typedef struct
{
	CControlSocket *pSocket;
	CServerThread *pThread;
} t_socketdata;

/////////////////////////////////////////////////////////////////////////////
// Thread CServerThread 

class CServerThread : public CThread
{
public:
	virtual CStdString GetExternalIP(const CStdString& localIP);
	virtual void ExternalIPFailed();
	CServerThread(int nNotificationMessageId);

	CPermissions *m_pPermissions;
	COptions *m_pOptions;
	CAutoBanManager* m_pAutoBanManager;
	void IncRecvCount(int count);
	void IncSendCount(int count);
	void IncIpCount(const CStdString &ip);
	void DecIpCount(const CStdString &ip);
	int GetIpCount(const CStdString &ip) const;
	BOOL IsReady();
	static const int GetGlobalNumConnections();
	void AddSocket(SOCKET sockethandle, bool ssl);
	const int GetNumConnections();

	struct t_Notification
	{
		WPARAM wParam;
		LPARAM lParam;
	};

	void SendNotification(WPARAM wParam, LPARAM lParam);

	/*
	 * The parameter should be an empty list, since m_pendingNotifications and 
	 * list get swapped to increase performance.
	 */
	void GetNotifications(std::list<CServerThread::t_Notification>& list);

	void AntiHammerIncrease(const CStdString& ip);
	
	CHashThread& GetHashThread();

protected:
	virtual ~CServerThread();

	void GatherTransferedBytes();
	void ProcessNewSlQuota();
	virtual BOOL InitInstance();
	virtual DWORD ExitInstance();

	virtual int OnThreadMessage(UINT Msg, WPARAM wParam, LPARAM lParam);
	void OnTimer(WPARAM wParam, LPARAM lParam);	
	
	void ProcessControlMessage(t_controlmessage *msg);
	CControlSocket * GetControlSocket(int userid);
	std::map<int, CControlSocket *> m_LocalUserIDs;
	void AddNewSocket(SOCKET sockethandle, bool ssl);
	static int CalcUserID();
	static std::map<int, t_socketdata> m_userids;
	static std::map<CStdString, int> m_userIPs;
	void AntiHammerDecrease();

	int m_nRecvCount;
	int m_nSendCount;
	UINT m_nRateTimer;
	BOOL m_bQuit;

	CCriticalSectionWrapper m_threadsync;
	static CCriticalSectionWrapper m_GlobalThreadsync;
	unsigned int m_timerid;

	//Speed limit code
	static std::list<CServerThread *> m_sInstanceList; //First instance is the SL master
	BOOL m_bIsMaster;
	int m_nLoopCount;

	int m_lastLimits[2];
	typedef struct {
		int nBytesAllowedToTransfer;
		int nTransferred;
	} t_Quota;
	t_Quota m_SlQuotas[2];

	CStdString m_RawWelcomeMessage;
	std::list<CStdString> m_ParsedWelcomeMessage;
	CExternalIpCheck *m_pExternalIpCheck;

	std::list<t_Notification> m_pendingNotifications;
	int m_throttled;

	int m_nNotificationMessageId;

	static std::map<CStdString, int> m_antiHammerInfo;
	int m_antiHammerTimer;

	static CHashThread* m_hashThread;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_SERVERTHREAD_H__4F566540_62DF_4338_85DE_EC699EB6640C__INCLUDED_
