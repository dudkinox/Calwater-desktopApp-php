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

// stdafx.h : Include-Datei für Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die häufig benutzt, aber
//      in unregelmäßigen Abständen geändert werden.
//

#if !defined(AFX_STDAFX_H__0D7D6CEC_E1AA_4287_BB10_A97FA4D444B6__INCLUDED_)
#define AFX_STDAFX_H__0D7D6CEC_E1AA_4287_BB10_A97FA4D444B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Selten verwendete Teile der Windows-Header nicht einbinden

#pragma warning (disable : 4786)

#include <windows.h>
#include <crtdbg.h>
#include <stddef.h>

#include <wtypes.h>
#include <oleauto.h>
#include "atlconv.h"

#include "shlobj.h"

#include "config.h"

#include "misc\stdstring.h"

#include "MFC64bitFix.h"
#include <map>
#include <list>
#include <vector>
#include <set>

#ifdef MMGR
#include "misc/mmgr.h"
#endif

#include "conversion.h"

#include "AsyncSocketEx.h"

#define FILEZILLA_SERVER_MESSAGE _T("FileZilla Server Message")
#define FILEZILLA_THREAD_MESSAGE _T("FileZilla Thread Message")

const UINT WM_FILEZILLA_RELOADCONFIG = WM_APP;
const UINT WM_FILEZILLA_SERVERMSG = (WM_APP + 1);
const UINT WM_FILEZILLA_THREADMSG = ::RegisterWindowMessage(FILEZILLA_THREAD_MESSAGE);

#define FSM_STATUSMESSAGE 0
#define FSM_CONNECTIONDATA 1
#define FSM_THREADCANQUIT 2
#define FSM_SEND 3
#define FSM_RECV 4

#define FTM_NEWSOCKET 0
#define FTM_DELSOCKET 1
#define FTM_COMMAND 2
#define FTM_TRANSFERMSG 3
#define FTM_GOOFFLINE 4
#define FTM_CONTROL 5
#define FTM_NEWSOCKET_SSL 6
#define FTM_HASHRESULT 7

#define USERCONTROL_GETLIST 0
#define USERCONTROL_CONNOP 1
#define USERCONTROL_KICK 2
#define USERCONTROL_BAN 3

#define USERCONTROL_CONNOP_ADD 0
#define USERCONTROL_CONNOP_CHANGEUSER 1
#define USERCONTROL_CONNOP_REMOVE 2
#define USERCONTROL_CONNOP_TRANSFERINIT 3
#define USERCONTROL_CONNOP_TRANSFEROFFSETS 4

typedef struct
{
	int command;
	int socketid;
} t_controlmessage;

typedef struct
{
	TCHAR ip[40];
	LPTSTR user;
	SYSTEMTIME time;
	UINT userid;
	int type;
	LPTSTR status;
} t_statusmsg;

class CServerThread;
typedef struct
{
	int userid;
	
	// Set only by USERCONTROL_CONNOP_CHANGEUSER messages
	CStdString user;

	// Set only by USERCONTROL_CONNOP_ADD messages
	TCHAR ip[40];
	unsigned int port;
	CServerThread *pThread;

	// Set only by USERCONTROL_CONNOP_TRANSFERINFO messages
	unsigned char transferMode;
	CStdString physicalFile;
	CStdString logicalFile;
	__int64 currentOffset;
	__int64 totalSize;
} t_connectiondata;

struct t_connectiondata_add
{
	TCHAR ip[40];
	unsigned int port;
	CServerThread *pThread;
};

struct t_connectiondata_changeuser
{
	CStdString user;
};

struct t_connectiondata_transferinfo
{
	unsigned char transferMode;
	CStdString physicalFile;
	CStdString logicalFile;
	__int64 startOffset;
	__int64 totalSize;
};

struct t_connectiondata_transferoffsets
{
	unsigned char* pData;
	int len;
};

typedef struct
{
	void *data;
	int op;
	int userid;
} t_connop;

extern HWND hMainWnd;
#ifndef CCRITICALSECTIONWRAPPERINCLUDED
class CCriticalSectionWrapper
{
public:
	CCriticalSectionWrapper();
	~CCriticalSectionWrapper();
	
	void Lock();
	void Unlock();

#ifndef DEADLOCKDEBUG
protected:
#else
public:
#endif
	CRITICAL_SECTION m_criticalSection;
	BOOL m_bInitialized;
#ifdef DEBUG
	int m_lockCount;
#endif

};
#define CCRITICALSECTIONWRAPPERINCLUDED
#endif

#ifndef DEADLOCKDEBUG
#define EnterCritSection(section) section.Lock()
#define LeaveCritSection(section) section.Unlock()
#else
void EnterCritSectionDebug(CCriticalSectionWrapper &section, const char *pFile, int line);
void LeaveCritSectionDebug(CCriticalSectionWrapper &section, const char *pFile, int line);
#define EnterCritSection(section) EnterCritSectionDebug(section, __FILE__, __LINE__)
#define LeaveCritSection(section) LeaveCritSectionDebug(section, __FILE__, __LINE__)
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_STDAFX_H__0D7D6CEC_E1AA_4287_BB10_A97FA4D444B6__INCLUDED_)
