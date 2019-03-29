// P2P_ENDDlg.cpp : 实现文件
//
#pragma once

#include <ctime>
#include "stdafx.h"
#include "P2P_END.h"
#include "P2P_ENDDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };  //100

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CP2P_ENDDlg 对话框

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

CP2P_ENDDlg::CP2P_ENDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CP2P_ENDDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CP2P_ENDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOGIN, m_UserName);
	DDX_Control(pDX, IDC_EDIT_SERVMSG, m_ServMsg);
	DDX_Control(pDX, IDC_EDIT_SEND, m_ServSend);
	DDX_Control(pDX, IDC_EDIT_SERVIP, m_ServIP);
	DDX_Control(pDX, IDC_EDIT_SERVPORT, m_ServPort);
	DDX_Control(pDX, IDC_LOGIN, m_LoginButton);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_ExitButton);
	DDX_Control(pDX, IDC_SERVSEND, m_SendButton);
	DDX_Control(pDX, IDC_LIST1, m_OLUserList);
	//DDX_Control(pDX, IDC_USERLIST, m_UserListBox);
	DDX_Control(pDX, IDC_EDIT_PSW, m_Password);
}

BEGIN_MESSAGE_MAP(CP2P_ENDDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_LOGIN, &CP2P_ENDDlg::OnLogin)
	ON_BN_CLICKED(IDC_SERVSEND, &CP2P_ENDDlg::OnServSend)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CP2P_ENDDlg::OnExit)
	ON_WM_TIMER()
	ON_LBN_DBLCLK(IDC_LIST1, &CP2P_ENDDlg::OnUserList)
	ON_EN_CHANGE(IDC_EDIT_SERVPORT, &CP2P_ENDDlg::OnEnChangeEditServport)
	ON_BN_CLICKED(IDC_CANEL, &CP2P_ENDDlg::OnCanel)
	ON_BN_CLICKED(IDC_SETTING, &CP2P_ENDDlg::OnSetting)
	ON_BN_CLICKED(IDC_FORGET, &CP2P_ENDDlg::OnForget)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CP2P_ENDDlg::OnClear)
	ON_BN_CLICKED(IDC_REG1, &CP2P_ENDDlg::OnReg1)
	ON_BN_CLICKED(IDC_REG2, &CP2P_ENDDlg::OnReg2)
	ON_BN_CLICKED(IDC_BACK, &CP2P_ENDDlg::OnBack)
	ON_BN_CLICKED(IDC_FORGET2, &CP2P_ENDDlg::OnForget2)
	ON_EN_CHANGE(IDC_EDIT_IDCARD, &CP2P_ENDDlg::OnEnChangeEditIdcard)
END_MESSAGE_MAP()


// CP2P_ENDDlg 消息处理程序

BOOL CP2P_ENDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//默认的服务器ip和端口号
	m_UserData.strPort = "1000";
	m_UserData.strIP = "127.0.0.1";
	m_ServIP.SetWindowText("127.0.0.1");
	m_ServPort.SetWindowText("1000");
	m_ExitButton.EnableWindow(FALSE);
	m_SendButton.EnableWindow(FALSE);
	m_State = FALSE ;
	   //为对话框分配空间  否则create不出来 - -
	m_Extend=FALSE;
	this->MoveWindow(500, 300, 500, 320, 1);  //窗口大小及位置

	buffer.READ = true;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//最小化
void CP2P_ENDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CP2P_ENDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CP2P_ENDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CP2P_ENDDlg::OnLogin()
{
	CString strName;
	CString strPSW;
	///CString strChat;
	//m_State = TRUE ;
	//获取窗口数据
	this->GetDlgItem(IDC_EDIT_LOGIN)->GetWindowText(strName);
	this->GetDlgItem(IDC_EDIT_PSW)->GetWindowText(strPSW);
	this->GetDlgItem(IDC_EDIT_SERVIP)->GetWindowText(m_UserData.strIP);
	this->GetDlgItem(IDC_EDIT_SERVPORT)->GetWindowText(m_UserData.strPort);

	//初始化数据
	strcpy(m_UserData.userName,strName.GetBuffer());
	strName.ReleaseBuffer();
	strcpy(m_ClientMsg.m_UserName,m_UserData.userName);
	strcpy(m_ClientMsg.m_PSW,strPSW.GetBuffer());
	strPSW.ReleaseBuffer();
	strName+=" 上线了！！！";
	strcpy(m_ClientMsg.chat,strName.GetBuffer());
	strName.ReleaseBuffer();
	m_ClientMsg.sign = 1;  //表示登录
	m_ClientMsg.id = 1;
	m_ClientSock.SetDlg(this);

	if (strName.GetLength()==0)
	{
		MessageBox("请输入用户名");
		return;
	}
	if(m_UserData.strIP.GetLength()==0||m_UserData.strPort.GetLength()==0)
	{
		MessageBox("请输入IP和端口号");  //新窗口提示
		return;
	}
	if(!m_ClientSock.Create(0,SOCK_DGRAM))		//	0表示客户端随机端口
	{
		char szMsg[1024] = {0};
		sprintf(szMsg, "create faild: %d", m_ClientSock.GetLastError());
		AfxMessageBox(szMsg);
		return;
	}
	int nPort = atoi(m_UserData.strPort);
	m_ClientSock.SendTo((char*)&m_ClientMsg, sizeof(m_ClientMsg),nPort,m_UserData.strIP,0);  //将用户信息发送给客户端
	m_LoginButton.EnableWindow(FALSE); //按过一次不能再按了，因为客户端创建的连接还没关闭
	
	SetTimer(1,10000,NULL);   //设置定时器。判断登陆超时
	SetTimer(2,60000,NULL);   //设置定时器。判断是否与服务器保持连接
}

