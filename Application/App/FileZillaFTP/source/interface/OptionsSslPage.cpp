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
#include "filezilla server.h"
#include "OptionsDlg.h"
#include "OptionsPage.h"
#include "OptionsSslPage.h"
#include "GenerateCertificateDlg.h"
#include "../AsyncSslSocketLayer.h"
#include <set>

COptionsSslPage::COptionsSslPage(COptionsDlg *pOptionsDlg, CWnd* pParent /*=NULL*/)
	: COptionsPage(pOptionsDlg, COptionsSslPage::IDD, pParent)
	, m_enabled(FALSE)
	, m_allowExplicit(FALSE)
	, m_certificate(_T(""))
	, m_sslports(_T(""))
{
}

COptionsSslPage::~COptionsSslPage()
{
}

void COptionsSslPage::DoDataExchange(CDataExchange* pDX)
{
	COptionsPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_ENABLESSL, m_enabled);
	DDX_Check(pDX, IDC_ALLOWEXPLICIT, m_allowExplicit);
	DDX_Check(pDX, IDC_FORCEEXPLICIT, m_forceExplicit);
	DDX_Check(pDX, IDC_FORCEPROTP, m_forceProtP);
	DDX_Text(pDX, IDC_CERTIFICATE, m_certificate);
	DDX_Text(pDX, IDC_PRIVATEKEY, m_key);
	DDX_Text(pDX, IDC_KEYPASS, m_pass);
	DDX_Text(pDX, IDC_SSLONLY, m_sslports);
	DDX_Control(pDX, IDC_ALLOWEXPLICIT, m_cAllowExplicit);
	DDX_Control(pDX, IDC_FORCEEXPLICIT, m_cForceExplicit);
	DDX_Control(pDX, IDC_FORCEPROTP, m_cForceProtP);
	DDX_Control(pDX, IDC_CERTIFICATE, m_cCertificate);
	DDX_Control(pDX, IDC_CERTIFICATE_BROWSE, m_cCertificateBrowse);
	DDX_Control(pDX, IDC_PRIVATEKEY, m_cKey);
	DDX_Control(pDX, IDC_PRIVATEKEY_BROWSE, m_cKeyBrowse);
	DDX_Control(pDX, IDC_SSLONLY, m_cSslports);
	DDX_Control(pDX, IDC_KEYPASS, m_cPass);
}

BEGIN_MESSAGE_MAP(COptionsSslPage, COptionsPage)
	ON_BN_CLICKED(IDC_GENERATE, OnGenerate)
	ON_BN_CLICKED(IDC_PRIVATEKEY_BROWSE, OnKeyBrowse)
	ON_BN_CLICKED(IDC_CERTIFICATE_BROWSE, OnCertificateBrowse)
	ON_BN_CLICKED(IDC_ENABLESSL, OnEnableSsl)
	ON_BN_CLICKED(IDC_ALLOWEXPLICIT, OnEnableSsl)
END_MESSAGE_MAP()

void COptionsSslPage::OnGenerate()
{
	UpdateData();
	CGenerateCertificateDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_key = dlg.m_file;
		m_certificate = dlg.m_file;
		UpdateData(FALSE);
	}
}

