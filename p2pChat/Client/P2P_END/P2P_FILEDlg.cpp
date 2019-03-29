// P2P_FILEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "P2P_END.h"
#include "resource.h"
#include "P2P_FILEDlg.h"
#include "afxdialogex.h"
#include "P2PChatDlg.h"
#include "P2PFILEMSGDlg.h"
#include <cstringt.h>
#include <stdio.h>

// CP2P_FILEDlg dialog

IMPLEMENT_DYNAMIC(CP2P_FILEDlg, CDialog)

CP2P_FILEDlg::CP2P_FILEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{
}

CP2P_FILEDlg::~CP2P_FILEDlg()
{
}

void CP2P_FILEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_PATH, m_FilePath);
	DDX_Control(pDX, IDC_FEDIT_SIZE, m_FileSize);
	DDX_Control(pDX, IDC_FILE_MSG, m_FileMsg);
}


BEGIN_MESSAGE_MAP(CP2P_FILEDlg, CDialog)
	ON_EN_CHANGE(IDC_FILE_PATH, &CP2P_FILEDlg::OnEnChangeFilePath)
	ON_BN_CLICKED(IDC_FILE_BP, &CP2P_FILEDlg::OnBnClickedFileBp)
	ON_STN_CLICKED(IDC_FILE_SIZE, &CP2P_FILEDlg::OnStnClickedFileSize)
	ON_EN_CHANGE(IDC_FEDIT_SIZE, &CP2P_FILEDlg::OnEnChangeFeditSize)
	ON_STN_CLICKED(IDC_FILE_BIT, &CP2P_FILEDlg::OnStnClickedFileBit)
	ON_BN_CLICKED(IDC_FILE_CLOSE, &CP2P_FILEDlg::OnBnClickedFileClose)
	ON_EN_CHANGE(IDC_FILE_MSG, &CP2P_FILEDlg::OnEnChangeFileMsg)
	ON_BN_CLICKED(ID_FILE_SEND, &CP2P_FILEDlg::OnBnClickedFileSend)
	ON_BN_CLICKED(IDC_CHOOSE_RECV, &CP2P_FILEDlg::OnBnClickedChooseRecv)
	ON_BN_CLICKED(IDC_CHOOSE_SEND, &CP2P_FILEDlg::OnBnClickedChooseSend)
	ON_BN_CLICKED(IDC_FILE_START, &CP2P_FILEDlg::OnBnClickedFileStart)
	ON_WM_TIMER()  //定时器优先级
	ON_BN_CLICKED(IDC_REMOVE, &CP2P_FILEDlg::OnBnClickedRemove)
END_MESSAGE_MAP()


// CP2P_FILEDlg message handlers

void CP2P_FILEDlg::SetParentDlg2(CP2PChatDlg* p_Parent)
{
	m_pParent2 = p_Parent;
}

void CP2P_FILEDlg::SetParentDlg3(CP2PFILEMSGDlg* p_Parent)
{
	m_pParent3 = p_Parent;
}

void CP2P_FILEDlg::OnEnChangeFilePath()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

//获取路径
void CP2P_FILEDlg::OnBnClickedFileBp()  //点击目录/文件
{
	// TODO: Add your control notification handler code here
	// TODO:  在此添加控件通知处理程序代码
	if (SendOrRecv == 0) {
		MessageBox("请先选择方式！！");
		return;
	}
	if (SendOrRecv == 2) {  //发送
		char* bufname;
		CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "所有文件 (*.*)|*.*||", this);//所有文件 (*.*)|*.*||
		if (dlg.DoModal() == IDOK)
		{
			filePath = dlg.GetPathName();//获取文件路径	
			CString name = dlg.GetFileName();//获取文件名
			strcpy(fileinfo.FileName,name);

			CFile file(filePath, CFile::modeRead);//打开文件	
			fileinfo.FileSize = file.GetLength();//获取文件大小	
			file.Close();//关闭文件

			//将文件数据更新到控件上
			fileSize.Format("%d", fileinfo.FileSize);
			GetDlgItem(IDC_FEDIT_SIZE)->SetWindowText(fileSize);
			GetDlgItem(IDC_FILE_PATH)->SetWindowText(filePath);
			GetDlgItem(IDC_FILE_BP)->EnableWindow(FALSE);
		}
	}
	else {
		// TODO: Add your control notification handler code here
		BROWSEINFO   bInfo;
		ZeroMemory(&bInfo, sizeof(bInfo));
		bInfo.hwndOwner = m_hWnd;
		TCHAR tchPath[255];
		bInfo.lpszTitle = _T("所选择路径:   ");
		bInfo.ulFlags = BIF_RETURNONLYFSDIRS;

		LPITEMIDLIST lpDlist;
		//用来保存返回信息的IDList，使用SHGetPathFromIDList函数转换为字符串 
		lpDlist = SHBrowseForFolder(&bInfo);   //显示选择对话框 
		if (lpDlist != NULL)
		{
			SHGetPathFromIDList(lpDlist, tchPath);//把项目标识列表转化成目录 
			filePath = tchPath;
			GetDlgItem(IDC_FEDIT_SIZE)->SetWindowText("0");
			GetDlgItem(IDC_FILE_PATH)->SetWindowText(filePath);
			GetDlgItem(IDC_FILE_BP)->EnableWindow(FALSE);
		}
	}
}


