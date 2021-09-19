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

// OptionsGeneralWelcomemessagePage.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "filezilla server.h"
#include "OptionsDlg.h"
#include "OptionsPage.h"
#include "OptionsGeneralWelcomemessagePage.h"

#if defined(_DEBUG) && !defined(MMGR)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COptionsGeneralWelcomemessagePage 


COptionsGeneralWelcomemessagePage::COptionsGeneralWelcomemessagePage(COptionsDlg *pOptionsDlg, CWnd* pParent /*=NULL*/)
	: COptionsPage(pOptionsDlg, COptionsGeneralWelcomemessagePage::IDD, pParent)
	, m_hideWelcomeMessage(FALSE)
{
	//{{AFX_DATA_INIT(COptionsGeneralWelcomemessagePage)
	m_WelcomeMessage = _T("");
	//}}AFX_DATA_INIT
}


void COptionsGeneralWelcomemessagePage::DoDataExchange(CDataExchange* pDX)
{
	COptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsGeneralWelcomemessagePage)
	DDX_Text(pDX, IDC_OPTIONS_GENERAL_WELCOMEMESSAGE_WELCOMEMESSAGE, m_WelcomeMessage);
	DDV_MaxChars(pDX, m_WelcomeMessage, 7500);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_OPTIONS_WELCOMEMESSAGE_HIDE, m_hideWelcomeMessage);
}


BEGIN_MESSAGE_MAP(COptionsGeneralWelcomemessagePage, COptionsPage)
	//{{AFX_MSG_MAP(COptionsGeneralWelcomemessagePage)
		// HINWEIS: Der Klassen-Assistent f�gt hier Zuordnungsmakros f�r Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten COptionsGeneralWelcomemessagePage 

void COptionsGeneralWelcomemessagePage::LoadData()
{
	m_WelcomeMessage = m_pOptionsDlg->GetOption(OPTION_WELCOMEMESSAGE);
	m_hideWelcomeMessage = m_pOptionsDlg->GetOptionVal(OPTION_WELCOMEMESSAGE_HIDE) != 0;
}

void COptionsGeneralWelcomemessagePage::SaveData()
{
	CString msg = m_WelcomeMessage;
	std::list<CString> msgLines;
	int oldpos = 0;
	msg.Replace(_T("\r\n"), _T("\n"));
	int pos = msg.Find(_T("\n"));
	CString line;
	while (pos != -1)
	{
		if (pos)
		{
			line = msg.Mid(oldpos, pos - oldpos);
			line = line.Left(CONST_WELCOMEMESSAGE_LINESIZE);
			line.TrimRight(_T(" "));
			if (msgLines.size() || line != _T(""))
				msgLines.push_back(line);
		}
		oldpos = pos + 1;
		pos = msg.Find(_T("\n"), oldpos);
	}
	line = msg.Mid(oldpos);
	if (line != _T(""))
		msgLines.push_back(line);
	msg = _T("");
	for (std::list<CString>::iterator iter = msgLines.begin(); iter != msgLines.end(); iter++)
		msg += *iter + _T("\r\n");
	msg.TrimRight(_T("\r\n"));

	m_pOptionsDlg->SetOption(OPTION_WELCOMEMESSAGE, msg);
	m_pOptionsDlg->SetOption(OPTION_WELCOMEMESSAGE_HIDE, m_hideWelcomeMessage);
}