//主要逻辑
void CP2P_ENDDlg::ReceiveData(CClientSock *sock)
{
	//Message buffer;
	CString strChat;
	CString str;
	CString strTime;  
	PeerData *p_PeerData =NULL;
	int len = sizeof(SOCKADDR_IN);
	//接收服务器/客户端传回的数据
 	sock->ReceiveFrom((char*)&buffer,sizeof(buffer),(SOCKADDR*)&(this->m_ServAddr),&len,0);
	memcpy(&userMsg[buffer.m_UserName+(string)buffer.File.FileName],&buffer,sizeof(buffer));  //将用户的数据保存
	//更新列表
	
	if (buffer.sign != FILEQEUST && buffer.sign != P2PCHATMSG && buffer.sign != QUIT)  //p2p信息不更新在线列表
	{
		UpdateUserList(&buffer);
	}

	//处理文件
	if (buffer.READ == false && buffer.sign == P2PCHATMSG && buffer.isSave == false) {
		CreateMsgFileP2PDlg2(&buffer);
		return;
	}
	
	switch (buffer.sign)
	{
	case LOGINMSG:  //登录
		loginMsg();
		break;
	case MULCHATMSG:  //群聊
		if (strcmp(buffer.m_UserName,m_UserData.userName))  //
		{
			PlaySound((LPCTSTR)IDR_MULCHATMSG, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);		//播放声音
		}		
		AddRecvMsg(&(m_UserData.ServChat),&buffer);
		m_ServMsg.SetWindowText(m_UserData.ServChat);
		m_ServMsg.LineScroll(m_ServMsg.GetLineCount());		//	 自动滚到最底下
		break;
	case EXITMSG:   //退出
		exitMsg();
		break;
	case ISALIVEMSG:  //保活器
		UpdateUserList(&buffer);  //定时刷新列表
		buffer.id = m_UserData.id;  //获取计数值
		m_UserData.servACK = buffer.servACK;
		m_ClientSock.SendTo((char*)&buffer, sizeof(buffer),atoi(m_UserData.strPort),m_UserData.strIP,0);  //确认节点在线
		break;
	case PEERLOGINMSG:  //上线通知
		PlaySound((LPCTSTR)IDR_UPLINE, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);		//播放声音
		AddRecvMsg(&(m_UserData.ServChat),&buffer);
		m_ServMsg.SetWindowText(m_UserData.ServChat);
		m_ServMsg.LineScroll(m_ServMsg.GetLineCount());		//	 自动滚到最底下
		break;
    //UDP打洞
	case CONNECT1:  //第一次发送打洞消息
		{
			//节点地址
			sockaddr_in sock_peer = buffer.userAddr;
			//发送给对端节点
			buffer.sign = CONNECT_ACK1;
			//buffer.userAddr = addrBuffer;  //将节点地址当作数据
			sock->SendTo((char*)&buffer, sizeof(buffer), (SOCKADDR*)&(sock_peer), len, 0);
			Sleep(500);
			//将节点的数据发送给服务器
			//服务器端口
			int nport1 = atoi(m_UserData.strPort);  //
			buffer.sign = CONNECT_QUEST;
			m_ClientSock.SendTo((char*)&buffer, sizeof(buffer), nport1, m_UserData.strIP, 0);//不存在给服务器发送打洞请求
		}
		break;
	case CONNECT2:  //第二次发送打洞消息
		{
			//发送给被请求节点
			sockaddr_in sock_Peer = buffer.userAddr;  //取出对端节点地址
			buffer.sign = CONNECT_ACK2;
			sock->SendTo((char*)&buffer, sizeof(buffer), (SOCKADDR*)&(sock_Peer), len, 0);  //直接发送给对端节点
			}
		break;
	case CONNECT_ACK1:  //第一次接收反馈消息，（实际接收不到）
		//打洞消息忽略
		break;
	case CONNECT_ACK2:  //第二次接收反馈消息，接收对端节点的打洞消息
		{
			//发送给对端节点
			//m_UserData.strPort  //服务器port
			buffer.sign = CONNECT_OK;
			sock->SendTo((char*)&buffer, sizeof(buffer), (SOCKADDR*)&(this->m_ServAddr), len, 0);  //直接发送给对端节点
		}
		break;
	case CONNECT_OK:  //打洞成功
		CreateP2PDlg(&buffer);  //进入私聊页面
		break;
	case P2PCHATMSG:		//接受peer发送过来的信息.（私聊）
							//一来消息，对应的CLient就亮。存在则追加数据，不存在则创建对话框。用户双击了才显示
		peepChagMag();
		break;
	case REGMSG:  //注册反馈信息
		regMsg();
		break;
	case FORGETMSG:  //找回密码反馈信息
		forgetMsg();
		break;
	case QUIT:
		peepChagMag();
		RmoveUserList(buffer.m_UserName);
		if (m_ChatMsgDlg != NULL) {
			Sleep(5000);
			m_ChatMsgDlg->OnHide();
		}
		break;
	default:;
	};
	if (buffer.sign != FILEQEUST) { //更新定时器
		KillTimer(2);				// 重置定时器时间
		SetTimer(2, 60000, NULL);   //发送文件时，不更新定时器，发送大文件时也不用担心刷新问题，存在保活器
	}
}

