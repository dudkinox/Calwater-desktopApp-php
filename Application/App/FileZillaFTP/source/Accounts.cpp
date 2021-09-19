#include "stdafx.h"
#include "accounts.h"
#include "iputils.h"

t_directory::t_directory()
{
	bAutoCreate = FALSE;
}

t_group::t_group()
{
	pOwner = NULL;

	for (int i = 0; i < 2; i++)
	{
		nSpeedLimitType[i] = 0;
		nSpeedLimit[i] = 10;
		nBypassServerSpeedLimit[i] = 0;
	}
	nEnabled = 1;
	forceSsl = 0;
}

t_group& t_group::operator=(const t_group &a)
{
	group = a.group;
	nBypassUserLimit = a.nBypassUserLimit;
	nUserLimit = a.nUserLimit;
	nIpLimit = a.nIpLimit;
	permissions = a.permissions;
	nEnabled = a.nEnabled;
	disallowedIPs = a.disallowedIPs;
	allowedIPs = a.allowedIPs;
	comment = a.comment;
	forceSsl = a.forceSsl;

	for (int i = 0; i < 2; i++)
	{
		nBypassServerSpeedLimit[i] = a.nBypassServerSpeedLimit[i];
		nSpeedLimit[i] = a.nSpeedLimit[i];
		nSpeedLimitType[i] = a.nSpeedLimitType[i];
		SpeedLimits[i] = a.SpeedLimits[i];
	}

	return *this;
}

bool t_group::BypassUserLimit() const
{
	if (!nBypassUserLimit)
		return false;
	if (nBypassUserLimit == 2 && pOwner)
		return pOwner->BypassUserLimit();
	return true;
}

int t_group::GetIpLimit() const
{
	if (nIpLimit)
		return nIpLimit;
	if (pOwner)
		return pOwner->GetIpLimit();
	return 0;
}

int t_group::GetUserLimit() const
{
	if (nUserLimit)
		return nUserLimit;
	if (pOwner)
		return pOwner->GetUserLimit();
	return 0;
}

t_user::t_user()
{
}

t_user& t_user::operator=(const t_user &a)
{
	group = a.group;
	pOwner = a.pOwner;
	user=a.user;
	password=a.password;
	nBypassUserLimit = a.nBypassUserLimit;
	nUserLimit = a.nUserLimit;
	nIpLimit = a.nIpLimit;
	permissions = a.permissions;
	nEnabled = a.nEnabled;
	disallowedIPs = a.disallowedIPs;
	allowedIPs = a.allowedIPs;
	comment = a.comment;
	forceSsl = a.forceSsl;

	for (int i = 0; i < 2; i++)
	{
		nBypassServerSpeedLimit[i] = a.nBypassServerSpeedLimit[i];
		nSpeedLimit[i] = a.nSpeedLimit[i];
		nSpeedLimitType[i] = a.nSpeedLimitType[i];
		SpeedLimits[i] = a.SpeedLimits[i];
	}

	return *this;
}

