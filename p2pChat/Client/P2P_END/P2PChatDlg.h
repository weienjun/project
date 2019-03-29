#pragma once
#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "P2PBase.h"
#include "P2P_ENDDlg.h"
#include "afxwin.h"
#include "P2P_FILEDlg.h"

// CP2PChatDlg �Ի���
class CP2P_ENDDlg;
class CP2PChatDlg : public CDialog
{
	DECLARE_DYNAMIC(CP2PChatDlg)

public:
	CP2PChatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CP2PChatDlg();

	char m_PeerName[20] ;                //���ڻظ����ڼ�������
	CP2P_ENDDlg *m_pParent;				 //������
	Message m_SaveMsg;					 //���ݰ�
	BOOL isActive;						 //�����״̬
	CP2P_FILEDlg *m_FileMsgDlg = NULL;			 //�ļ�����

	void SetParentDlg(CP2P_ENDDlg*);
	void AddRecvMsg(CString *p_MsgLog,char *userName,CString *chat);
	void CreateP2PDlg2();

// �Ի�������
	enum { IDD = IDD_P2PCHAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHide();

	afx_msg void OnPeerSend();
	CEdit m_PeerRecv;  //������Ϣ�ؼ�
	CEdit m_PeerSend;  //���Ϳؼ�
	afx_msg void OnClear();
	afx_msg void OnEnChangeEditP2psend();
	afx_msg void OnBnClickedFile();
	afx_msg void OnEnChangeEditRecv();
};
#endif