// P2PChatDlg.cpp : ʵ���ļ�
//
#pragma once
#include "stdafx.h"
#include "P2P_END.h"
#include "P2PChatDlg.h"

// CP2PChatDlg �Ի���

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


// CP2PChatDlg ��Ϣ�������

void CP2PChatDlg::OnHide()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
	isActive = false;
}


void CP2PChatDlg::OnPeerSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSendMsg;
	POSITION pos = m_pParent->m_P2PChatList.GetHeadPosition();  //����һ�������������ͱ��� pos ��ȡ�����ͷ��
	this->GetDlgItem(IDC_EDIT_P2PSEND)->GetWindowText(strSendMsg);  //���ݿռ�id��ȡ�ؼ��еĲ���
	while(pos!=NULL)
	{
		PeerData *p_Peer = (PeerData*)m_pParent->m_P2PChatList.GetNext(pos);
		if (!strcmp(p_Peer->peerName,m_PeerName))
		{
			m_SaveMsg.READ = true;
			m_SaveMsg.isSave = false;
			m_SaveMsg.sign = P2PCHATMSG;
			AddRecvMsg(&(p_Peer->peerMsgLog),m_pParent->m_UserData.userName,&strSendMsg);//�Լ����͵���Ϣ����ʾ
			m_PeerRecv.SetWindowText(p_Peer->peerMsgLog);		//	���µ�peer��־
			strcpy(m_SaveMsg.m_UserName,m_pParent->m_UserData.userName);
			strcpy(m_SaveMsg.chat,strSendMsg.GetBuffer());//	����ȴ�����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_pParent->m_P2PChatList.GetHeadPosition();
	while(pos!=NULL)
	{
		PeerData *p_Peer = (PeerData*)m_pParent->m_P2PChatList.GetNext(pos);
		if (!strcmp(p_Peer->peerName,m_PeerName))
		{
			p_Peer->peerMsgLog = "";
			m_PeerRecv.SetWindowText(p_Peer->peerMsgLog);		//	���µ�peer��־
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
	//if (m_pParent->fileView == true) {  //ͬʱֻ�ܴ�һ������
	//	return;
	//}
	//else {
		m_pParent->fileView = true;
		CreateP2PDlg2();
	//}
}


void CP2PChatDlg::CreateP2PDlg2()
{
	m_FileMsgDlg = new CP2P_FILEDlg();  //�����ļ��Ի���
	m_FileMsgDlg->Create(IDD_DIALOG1, this);
	m_FileMsgDlg->ModifyStyleEx(0, WS_EX_APPWINDOW);//��������ʾ

	m_FileMsgDlg->SetWindowText("�ļ�����");
	m_FileMsgDlg->fileinfo.FileSize = 0;
	m_FileMsgDlg->SetParentDlg2(this);  //�������󴫸��Ӷ���
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
