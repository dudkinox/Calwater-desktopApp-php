// AdminListenSocket.cpp: Implementierung der Klasse CAdminListenSocket.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AdminListenSocket.h"
#include "AdminSocket.h"
#include "AdminInterface.h"
#include "Options.h"
#include "iputils.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CAdminListenSocket::CAdminListenSocket(CAdminInterface *pAdminInterface)
{
	ASSERT(pAdminInterface);
	m_pAdminInterface = pAdminInterface;
}

CAdminListenSocket::~CAdminListenSocket()
{
}

void CAdminListenSocket::OnAccept(int nErrorCode)
{
	CAdminSocket *pSocket = new CAdminSocket(m_pAdminInterface);

	SOCKADDR_IN sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	
	if (Accept(*pSocket))
	{
		//Validate IP address
		CStdString ip;
		UINT port = 0;

		bool allowed = false;
		if (pSocket->GetPeerName(ip, port))
		{
			if (!IsLocalhost(ip))
			{
				COptions options;

				// Get the list of IP filter rules.
				CStdString ips = options.GetOption(OPTION_ADMINIPADDRESSES);
				ips += _T(" ");

				int pos = ips.Find(' ');
				while (pos != -1)
				{
					CStdString filter = ips.Left(pos);
					ips = ips.Mid(pos + 1);
					pos = ips.Find(' ');

					if ((allowed = MatchesFilter(filter, ip)))
						break;
				}
			}
			else
				allowed = true;
		}

		if (!allowed)
		{
			delete pSocket;
			return;
		}

		pSocket->AsyncSelect();
		if (!m_pAdminInterface->Add(pSocket))
			delete pSocket;
	}
}