void CP2P_FILEDlg::OnStnClickedFileSize()
{
	// TODO: Add your control notification handler code here
}


void CP2P_FILEDlg::OnEnChangeFeditSize()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CP2P_FILEDlg::OnStnClickedFileBit()
{
	// TODO: Add your control notification handler code here
}


void CP2P_FILEDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CP2P_FILEDlg::OnBnClickedFileClose()
{
	// TODO: Add your control notification handler code here
	if (m_pParent2 != NULL) {
		m_pParent2->m_pParent->fileView = false;
	}
	else {
		m_pParent3->m_pParentMsgFile->fileView = false;
		m_pParent3->OnBnClickedFileIgno();  //关闭提醒对话框
	}

	isActive = true;
	this->ShowWindow(SW_HIDE);
}


void CP2P_FILEDlg::OnEnChangeFileMsg()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CP2P_FILEDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
}


void CP2P_FILEDlg::OnBnClickedFileSend()
{
	// TODO: Add your control notification handler code here
}


void CP2P_FILEDlg::OnBnClickedChooseRecv()
{
	// TODO: Add your control notification handler code here
	SendOrRecv = 1;
	GetDlgItem(IDC_CHOOSE_SEND)->EnableWindow(FALSE);
}


void CP2P_FILEDlg::OnBnClickedChooseSend()
{
	// TODO: Add your control notification handler code here
	SendOrRecv = 2; //发送
	GetDlgItem(IDC_CHOOSE_RECV)->EnableWindow(FALSE);
}

//字符串处理
void CP2P_FILEDlg::AddRecvMsg2(CString *p_MsgLog, char *userName, CString *chat)
{
	CTime t = CTime::GetCurrentTime();
	CString strTime;
	strTime.Format("%d:%d:%d", t.GetHour(), t.GetMinute(), t.GetSecond());

	*p_MsgLog += userName;
	*p_MsgLog += "\t";
	*p_MsgLog += strTime;
	*p_MsgLog += "\r\n";
	*p_MsgLog += *chat;
	*p_MsgLog += "\r\n";
	*p_MsgLog += "\r\n";
}

bool CP2P_FILEDlg::RequestMsg() {
	return Download;
}

//从私聊界面进入
void CP2P_FILEDlg::OnPeerChatMsgSend()
{
	POSITION pos = m_pParent2->m_pParent->m_P2PChatList.GetHeadPosition();  //定义一个抽象数据类型变量 pos 获取链表的头部
	while (pos != NULL)
	{
		PeerData *p_Peer = (PeerData*)m_pParent2->m_pParent->m_P2PChatList.GetNext(pos);
		if (!strcmp(p_Peer->peerName, m_PeerName2))
		{
			strcpy(m_SaveMsg2.m_UserName, m_pParent2->m_pParent->m_UserData.userName);
			m_pParent2->m_pParent->m_ClientSock.SendTo((char*)&m_SaveMsg2, sizeof(m_SaveMsg2), (SOCKADDR*)&(p_Peer->peerAddr), sizeof(SOCKADDR_IN), 0);
		}
	}
}


