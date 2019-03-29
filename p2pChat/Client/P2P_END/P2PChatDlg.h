#pragma once
#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "P2PBase.h"
#include "P2P_ENDDlg.h"
#include "afxwin.h"
#include "P2P_FILEDlg.h"

// CP2PChatDlg 对话框
class CP2P_ENDDlg;
class CP2PChatDlg : public CDialog
{
	DECLARE_DYNAMIC(CP2PChatDlg)

public:
	CP2PChatDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CP2PChatDlg();

	char m_PeerName[20] ;                //用于回复窗口检索数据
	CP2P_ENDDlg *m_pParent;				 //主界面
	Message m_SaveMsg;					 //数据包
	BOOL isActive;						 //界面打开状态
	CP2P_FILEDlg *m_FileMsgDlg = NULL;			 //文件界面

	void SetParentDlg(CP2P_ENDDlg*);
	void AddRecvMsg(CString *p_MsgLog,char *userName,CString *chat);
	void CreateP2PDlg2();

// 对话框数据
	enum { IDD = IDD_P2PCHAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHide();

	afx_msg void OnPeerSend();
	CEdit m_PeerRecv;  //接收消息控件
	CEdit m_PeerSend;  //发送控件
	afx_msg void OnClear();
	afx_msg void OnEnChangeEditP2psend();
	afx_msg void OnBnClickedFile();
	afx_msg void OnEnChangeEditRecv();
};
#endif