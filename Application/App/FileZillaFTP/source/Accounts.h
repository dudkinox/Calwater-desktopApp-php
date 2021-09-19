#ifndef ACCOUNTS_H_INCLUDED
#define ACCOUNTS_H_INCLUDED

#ifdef _AFX
#define CStdString CString
#define CStdStringW CStringW
#define CStdStringA CStringA
#endif //_AFX

#include "SpeedLimit.h"

class t_directory
{
public:
	t_directory();
#ifdef SERVICE
	CStdString dir;
	std::list<CStdString> aliases;
#else
	CStdString dir;
	std::list<CStdString> aliases;
#endif
	BOOL bFileRead, bFileWrite, bFileDelete, bFileAppend;
	BOOL bDirCreate, bDirDelete, bDirList, bDirSubdirs, bIsHome;
	BOOL bAutoCreate;
};

enum sltype
{
	download = 0,
	upload = 1
};

class t_group
{
public:
	t_group();

	virtual int GetRequiredBufferLen() const;
	virtual int GetRequiredStringBufferLen(const CStdString& str) const;
	virtual char * FillBuffer(char *p) const;
	virtual void FillString(char *&p, const CStdString& str) const;
	virtual unsigned char * ParseBuffer(unsigned char *pBuffer, int length);

	virtual bool BypassUserLimit() const;
	virtual int GetUserLimit() const;
	virtual int GetIpLimit() const;
	virtual bool IsEnabled() const;
	virtual bool ForceSsl() const;

	virtual int GetCurrentSpeedLimit(sltype type) const;
	virtual bool BypassServerSpeedLimit(sltype type) const;

	bool AccessAllowed(const CStdString& ip) const;

	virtual t_group& t_group::operator=(const t_group &a);

	CStdString group;
	std::vector<t_directory> permissions;
	int nBypassUserLimit;
	int nUserLimit, nIpLimit;
	int nEnabled;
	int forceSsl;

	int nSpeedLimitType[2];
	int nSpeedLimit[2];
	SPEEDLIMITSLIST SpeedLimits[2];
	int nBypassServerSpeedLimit[2];
	
	std::list<CStdString> allowedIPs, disallowedIPs;

	CStdString comment;

	t_group *pOwner;

protected:
	bool ParseString(const unsigned char* endMarker, unsigned char *&p, CStdString &string);
};

class t_user : public t_group
{
public:
	t_user();

	virtual int GetRequiredBufferLen() const;
	virtual char * FillBuffer(char *p) const;
	virtual unsigned char * ParseBuffer(unsigned char *pBuffer, int length);

	virtual t_user& t_user::operator=(const t_user &a);

	CStdString user;
	CStdString password;
};

#endif //#define ACCOUNTS_H_INCLUDED