void CP2P_FILEDlg::OnPeerFileMsgSend()
{
	POSITION pos = m_pParent3->m_pParentMsgFile->m_P2PChatList.GetHeadPosition();  //定义一个抽象数据类型变量 pos 获取链表的头部
	while (pos != NULL)
	{
		PeerData *p_Peer = (PeerData*)m_pParent3->m_pParentMsgFile->m_P2PChatList.GetNext(pos);
		if (!strcmp(p_Peer->peerName, m_PeerName2))
		{
			strcpy(m_SaveMsg2.m_UserName, m_pParent3->m_pParentMsgFile->m_UserData.userName);
			m_pParent3->m_pParentMsgFile->m_ClientSock.SendTo((char*)&m_SaveMsg2, sizeof(m_SaveMsg2), (SOCKADDR*)&(p_Peer->peerAddr), sizeof(SOCKADDR_IN), 0);
		}
	}
}

//收不到此消息？？
void CP2P_FILEDlg::recvResponse() {
	//初始化数据
	m_SaveMsg2.READ = true;
	m_SaveMsg2.isSave = false;
	m_SaveMsg2.sign = P2PCHATMSG;
	m_SaveMsg2.File.lose = false;

	string str;;
	if (Download == true) {
		str = " 已接收文件: " + (string)fileinfo.FileName;
		strcpy(m_SaveMsg2.chat, str.c_str());
	}
	else {
		str = " 未接收文件: " + (string)fileinfo.FileName;
		strcpy(m_SaveMsg2.chat, str.c_str());
	}
	Send();
}

DWORD WINAPI thread_heart_proc(LPVOID pointer)
{
	//等待接收反馈信息
	//KillTimer(2);				// 重置定时器时间
	CP2P_FILEDlg *arg = (CP2P_FILEDlg*)pointer;
	arg->SetTimer(3,100000,NULL);
	while (arg->getData2()) {
		if (arg->m_SaveMsg2.READ == true && arg->m_SaveMsg2.isSave == true && arg->m_SaveMsg2.sign == FILEQEUST) {
			arg->KillTimer(3);  //关闭发送定时器
			string str = "正在发送文件: " + (string)arg->fileinfo.FileName;
			arg->m_FileMsg.SetWindowText(str.c_str());
			arg->m_FileMsg.LineScroll(arg->m_FileMsg.GetLineCount());
			arg->sendFileMsg();
			break;
		}
		//终止接收
		if (arg->m_SaveMsg2.isSave == false && arg->m_SaveMsg2.READ == true  && arg->m_SaveMsg2.sign == FILEQEUST) {
			arg->modifyState();
			arg->KillTimer(3);  //关闭发送定时器
			return 0;
		}
		//终止发送
		if (arg->fileSend == false) { //终止发送或受到终止接收消息
			arg->OnBnClickedRemove(); //初始化终止发送信息
			arg->KillTimer(3);  //关闭定时器
			return 0; //退出发送线程 
		}
	}
	return 0;
}

void CP2P_FILEDlg::OnBnClickedFileStart()
{
	// TODO: Add your control notification handler code here
	//发送文件
	GetDlgItem(IDC_REMOVE)->EnableWindow(true);
	if (SendOrRecv == 2) {
		string str = "准备发送文件: " + (string)fileinfo.FileName;
		m_FileMsg.SetWindowText(str.c_str());
		GetDlgItem(IDC_FILE_START)->EnableWindow(false);
		m_FileMsg.LineScroll(m_FileMsg.GetLineCount());
		sendFile();
	}
	//接收文件
	else if (SendOrRecv == 1) {
		if (fileinfo.FileSize == 0) {
			MessageBox("无文件可接收！");
			return;
		}
		string str = "正在下载文件: " + (string)fileinfo.FileName;
		m_FileMsg.SetWindowText(str.c_str());
		GetDlgItem(IDC_FILE_START)->EnableWindow(false);
		m_FileMsg.LineScroll(m_FileMsg.GetLineCount());
		recvFile();
	}
	else {
		MessageBox("无效操作！");
		return;
	}
}

void CP2P_FILEDlg::sendFile() {
	//发送文件信息
	strcpy(m_SaveMsg2.File.FileName, fileinfo.FileName);
	m_SaveMsg2.File.FileSize = fileinfo.FileSize;

	m_SaveMsg2.READ = false;
	m_SaveMsg2.isSave = false;
	m_SaveMsg2.File.lose = false;
	m_SaveMsg2.sign = P2PCHATMSG;

	//根据对象选择发送方法,同时修改发送状态
	fileSend = true;
	Send();
	//创建发送文件线程
	HANDLE h_getList = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_heart_proc, this, 0, NULL);  //此处设置成CHECK_RESP																								 //FileMsgSend();
}