void CP2P_ENDDlg::peepChagMag() {
	PeerData *p_PeerData = NULL;
	PlaySound((LPCTSTR)IDR_PEERMSG, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);		//播放声音
	buffer.userAddr = m_ServAddr;   //p2pmsg肯定是client发过来的
	p_PeerData = FindP2PChatDlgByName(buffer.m_UserName);  //查看用户是否已和用户已创建私聊对话框
	if (p_PeerData != NULL)
	{
		if (p_PeerData->peerChatDlg->isActive)
		{
			ShowP2PChatDlg(&buffer);	//	窗口已存在并显示，追加内容
		}
		else
		{
			p_PeerData->isRead = FALSE;
			UserListLightUp(TRUE, buffer.m_UserName);	//窗口已存在未显示，高亮它，追加内容
			ShowP2PChatDlg(&buffer);
		}
	}
	else
	{
		UserListLightUp(TRUE, buffer.m_UserName);
		CreateP2PDlg(&buffer); //创建并追加内容
	}
}

void CP2P_ENDDlg::exitMsg() {
	POSITION pos;
	PlaySound((LPCTSTR)IDR_EXITMSG, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);		//播放声音
	if (buffer.servACK == 0)
	{
		//通知文件传输终止
		if (m_MsgFileDlg && m_MsgFileDlg->m_FileMsgDlg2) {
			m_MsgFileDlg->m_FileMsgDlg2->OnBnClickedRemove();
		}

		if (m_ChatMsgDlg && m_ChatMsgDlg->m_FileMsgDlg) {
			m_ChatMsgDlg->m_FileMsgDlg->OnBnClickedRemove();
		}
		sendQuitMsg();	//通知私聊用户，退出私聊

		m_ClientSock.Close();
		m_State = FALSE;
		m_LoginButton.EnableWindow(TRUE);
		m_ExitButton.EnableWindow(FALSE);
		m_SendButton.EnableWindow(FALSE);
		m_ServIP.EnableWindow(TRUE);
		m_ServPort.EnableWindow(TRUE);
		m_UserName.EnableWindow(TRUE);
		m_OLUserList.ResetContent();	//移出列表中的内容

		pos = m_P2PChatList.GetHeadPosition();
		PeerData *p_PeerData = NULL;
		while (pos != NULL)   //析构所用的节点空间
		{
			p_PeerData = (PeerData*)m_P2PChatList.GetNext(pos);
			delete p_PeerData;
			//p_PeerData->peerChatDlg; //未析构
		}
	}
	MessageBox(_T("与服务器断开连接，程序即将退出！"));
	OnCancel();
}

void CP2P_ENDDlg::loginMsg() {
	CString strName;
	this->GetDlgItem(IDC_EDIT_LOGIN)->GetWindowText(strName);
	if (buffer.servACK == -1)
	{
		MessageBox(_T("用户名或密码错误！！"));
		m_LoginButton.EnableWindow(TRUE);
		m_ClientSock.Close();
		return;
	}
	PlaySound((LPCTSTR)IDR_LOGINMSG, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);		//播放声音

	m_State = TRUE;
	m_UserData.id = buffer.id;
	m_UserData.servACK = buffer.servACK;
	//更新窗口按钮
	m_LoginButton.EnableWindow(FALSE);
	m_ExitButton.EnableWindow(TRUE);
	m_SendButton.EnableWindow(TRUE);
	m_ServIP.EnableWindow(FALSE);
	m_ServPort.EnableWindow(FALSE);
	m_UserName.EnableWindow(FALSE);

	this->SetWindowText(strName + "的P2P聊天室");
	MessageBox("连接成功");
	LoginToChat();  //跳转至消息窗口
}

void CP2P_ENDDlg::regMsg() {
	KillTimer(1);
	if (buffer.servACK == -1)
	{
		MessageBox(_T("用户名已被注册！！"));
		this->GetDlgItem(IDC_REG2)->EnableWindow(TRUE);
		m_ClientSock.Close();
		return;
	}
	else
	{
		MessageBox(_T("注册成功！！"));
		this->GetDlgItem(IDC_REG2)->EnableWindow(TRUE);
		m_ClientSock.Close();
		GetDlgItem(IDC_LOGIN)->ShowWindow(TRUE);
		GetDlgItem(IDC_REG1)->ShowWindow(TRUE);
		GetDlgItem(IDC_CHECK1)->ShowWindow(TRUE);
		GetDlgItem(IDC_FORGET)->ShowWindow(TRUE);
		GetDlgItem(IDC_CHECK2)->ShowWindow(TRUE);
		GetDlgItem(IDC_CANEL)->ShowWindow(TRUE);
		GetDlgItem(IDC_REG2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_IDCARD)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_IDCARD)->ShowWindow(FALSE);
		GetDlgItem(IDC_BACK)->ShowWindow(FALSE);

		return;
	}
}

void CP2P_ENDDlg::forgetMsg() {
	KillTimer(1);
	if (buffer.servACK == -1)
	{
		MessageBox(_T("资料填写错误！！"));
		this->GetDlgItem(IDC_FORGET2)->EnableWindow(TRUE);
		m_ClientSock.Close();
		return;
	}
	else
	{
		MessageBox(_T("密码找回成功！！"));
		m_Password.SetPasswordChar(NULL);
		GetDlgItem(IDC_EDIT_PSW)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PSW)->SetWindowText(buffer.m_PSW);
		//销毁密码，ID.防止泄露
		memset(buffer.m_PSW, 0, sizeof(buffer.m_PSW));
		memset(buffer.m_IDCard, 0, sizeof(buffer.m_IDCard));

		GetDlgItem(IDC_FORGET2)->EnableWindow(TRUE);
		m_ClientSock.Close();
		return;
	}
}

