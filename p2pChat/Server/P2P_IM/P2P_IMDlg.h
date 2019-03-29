// P2P_IMDlg.h : ͷ�ļ�
//
#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include "SQL.h"
#include "ServSock.h"
#include "P2PBase.h"
#include "P2P_IM.h"


#include "afxwin.h"

// CP2P_IMDlg �Ի���
class CP2P_IMDlg : public CDialog
{
// ����
public:
	CP2P_IMDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void refresh();  //ˢ�·���������
	void UpdateUserList(Msg *buffer);	//���������û��б����û�
	void ReceiveData(CServSock* sock);
	void Stop(int id);
	void AcceptConnect();
	UserData *FindClientByName(char *);
	BOOL ADOCheckUser(Message *p_Userbuffer,int sign);
	ServerData m_ServData;
	CServSock m_ServSock;
	Msg m_ServBaseMsg;				//�������������û��б����㷢��
	SOCKADDR_IN m_clientAddr;
	CPtrList m_SockUserList;
	CDataBaseAcess AdoAccess;
	
// �Ի�������
	enum { IDD = IDD_P2P_IM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_OLUserList;
	CStatic m_OLNum;
	CStatic m_State;
	CEdit m_ServerLog;
	afx_msg void OnStart();
	
	afx_msg void OnStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
