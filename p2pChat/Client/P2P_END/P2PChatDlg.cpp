// P2PChatDlg.cpp : 实现文件
//
#pragma once
#include "stdafx.h"
#include "P2P_END.h"
#include "P2PChatDlg.h"

// CP2PChatDlg 对话框

IMPLEMENT_DYNAMIC(CP2PChatDlg, CDialog)

CP2PChatDlg::CP2PChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CP2PChatDlg::IDD, pParent)
{
	
}

CP2PChatDlg::~CP2PChatDlg()
{
}

void CP2PChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RECV, m_PeerRecv);
	DDX_Control(pDX, IDC_EDIT_P2PSEND, m_PeerSend);
}

void CP2PChatDlg::SetParentDlg(CP2P_ENDDlg* p_Parent)
{
	m_pParent = p_Parent;
	//Esock2 = p_Parent->Esock;
}

BEGIN_MESSAGE_MAP(CP2PChatDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, &CP2PChatDlg::OnHide)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CP2PChatDlg::OnPeerSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CP2PChatDlg::OnClear)
	ON_EN_CHANGE(IDC_EDIT_P2PSEND, &CP2PChatDlg::OnEnChangeEditP2psend)
	ON_BN_CLICKED(IDC_FILE, &CP2PChatDlg::OnBnClickedFile)
	ON_EN_CHANGE(IDC_EDIT_RECV, &CP2PChatDlg::OnEnChangeEditRecv)
END_MESSAGE_MAP()


// CP2PChatDlg 消息处理程序

void CP2PChatDlg::OnHide()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	isActive = false;
}


void CP2PChatDlg::OnPeerSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSendMsg;
	POSITION pos = m_pParent->m_P2PChatList.GetHeadPosition();  //定义一个抽象数据类型变量 pos 获取链表的头部
	this->GetDlgItem(IDC_EDIT_P2PSEND)->GetWindowText(strSendMsg);  //根据空间id获取控件中的参数
	while(pos!=NULL)
	{
		PeerData *p_Peer = (PeerData*)m_pParent->m_P2PChatList.GetNext(pos);
		if (!strcmp(p_Peer->peerName,m_PeerName))
		{
			m_SaveMsg.READ = true;
			m_SaveMsg.isSave = false;
			m_SaveMsg.sign = P2PCHATMSG;
			AddRecvMsg(&(p_Peer->peerMsgLog),m_pParent->m_UserData.userName,&strSendMsg);//自己发送的信息先显示
			m_PeerRecv.SetWindowText(p_Peer->peerMsgLog);		//	更新的peer日志
			strcpy(m_SaveMsg.m_UserName,m_pParent->m_UserData.userName);
			strcpy(m_SaveMsg.chat,strSendMsg.GetBuffer());//	保存等待发送
			strSendMsg.ReleaseBuffer();

			m_pParent->m_ClientSock.SendTo((char*)&m_SaveMsg, sizeof(m_SaveMsg),(SOCKADDR*)&(p_Peer->peerAddr),sizeof(SOCKADDR_IN),0);
		}
	}
	m_PeerSend.SetWindowText("");
	m_PeerRecv.LineScroll(m_PeerRecv.GetLineCount());

}

void CP2PChatDlg::AddRecvMsg(CString *p_MsgLog,char *userName,CString *chat)
{
	CTime t=CTime::GetCurrentTime();
	CString strTime;
	strTime.Format("%d:%d:%d",t.GetHour(),t.GetMinute(),t.GetSecond());

	*p_MsgLog+=userName;
	*p_MsgLog+="\t";
	*p_MsgLog+=strTime;
	*p_MsgLog+="\r\n";
	*p_MsgLog+=*chat;
	*p_MsgLog+="\r\n";
	*p_MsgLog+="\r\n";
}

void CP2PChatDlg::OnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_pParent->m_P2PChatList.GetHeadPosition();
	while(pos!=NULL)
	{
		PeerData *p_Peer = (PeerData*)m_pParent->m_P2PChatList.GetNext(pos);
		if (!strcmp(p_Peer->peerName,m_PeerName))
		{
			p_Peer->peerMsgLog = "";
			m_PeerRecv.SetWindowText(p_Peer->peerMsgLog);		//	更新的peer日志
		}
	}
	

}


void CP2PChatDlg::OnEnChangeEditP2psend()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CP2PChatDlg::OnBnClickedFile()
{
	// TODO: Add your control notification handler code here
	//if (m_pParent->fileView == true) {  //同时只能打开一个界面
	//	return;
	//}
	//else {
		m_pParent->fileView = true;
		CreateP2PDlg2();
	//}
}


void CP2PChatDlg::CreateP2PDlg2()
{
	m_FileMsgDlg = new CP2P_FILEDlg();  //创建文件对话框
	m_FileMsgDlg->Create(IDD_DIALOG1, this);
	m_FileMsgDlg->ModifyStyleEx(0, WS_EX_APPWINDOW);//任务栏显示

	m_FileMsgDlg->SetWindowText("文件操作");
	m_FileMsgDlg->fileinfo.FileSize = 0;
	m_FileMsgDlg->SetParentDlg2(this);  //将父对象传给子对象
	strcpy(m_FileMsgDlg->m_PeerName2, m_PeerName);
	m_FileMsgDlg->ShowWindow(SW_SHOW);
	//m_FileMsgDlg->isActive = TRUE;
}


void CP2PChatDlg::OnEnChangeEditRecv()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