void CP2P_ENDDlg::UserListLightUp(BOOL flag,char *userName) //flag为真时候高亮
{
	int index ;
	index = m_OLUserList.FindString(0,userName);
	m_OLUserList.SetSel(index,TRUE);
}

//判断用户是否正确及打印消息
void CP2P_ENDDlg::ShowP2PChatDlg(Message *p_PeerBuffer)
{
	//判断对话是否存在于列表
	CString userName = p_PeerBuffer->m_UserName;	//	对方的名字
	POSITION pos = m_P2PChatList.GetHeadPosition();
	PeerData *p_PeerData = NULL;
	p_PeerData = FindP2PChatDlgByName(p_PeerBuffer->m_UserName);
	if (!strcmp(p_PeerData->peerName,userName))
	{
		AddRecvMsg(&(p_PeerData->peerMsgLog),p_PeerBuffer);  //拼接消息
		p_PeerData->peerChatDlg->m_PeerRecv.SetWindowText(p_PeerData->peerMsgLog);
		p_PeerData->peerChatDlg->m_PeerRecv.LineScroll(p_PeerData->peerChatDlg->m_PeerRecv.GetLineCount());  //自动滚动到最后一行
		return;	
	}
}

//群聊发送消息
void CP2P_ENDDlg::OnServSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText;
	Message buffer ;
	int nPort ;
	
	if (m_State)
	{
		this->GetDlgItem(IDC_EDIT_SEND)->GetWindowText(strText);
		if (strText=="")
		{
			MessageBox("请输入消息！");
			return;
		}
		m_ClientSock.SetDlg(this);
		strcpy(buffer.m_UserName,m_UserData.userName);
		strcpy(buffer.chat,strText.GetBuffer());	strText.ReleaseBuffer();
		buffer.sign = MULCHATMSG;  //发送消息
		buffer.id = m_UserData.id;
		m_ServSend.SetWindowText("");
		nPort = atoi(m_UserData.strPort);
		m_ClientSock.SendTo((char*)&buffer, sizeof(buffer),nPort,m_UserData.strIP,0);
	}
	else
	{
		MessageBox("请先登录！");
		return;
	}
}

void CP2P_ENDDlg::OnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	Message buffer ;
	buffer.sign = EXITMSG;
	buffer.id = m_UserData.id;
	m_ClientSock.SendTo((char*)&buffer, sizeof(buffer),atoi(m_UserData.strPort),m_UserData.strIP,0);
}

//更新用户列表
void CP2P_ENDDlg::UpdateUserList(Message *buffer)
{
	PeerData *p_PeerData=NULL;
	POSITION pos = m_P2PChatList.GetHeadPosition();
	m_OLUserList.ResetContent();
	for(int i=0 ;i<buffer->userNum ; i++ )
	{
		strcpy(m_ClientMsg.OLUserList[i],buffer->OLUserList[i]);
		m_OLUserList.AddString(m_ClientMsg.OLUserList[i]);//更新在线用户列表
	}
	while (pos!=NULL)
	{
		p_PeerData = (PeerData *)m_P2PChatList.GetNext(pos);
		if (p_PeerData->isRead==FALSE)
		{
			UserListLightUp(TRUE,p_PeerData->peerName);  //显示节点的name
		}
	}

}

void CP2P_ENDDlg::OnTimer(UINT_PTR nIDEvent)  //定时器处理函数
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case 1:
		KillTimer(1);
		if (!m_State)
		{
			MessageBox("连接服务器超时！");
			m_ClientSock.Close();
			m_LoginButton.EnableWindow(TRUE);
			GetDlgItem(IDC_FORGET2)->EnableWindow(TRUE);
			GetDlgItem(IDC_REG2)->EnableWindow(TRUE);
		}
		break;
	case 2:
		KillTimer(2);
		MessageBox("与服务器丢失连接！");
		//this->CloseWindow();
		m_ClientSock.Close();
		m_LoginButton.EnableWindow(TRUE);
		break;
	case 4:
		MessageBox("错误！");
		break;
	default:;
	}
	CDialog::OnTimer(nIDEvent);
}

void CP2P_ENDDlg::OnUserList()
{
	// TODO: 在此添加控件通知处理程序代码

	//是否向服务器发一条P2P请求
	//Message buffer;
	int listCount;
	int nPort = atoi(m_UserData.strPort);
	PeerData *p_PeerData;
	buffer.id = m_UserData.id;
	listCount = m_OLUserList.GetCurSel();
	m_OLUserList.GetText(listCount,buffer.m_UserName);
	//点击自己忽略
	if (strcmp(buffer.m_UserName, m_UserData.userName) == 0) {
		return;
	}

	p_PeerData=FindP2PChatDlgByName(buffer.m_UserName);	//	查找是否已存在对话框
	if (p_PeerData!=NULL)		//存在了，因为被双击，直接SHOW他
	{
		p_PeerData->isRead = TRUE;
		p_PeerData->peerChatDlg->ShowWindow(SW_SHOW);
		m_OLUserList.SetSel(listCount,FALSE);
		return;
	}

	//此处如何避免重复打洞过程？？？
	//此法操作不可
	if (buffer.sign == CONNECT_ACK2) {  //如果已经进行过打洞操作
		buffer.sign = CONNECT_OK;
		CreateP2PDlg(&buffer);  //进入私聊页面
		return;
	}
	buffer.sign = CONNECT_RES;  //请求打洞
	m_ClientSock.SendTo((char*)&buffer, sizeof(buffer),nPort,m_UserData.strIP,0);//不存在给服务器发送打洞请求
	
}