unsigned char * t_group::ParseBuffer(unsigned char *pBuffer, int length)
{
	unsigned char *p = pBuffer;
	unsigned char *endMarker = pBuffer + length;

	if (!ParseString(endMarker, p, group))
		return 0;

	if ((endMarker - p) < 11)
		return NULL;

	memcpy(&nIpLimit, p, 4);
	p += 4;
	memcpy(&nUserLimit, p, 4);
	p += 4;

	int options = *p++;

	nBypassUserLimit	= options & 0x03;
	nEnabled			= (options >> 2) & 0x03;

	// Parse IP filter rules.
	int numDisallowedIPs = (int(*p) << 8) + p[1];
	p += 2;
	while (numDisallowedIPs--)
	{
		CStdString ip;
		if (!ParseString(endMarker, p, ip))
			return 0;

		if (IsValidAddressFilter(ip) || ip == _T("*"))
			disallowedIPs.push_back(ip);
	}

	if ((endMarker - p) < 2)
		return NULL;

	int numAllowedIPs = (int(*p) << 8) + p[1];
	p += 2;
	while (numAllowedIPs--)
	{
		CStdString ip;
		if (!ParseString(endMarker, p, ip))
			return 0;

		if (IsValidAddressFilter(ip) || ip == _T("*"))
			allowedIPs.push_back(ip);
	}

	if ((endMarker - p) < 2)
		return NULL;

	int dircount = (int(*p) << 8) + p[1];
	p += 2;

	BOOL bGotHome = FALSE;

	for (int j = 0; j < dircount; j++)
	{
		t_directory dir;

		CStdString str;
		if (!ParseString(endMarker, p, str))
			return 0;

		str.TrimRight(_T("\\"));
		if (str == _T(""))
			return 0;

		dir.dir = str;

		// Get directory aliases.
		if ((endMarker - p) < 2)
			return NULL;

		int aliascount = (int(*p) << 8) + p[1];
		p += 2;

		for (int i = 0; i < aliascount; i++)
		{
			CStdString alias;
			if (!ParseString(endMarker, p, alias))
				return 0;

			alias.TrimRight(_T("\\"));

			if (alias == _T(""))
				return 0;

			dir.aliases.push_back(alias);
		}

		if ((endMarker - p) < 2)
			return NULL;

		int rights = (int(*p) << 8) + p[1];
		p += 2;

		dir.bDirCreate	= rights & 0x0001 ? 1:0;
		dir.bDirDelete	= rights & 0x0002 ? 1:0;
		dir.bDirList	= rights & 0x0004 ? 1:0;
		dir.bDirSubdirs	= rights & 0x0008 ? 1:0;
		dir.bFileAppend	= rights & 0x0010 ? 1:0;
		dir.bFileDelete	= rights & 0x0020 ? 1:0;
		dir.bFileRead	= rights & 0x0040 ? 1:0;
		dir.bFileWrite	= rights & 0x0080 ? 1:0;
		dir.bIsHome		= rights & 0x0100 ? 1:0;
		dir.bAutoCreate	= rights & 0x0200 ? 1:0;

		// Avoid multiple home directories.
		if (dir.bIsHome)
			if (!bGotHome)
				bGotHome = TRUE;
			else
				dir.bIsHome = FALSE;

		permissions.push_back(dir);
	}

	for (int i = 0; i < 2; i++)
	{
		if ((endMarker - p) < 5)
			return NULL;

		nSpeedLimitType[i] = *p & 3;
		nBypassServerSpeedLimit[i] = (*p++ >> 2) & 3;

		nSpeedLimit[i] = int(*p++) << 8;
		nSpeedLimit[i] |= *p++;
	
		if (!nSpeedLimit[i])
			nSpeedLimit[i] = 10;

		int num = (int(*p) << 8) + p[1];
		p += 2;
		while (num--)
		{
			CSpeedLimit sl;
			p = sl.ParseBuffer(p, length-(int)(p-pBuffer));
			if (!p)
				return NULL;
			SpeedLimits[i].push_back(sl);
		}
	}

	if (!ParseString(endMarker, p, comment))
		return 0;

	if (p >= endMarker)
		return 0;

	forceSsl = *p++;

	return p;
}

int t_group::GetRequiredStringBufferLen(const CStdString& str) const
{
	char* utf8 = ConvToNetwork(str);

	if (!utf8)
		return 2;

	int len = strlen(utf8);

	delete [] utf8;

	return len + 2;
}

void t_group::FillString(char *& p, const CStdString& str) const
{
	char* utf8 = ConvToNetwork(str);

	if (!utf8)
	{
		*p++ = 0;
		*p++ = 0;
		return;
	}

	int len = strlen(utf8);
	*p++ = (char)(len >> 8);
	*p++ = (char)(len & 0xff);

	memcpy(p, utf8, len);
	p += len;

	delete [] utf8;
}

