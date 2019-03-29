// P2PFILEMSGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "P2P_END.h"
#include "P2PFILEMSGDlg.h"
#include "afxdialogex.h"


// CP2PFILEMSGDlg dialog

IMPLEMENT_DYNAMIC(CP2PFILEMSGDlg, CDialog)

CP2PFILEMSGDlg::CP2PFILEMSGDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

CP2PFILEMSGDlg::~CP2PFILEMSGDlg()
{
}

void CP2PFILEMSGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_MSG, m_Msg);
}


BEGIN_MESSAGE_MAP(CP2PFILEMSGDlg, CDialog)
	ON_BN_CLICKED(IDC_FILE_SAVE, &CP2PFILEMSGDlg::OnBnClickedFileSave)
	ON_BN_CLICKED(IDC_FILE_IGNO, &CP2PFILEMSGDlg::OnBnClickedFileIgno)
	ON_EN_CHANGE(IDC_FILE_MSG, &CP2PFILEMSGDlg::OnEnChangeFileMsg)
END_MESSAGE_MAP()


// CP2PFILEMSGDlg message handlers


void CP2PFILEMSGDlg::OnBnClickedFileSave()
{
	// TODO: Add your control notification handler code here
	//if (m_pParentMsgFile->fileView == true) {  //只能创建一个界面
	//	return;
	//}
	//else {
		m_pParentMsgFile->fileView = true;
		CreateP2PFileDlg();
		OnBnClickedFileIgno();
	//}
}


void CP2PFILEMSGDlg::OnBnClickedFileIgno()
{
	// TODO: Add your control notification handler code here 
	this->ShowWindow(SW_HIDE);
	isActiveMsgFile = false;
}


void CP2PFILEMSGDlg::SetMsgFileParentDlg(CP2P_ENDDlg* p_Parent)
{
	m_pParentMsgFile = p_Parent;
}


void CP2PFILEMSGDlg::OnEnChangeFileMsg()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CP2PFILEMSGDlg::OnPeerMsgSend()
{
	POSITION pos = m_pParentMsgFile->m_P2PChatList.GetHeadPosition();  //定义一个抽象数据类型变量 pos 获取链表的头部
	while (pos != NULL)
	{
		PeerData *p_Peer = (PeerData*)m_pParentMsgFile->m_P2PChatList.GetNext(pos);
		if (!strcmp(p_Peer->peerName, m_PeerNameMsgFile))
		{
			strcpy(m_SaveMsgFile.m_UserName, m_pParentMsgFile->m_UserData.userName);		
			m_pParentMsgFile->m_ClientSock.SendTo((char*)&m_SaveMsgFile, sizeof(m_SaveMsgFile), (SOCKADDR*)&(p_Peer->peerAddr), sizeof(SOCKADDR_IN), 0);
		}
	}
}

void CP2PFILEMSGDlg::CreateP2PFileDlg()
{
	m_FileMsgDlg2 = new CP2P_FILEDlg();  //创建私聊对话框
	m_FileMsgDlg2->Create(IDD_DIALOG1, this);
	m_FileMsgDlg2->ModifyStyleEx(0, WS_EX_APPWINDOW);//任务栏显示

	m_FileMsgDlg2->SetWindowText("文件操作");
	m_FileMsgDlg2->SetParentDlg3(this);  //将父对象传给子对象
	strcpy(m_FileMsgDlg2->m_PeerName2, m_PeerNameMsgFile);
	strcpy(m_FileMsgDlg2->fileinfo.FileName, files.FileName);
	m_FileMsgDlg2->fileinfo.FileSize = files.FileSize;
	m_FileMsgDlg2->ShowWindow(SW_SHOW);
}

