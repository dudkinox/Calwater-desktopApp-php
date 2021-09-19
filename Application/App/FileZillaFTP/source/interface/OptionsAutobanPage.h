// FileZilla Server - a Windows ftp server

// Copyright (C) 2002-2007 - Tim Kosse <tim.kosse@gmx.de>

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

#if !defined(AFX_OptionsAutobanPage_H__F0686D50_BB18_4BD7_B9E5_6498A7593F9F__INCLUDED_)
#define AFX_OptionsAutobanPage_H__F0686D50_BB18_4BD7_B9E5_6498A7593F9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COptionsDlg;
class COptionsAutobanPage : public COptionsPage
{
// Konstruktion
public:
	COptionsAutobanPage(COptionsDlg *pOptionsDlg, CWnd* pParent = NULL);   // Standardkonstruktor

	virtual void SaveData();
	virtual void LoadData();
	virtual BOOL IsDataValid();

// Dialogfelddaten
	//{{AFX_DATA(COptionsAutobanPage)
	enum { IDD = IDD_OPTIONS_AUTOBAN };
	BOOL	m_enable;
	CString	m_attempts;
	CString	m_time;
	int		m_type;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(COptionsAutobanPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(COptionsAutobanPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_OptionsAutobanPage_H__F0686D50_BB18_4BD7_B9E5_6498A7593F9F__INCLUDED_
