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

// UsersDlgIpFilter.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "FileZilla server.h"
#include "UsersDlgIpFilter.h"
#include "UsersDlg.h"
#include "..\iputils.h"

#if defined(_DEBUG) && !defined(MMGR)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CUsersDlgIpFilter 

CUsersDlgIpFilter::CUsersDlgIpFilter(CUsersDlg* pOwner) 
	: CSAPrefsSubDlg(IDD)
{
	m_pOwner = pOwner;
	
	m_pUser = 0;
}

CUsersDlgIpFilter::~CUsersDlgIpFilter()
{
}


void CUsersDlgIpFilter::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsersDlgIpFilter)
	DDX_Text(pDX, IDC_USERS_IPFILTER_ALLOWED, m_AllowedAddresses);
	DDX_Text(pDX, IDC_USERS_IPFILTER_DISALLOWED, m_DisallowedAddresses);
	DDV_MaxChars(pDX, m_AllowedAddresses, 20000);
	DDV_MaxChars(pDX, m_DisallowedAddresses, 20000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsersDlgIpFilter, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CUsersDlgIpFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CUsersDlgIpFilter 

BOOL CUsersDlgIpFilter::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

CString CUsersDlgIpFilter::Validate()
{
	UpdateData(TRUE);

	if (!ParseIPFilter(m_DisallowedAddresses))
	{
		GetDlgItem(IDC_USERS_IPFILTER_DISALLOWED)->SetFocus();
		return _T("Invalid IP address/range/mask");
	}

	if (!ParseIPFilter(m_AllowedAddresses))
	{
		GetDlgItem(IDC_USERS_IPFILTER_ALLOWED)->SetFocus();
		return _T("Invalid IP address/range/mask");
	}

	return _T("");
}

void CUsersDlgIpFilter::SetCtrlState()
{
	if (!m_pOwner->GetCurrentUser())
	{
		GetDlgItem(IDC_USERS_IPFILTER_ALLOWED)->EnableWindow(FALSE);
		GetDlgItem(IDC_USERS_IPFILTER_DISALLOWED)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_USERS_IPFILTER_ALLOWED)->EnableWindow(TRUE);
		GetDlgItem(IDC_USERS_IPFILTER_DISALLOWED)->EnableWindow(TRUE);
	}
}

BOOL CUsersDlgIpFilter::DisplayUser(t_user *pUser)
{
	m_pUser = pUser;

	m_DisallowedAddresses = _T("");
	m_AllowedAddresses = _T("");

	if (!pUser)
	{
		UpdateData(FALSE);

		return TRUE;
	}

	std::list<CString>::const_iterator iter;
	for (iter = pUser->disallowedIPs.begin(); iter != pUser->disallowedIPs.end(); iter++)
		m_DisallowedAddresses += *iter + "\r\n";
	for (iter = pUser->allowedIPs.begin(); iter != pUser->allowedIPs.end(); iter++)
		m_AllowedAddresses += *iter + "\r\n";
	
	UpdateData(FALSE);
	
	return TRUE;
}

BOOL CUsersDlgIpFilter::SaveUser(t_user *pUser)
{
	if (!pUser)
		return FALSE;

	UpdateData(TRUE);

	pUser->disallowedIPs.clear();
	pUser->allowedIPs.clear();

	ParseIPFilter(m_DisallowedAddresses, &pUser->disallowedIPs);
	ParseIPFilter(m_AllowedAddresses, &pUser->allowedIPs);
	
	return TRUE;
}
