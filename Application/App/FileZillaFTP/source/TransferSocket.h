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

#if !defined(AFX_TRANSFERSOCKET_H__38ADA982_DD96_4607_B7D2_982011F162FE__INCLUDED_)
#define AFX_TRANSFERSOCKET_H__38ADA982_DD96_4607_B7D2_982011F162FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransferSocket.h : Header-Datei
//

class CControlSocket;

#define TRANSFERMODE_NOTSET 0
#define TRANSFERMODE_LIST 1
#define TRANSFERMODE_RECEIVE 2
#define TRANSFERMODE_SEND 3
#define TRANSFERMODE_NLST 4

struct t_dirlisting;

#include <zlib.h>

/////////////////////////////////////////////////////////////////////////////
// Befehlsziel CTransferSocket 
class CAsyncGssSocketLayer;
class CAsyncSslSocketLayer;
class CTransferSocket : public CAsyncSocketEx
{
// Attribute
public:

// Operationen
public:
	CTransferSocket(CControlSocket *pOwner);
	void Init(t_dirlisting *pDir, int nMode);
	void Init(const CStdString& filename, int nMode, _int64 rest);
	inline bool InitCalled() { return m_bReady; }
	void UseGSS(CAsyncGssSocketLayer* pGssLayer);
	bool UseSSL(void* sslContext);
	virtual ~CTransferSocket();

// �berschreibungen
public:
	int GetMode() const;
	BOOL Started() const;
	BOOL CheckForTimeout();
	void PasvTransfer();
	int GetStatus();
	bool InitZLib(int level);
	bool GetZlibStats(_int64 &bytesIn, _int64 &bytesOut) const;
	__int64 GetCurrentFileOffset() const { return m_currentFileOffset; }
	bool WasActiveSinceCheck() const { return m_wasActiveSinceCheck; }

	BOOL pasv;
// Implementierung
protected:
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	virtual int OnLayerCallback(std::list<t_callbackMsg>& callbacks);

	void EndTransfer(int status);

	t_dirlisting *m_pDirListing;
	BOOL m_bSentClose;
	CStdString m_Filename;
	bool m_bReady;
	BOOL m_bStarted;
	BOOL InitTransfer(BOOL bCalledFromSend);
	int m_nMode;
	int m_status;
	CControlSocket *m_pOwner;
	_int64 m_nRest;
	BOOL m_bBinary;
	HANDLE m_hFile;
	char *m_pBuffer;
	char *m_pBuffer2; // Used by zlib transfers
	unsigned int m_nBufferPos;
	BOOL m_bAccepted;
	SYSTEMTIME m_LastActiveTime;
	bool m_wasActiveSinceCheck;
	CAsyncGssSocketLayer* m_pGssLayer;
	
	CAsyncSslSocketLayer* m_pSslLayer;
	void* m_sslContext;

	unsigned int m_nBufSize;
	bool m_useZlib;
	z_stream m_zlibStream;
	__int64 m_zlibBytesIn;
	__int64 m_zlibBytesOut;
	
	__int64 m_currentFileOffset;

	bool m_waitingForSslHandshake;

	bool m_premature_send;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_TRANSFERSOCKET_H__38ADA982_DD96_4607_B7D2_982011F162FE__INCLUDED_