void CP2P_ENDDlg::RecvP2PMsg(Message *p_PeerBuffer)
{

}

//根据用户名查找某个节点的数据
PeerData* CP2P_ENDDlg::FindP2PChatDlgByName(char *userName)
{													//	对方的名字
	POSITION pos = m_P2PChatList.GetHeadPosition();
	PeerData *p_PeerData = NULL;
	p_PeerData = new PeerData();		//	不分配空间就无法给里面的变量赋值；
	while(pos!=NULL)
	{
		p_PeerData = (PeerData*)m_P2PChatList.GetNext(pos);
		if (!strcmp(p_PeerData->peerName ,userName))
		{
			return p_PeerData;	
		}
		//isPeerExist = true;
	}
	return NULL;
}

//拼接显示的字符串
void CP2P_ENDDlg::AddRecvMsg(CString *p_MsgLog,Message *p_MsgBuffer)
{
	CTime t=CTime::GetCurrentTime();
	CString strTime;
	strTime.Format("%d:%d:%d",t.GetHour(),t.GetMinute(),t.GetSecond());

	*p_MsgLog+=p_MsgBuffer->m_UserName;
	*p_MsgLog+="\t";
	*p_MsgLog+=strTime;
	*p_MsgLog+="\r\n";
	*p_MsgLog+=p_MsgBuffer->chat;
	*p_MsgLog+="\r\n";
	*p_MsgLog+="\r\n";
}

//创建私聊对话框
void CP2P_ENDDlg::CreateP2PDlg(Message *p_PeerBuffer)
{
	CString userName = p_PeerBuffer->m_UserName;	//	对方的名字
	POSITION pos = m_P2PChatList.GetHeadPosition();
	PeerData *p_PeerData = NULL;
	m_ChatMsgDlg = new CP2PChatDlg();  //创建私聊对话框
	m_ChatMsgDlg->Create(IDD_P2PCHAT,this);
	m_ChatMsgDlg->ModifyStyleEx(0,  WS_EX_APPWINDOW);//任务栏显示
	
	m_ChatMsgDlg->SetWindowText("正在与"+userName+"交谈中");

	m_ChatMsgDlg->SetParentDlg(this);				//传入父窗口的指针
	m_ChatMsgDlg->m_SaveMsg = *p_PeerBuffer;
	m_ChatMsgDlg->m_SaveMsg.sign = P2PCHATMSG;  //私聊
	m_ChatMsgDlg->isActive = FALSE;
	strcpy(m_ChatMsgDlg->m_SaveMsg.m_UserName,m_UserData.userName);
	strcpy(m_ChatMsgDlg->m_PeerName,userName);

	//m_ChatMsgDlg->m_ParentMsg = *p_PeerBuffer;
	//p_PeerData = NULL;				//容器循环后经常忘记把指针重置 导致容器中都变东西
	p_PeerData = new PeerData();
	p_PeerData->peerAddr = p_PeerBuffer->userAddr;
	p_PeerData->state = true;
	p_PeerData->isRead = FALSE;
	strcpy(p_PeerData->peerName,userName);
	p_PeerData->peerChatDlg = m_ChatMsgDlg;
	//if (p_PeerBuffer->sign==P2PHOLETO)  //与switch一样
	if (p_PeerBuffer->sign == CONNECT_OK)  //打洞成功与switch一样
	{
		m_ChatMsgDlg->ShowWindow(SW_SHOW);
		m_ChatMsgDlg->isActive = TRUE;
		p_PeerData->isRead = TRUE;
		p_PeerData->peerMsgLog = "请求聊天成功\r\n";
		strcpy(p_PeerData->peerChatDlg->m_SaveMsg.chat,"请求聊天成功\r\n");
		p_PeerData->peerChatDlg->m_PeerRecv.SetWindowText(p_PeerData->peerMsgLog);
	}
	else
	{
		AddRecvMsg(&(p_PeerData->peerMsgLog),p_PeerBuffer);
		p_PeerData->peerChatDlg->m_PeerRecv.SetWindowText(p_PeerData->peerMsgLog);
	}
	//追加聊天记录
	m_P2PChatList.AddTail(p_PeerData); //加入到对话链表里头
	//m_ChatMsgDlg = NULL;
}

void CP2P_ENDDlg::OnEnChangeEditServport()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CP2P_ENDDlg::OnCanel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->OnCancel();
}

//高级设置
void CP2P_ENDDlg::OnSetting()
{
	// TODO: 在此添加控件通知处理程序代码
	PlaySound((LPCTSTR)IDR_FOLDER, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);		//播放声音

	if(m_Extend)
	{
		this->MoveWindow(500,300,500,320,1);
		GetDlgItem(IDC_SETTING)->SetWindowText("高级设置↓");		
		m_Extend=FALSE;
	}
	else
	{
		this->MoveWindow(500, 300, 500, 480, 1);
		//this->MoveWindow(470,260,327,360,1);
		GetDlgItem(IDC_SETTING)->SetWindowText("高级设置↑");
		m_Extend=TRUE;
	}
}

