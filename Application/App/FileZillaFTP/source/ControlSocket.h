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

#if !defined(AFX_CONTROLSOCKET_H__17DD46FD_8A4A_4394_9F90_C14BA65F6BF6__INCLUDED_)
#define AFX_CONTROLSOCKET_H__17DD46FD_8A4A_4394_9F90_C14BA65F6BF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControlSocket.h : Header-Datei
//

#include "hash_thread.h"

class CAsyncGssSocketLayer;
class CAsyncSslSocketLayer;
class CTransferSocket;

#ifndef TRANSFERMODE_NOTSET
#define TRANSFERMODE_NOTSET 0
#endif

/////////////////////////////////////////////////////////////////////////////
// Befehlsziel CControlSocket

class CControlSocket : public CAsyncSocketEx
{
// Attribute
public:

// Operationen
public:
	CControlSocket(CServerThread *pOwner);
	virtual ~CControlSocket();

// Überschreibungen
public:
	CServerThread * m_pOwner;
	CStdString m_RemoteIP;
	void WaitGoOffline(bool wait = true);
	BOOL m_bWaitGoOffline;
	void CheckForTimeout();
	void ForceClose(int nReason);
	CTransferSocket* GetTransferSocket();
	void ProcessTransferMsg();
	void ParseCommand();
	int m_userid;
	BOOL Send(LPCTSTR str, bool sendStatus = true);
	void SendStatus(LPCTSTR status,int type);
	BOOL GetCommand(CStdString &command, CStdString &args);
	bool InitImplicitSsl();

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	void AntiHammerIncrease(int amount = 1);

	void Continue();

	void ProcessHashResult(int hash_id, int res, CHashThread::_algorithm alg, const CStdString& hash, const CStdString& file);

// Implementierung
protected:
	BOOL DoUserLogin(LPCTSTR password, bool skipPass = false);
	BOOL UnquoteArgs(CStdString &args);
	static int GetUserCount(const CStdString &user);
	static void IncUserCount(const CStdString &user);
	static void DecUserCount(const CStdString &user);
	void ResetTransferstatus();
	BOOL CreateTransferSocket(CTransferSocket *pTransferSocket);
	bool CheckIpForZlib();
	void SendTransferinfoNotification(const char transfermode = TRANSFERMODE_NOTSET, const CStdString& physicalFile = "", const CStdString& logicalFile = "", __int64 startOffset = 0, __int64 totalSize = -1);
	bool CanQuit();
	CStdString GetPassiveIP();

	virtual int OnLayerCallback(std::list<t_callbackMsg>& callbacks);

	CAsyncGssSocketLayer *m_pGssLayer;
	CAsyncSslSocketLayer *m_pSslLayer;

	std::list<CStdStringA> m_RecvLineBuffer;
	char m_RecvBuffer[2048];
	int m_nRecvBufferPos;
	char *m_pSendBuffer;
	int m_nSendBufferLen;

	int m_nTelnetSkip;
	BOOL m_bQuitCommand;
	SYSTEMTIME m_LastCmdTime, m_LastTransferTime, m_LoginTime;
	static std::map<CStdString, int> m_UserCount;
	CStdString m_CurrentServerDir;
	static CCriticalSectionWrapper m_Sync;
	struct t_status
	{
		BOOL loggedon;
		CStdString user;
		CStdString ip;

		int hammerValue;
	} m_status;
	struct t_transferstatus
	{
		int pasv;
		_int64 rest;
		int type;
		CStdString ip;
		int port;
		CTransferSocket *socket;
		bool usedResolvedIP;
		int family;
	} m_transferstatus;

	CStdString RenName;
	BOOL bRenFile;

	enum TransferMode
	{
		mode_stream,
		mode_zlib
	};

	TransferMode m_transferMode;
	int m_zlibLevel;

	int m_antiHammeringWaitTime;

	bool m_bProtP;

	bool m_useUTF8; // Enabled by default, can be turned off using
					// OPTS UF8 OFF

	void ParseMlstOpts(CStdString args);
	void ParseHashOpts(CStdString args);

	// Enabled MLST facts
	bool m_facts[4];

	bool m_shutdown;

	int m_hash_id;
	
	enum CHashThread::_algorithm m_hash_algorithm;

public:
	int GetSpeedLimit(enum sltype);

	typedef struct {
		bool bContinue;
		int nBytesAllowedToTransfer;
		int nTransferred;
		bool bBypassed;
	} t_Quota;
	t_Quota m_SlQuotas[2];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_CONTROLSOCKET_H__17DD46FD_8A4A_4394_9F90_C14BA65F6BF6__INCLUDED_
