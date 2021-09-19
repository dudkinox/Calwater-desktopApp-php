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

// Thread.h: Schnittstelle f�r die Klasse CThread.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREAD_H__67621B15_8724_4B5D_9343_7667075C89F2__INCLUDED_)
#define AFX_THREAD_H__67621B15_8724_4B5D_9343_7667075C89F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CThread
{
public:
	CThread();

protected:
	virtual ~CThread();
	
	// Operationen
public:
	DWORD m_dwThreadId;
	HANDLE m_hThread;
	BOOL Create(int nPriority = THREAD_PRIORITY_NORMAL, DWORD dwCreateFlags = 0);
	DWORD SuspendThread();
	DWORD ResumeThread();
	BOOL PostThreadMessage( UINT message , WPARAM wParam, LPARAM lParam );
	BOOL SetPriority(int nPriority);
	
protected:
	virtual int OnThreadMessage(UINT Msg, WPARAM wParam, LPARAM lParam);
	virtual BOOL InitInstance();
	virtual DWORD ExitInstance();
	DWORD Run();
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
	HANDLE m_hEventStarted;
	bool m_started;
};

#endif // !defined(AFX_THREAD_H__67621B15_8724_4B5D_9343_7667075C89F2__INCLUDED_)