//空间状态设置
void CP2P_ENDDlg::OnForget()
{
	GetDlgItem(IDC_LOGIN)->ShowWindow(FALSE);
	GetDlgItem(IDC_REG1)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHECK1)->ShowWindow(FALSE);
	GetDlgItem(IDC_FORGET)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHECK2)->ShowWindow(FALSE);
	GetDlgItem(IDC_CANEL)->ShowWindow(FALSE);
	GetDlgItem(IDC_FORGET2)->ShowWindow(TRUE);
	GetDlgItem(IDC_BACK)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_IDCARD)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_IDCARD)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_PSW)->EnableWindow(FALSE);
}

void CP2P_ENDDlg::LoginToChat()  //消息窗口
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_SETTING)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_LOGIN)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_PSW)->ShowWindow(FALSE);
	GetDlgItem(IDC_LOGIN)->ShowWindow(FALSE);
	GetDlgItem(IDC_REG1)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHECK1)->ShowWindow(FALSE);
	GetDlgItem(IDC_FORGET)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHECK2)->ShowWindow(FALSE);
	GetDlgItem(IDC_CANEL)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_BOX1)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_PSW)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVIP)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVPORT)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_BOX2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_IP)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_PORT)->ShowWindow(FALSE);
	MoveWindow(350,200,700,550,1);  //窗口位置及大小

	//设置控件位置及大小
	GetDlgItem(IDC_BUTTON_EXIT)->SetWindowPos(NULL, 535, 10, 0, 0, SWP_NOZORDER | SWP_NOSIZE);//退出
	GetDlgItem(IDC_EDIT_SERVMSG)->SetWindowPos(NULL, 20, 80, 480, 250, SWP_NOZORDER); //消息
	GetDlgItem(IDC_EDIT_SEND)->SetWindowPos(NULL, 20, 330, 480, 100, SWP_NOZORDER); //发生消息
	GetDlgItem(IDC_LIST1)->SetWindowPos(NULL, 500, 80, 150, 350, SWP_NOZORDER); //列表
	GetDlgItem(IDC_BUTTON_CLEAR)->SetWindowPos(NULL, 300, 440, 0, 0, SWP_NOZORDER | SWP_NOSIZE); //清屏
	GetDlgItem(IDC_STATIC_LIST)->SetWindowPos(NULL, 500, 50, 0, 0, SWP_NOZORDER | SWP_NOSIZE); //用户列表
	GetDlgItem(IDC_SERVSEND)->SetWindowPos(NULL, 400, 440, 0, 0, SWP_NOZORDER | SWP_NOSIZE); //发送
	GetDlgItem(IDC_FILE)->SetWindowPos(NULL, 200, 440, 0, 0, SWP_NOZORDER | SWP_NOSIZE); //发送

}
//清空消息
void CP2P_ENDDlg::OnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_UserData.ServChat = "";
	GetDlgItem(IDC_EDIT_SERVMSG)->SetWindowText("");

}

//空间状态2
void CP2P_ENDDlg::OnReg1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_LOGIN)->ShowWindow(FALSE);
	GetDlgItem(IDC_REG1)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHECK1)->ShowWindow(FALSE);
	GetDlgItem(IDC_FORGET)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHECK2)->ShowWindow(FALSE);
	GetDlgItem(IDC_CANEL)->ShowWindow(FALSE);
	GetDlgItem(IDC_REG2)->ShowWindow(TRUE);
	GetDlgItem(IDC_BACK)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_IDCARD)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_IDCARD)->ShowWindow(TRUE);
}

//注册按钮
void CP2P_ENDDlg::OnReg2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strName;
	CString strPSW;
	CString strIDCard;
	
	this->GetDlgItem(IDC_EDIT_LOGIN)->GetWindowText(strName);
	this->GetDlgItem(IDC_EDIT_PSW)->GetWindowText(strPSW);
	this->GetDlgItem(IDC_EDIT_IDCARD)->GetWindowText(strIDCard);
	this->GetDlgItem(IDC_EDIT_SERVIP)->GetWindowText(m_UserData.strIP);
	this->GetDlgItem(IDC_EDIT_SERVPORT)->GetWindowText(m_UserData.strPort);
	if (strName.GetLength()<6)
	{
		MessageBox("用户名必须大于3个汉字或者6个字符！");
		return;
	}
	if (strPSW.GetLength()<5)
	{
		MessageBox("密码必须大于六位！");
		return;
	}
	if (strIDCard.GetLength()==0)
	{
		MessageBox("请输入身份证号码！");
		return;
	}
	if (strIDCard.GetLength()!=18)
	{
		MessageBox("请输入正确的身份证号码！");
		return;
	}
	if(m_UserData.strIP.GetLength()==0||m_UserData.strPort.GetLength()==0)
	{
		MessageBox("请输入IP和端口号");
		return;
	}
	strcpy(m_ClientMsg.m_UserName,strName.GetBuffer());
	strcpy(m_ClientMsg.m_PSW,strPSW.GetBuffer());
	strcpy(m_ClientMsg.m_IDCard,strIDCard.GetBuffer());
	strName.ReleaseBuffer();
	strPSW.ReleaseBuffer();
	strIDCard.ReleaseBuffer();
	m_ClientMsg.sign = REGMSG;
	m_ClientMsg.id = 1;
	m_ClientSock.SetDlg(this);

	if(!m_ClientSock.Create(0,SOCK_DGRAM))		//	0表示客户端随机端口
	{
		char szMsg[1024] = {0};
		sprintf(szMsg, "create faild: %d", m_ClientSock.GetLastError());
		AfxMessageBox(szMsg);
		return;
	}
	int nPort = atoi(m_UserData.strPort);  //获取服务器的port
	m_ClientSock.SendTo((char*)&m_ClientMsg, sizeof(m_ClientMsg),nPort,m_UserData.strIP,0);
	this->GetDlgItem(IDC_REG2)->EnableWindow(FALSE);
	SetTimer(1,10000,NULL);   //设置定时器。判断登陆超时
	//按过一次不能再按了，因为客户端创建的连接还没关闭
}

