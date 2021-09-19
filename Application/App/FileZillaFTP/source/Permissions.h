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

// Permissions.h: Schnittstelle für die Klasse CPermissions.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERMISSIONS_H__33DEA50E_AA34_4190_9ACD_355BF3D72FE0__INCLUDED_)
#define AFX_PERMISSIONS_H__33DEA50E_AA34_4190_9ACD_355BF3D72FE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Accounts.h"

#define FOP_READ		0x01
#define FOP_WRITE		0x02
#define FOP_DELETE		0x04
#define FOP_APPEND		0x08
#define FOP_CREATENEW	0x10
#define DOP_DELETE		0x20
#define DOP_CREATE		0x40
#define FOP_LIST		0x80

#define PERMISSION_DENIED			0x01
#define PERMISSION_NOTFOUND			0x02
#define PERMISSION_DIRNOTFILE		(0x04 | PERMISSION_DOESALREADYEXIST)
#define PERMISSION_FILENOTDIR		(0x08 | PERMISSION_DOESALREADYEXIST)
#define PERMISSION_DOESALREADYEXIST	0x10
#define PERMISSION_INVALIDNAME		0x20

class TiXmlElement;
class CPermissionsHelperWindow;
class COptions;

class CUser : public t_user
{
public:
	CStdString homedir;

	// Replace :u and :g (if a group it exists)
	void DoReplacements(CStdString& path) const;

	/*
	 * t_alias is used in the alias maps.
	 * See implementation of PrepareAliasMap for a detailed
	 * description
	 */
	struct t_alias
	{
		CStdString targetFolder;
		CStdString name;
	};

	void PrepareAliasMap();

	// GetAliasTarget returns the target of the alias with the specified
	// path and name or returns an empty string if the alias can't be found.
	CStdString GetAliasTarget(const CStdString& path, const CStdString& virtualPath, const CStdString& name) const;

	std::multimap<CStdString, t_alias> aliasMap;
	std::map<CStdString, CStdString> virtualAliases;
	std::multimap<CStdString, CStdString> virtualAliasNames;
};

struct t_dirlisting
{
	char buffer[8192];
	unsigned int len;

	t_dirlisting *pNext;
};

enum _facts {
	fact_type,
	fact_size,
	fact_modify,
	fact_perm
};

class CPermissions  
{
public:
	CPermissions();
	virtual ~CPermissions();

protected:
	/*
	 * CanonifyPath takes the current and the new server dir as parameter,
	 * concats the paths if neccessary and canonifies the dir:
	 * - remove dot-segments
	 * - convert backslashes into slashes
	 * - remove double slashes
	 */
	CStdString CanonifyServerDir(CStdString currentDir, CStdString newDir) const;

public:
	// Change current directory to the specified directory. Used by CWD and CDUP
	int ChangeCurrentDir(LPCTSTR username, CStdString& currentdir, CStdString &dir);

	// Retrieve a directory listing. Pass the actual formatting function as last parameter.
	int GetDirectoryListing(LPCTSTR username, CStdString currentDir, CStdString dirToDisplay,
							 t_dirlisting *&pResult, CStdString& physicalDir, 
							 CStdString& logicalDir,
							 void (*addFunc)(t_dirlisting *&pResult, bool isDir, const char* name, const t_directory& directory, __int64 size, FILETIME* pTime, const char* dirToDisplay, bool *enabledFacts),
							 bool useUTF8, bool *enabledFacts = 0);

	char* ConvertFilename(const CStdString& filename, bool useUTF8);

	// Full direcoty listing with all details. Used by LIST command
	static void AddLongListingEntry(t_dirlisting *&pResult, bool isDir, const char* name, const t_directory& directory, __int64 size, FILETIME* pTime, const char* dirToDisplay, bool *);

	// Directory listing with just the filenames. Used by NLST command
	static void AddShortListingEntry(t_dirlisting *&pResult, bool isDir, const char* name, const t_directory& directory, __int64 size, FILETIME* pTime, const char* dirToDisplay, bool *);

	// Directory listing format used by MLSD
	static void AddFactsListingEntry(t_dirlisting *&pResult, bool isDir, const char* name, const t_directory& directory, __int64 size, FILETIME* pTime, const char* dirToDisplay, bool *enabledFacts);

	CStdString GetHomeDir(LPCTSTR username, bool physicalPath = false) const;
	CStdString GetHomeDir(const CUser &user, bool physicalPath = false) const;

	int CheckDirectoryPermissions(LPCTSTR username, CStdString dirname, CStdString currentdir, int op, CStdString &physicalDir, CStdString &logicalDir);
	int CheckFilePermissions(LPCTSTR username, CStdString filename, CStdString currentdir, int op, CStdString &physicalDir, CStdString &logicalDir);

	BOOL GetUser(CStdString username, CUser &userdata) const;
	BOOL CheckUserLogin(LPCTSTR username, LPCTSTR pass, CUser &userdata, BOOL noPasswordCheck = FALSE);

	BOOL GetAsCommand(char **pBuffer, DWORD *nBufferLength);
	BOOL ParseUsersCommand(unsigned char *pData, DWORD dwDataLength);
	void AutoCreateDirs(LPCTSTR username);
	void ReloadConfig();

	int GetFact(LPCTSTR username, CStdString currentDir, CStdString file, CStdString& fact, CStdString& logicalName, bool enabledFacts[3]);

	static void DestroyDirlisting(struct t_dirlisting* pListing);

protected:
	bool Init();
	void UpdateInstances();

	void ReadSettings();

	void ReadPermissions(TiXmlElement *pXML, t_group &user, BOOL &bGotHome);
	void SavePermissions(TiXmlElement *pXML, const t_group &user);

	void ReadSpeedLimits(TiXmlElement *pXML, t_group &group);
	void SaveSpeedLimits(TiXmlElement *pXML, const t_group &group);

	void ReadIpFilter(TiXmlElement *pXML, t_group &group);
	void SaveIpFilter(TiXmlElement *pXML, const t_group &group);

	void SetKey(TiXmlElement *pXML, LPCTSTR name, LPCTSTR value);
	void SetKey(TiXmlElement *pXML, LPCTSTR name, int value);
	
	int GetRealDirectory(CStdString directory, const CUser &user, t_directory &ret, BOOL &truematch);

	static CCriticalSectionWrapper m_sync;

	bool WildcardMatch(CStdString string, CStdString pattern) const;
	
	typedef std::vector<CUser> t_UsersList; 
	typedef std::vector<t_group> t_GroupsList; 
	static t_UsersList m_sUsersList;
	static t_GroupsList m_sGroupsList;
	t_UsersList m_UsersList;
	t_GroupsList m_GroupsList;
	
	static std::list<CPermissions *> m_sInstanceList;
	CPermissionsHelperWindow *m_pPermissionsHelperWindow;

	friend CPermissionsHelperWindow;
};

#endif // !defined(AFX_PERMISSIONS_H__33DEA50E_AA34_4190_9ACD_355BF3D72FE0__INCLUDED_)