//void CP2P_FILEDlg::thread_heart_saveFile() {
DWORD WINAPI thread_heart_saveFile(LPVOID pointer)
{
	CP2P_FILEDlg *arg = (CP2P_FILEDlg*)pointer;
	long long len = 0;
	arg->fileName = arg->fileinfo.FileName;
	long n = 0;
	CString fileSize;
	CString str;
	CString strn;
	int dn = 0;
	arg->filePath += "/" + (CString)arg->fileName;
	string userNamef = arg->m_PeerName2 + (string)arg->fileinfo.FileName;
	CFile file(arg->filePath, CFile::modeCreate | CFile::modeWrite);  //第二次点击接收会崩溃
	{
		while (arg->fileinfo.FileSize > len) {
			//获取数据
			if (arg->getData2() == false) {
				arg->m_FileMsg.SetWindowText("获取数据失败！");
				file.Close();//关闭文件
				return 0;
			}
			//终止接收
			if (arg->fileRecv == false) { //终止发送或受到终止接收消息
				//arg->OnBnClickedRemove2(); //初始化终止发送信息
				file.Close();//关闭文件

				arg->m_SaveMsg2.READ = true;
				arg->m_SaveMsg2.isSave = false;
				arg->m_SaveMsg2.sign = FILEQEUST;
				arg->Send();

				return 0; //退出发送线程
			}

			//发送端终止发送
			if (arg->m_SaveMsg2.isSave == false && arg->m_SaveMsg2.READ == false &&  arg->m_SaveMsg2.sign == FILEQEUST) {
				arg->modifyState();
				file.Close();
				return 0;
			}

			if (arg->m_SaveMsg2.File.count == n) {
				continue;
			}
	
			if (arg->m_SaveMsg2.READ == false && arg->m_SaveMsg2.isSave == true && arg->m_SaveMsg2.sign == FILEQEUST){//&& arg->m_SaveMsg2.sign == FILEQEUST) {
				if (n + 1 != arg->m_SaveMsg2.File.count) {
					//丢包处理
					arg->m_SaveMsg2.File.count = n;  
					arg->m_SaveMsg2.File.lose = true;

					if (arg->m_pParent2 != NULL) {
						arg->m_pParent2->m_pParent->userMsg[userNamef].File.count = n;
					}
					else {
						arg->m_pParent3->m_pParentMsgFile->userMsg[userNamef].File.count = n;
					}

					dn++;
					arg->Send();
					Sleep(30);
					continue;
				}

				int size = arg->m_SaveMsg2.File.FileSize;
				file.Write(arg->m_SaveMsg2.File.file, size);
				len += size;
				arg->KillTimer(4);  //关闭定时器
				fileSize.Format("%d/", arg->fileinfo.FileSize);
				str.Format("%d/", len);
				fileSize += str;
				strn.Format("%d", dn);
				fileSize += strn;

				arg->GetDlgItem(IDC_FEDIT_SIZE)->SetWindowTextA(fileSize);
				n = arg->m_SaveMsg2.File.count;
			}
		}
	}

	file.Close();//关闭文件
	string strs = "文件接收完成: " + (string)arg->fileinfo.FileName;
	arg->m_FileMsg.SetWindowText(strs.c_str());
	arg->SendOrRecv = 0;
	arg->m_FileMsg.LineScroll(arg->m_FileMsg.GetLineCount());
	arg->GetDlgItem(IDC_FILE_START)->EnableWindow(true);
	arg->GetDlgItem(IDC_REMOVE)->EnableWindow(false);
	
	arg->InitState();
	
	arg->Download = true;
	arg->recvResponse();
	return 0;
}

void CP2P_FILEDlg::recvFile() {
	//终止发送
	if (getData2() && m_SaveMsg2.isSave == false && m_SaveMsg2.READ == false && m_SaveMsg2.sign == FILEQEUST) {
		modifyState();
		return ;
	}
	
	//反馈信息
	m_SaveMsg2.READ = true;
	m_SaveMsg2.isSave = true;
	m_SaveMsg2.sign = FILEQEUST;
	m_SaveMsg2.File.lose = false;
	strcpy(m_SaveMsg2.File.FileName, fileinfo.FileName);
	//根据对象选择发送方法,同时修改发送状态
	fileRecv = true;
	Send();
	SetTimer(4, 3000, NULL);  //接收文件ACK重发定时器

	HANDLE h_getList = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_heart_saveFile, this, 0, NULL);  //此处设置成CHECK_RESP	
	Download = false;
}


