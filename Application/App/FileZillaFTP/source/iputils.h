// FileZilla Server - a Windows ftp server

// Copyright (C) 2004 - Tim Kosse <tim.kosse@gmx.de>

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

#ifdef _AFX
#define CStdString CString
#endif

bool IsLocalhost(const CStdString& ip);
bool IsValidAddressFilter(CStdString& filter);
bool MatchesFilter(CStdString filter, CStdString ip);
bool IsIpAddress(const CStdString& address);

// Also verifies that it is a correct IPv6 address
CStdString GetIPV6LongForm(CStdString short_address);
CStdString GetIPV6ShortForm(const CStdString& ip);
bool IsRoutableAddress(const CStdString& address);

bool ParseIPFilter(CStdString in, std::list<CStdString>* output = 0);
