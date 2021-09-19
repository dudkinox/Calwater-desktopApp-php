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

#include "stdafx.h"
#include "autobanmanager.h"
#include "Options.h"

int CAutoBanManager::m_refCount = 0;
std::map<CStdString, time_t> CAutoBanManager::m_banMap;
std::map<CStdString, CAutoBanManager::t_attemptInfo> CAutoBanManager::m_attemptMap;

CCriticalSectionWrapper CAutoBanManager::m_sync;

CAutoBanManager::CAutoBanManager(COptions* pOptions)
	: m_pOptions(pOptions)
{
	m_sync.Lock();
	m_refCount++;
	m_sync.Unlock();
}

CAutoBanManager::~CAutoBanManager()
{
	m_sync.Lock();
	m_refCount--;
	if (!m_refCount)
	{
		m_banMap.clear();
		m_attemptMap.clear();
	}
	m_sync.Unlock();
}

bool CAutoBanManager::IsBanned(const CStdString& ip)
{
	bool enabled = m_pOptions->GetOptionVal(OPTION_AUTOBAN_ENABLE) != 0;
	if (!enabled)
		return false;

	m_sync.Lock();
	bool banned = m_banMap.find(ip) != m_banMap.end();
	m_sync.Unlock();
	
	return banned;
}

bool CAutoBanManager::RegisterAttempt(const CStdString& ip)
{
	bool enabled = m_pOptions->GetOptionVal(OPTION_AUTOBAN_ENABLE) != 0;
	if (!enabled)
		return false;

	const int maxAttempts = (int)m_pOptions->GetOptionVal(OPTION_AUTOBAN_ATTEMPTS);
	const int banType = (int)m_pOptions->GetOptionVal(OPTION_AUTOBAN_TYPE);

	m_sync.Lock();
	if (m_banMap.find(ip) != m_banMap.end())
	{
		m_sync.Unlock();
		return true;
	}

	std::map<CStdString, t_attemptInfo>::iterator iter = m_attemptMap.find(ip);
	if (iter == m_attemptMap.end())
	{
		t_attemptInfo info;
		info.attempts = 1;
		info.time = time(0);
		m_attemptMap[ip] = info;
	}
	else
	{
		if (++iter->second.attempts >= maxAttempts)
		{
			m_attemptMap.erase(iter);

			if (!banType)
				m_banMap[ip] = time(0);
			else
			{
				// TODO
			}
			
			m_sync.Unlock();
			return true;
		}
		else
			iter->second.time = time(0);
	}

	m_sync.Unlock();

    return false;
}

void CAutoBanManager::PurgeOutdated()
{
	const int banTime = (int)m_pOptions->GetOptionVal(OPTION_AUTOBAN_BANTIME) * 60 * 60;

	time_t now = time(0);

	m_sync.Lock();
	std::map<CStdString, time_t>::iterator iter = m_banMap.begin();
	while (iter != m_banMap.end())
	{
		const time_t diff = now - iter->second;
		if (diff > banTime)
		{
			std::map<CStdString, time_t>::iterator remove = iter++;
			m_banMap.erase(remove);
		}
		else
			iter++;
	}

	{
		std::map<CStdString, t_attemptInfo>::iterator iter = m_attemptMap.begin();
		while (iter != m_attemptMap.end())
		{
			const time_t diff = now - iter->second.time;
			if (diff > banTime)
			{
				std::map<CStdString, t_attemptInfo>::iterator remove = iter++;
				m_attemptMap.erase(remove);
			}
			else
				iter++;
		}
	}

	m_sync.Unlock();
}
