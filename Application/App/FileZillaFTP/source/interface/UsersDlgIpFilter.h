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

#if !defined(AFX_USERSDLGIPFILTER_H__5348112C_F36E_42D1_B073_78272B897DDA__INCLUDED_)
#define AFX_USERSDLGIPFILTER_H__5348112C_F36E_42D1_B073_78272B897DDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UsersDlg.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CUsersDlgIpFilter 
class CUsersDlgIpFilter : public CSAPrefsSubDlg
{
	friend CUsersDlg;
// Konstruktion
public:
	CUsersDlgIpFilter(CUsersDlg* pOwner = NULL);   // Standardkonstruktor
	~CUsersDlgIpFilter();

	BOOL DisplayUser(t_user *pUser);
	BOOL SaveUser(t_user *pUser);

protected:
	t_user *m_pUser;

// Dialogfelddaten
	//{{AFX_DATA(CUsersDlgIpFilter)
	enum { IDD = IDD_USERS_IPFILTER };
	CString	m_AllowedAddresses;
	CString	m_DisallowedAddresses;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CUsersDlgIpFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CUsersDlg *m_pOwner;
	void SetCtrlState();
	CString Validate();

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CUsersDlgIpFilter)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_USERSDLGIPFILTER_H__5348112C_F36E_42D1_B073_78272B897DDA__INCLUDED_