void CP2P_FILEDlg::sendFileMsg() {
	USES_CONVERSION;
	CFile file;
	if (!file.Open(filePath, CFile::modeRead | CFile::typeBinary))
	{
		string str = "文件打开失败: " + (string)fileinfo.FileName;
		AfxMessageBox(_T(str.c_str()));
		return;
	}
	char buf[READSIZE] = { 0 };
	file.Seek(0, CFile::begin);
	long nLen = 0;//读取长度
	long long nSize = 0;//发送长度
	DWORD dwCount = 0;
	strcpy(m_SaveMsg2.File.FileName, fileinfo.FileName);

	m_SaveMsg2.File.count = 0;
	m_SaveMsg2.File.lose = false;
	long n = 0;
	CString fileSize;
	CString str;
	int dn = 0;
	while (fileinfo.FileSize > nSize || (getData2() && m_SaveMsg2.File.lose == true)) {  //处理最后一丢包问题
		//终止发送
		if (fileSend == false) { //终止发送或受到终止接收消息
			file.Close();
			m_SaveMsg2.READ = false;
			m_SaveMsg2.isSave = false;
			m_SaveMsg2.sign = FILEQEUST;
			Send();
			return; //退出发送线程
		}

		//接收端终止接收
		if (getData2() && m_SaveMsg2.READ == true && m_SaveMsg2.isSave == false && m_SaveMsg2.sign == FILEQEUST) {
			modifyState();
			file.Close();
			return;
		}

		if (m_SaveMsg2.File.lose == true) {
			//丢包处理
			n = m_SaveMsg2.File.count;
			file.Seek((n*READSIZE), CFile::begin); //修改文件指针位置,从丢失位置重传
			nSize = n*READSIZE;
			dn++;
			m_SaveMsg2.File.lose = false;  //注意此处要修改根源数据，否则修改无效
			if (m_pParent2 != NULL) {
				m_pParent2->m_pParent->userMsg[m_PeerName2+(string)fileinfo.FileName].File.lose = false;
			}
			else {//if (m_pParent3 != NULL) {  //弹跳出现
				m_pParent3->m_pParentMsgFile->userMsg[m_PeerName2+(string)fileinfo.FileName].File.lose = false;
			}
		}

		//发送文件
		memset(m_SaveMsg2.File.file, 0, sizeof(m_SaveMsg2.File.file));
		nLen = file.Read(m_SaveMsg2.File.file, READSIZE);
		if (nLen > READSIZE) {
			MessageBox(_T("读取操作有误"));
		}
		nSize += nLen;


		//处理最后一个丢包问题
		if (nSize > fileinfo.FileSize) {
			long long ptr = fileinfo.FileSize - (READSIZE - (nSize - fileinfo.FileSize));
			file.Seek(ptr, CFile::begin); //修改文件指针位置,从丢失位置重传
			nSize = ptr;
			//n  = m_SaveMsg2.File.count;		//产生丢包
			memset(m_SaveMsg2.File.file, 0, sizeof(m_SaveMsg2.File.file));
			nLen = file.Read(m_SaveMsg2.File.file, READSIZE);
			nSize += nLen;
			dn++;
		}
		
		m_SaveMsg2.READ = false;
		m_SaveMsg2.isSave = true;
		m_SaveMsg2.sign = FILEQEUST;
		m_SaveMsg2.File.count = ++n;  //序列号
		m_SaveMsg2.File.FileSize = nLen;
		Send();  //发送

		//将文件数据更新到控件上
		fileSize.Format("%d/", fileinfo.FileSize);
		str.Format("%d/", nSize);
		fileSize += str;

		CString strn;
		strn.Format("%d", dn);
		fileSize += strn;

		GetDlgItem(IDC_FEDIT_SIZE)->SetWindowTextA(fileSize);
		Sleep(50);
	}


	file.Close();
	GetDlgItem(IDC_FILE_START)->EnableWindow(true);
	GetDlgItem(IDC_REMOVE)->EnableWindow(false);
	string strs = "文件发送完成: " + (string)fileinfo.FileName;
	m_FileMsg.SetWindowText(strs.c_str());
	m_FileMsg.LineScroll(m_FileMsg.GetLineCount());
	//修改状态，防止下次发送时获取的是上次反馈信息
	InitState();
}