char * t_group::FillBuffer(char *p) const
{
	FillString(p, group);
	
	memcpy(p, &nIpLimit, 4);
	p += 4;
	memcpy(p, &nUserLimit, 4);
	p += 4;

	int options = nBypassUserLimit & 3;
	options |= (nEnabled & 3) << 2;

	*p++ = options & 0xff;

	std::list<CStdString>::const_iterator ipLimitIter;

	*p++ = (char)(disallowedIPs.size() >> 8);
	*p++ = (char)(disallowedIPs.size() & 0xff);
	for (ipLimitIter = disallowedIPs.begin(); ipLimitIter != disallowedIPs.end(); ipLimitIter++)
		FillString(p, *ipLimitIter);

	*p++ = (char)(allowedIPs.size() >> 8);
	*p++ = (char)(allowedIPs.size() & 0xff);
	for (ipLimitIter = allowedIPs.begin(); ipLimitIter != allowedIPs.end(); ipLimitIter++)
		FillString(p, *ipLimitIter);

	*p++ = (char)(permissions.size() >> 8);
	*p++ = (char)(permissions.size() & 0xff);
	for (std::vector<t_directory>::const_iterator permissioniter = permissions.begin(); permissioniter!=permissions.end(); permissioniter++)
	{
		FillString(p, permissioniter->dir);

		*p++ = (char)(permissioniter->aliases.size() >> 8);
		*p++ = (char)(permissioniter->aliases.size() & 0xff);
		for (std::list<CStdString>::const_iterator aliasiter = permissioniter->aliases.begin(); aliasiter != permissioniter->aliases.end(); aliasiter++)
			FillString(p, *aliasiter);

		int rights = 0;
		rights |= permissioniter->bDirCreate	? 0x0001:0;
		rights |= permissioniter->bDirDelete	? 0x0002:0;
		rights |= permissioniter->bDirList		? 0x0004:0;
		rights |= permissioniter->bDirSubdirs	? 0x0008:0;
		rights |= permissioniter->bFileAppend	? 0x0010:0;
		rights |= permissioniter->bFileDelete	? 0x0020:0;
		rights |= permissioniter->bFileRead		? 0x0040:0;
		rights |= permissioniter->bFileWrite	? 0x0080:0;
		rights |= permissioniter->bIsHome		? 0x0100:0;
		rights |= permissioniter->bAutoCreate	? 0x0200:0;
		*p++ = (char)(rights >> 8);
		*p++ = (char)(rights & 0xff);
	}

	for (int i = 0; i < 2; i++)
	{
		*p++ = (char)((nSpeedLimitType[i] & 3) + ((nBypassServerSpeedLimit[i] & 3) << 2));
		*p++ = (char)(nSpeedLimit[i] >> 8);
		*p++ = (char)(nSpeedLimit[i] & 0xff);

		SPEEDLIMITSLIST::const_iterator iter;

		*p++ = (char)(SpeedLimits[i].size() >> 8);
		*p++ = (char)(SpeedLimits[i].size() & 0xff);
		for (iter = SpeedLimits[i].begin(); (iter != SpeedLimits[i].end()) && p; iter++)
			p = iter->FillBuffer(p);
		if (!p)
			return NULL;
	}

	FillString(p, comment);

	*p++ = (char)forceSsl;

	return p;
}

int t_group::GetRequiredBufferLen() const
{
	int len = 9;
	len += GetRequiredStringBufferLen(group);

	len += 4;
	std::list<CStdString>::const_iterator ipLimitIter;
	for (ipLimitIter = disallowedIPs.begin(); ipLimitIter != disallowedIPs.end(); ipLimitIter++)
		len += GetRequiredStringBufferLen(*ipLimitIter);
	for (ipLimitIter = allowedIPs.begin(); ipLimitIter != allowedIPs.end(); ipLimitIter++)
		len += GetRequiredStringBufferLen(*ipLimitIter);

	len += 2;
	for (std::vector<t_directory>::const_iterator permissioniter = permissions.begin(); permissioniter!=permissions.end(); permissioniter++)
	{
		t_directory directory = *permissioniter;
		len += 2;

		len += GetRequiredStringBufferLen(directory.dir);

		len += 2;
		for (std::list<CStdString>::const_iterator aliasiter = permissioniter->aliases.begin(); aliasiter != permissioniter->aliases.end(); aliasiter++)
			len += GetRequiredStringBufferLen(*aliasiter);
	}

	// Speed limits.
	len += 6; // Basic limits.
	len += 4; // Number of rules.
	for (int i = 0; i < 2; i++)
	{
		SPEEDLIMITSLIST::const_iterator iter;
		for (iter = SpeedLimits[i].begin(); iter != SpeedLimits[i].end(); iter++)
			len += iter->GetRequiredBufferLen();
	}

	len += GetRequiredStringBufferLen(comment);

	len++; //forceSsl

	return len;
}