void COptionsSslPage::OnKeyBrowse()
{
	UpdateData();
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_key = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void COptionsSslPage::OnCertificateBrowse()
{
	UpdateData();
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_certificate = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void COptionsSslPage::OnEnableSsl()
{
	UpdateData();
	m_cAllowExplicit.EnableWindow(m_enabled);
	m_cCertificate.EnableWindow(m_enabled);
	m_cCertificateBrowse.EnableWindow(m_enabled && m_pOptionsDlg->IsLocalConnection());
	m_cKey.EnableWindow(m_enabled);
	m_cKeyBrowse.EnableWindow(m_enabled && m_pOptionsDlg->IsLocalConnection());
	m_cSslports.EnableWindow(m_enabled);
	m_cForceExplicit.EnableWindow(m_enabled && m_allowExplicit);
	m_cForceProtP.EnableWindow(m_enabled);
	m_cPass.EnableWindow(m_enabled);
}

BOOL COptionsSslPage::IsDataValid()
{
	USES_CONVERSION;

	UpdateData();

	std::set<int> portSet;
	bool valid = true;

	CString ports = m_sslports;
	ports.TrimLeft(_T(" ,"));

	int pos = ports.FindOneOf(_T(" ,"));
	while (pos != -1 && valid)
	{
		int port = _ttoi(ports.Left(pos));
		if (port < 1 || port > 65535)
		{
			valid = false;
			break;
		}
		else
			portSet.insert(port);
		ports = ports.Mid(pos + 1);
		ports.TrimLeft(_T(" ,"));
		pos = ports.FindOneOf(_T(" ,"));
	}
	if (valid && ports != _T(""))
	{
		int port = _ttoi(ports);
		if (port < 1 || port > 65535)
			valid = false;
		else
			portSet.insert(port);
	}

	if (!valid && m_enabled)
	{
		m_pOptionsDlg->ShowPage(this);
		m_cSslports.SetFocus();
		AfxMessageBox(_T("Invalid port found, please only enter ports in the range from 1 to 65535."));
		return FALSE;
	}

	m_sslports = _T("");
	for (std::set<int>::const_iterator iter = portSet.begin(); iter != portSet.end(); iter++)
	{
		CString tmp;
		tmp.Format(_T("%d "), *iter);
		m_sslports += tmp;
	}
	m_sslports.TrimRight(' ');
	UpdateData(false);

	if (m_enabled && m_pOptionsDlg->IsLocalConnection())
	{
		CAsyncSslSocketLayer layer;
		CString error;
		int res = layer.SetCertKeyFile(T2A(m_certificate), T2A(m_key), T2A(m_pass), &error);
		if (res == SSL_FAILURE_LOADDLLS)
		{
			m_pOptionsDlg->ShowPage(this);
			AfxMessageBox(_T("Failed to load SSL libraries"));
			return FALSE;
		}
		else if (res == SSL_FAILURE_INITSSL)
		{
			m_pOptionsDlg->ShowPage(this);
			AfxMessageBox(_T("Failed to initialize SSL libraries"));
			return FALSE;
		}
		else if (res == SSL_FAILURE_VERIFYCERT)
		{
			m_pOptionsDlg->ShowPage(this);
			if (error != _T(""))
				AfxMessageBox(error);
			else
				AfxMessageBox(_T("Failed to set certificate and private key"));
			return FALSE;
		}
		else if (res)
		{
			m_pOptionsDlg->ShowPage(this);
			return FALSE;
		}
	}

	return true;
}

void COptionsSslPage::SaveData()
{
	m_pOptionsDlg->SetOption(OPTION_ENABLESSL, m_enabled ? 1 : 0);
	m_pOptionsDlg->SetOption(OPTION_SSLKEYFILE, m_key);
	m_pOptionsDlg->SetOption(OPTION_SSLKEYPASS, m_pass);
	m_pOptionsDlg->SetOption(OPTION_SSLCERTFILE, m_certificate);
	m_pOptionsDlg->SetOption(OPTION_SSLPORTS, m_sslports);
	m_pOptionsDlg->SetOption(OPTION_ALLOWEXPLICITSSL, m_allowExplicit ? 1 : 0);
	m_pOptionsDlg->SetOption(OPTION_SSLFORCEEXPLICIT, m_forceExplicit ? 1 : 0);
	m_pOptionsDlg->SetOption(OPTION_FORCEPROTP, m_forceProtP ? 1 : 0);
}

void COptionsSslPage::LoadData()
{
	m_enabled = m_pOptionsDlg->GetOptionVal(OPTION_ENABLESSL) != 0;
	m_key = m_pOptionsDlg->GetOption(OPTION_SSLKEYFILE);
	m_pass = m_pOptionsDlg->GetOption(OPTION_SSLKEYPASS);
	m_certificate = m_pOptionsDlg->GetOption(OPTION_SSLCERTFILE);
	m_sslports = m_pOptionsDlg->GetOption(OPTION_SSLPORTS);
	m_allowExplicit = m_pOptionsDlg->GetOptionVal(OPTION_ALLOWEXPLICITSSL) != 0;
	m_forceExplicit = m_pOptionsDlg->GetOptionVal(OPTION_SSLFORCEEXPLICIT) != 0;
	m_forceProtP = m_pOptionsDlg->GetOptionVal(OPTION_FORCEPROTP) != 0;
}

BOOL COptionsSslPage::OnInitDialog()
{
	COptionsPage::OnInitDialog();

	OnEnableSsl();

	return TRUE;
}
