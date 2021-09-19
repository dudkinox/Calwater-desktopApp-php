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
#include "version.h"

CStdString GetVersionString()
{
	//Fill the version info
	TCHAR fullpath[MAX_PATH + 10];
	GetModuleFileName(0, fullpath, MAX_PATH + 10);
	
	TCHAR *str = new TCHAR[_tcslen(fullpath) + 1];
	_tcscpy(str, fullpath);
	DWORD tmp = 0;
	DWORD len = GetFileVersionInfoSize(str, &tmp);
	LPVOID pBlock = new char[len];
	GetFileVersionInfo(str, 0, len, pBlock);
	LPVOID ptr;
	UINT ptrlen;

	CStdString ProductName;
	//Retreive the product name
	
	TCHAR SubBlock[50];
			
	// Structure used to store enumerated languages and code pages.
	struct LANGANDCODEPAGE {
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;

	UINT cbTranslate;
			
	// Read the list of languages and code pages.
	if (VerQueryValue(pBlock, 
				_T("\\VarFileInfo\\Translation"),
				(LPVOID*)&lpTranslate,
				&cbTranslate))
	{
		// Read the file description for each language and code page.
	
		_stprintf( SubBlock, 
	           _T("\\StringFileInfo\\%04x%04x\\ProductName"),
	           lpTranslate[0].wLanguage,
	           lpTranslate[0].wCodePage);
		// Retrieve file description for language and code page "0". 
		if (VerQueryValue(pBlock, 
				SubBlock, 
				&ptr, 
					&ptrlen))
		{
			ProductName = (TCHAR*)ptr;
		}
	}
	CStdString version;
	//Format the versionstring
	if (VerQueryValue(pBlock, _T("\\"), &ptr, &ptrlen))
	{
		VS_FIXEDFILEINFO *fi = (VS_FIXEDFILEINFO*)ptr;
		
		if (fi->dwFileVersionMS >> 16)
		{
			//v1.00+
			if (fi->dwFileVersionLS & 0xFFFF)
			{ //test releases
				if (fi->dwFileVersionLS >> 16)
				{
					TCHAR ch = 'a';
					ch += static_cast<TCHAR>(fi->dwFileVersionLS >> 16) - 1;
					version.Format(_T("%s version %d.%d%c test release %d)"), (LPCTSTR)ProductName, fi->dwFileVersionMS >> 16, fi->dwFileVersionMS & 0xFFFF, ch, fi->dwFileVersionLS & 0xFFFF);
				}
				else
					version.Format(_T("%s version %d.%d test release %d"), (LPCTSTR)ProductName, fi->dwFileVersionMS >> 16, fi->dwFileVersionMS & 0xFFFF, fi->dwFileVersionLS & 0xFFFF);
			}
			else
			{ //final versions
				if (fi->dwFileVersionLS >> 16)
				{
					TCHAR ch = 'a';
					ch += static_cast<TCHAR>(fi->dwFileVersionLS >> 16) - 1;
					version.Format(_T("%s version %d.%d%c final"), (LPCTSTR)ProductName, fi->dwFileVersionMS >> 16, fi->dwFileVersionMS & 0xFFFF, ch);
				}
				else
					version.Format(_T("%s version %d.%d final"), (LPCTSTR)ProductName, fi->dwFileVersionMS >> 16, fi->dwFileVersionMS & 0xFFFF);
			}
		}
		else
		{
			//beta versions
			if ((fi->dwFileVersionLS & 0xFFFF) / 100)
				if ((fi->dwFileVersionLS & 0xFFFF) % 100)
					//test release
					version.Format(_T("%s version 0.%d.%d%c beta test release %d"), (LPCTSTR)ProductName, fi->dwFileVersionMS & 0xFFFF, fi->dwFileVersionLS >> 16, (fi->dwFileVersionLS & 0xFFFF) / 100 + 'a' - 1, (fi->dwFileVersionLS & 0xFFFF) % 100);
				else
					//final version
					version.Format(_T("%s version 0.%d.%d%c beta"), (LPCTSTR)ProductName, fi->dwFileVersionMS & 0xFFFF, fi->dwFileVersionLS>>16, (fi->dwFileVersionLS & 0xFFFF) / 100 + 'a' - 1);
			else
				if (fi->dwFileVersionLS&0xFFFF)
					//test release
					version.Format(_T("%s version 0.%d.%d beta test release %d"), (LPCTSTR)ProductName, fi->dwFileVersionMS & 0xFFFF, fi->dwFileVersionLS >> 16, fi->dwFileVersionLS & 0xFFFF);
				else
					//final version
					version.Format(_T("%s version 0.%d.%d beta"), (LPCTSTR)ProductName, fi->dwFileVersionMS&0xFFFF, fi->dwFileVersionLS >> 16);
		}
		
	}
	delete [] str;
	delete [] pBlock;
	return version;
}