int t_group::GetCurrentSpeedLimit(sltype type) const
{
	switch (nSpeedLimitType[type])
	{
	case 0:
		if (pOwner)
			return pOwner->GetCurrentSpeedLimit(type);
		else
			return 0;
	case 1:
		return 0;
	case 2:
		return nSpeedLimit[type];
	case 3:
		{
			SYSTEMTIME st;
			GetLocalTime(&st);
			for (SPEEDLIMITSLIST::const_iterator iter = SpeedLimits[type].begin(); iter != SpeedLimits[type].end(); iter++)
				if (iter->IsItActive(st))
					return iter->m_Speed;
		}
		if (pOwner)
			return pOwner->GetCurrentSpeedLimit(type);
		else
			return 0;
	}
	return 0;
}

bool t_group::BypassServerSpeedLimit(sltype type) const
{
	if (nBypassServerSpeedLimit[type] == 1)
		return true;
	else if (!nBypassServerSpeedLimit[type])
		return false;
	else if (pOwner)
		return pOwner->BypassServerSpeedLimit(type);
	else
		return false;
}

bool t_group::IsEnabled() const
{
	switch (nEnabled)
	{
	default:
	case 0:
		return false;
	case 1:
		return true;
	case 2:
		if (!pOwner)
			return false;

		return pOwner->IsEnabled();
	}
}

bool t_group::AccessAllowed(const CStdString& ip) const
{
	bool disallowed = false;

	std::list<CStdString>::const_iterator iter;
	for (iter = disallowedIPs.begin(); iter != disallowedIPs.end(); iter++)
	{
		if (disallowed = MatchesFilter(*iter, ip))
			break;
	}

	if (!disallowed)
	{
		if (!pOwner)
			return true;

		if (pOwner->AccessAllowed(ip))
			return true;
	}

	for (iter = allowedIPs.begin(); iter != allowedIPs.end(); iter++)
	{
		if (MatchesFilter(*iter, ip))
			return true;
	}

	if (pOwner && !disallowed)
		return pOwner->AccessAllowed(ip);

	return false;
}

unsigned char * t_user::ParseBuffer(unsigned char *pBuffer, int length)
{
	unsigned char *p = pBuffer;
	unsigned char *endMarker = pBuffer + length;

	p = t_group::ParseBuffer(p, length);
	if (!p)
		return NULL;

	if (!ParseString(endMarker, p, user))
		return 0;

	if (!ParseString(endMarker, p, password))
		return 0;

	return p;
}

char * t_user::FillBuffer(char *p) const
{
	p = t_group::FillBuffer(p);
	if (!p)
		return NULL;

	FillString(p, user);
	FillString(p, password);

	return p;
}

int t_user::GetRequiredBufferLen() const
{
	int len = t_group::GetRequiredBufferLen();
	len += GetRequiredStringBufferLen(user);
	len += GetRequiredStringBufferLen(password);
	return len;
}

bool t_group::ParseString(const unsigned char* endMarker, unsigned char *&p, CStdString &string)
{
	if ((endMarker - p) < 2)
		return false;

	int len = *p * 256 + p[1];
	p += 2;

	if ((endMarker - p) < len)
		return false;
	char* tmp = new char[len + 1];
	tmp[len] = 0;
	memcpy(tmp, p, len);
	CStdStringW str = ConvFromNetwork((const char*)tmp);
	delete [] tmp;
	p += len;
#ifdef _UNICODE
	string = str;
#else
	string = ConvToLocal(str);
#endif
	
	return true;
}

bool t_group::ForceSsl() const
{
	switch (forceSsl)
	{
	default:
	case 0:
		return false;
	case 1:
		return true;
	case 2:
		if (!pOwner)
			return false;

		return pOwner->ForceSsl();
	}
}
