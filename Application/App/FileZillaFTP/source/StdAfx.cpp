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

// stdafx.cpp : Quelltextdatei, die nur die Standard-Includes einbindet
//	FileZilla server.pch ist die vorcompilierte Header-Datei
//	stdafx.obj enthält die vorcompilierte Typinformation

#include "stdafx.h"



HWND hMainWnd = NULL;

CCriticalSectionWrapper::CCriticalSectionWrapper()
{
	m_bInitialized = TRUE;
	InitializeCriticalSection(&m_criticalSection);
#ifdef DEBUG
	m_lockCount = 0;
#endif
}

CCriticalSectionWrapper::~CCriticalSectionWrapper()
{
	if (m_bInitialized)
		DeleteCriticalSection(&m_criticalSection);
	m_bInitialized = FALSE;
}

void CCriticalSectionWrapper::Lock()
{
	if (!m_bInitialized)
		return;

	EnterCriticalSection(&m_criticalSection);
#ifdef DEBUG
	m_lockCount++;
#endif
}

void CCriticalSectionWrapper::Unlock()
{
	if (!m_bInitialized)
		return;

#ifdef DEBUG
	if (m_criticalSection.OwningThread != (HANDLE)GetCurrentThreadId())
	{
		// Suspend thread to avoid further damage
		SuspendThread(GetCurrentThread());
	}
	if (m_lockCount < 1)
	{
		// Suspend thread to avoid further damage
		SuspendThread(GetCurrentThread());
	}
	m_lockCount--;
#endif
	LeaveCriticalSection(&m_criticalSection);
}

#ifdef DEADLOCKDEBUG

CCriticalSectionWrapper deadlocklock; //pun intended
void EnterCritSectionDebug(CCriticalSectionWrapper &section, const char *pFile, int line)
{
	CStdString fn;
	fn.Format("c:\\fz%u.txt", (unsigned int)&section.m_criticalSection);
	deadlocklock.Lock();
	HANDLE hFile = CreateFile(fn, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, 0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		// Avoid overflow, halt server
		int len = GetFileSize(hFile, 0);
		if ((len / 100) > ((len % 100) * 3) + 95)
		{
			SuspendThread(GetCurrentThread());
			while (true)
				Sleep(1000);
		}

		SetFilePointer(hFile, 0, 0, FILE_END);
		CStdString fn2 = pFile;
		int pos = fn2.ReverseFind('\\');
		if (pos != -1)
			fn2 = fn2.Mid(pos + 1);

		CStdString str;
		str.Format("locking in %s:%d", fn2.c_str(), line);
		while (str.GetLength() < 98)
			str += " ";
		str += "\r\n";
		DWORD numwritten = 0;
		WriteFile(hFile, str, 100, &numwritten, 0);
		CloseHandle(hFile);
	}
	deadlocklock.Unlock();
	section.Lock();
	deadlocklock.Lock();
	hFile = CreateFile(fn, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, 0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		SetFilePointer(hFile, 0, 0, FILE_END);
		CStdString fn2 = pFile;
		int pos = fn2.ReverseFind('\\');
		if (pos != -1)
			fn2 = fn2.Mid(pos + 1);

		CStdString str;
		str.Format("lock obtained in %s:%d", fn2.c_str(), line);
		while (str.GetLength() < 98)
			str += " ";
		str += "\r\n";
		DWORD numwritten = 0;
		WriteFile(hFile, str, 100, &numwritten, 0);
		CloseHandle(hFile);
	}
	deadlocklock.Unlock();
}

void LeaveCritSectionDebug(CCriticalSectionWrapper &section, const char *pFile, int line)
{
	section.Unlock();

	deadlocklock.Lock();
	CStdString fn;
	fn.Format("c:\\fz%u.txt", (unsigned int)&section.m_criticalSection);
	HANDLE hFile = CreateFile(fn, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, 0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		SetFilePointer(hFile, 0, 0, FILE_END);
		CStdString fn2 = pFile;
		int pos = fn2.ReverseFind('\\');
		if (pos != -1)
			fn2 = fn2.Mid(pos + 1);

		CStdString str;
		str.Format("unlocked in %s:%d", fn2.c_str(), line);
		while (str.GetLength() < 99)
			str += " ";
		str += "\r\n";
		DWORD numwritten = 0;
		WriteFile(hFile, str, 101, &numwritten, 0);
		int len = GetFileSize(hFile, 0);
		CloseHandle(hFile);
		if ((len / 100) == (len % 100) * 3)
			DeleteFile(fn);
	}
	deadlocklock.Unlock();
}

#endif