//按退出按钮后的空间状态
void CP2P_ENDDlg::OnBack()
{
	// TODO: 在此添加控件通知处理程序代码
	this->GetDlgItem(IDC_FORGET2)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_EDIT_PSW)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_EDIT_PSW)->SetWindowText("");
	this->GetDlgItem(IDC_EDIT_IDCARD)->SetWindowText("");
	m_Password.SetPasswordChar('*');
	if (m_ClientSock)
	{
		m_ClientSock.Close();
	}
	
	GetDlgItem(IDC_LOGIN)->ShowWindow(TRUE);
	GetDlgItem(IDC_REG1)->ShowWindow(TRUE);
	GetDlgItem(IDC_CHECK1)->ShowWindow(TRUE);
	GetDlgItem(IDC_FORGET)->ShowWindow(TRUE);
	GetDlgItem(IDC_CHECK2)->ShowWindow(TRUE);
	GetDlgItem(IDC_CANEL)->ShowWindow(TRUE);
	GetDlgItem(IDC_REG2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_IDCARD)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_IDCARD)->ShowWindow(FALSE);
	GetDlgItem(IDC_BACK)->ShowWindow(FALSE);
}

//忘记密码
void CP2P_ENDDlg::OnForget2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strName;
	CString strPSW;
	CString strIDCard;

	this->GetDlgItem(IDC_EDIT_LOGIN)->GetWindowText(strName);
	this->GetDlgItem(IDC_EDIT_PSW)->GetWindowText(strPSW);
	this->GetDlgItem(IDC_EDIT_IDCARD)->GetWindowText(strIDCard);
	this->GetDlgItem(IDC_EDIT_SERVIP)->GetWindowText(m_UserData.strIP);
	this->GetDlgItem(IDC_EDIT_SERVPORT)->GetWindowText(m_UserData.strPort);
	if (strName.GetLength()==0)
	{
		MessageBox("请输入用户名");
		return;
	}
	if (strIDCard.GetLength()==0)
	{
		MessageBox("请输入身份证号码");
		return;
	}
	if(m_UserData.strIP.GetLength()==0||m_UserData.strPort.GetLength()==0)
	{
		MessageBox("请输入IP和端口号");
		return;
	}
	strcpy(m_ClientMsg.m_UserName,strName.GetBuffer());
	strcpy(m_ClientMsg.m_PSW,strPSW.GetBuffer());
	strcpy(m_ClientMsg.m_IDCard,strIDCard.GetBuffer());
	strName.ReleaseBuffer();
	strPSW.ReleaseBuffer();
	strIDCard.ReleaseBuffer();
	m_ClientMsg.sign = FORGETMSG;
	m_ClientMsg.id = 1;
	m_ClientSock.SetDlg(this);
	if(!m_ClientSock.Create(0,SOCK_DGRAM))		//	0表示客户端随机端口
	{
		char szMsg[1024] = {0};
		sprintf(szMsg, "create faild: %d", m_ClientSock.GetLastError());
		AfxMessageBox(szMsg);
		return;
	}
	int nPort = atoi(m_UserData.strPort);
	m_ClientSock.SendTo((char*)&m_ClientMsg, sizeof(m_ClientMsg),nPort,m_UserData.strIP,0);
	this->GetDlgItem(IDC_FORGET2)->EnableWindow(FALSE);
	SetTimer(1,10000,NULL);   //设置定时器。判断登陆超时
	//按过一次不能再按了，因为客户端创建的连接还没关闭
}

