// P2P_ENDDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "ClientSock.h"
#include "P2PBase.h"
#include "P2P_END.h"
#include "P2PChatDlg.h"
#include "P2PFILEMSGDlg.h"
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

#include <iostream>
#include<map>
using namespace std;


// CP2P_ENDDlg 对话框(登录对话框)
class CP2P_ENDDlg : public CDialog
{
// 构造
public:
	CP2P_ENDDlg(CWnd* pParent = NULL);	// 标准构造函数
	CClientSock m_ClientSock;			//连接用的csocket
	//CClientSock *socks;
	Message m_ClientMsg;		        //主要用来存用户列表

	SOCKADDR_IN m_ServAddr;	            //服务器/节点地址信息（通信节点地址信息）
	BOOL m_State;			            //客户端状态
	UserData m_UserData;                //用户数据
	CP2PChatDlg *m_ChatMsgDlg = NULL;   //私聊界面
	CPtrList m_P2PChatList;		        //保存对话框到列表,存储已建立的对话框
	BOOL m_Extend;                      //设置服务器IP
	Message buffer;						//数据包
	CP2PFILEMSGDlg* m_MsgFileDlg = NULL;//文件提醒界面
	bool fileView = false;				//文件对话框是否打开

	map<string, Message> userMsg;
	
	void CreateMsgFileP2PDlg2(Message *p_PeerBuffer);
	void ReceiveData(CClientSock *m_ClientSock);
	void UpdateUserList(Message *buffer);		//把服务器发来的存入缓存的东西更新到列表
	void ShowP2PChatDlg(Message *buffer);
	void AddRecvMsg(CString *, Message *);
	void RecvP2PMsg(Message *p_PeerBuffer);
	PeerData* FindP2PChatDlgByName(char *userName);
	void UserListLightUp(BOOL flag,char *userName);
	void CreateP2PDlg(Message *p_PeerBuffer);
	void LoginToChat();
	bool putFileView();
	void CreateChatView(Message *p_PeerBuffer);
	void RmoveUserList(string name);
	void sendQuitMsg();
	void peepChagMag();
	void exitMsg();
	void loginMsg();
	void regMsg();
	void forgetMsg();
	void deleteUserMsg(string usernamef);


// 对话框数据
	enum { IDD = IDD_P2P_END_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:  //窗口控件
	afx_msg void OnLogin();
	CEdit m_UserName;
	CEdit m_ServMsg;
	CEdit m_ServSend;
	afx_msg void OnServSend();
	CEdit m_ServIP;
	CEdit m_ServPort;
	CButton m_LoginButton;
	CButton m_ExitButton;
	CButton m_SendButton;
	afx_msg void OnExit();
	CListBox m_OLUserList;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUserList();
	//CListBox m_UserListBox;
	afx_msg void OnEnChangeEditServport();
	afx_msg void OnCanel();
	afx_msg void OnSetting();
	afx_msg void OnForget();
	afx_msg void OnClear();
	CEdit m_Password;
	afx_msg void OnReg1();
	afx_msg void OnReg2();
	afx_msg void OnBack();
	afx_msg void OnForget2();
	afx_msg void OnEnChangeEditIdcard();
};
