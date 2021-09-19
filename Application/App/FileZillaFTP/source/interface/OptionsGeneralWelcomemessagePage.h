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

#if !defined(AFX_OPTIONSGENERALWELCOMEMESSAGEPAGE_H__594F7F6C_AF38_4737_ABBD_CEB68D6058D8__INCLUDED_)
#define AFX_OPTIONSGENERALWELCOMEMESSAGEPAGE_H__594F7F6C_AF38_4737_ABBD_CEB68D6058D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsGeneralWelcomeMessagePage.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COptionsGeneralWelcomemessagePage 

class COptionsDlg;
class COptionsGeneralWelcomemessagePage : public COptionsPage
{
// Konstruktion
public:
	COptionsGeneralWelcomemessagePage(COptionsDlg *pOptionsDlg, CWnd* pParent = NULL);   // Standardkonstruktor

	virtual void SaveData();
	virtual void LoadData();

	// Dialogfelddaten
	//{{AFX_DATA(COptionsGeneralWelcomemessagePage)
	enum { IDD = IDD_OPTIONS_GENERAL_WELCOMEMESSAGE };
	CString	m_WelcomeMessage;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(COptionsGeneralWelcomemessagePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(COptionsGeneralWelcomemessagePage)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_hideWelcomeMessage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_OPTIONSWELCOMEMESSAGEPAGE_H__594F7F6C_AF38_4737_ABBD_CEB68D6058D8__INCLUDED_