void CP2P_ENDDlg::OnEnChangeEditIdcard()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CP2P_ENDDlg::CreateMsgFileP2PDlg2(Message *p_PeerBuffer) {
	CString userName = p_PeerBuffer->m_UserName;	//	对方的名字
	POSITION pos = m_P2PChatList.GetHeadPosition();
	PeerData *p_PeerData = NULL;
	m_MsgFileDlg = new CP2PFILEMSGDlg();  //创建私聊对话框
	m_MsgFileDlg->Create(IDD_DIALOG2, this);
	m_MsgFileDlg->ModifyStyleEx(0, WS_EX_APPWINDOW);//任务栏显示

	m_MsgFileDlg->SetWindowText("文件操作");

	m_MsgFileDlg->SetMsgFileParentDlg(this);				//传入父窗口的指针
	m_MsgFileDlg->m_SaveMsgFile = *p_PeerBuffer;
	m_MsgFileDlg->m_SaveMsgFile.sign = P2PCHATMSG;  //私聊
	m_MsgFileDlg->isActiveMsgFile = FALSE;
	m_MsgFileDlg->isSave = false;
	//获取文件信息
	m_MsgFileDlg->files.FileSize = p_PeerBuffer->File.FileSize;
	strcpy(m_MsgFileDlg->files.FileName, p_PeerBuffer->File.FileName);

	strcpy(m_MsgFileDlg->m_SaveMsgFile.m_UserName, m_UserData.userName);
	strcpy(m_MsgFileDlg->m_PeerNameMsgFile, userName);  //获取用户名



	//m_ChatMsgDlg->m_ParentMsg = *p_PeerBuffer;
	//p_PeerData = NULL;				//容器循环后经常忘记把指针重置 导致容器中都变东西
	p_PeerData = new PeerData();
	p_PeerData->peerAddr = p_PeerBuffer->userAddr;
	p_PeerData->state = true;
	p_PeerData->isRead = true;
	
	strcpy(p_PeerData->peerName, userName);
	p_PeerData->peerMsgFileDlg = m_MsgFileDlg;
	//if (p_PeerBuffer->sign==P2PHOLETO)  //与switch一样
	if (p_PeerBuffer->READ == false)  //打洞成功与switch一样
	{
		m_MsgFileDlg->ShowWindow(SW_SHOW);
		m_MsgFileDlg->isActiveMsgFile = TRUE;
		p_PeerData->isRead = TRUE;
		string str = "有一个待收文件: " + (string)p_PeerBuffer->File.FileName + "\r\n";
		p_PeerData->peerMsgLog = str.c_str();
		//strcpy(p_PeerData->peerMsgFileDlg->m_SaveMsgFile.chat, "请求聊天成功\r\n");
		p_PeerData->peerMsgFileDlg->m_Msg.SetWindowText(p_PeerData->peerMsgLog);
	}
	//追加聊天记录
	PeerData* tmp = FindP2PChatDlgByName(buffer.m_UserName);  //查看用户是否已和用户已创建私聊对话框
	if (tmp == NULL) {
		buffer.userAddr = m_ServAddr;
		CreateChatView(p_PeerBuffer);  //创建私聊对话框，不显示
		//m_P2PChatList.AddTail(p_PeerData); //加入到对话链表里头
	}

	//delete p_PeerData;
}

bool CP2P_ENDDlg::putFileView() {
	return fileView;
}

//将用户添加到私聊列表
void CP2P_ENDDlg::CreateChatView(Message *p_PeerBuffer) {
	CString userName = p_PeerBuffer->m_UserName;	//	对方的名字
	POSITION pos = m_P2PChatList.GetHeadPosition();
	PeerData *p_PeerData = NULL;
	m_ChatMsgDlg = new CP2PChatDlg();  //创建私聊对话框
	m_ChatMsgDlg->Create(IDD_P2PCHAT, this);
	m_ChatMsgDlg->ModifyStyleEx(0, WS_EX_APPWINDOW);//任务栏显示

	m_ChatMsgDlg->SetWindowText("正在与" + userName + "交谈中");

	m_ChatMsgDlg->SetParentDlg(this);				//传入父窗口的指针
	m_ChatMsgDlg->m_SaveMsg = *p_PeerBuffer;
	m_ChatMsgDlg->m_SaveMsg.sign = P2PCHATMSG;  //私聊
	m_ChatMsgDlg->isActive = false;
	strcpy(m_ChatMsgDlg->m_SaveMsg.m_UserName, m_UserData.userName);
	strcpy(m_ChatMsgDlg->m_PeerName, userName);

	//m_ChatMsgDlg->m_ParentMsg = *p_PeerBuffer;
	//p_PeerData = NULL;				//容器循环后经常忘记把指针重置 导致容器中都变东西
	p_PeerData = new PeerData();
	p_PeerData->peerAddr = p_PeerBuffer->userAddr;
	p_PeerData->state = true;
	strcpy(p_PeerData->peerName, userName);
	p_PeerData->peerChatDlg = m_ChatMsgDlg;
	p_PeerData->peerMsgLog = "请求聊天成功\r\n";
	strcpy(p_PeerData->peerChatDlg->m_SaveMsg.chat, "请求聊天成功\r\n");
	m_ChatMsgDlg->isActive = false;
	p_PeerData->isRead = TRUE;
	//追加聊天记录
	m_P2PChatList.AddTail(p_PeerData); //加入到对话链表里头
	//m_ChatMsgDlg = NULL;
}

void CP2P_ENDDlg::RmoveUserList(string name) {
	POSITION tmp;
	POSITION pos = m_P2PChatList.GetHeadPosition();  //定义一个抽象数据类型变量 pos 获取链表的头部
	while (pos != NULL)
	{
		tmp = pos;
		PeerData *p_Peer = (PeerData*)m_P2PChatList.GetNext(pos);
		if (!strcmp(p_Peer->peerName, name.c_str()))
		{
			delete p_Peer;
			m_P2PChatList.RemoveAt(tmp);
			return;
		}
	}
}

void CP2P_ENDDlg::sendQuitMsg() {
	Message quit_msg;
	POSITION pos = m_P2PChatList.GetHeadPosition();  //定义一个抽象数据类型变量 pos 获取链表的头部
	while (pos != NULL)
	{
		PeerData *p_Peer = (PeerData*)m_P2PChatList.GetNext(pos);
		quit_msg.sign = QUIT;
		quit_msg.READ = true;
		quit_msg.isSave = false;
		string str = (string)m_UserData.userName + "下线了";
		strcpy(quit_msg.chat , str.c_str());
		strcpy(quit_msg.m_UserName, m_UserData.userName);
		m_ClientSock.SendTo((char*)&quit_msg, sizeof(quit_msg), (SOCKADDR*)&(p_Peer->peerAddr), sizeof(SOCKADDR_IN), 0);
	}
}
void CP2P_ENDDlg::deleteUserMsg(string usernamef) {
	map<string, Message> userMsg;
	map<string, Message>::iterator it = userMsg.find(usernamef);
	while (it != userMsg.end()) {
		userMsg.erase(it);
	}
}
