#pragma once
#include "stdafx.h"
//#include "P2PBase.h"
//#include "P2P_IMDlg.h"

class CP2P_IMDlg;
class CServSock : public CSocket
{
	// Attributes
public:
	
	// Operations
public:
	CServSock();
	CP2P_IMDlg *m_ServDlg;	//�������Ի���
	virtual ~CServSock();
	//char m_UserName[20];
	//int m_id;
	void SetDlg(CP2P_IMDlg* Dlg);	//����
	// Overrides
public:

public:
	//virtual void OnAccept(int nErrorCode);
	void OnClose(int nErrorCode);
	void OnReceive(int nErrorCode);
	
protected:
};