void CP2P_FILEDlg::OnTimer(UINT_PTR nIDEvent)  //定时器处理函数
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 3:
		KillTimer(3);
		MessageBox("等待确认接收超时！");
		fileSend = false;
		break;
	case 4:  //超时重传确认命令
		{
			KillTimer(4);
			m_SaveMsg2.READ = true;
			m_SaveMsg2.isSave = true;
			m_SaveMsg2.File.lose = false;
			m_SaveMsg2.sign = FILEQEUST;
			//根据对象选择发送方法
			Send();
			SetTimer(4, 3000, NULL);  //定时器
		}
		break;
	default:;
	}
	CDialog::OnTimer(nIDEvent);
}

void CP2P_FILEDlg::Send() {
	if (m_pParent2 != NULL) {
		OnPeerChatMsgSend();
	}
	else if (m_pParent3 != NULL) {  //弹跳出现
		OnPeerFileMsgSend();
	}
	else {
		AfxMessageBox("用户获取异常");
		return;
	}
}


//终止操作
void CP2P_FILEDlg::OnBnClickedRemove()
{
	// TODO: Add your control notification handler code here
	string str; 
	if (SendOrRecv == 0) {
		return;
	}
	if (SendOrRecv == 1) {  //接收
		fileRecv = false;
		SendOrRecv = 0;
		str = "已终止接收文件: " + (string)fileinfo.FileName;
		m_FileMsg.SetWindowText(str.c_str());
	}
	else if (SendOrRecv == 2) {  //发送
		fileSend = false;
		str = "已终止发送文件: " + (string)fileinfo.FileName;
		m_FileMsg.SetWindowText(str.c_str());
		GetDlgItem(IDC_FILE_START)->EnableWindow(true);
	}

	InitState(); 
	GetDlgItem(IDC_REMOVE)->EnableWindow(false);
}

void CP2P_FILEDlg::modifyState() {
	string str;
	if (SendOrRecv == 0) {
		return;
	}
	if (SendOrRecv == 1) {  //接收
		fileRecv = false;
		SendOrRecv = 0;
		str = "发送端已终止发送文件：" + (string)fileinfo.FileName;
		m_FileMsg.SetWindowText(str.c_str());
		m_FileMsg.LineScroll(m_FileMsg.GetLineCount());
	}
	else if (SendOrRecv == 2) {  //发送
		fileSend = false;
		str = "接收端已终止接收文件: " + (string)fileinfo.FileName;
		m_FileMsg.SetWindowText(str.c_str());
		m_FileMsg.LineScroll(m_FileMsg.GetLineCount());
		GetDlgItem(IDC_FILE_START)->EnableWindow(true);
	}
	InitState();  //初始原状态
	GetDlgItem(IDC_REMOVE)->EnableWindow(false);
}

bool CP2P_FILEDlg::getData2() {
	if (m_pParent3 != NULL) {
		m_SaveMsg2 = m_pParent3->m_pParentMsgFile->userMsg[m_PeerName2+(string)fileinfo.FileName];
		return true;
	}
	else if (m_pParent2 != NULL) {
		m_SaveMsg2 = m_pParent2->m_pParent->userMsg[m_PeerName2+(string)fileinfo.FileName];
		return true;
	}
	else {
		return false;
	}
}

void CP2P_FILEDlg::InitState() {
	//修改根源的状态,并发出消息
	string userNamef = m_PeerName2 + (string)fileinfo.FileName;
	if (m_pParent2 != NULL) {
		m_pParent2->m_pParent->userMsg[userNamef].sign = P2PCHATMSG;
		m_pParent2->m_pParent->userMsg[userNamef].READ = true;
		m_pParent2->m_pParent->userMsg[userNamef].isSave = false;
		m_pParent2->m_pParent->deleteUserMsg(userNamef);
	}
	else {
		//注意：由于多线程共享变量的原因，变量修改的顺序直接会影响其它线程执行，所以要以主要的变量交叉操作
		m_pParent3->m_pParentMsgFile->userMsg[userNamef].sign = P2PCHATMSG;  //要放在前边，否则会影响其它线程的判断
		m_pParent3->m_pParentMsgFile->userMsg[userNamef].READ = true;
		m_pParent3->m_pParentMsgFile->userMsg[userNamef].isSave = false;
		m_pParent3->m_pParentMsgFile->deleteUserMsg(userNamef);
	}
}