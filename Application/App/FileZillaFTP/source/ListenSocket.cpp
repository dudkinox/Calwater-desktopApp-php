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

// ListenSocket.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ListenSocket.h"
#include "ServerThread.h"
#include "Server.h"
#include "Options.h"
#include "iputils.h"
#include "autobanmanager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CListenSocket::CListenSocket(CServer *pServer, bool ssl)
{
	ASSERT(pServer);
	m_pServer = pServer;

	m_bLocked = FALSE;
	m_ssl = ssl;
}

CListenSocket::~CListenSocket()
{
}

/////////////////////////////////////////////////////////////////////////////
// Member-Funktion CListenSocket

void CListenSocket::OnAccept(int nErrorCode)
{
	CAsyncSocketEx socket;
	if (!Accept(socket))
	{
		int nError = WSAGetLastError();
		CStdString str;
		str.Format(_T("Failure in CListenSocket::OnAccept(%d) - call to CAsyncSocketEx::Accept failed, errorcode %d"), nErrorCode, nError);
		SendStatus(str, 1);
		SendStatus(_T("If you use a firewall, please check your firewall configuration"), 1);
		return;
	}

	if (!AccessAllowed(socket))
	{
		CStdStringA str = "550 No connections allowed from your IP\r\n";
		socket.Send(str, str.GetLength());
		return;
	}

	if (m_bLocked)
	{
		CStdStringA str = "421 Server is locked, please try again later.\r\n";
		socket.Send(str, str.GetLength());
		return;
	}

	int minnum = 255*255*255;
	CServerThread *pBestThread=0;;
	for (std::list<CServerThread *>::iterator iter=m_pThreadList->begin(); iter!=m_pThreadList->end(); iter++)
	{
		int num=(*iter)->GetNumConnections();
		if (num<minnum && (*iter)->IsReady())
		{
			minnum=num;
			pBestThread=*iter;
			if (!num)
				break;
		}
	}
	if (!pBestThread)
	{
		char str[] = "421 Server offline.";
		socket.Send(str, strlen(str)+1);
		socket.Close();
		return;
	}

	/* Disable Nagle algorithm. Most of the time single short strings get
	 * transferred over the control connection. Waiting for additional data
	 * where there will be most likely none affects performance.
	 */
	BOOL value = TRUE;
	socket.SetSockOpt(TCP_NODELAY, &value, sizeof(value), IPPROTO_TCP);

	SOCKET sockethandle = socket.Detach();

	pBestThread->AddSocket(sockethandle, m_ssl);

	CAsyncSocketEx::OnAccept(nErrorCode);
}

void CListenSocket::SendStatus(CStdString status, int type)
{
	m_pServer->ShowStatus(status, type);
}

bool CListenSocket::AccessAllowed(CAsyncSocketEx &socket) const
{
	CStdString peerIP;
	UINT port = 0;
	BOOL bResult = socket.GetPeerName(peerIP, port);
	if (!bResult)
		return true;

	if (m_pServer->m_pAutoBanManager)
	{
		if (m_pServer->m_pAutoBanManager->IsBanned(peerIP))
			return false;
	}

	bool disallowed = false;

	// Get the list of IP filter rules.
	CStdString ips = m_pServer->m_pOptions->GetOption(OPTION_IPFILTER_DISALLOWED);
	ips += _T(" ");

	int pos = ips.Find(' ');
	while (pos != -1)
	{
		CStdString blockedIP = ips.Left(pos);
		ips = ips.Mid(pos + 1);
		pos = ips.Find(' ');

		if ((disallowed = MatchesFilter(blockedIP, peerIP)))
			break;
	}

	if (!disallowed)
		return true;

	ips = m_pServer->m_pOptions->GetOption(OPTION_IPFILTER_ALLOWED);
	ips += _T(" ");

	pos = ips.Find(' ');
	while (pos != -1)
	{
		CStdString blockedIP = ips.Left(pos);
		ips = ips.Mid(pos + 1);
		pos = ips.Find(' ');

		if (MatchesFilter(blockedIP, peerIP))
			return true;
	}

	return false;
}
