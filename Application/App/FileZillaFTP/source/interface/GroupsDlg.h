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

#if !defined(AFX_GROUPSDLG_H__3548112C_F36E_42D1_B073_78272B897DDA__INCLUDED_)
#define AFX_GROUPSDLG_H__3548112C_F36E_42D1_B073_78272B897DDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GroupsDlg.h : Header-Datei
//

#include "..\Accounts.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CGroupsDlg 
class CGroupsDlgGeneral;
class CGroupsDlgSpeedLimit;
class CGroupsDlgSharedFolders;
class CGroupsDlgIpFilter;

class CGroupsDlg : public CSAPrefsDialog
{
// Konstruktion
public:
	CGroupsDlg(CWnd* pParent, bool localConnection);
	~CGroupsDlg();
	BOOL GetAsCommand(char **pBuffer, DWORD *nBufferLength);
	BOOL Init(unsigned char *pData, DWORD dwDataLength);
	t_group* GetCurrentGroup();
	bool IsLocalConnection() const { return m_localConnection; }

protected:
// Dialogfelddaten
	//{{AFX_DATA(CGroupsDlg)
	enum { IDD = IDD_GROUPS };
	CListBox	m_cGrouplist;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CGroupsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CGroupsDlgGeneral *m_pGeneralPage;
	CGroupsDlgSpeedLimit *m_pSpeedLimitPage;
	CGroupsDlgSharedFolders *m_pSharedFoldersPage;
	CGroupsDlgIpFilter *m_pIpFilterPage;

	void SetCtrlState();
	int m_oldgroup;
	BOOL Validate();
	
	typedef std::vector<t_group> t_GroupsList; 
	typedef std::vector<t_user> t_UsersList;
	t_GroupsList m_GroupsList;
	t_UsersList m_UsersList;
	bool m_localConnection;
	bool m_insideSelchange;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CGroupsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeGrouplist();
	virtual void OnOK();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnGroupAdd();
	afx_msg void OnGroupCopy();
	afx_msg void OnGroupRemove();
	afx_msg void OnGroupRename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_GROUPSDLG_H__3548112C_F36E_42D1_B073_78272B897DDA__INCLUDED_
