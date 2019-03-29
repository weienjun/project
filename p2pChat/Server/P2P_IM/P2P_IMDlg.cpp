// P2P_IMDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "P2P_IM.h"
#include "P2P_IMDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CP2P_IMDlg �Ի���
CP2P_IMDlg::CP2P_IMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CP2P_IMDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CP2P_IMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USERLIST, m_OLUserList);
	DDX_Control(pDX, IDC_STATIC_NUM, m_OLNum);
	DDX_Control(pDX, IDC_STATIC_STATE, m_State);
	DDX_Control(pDX, IDC_EDIT_LOG, m_ServerLog);
}

BEGIN_MESSAGE_MAP(CP2P_IMDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_START, &CP2P_IMDlg::OnStart)
	ON_BN_CLICKED(ID_STOP, &CP2P_IMDlg::OnStop)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CP2P_IMDlg ��Ϣ�������

BOOL CP2P_IMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_OLUserList.SetItemHeight(0,18);
	m_ServData.state = false; //���÷�����״̬
	m_ServData.userNum = 0;
	m_ServData.userID = 8888;
	m_ServData.servACK = 8888; //��¼�ڼ�����ѯ
	m_State.SetWindowText("�������ر�");
	m_OLNum.SetWindowText("��ǰ����������0");
	for (int i = 0;i<MAXUSERS;i++)		//�����½ʱ���б���ʾ������
	{
		m_ServBaseMsg.OLUserList[i][0] = '\0';  //��ʼ���ڵ��б�
	}
	
	refresh();			//���½�����Ϣ
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//����������
void CP2P_IMDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CP2P_IMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CP2P_IMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CP2P_IMDlg::refresh()	//ˢ�½���
{
	CString strNum;
	UpdateUserList(&m_ServBaseMsg);  //�����û��б�
	strNum.Format("��ǰ��������:%4d",m_ServData.userNum);
	m_OLNum.SetWindowText(strNum);
	m_ServerLog.SetWindowText(m_ServData.servLog);
	if (m_ServData.state)
	{
		m_State.SetWindowText("����������");
	} 
	else
	{
		m_State.SetWindowText("�������ر�");
	}
	m_ServerLog.LineScroll(m_ServerLog.GetLineCount());  //�Զ����������һ��
}
//����
void CP2P_IMDlg::OnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_ServData.state)
	{
		MessageBox(_T("�������Ѿ���!"));
	}
		//���÷����������˿�1000��Э������ΪSOCK_DGRAM��UDP��
		m_ServSock.Create(1000,SOCK_DGRAM); //SOCK_STREAM��TCP��//��һ�������������׽��ֵĺöಽ��
		m_ServSock.SetDlg(this);
		m_ServData.state = true;
		m_ServData.servLog +="�������ɹ�����\r\n";	//�س��ӻ���
		refresh();							//���½�����Ϣ
		MessageBox(_T("�����������ɹ�"));
		GetDlgItem(ID_START)->EnableWindow(FALSE);
		GetDlgItem(ID_STOP)->EnableWindow(TRUE);
		SetTimer(1,30000,NULL);				//ͨ����ʱ�����ͻ����Ƿ����
		SetTimer(2,10000,NULL);				//������ڿͻ���
	
}

//��������
void CP2P_IMDlg::ReceiveData(CServSock *sock)
{
	Msg buffer;  //���շ����������ݱ���
	CString str;
	sockaddr_in addrBuffer; //
	UserData *userBuffer;	//ͨ�Žڵ�(�û�)��Ϣ
	userBuffer =new UserData();	//	�����Ҫ������������ͷ
	int len = sizeof(SOCKADDR_IN);
	POSITION pos = m_SockUserList.GetHeadPosition();
	//���յ����ݱ�����buffer�У�ͨ�Žڵ�ĵ�ַ��Ϣ������userBuffer->userAddr��
	sock->ReceiveFrom((char*)&buffer,sizeof(buffer),(SOCKADDR*)&(userBuffer->userAddr),&len,0);	//���û��壬��������
	if (abs(buffer.id)>m_ServData.userID)  //��������ID���ϵ����� �൱��ȫ��ʱ�䣬ʱ�䲻ͬ����֪ͨ�ͻ����˳�
	{
		buffer.sign = EXITMSG; 
		buffer.servACK = 0;
		sock->SendTo((char*)&buffer, sizeof(buffer),(SOCKADDR*)&(userBuffer->userAddr),len,0);
	}
	UpdateUserList(&buffer); //����BUFFER�е������б�
	switch (buffer.sign)
	{
	case LOGINMSG: 	//��һ�ε�½��Ϣ
		if (!ADOCheckUser(&buffer,buffer.sign))  //У���õ�name,�����Ƿ�ƥ��
		{
			buffer.servACK = -1; //�û������������
			strcpy(m_ServBaseMsg.m_UserName, buffer.m_UserName);
			sock->SendTo((char*)&buffer, sizeof(buffer),(SOCKADDR*)&(userBuffer->userAddr),len,0);
			return;
		}
		//���������ID,��ֹй¶
		memset(buffer.m_PSW, 0, sizeof(buffer.m_PSW));
		memset(buffer.m_IDCard, 0, sizeof(buffer.m_IDCard));

		strcpy(userBuffer->userName,buffer.m_UserName);	//���û������浽�׽��ֶ�����
		userBuffer->userState = true ;
		m_ServData.userID++;  //��ʱ��+1
		userBuffer->id = m_ServData.userID;
		userBuffer->servACK = m_ServData.servACK+2;
		m_SockUserList.AddTail(userBuffer);				//���û���Ϣ��ӵ�������û��б��У�	
		m_ServData.userNum++;  //m_ServData����ͬbuffer�����ڷ�������
		m_ServBaseMsg.sign=LOGINMSG;
		m_ServBaseMsg.userNum = m_ServData.userNum;
		m_ServBaseMsg.servACK=m_ServData.servACK;	//	������ȷ�ϵ�½
		m_ServBaseMsg.id = m_ServData.userID;
		strcpy(m_ServBaseMsg.m_UserName, buffer.m_UserName);
		//sock->m_id++;		//����ID  ����ѡ���㷨
		UpdateUserList(&m_ServBaseMsg);					//	֮ǰ����ʱ���ͳ���buffer�͸��µ�buffer��һ�� ���µ���ʱ���õ��б�׼ȷ
		sock->SendTo((char*)&m_ServBaseMsg, sizeof(m_ServBaseMsg),(SOCKADDR*)&(userBuffer->userAddr),len,0);
		
		//////����֪ͨ���������û�/////
		UpdateUserList(&buffer);
		strcpy(buffer.m_UserName,"������֪ͨ��");
		buffer.sign = PEERLOGINMSG;
		//str.Format("%s����\r\n", userBuffer->userName);//��ʾ������Ϣ

		while(pos!=NULL)
		{
			UserData* p_User=(UserData*)m_SockUserList.GetNext(pos);
			if(p_User->userState)
			{
				sock->SendTo((char*)&buffer, sizeof(buffer),(SOCKADDR*)&(p_User->userAddr),sizeof(SOCKADDR),0);
			}
		}
		///////
		str.Format("%s����\r\n", userBuffer->userName);//��ʾ������Ϣ
		m_ServData.servLog+=str;
		m_ServerLog.SetWindowText(str);
		m_ServerLog.LineScroll(m_ServerLog.GetLineCount());	
		break;

	case MULCHATMSG: //Ⱥ����Ϣ
		while(pos!=NULL)  //��ѯת��
		{
			UserData* p_User=(UserData*)m_SockUserList.GetNext(pos);
			if(p_User->userState)
			{
				sock->SendTo((char*)&buffer, sizeof(buffer),(SOCKADDR*)&(p_User->userAddr),sizeof(SOCKADDR),0);
			}
		}
		break;
	case EXITMSG:
		Stop(buffer.id);  //�߿ͻ�������
		break;
	case ISALIVEMSG:  //������Ϣ
		pos = m_SockUserList.GetHeadPosition();
		while(pos!=NULL)
		{
			UserData* p_User=(UserData*)m_SockUserList.GetNext(pos);
			if(p_User->id == buffer.id)  //ID��ȣ�˵��ʱ��ͬ�����ͻ�������
			{
				p_User->isAlive = true ;
				p_User->servACK = buffer.servACK+1;   //����servACK��ʼֵ����û����
			}
		}
		break;
	case P2PHOLETO:  //������
		addrBuffer = userBuffer->userAddr;		//����P2P���ĵ�ַ����
		userBuffer = FindClientByName("��������");	//�ҵ���Ҫ���͵Ŀͻ���
		if(!userBuffer)
		{
			return;
		}
		buffer.userAddr = userBuffer->userAddr;  //���ҵ����û���Ϣ���ͻ�ȥ
		sock->SendTo((char*)&buffer, sizeof(buffer),(SOCKADDR*)&(addrBuffer),len,0);
		break;

	//�ڵ�����������������
	case CONNECT_RES:  //�˴�Ӧ��Ѱ��������ڵ��name
		{
			addrBuffer = userBuffer->userAddr;		//��ȡͨ�Žڵ��ַ
			userBuffer = FindClientByName(buffer.m_UserName);	//�ҵ���Ҫ���͵Ŀͻ��˽ڵ�����
			if (!userBuffer)  //δ�ҵ��ýڵ�
			{
				//�˴���ñ���һ����־�򷵻ش�����Ϣ
				return;
			}
			//������֪ͨ������ڵ�������ڵ㷢�����ݰ�
			buffer.sign = CONNECT1;  
			buffer.userAddr = addrBuffer;  //������ڵ�ĵ�ַ����������ڵ�
			sock->SendTo((char*)&buffer, sizeof(buffer), (SOCKADDR*)&(userBuffer->userAddr), len, 0); 
		}
		break;

	//�������ظ�������ڵ㣬�����ر�����ڵ�ĵ�ַ
	case CONNECT_QUEST:
		{
		//������������ڵ�ظ���ַ��Ϣ
			sockaddr_in Qpeer = buffer.userAddr;  //����ڵ�ĵ�ַ
			buffer.userAddr = userBuffer->userAddr; //������ڵ�ĵ�ַ
			buffer.sign = CONNECT2;
			sock->SendTo((char*)&buffer, sizeof(buffer), (SOCKADDR*)&(Qpeer), len, 0);
		}
		break;

	case REGMSG:  //ע��
		if (!ADOCheckUser(&buffer,buffer.sign))
		{
			buffer.servACK = -1; //ע�����
			sock->SendTo((char*)&buffer, sizeof(buffer),(SOCKADDR*)&(userBuffer->userAddr),len,0);
			return;
		}
		else
		{
			CString sql;
			sql.Format("INSERT INTO Users ([UserName],[PassWord],[IDNumber]) VALUES(\"%s\",\"%s\",\"%s\")",buffer.m_UserName,buffer.m_PSW,buffer.m_IDCard);
			if(0 != AdoAccess.Open("test.mdb","","",""))
			{
				MessageBox((LPCTSTR)AdoAccess.GetLastErrCode().c_str());
				
			}
			if (!AdoAccess.Exectue((string)sql)==0)
			{
				//MessageBox((LPCTSTR)AdoAccess.GetLastErrCode().c_str());
				//::AfxMessageBox(_T("�������ʧ��!"));
			}
			buffer.servACK = 0;  //��ʾע��ɹ�
			sock->SendTo((char*)&buffer, sizeof(buffer),(SOCKADDR*)&(userBuffer->userAddr),len,0);
			return;
		}
		break;
	case FORGETMSG:  //�һ�����
		if (!ADOCheckUser(&buffer,buffer.sign))
		{
			buffer.servACK = -1; //�һ�����ʧ��
			sock->SendTo((char*)&buffer, sizeof(buffer),(SOCKADDR*)&(userBuffer->userAddr),len,0);
			return;
		}
		else
		{
			buffer.servACK = 0;
			sock->SendTo((char*)&buffer, sizeof(buffer),(SOCKADDR*)&(userBuffer->userAddr),len,0);
			return;
		}
		break;
	default:;
	};
	
//	send(*sock,data,sizeof(data),0);//��������б�//
	refresh();  //ˢ���б�
}

void CP2P_IMDlg::Stop(int id)		//	���¿ͻ���
{
	CString st;
	POSITION pos = m_SockUserList.GetHeadPosition();
	POSITION posBuffer = NULL;
	Msg buffer;
	buffer.sign = EXITMSG;
	buffer.servACK = 0;
	while (pos!=NULL)
	{
		posBuffer = pos;
		UserData* p_User=(UserData*)m_SockUserList.GetNext(pos);
		if(p_User->id==id)
		{
			st.Format("%s����\r\n",p_User->userName);	
			m_ServData.servLog+=st;
			m_ServData.userNum--;
			m_ServerLog.SetWindowText(m_ServData.servLog);
			m_ServSock.SendTo((char*)&buffer, sizeof(buffer),(SOCKADDR*)&(p_User->userAddr),sizeof(SOCKADDR),0);
			delete p_User;
			m_SockUserList.RemoveAt(posBuffer);
		}
	}
	m_ServerLog.LineScroll(m_ServerLog.GetLineCount());
	//delete sock;
	this->refresh();
}

void CP2P_IMDlg::OnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBox("ȷ��Ҫ�رշ�����?","ϵͳ",MB_YESNO)==IDYES)
	{
		
		POSITION pos = m_SockUserList.GetHeadPosition();
		while(pos!=NULL)
		{
			UserData* p_User=(UserData*)m_SockUserList.GetNext(pos);
			Stop(p_User->id);
		}
		//m_SockUserList.RemoveAll();
		m_ServData.state=FALSE;
		this->refresh();
		m_ServData.servLog += "�������ɹ��ر�\r\n";
		m_ServerLog.SetWindowText(m_ServData.servLog);
		m_ServSock.Close();
		MessageBox("����رշ���");
		GetDlgItem(ID_START)->EnableWindow(TRUE);
		GetDlgItem(ID_STOP)->EnableWindow(FALSE);
	}
}

void CP2P_IMDlg::UpdateUserList(Msg *buffer)
{
	POSITION pos=m_SockUserList.GetHeadPosition();
	//UserData *p_Data;
	m_OLUserList.ResetContent();
	//POSITION posBuffer = NULL;
	buffer->userNum = m_ServData.userNum;
	for(int i=0 ; pos!=NULL ; i++ )
	{
		UserData* p_User=(UserData*)m_SockUserList.GetNext(pos);
		if (p_User->id>1000)
		{
			strcpy(buffer->OLUserList[i],p_User->userName);
			m_OLUserList.AddString(p_User->userName);//���������û��б�
		}
	}
}

UserData* CP2P_IMDlg::FindClientByName(char *userName)
{
	POSITION pos = m_SockUserList.GetHeadPosition();
	while(pos!=NULL)
	{
		UserData* p_User=(UserData*)m_SockUserList.GetNext(pos);
		if(!strcmp(p_User->userName,userName))
		{
			return p_User;
		}
	}
	return NULL;
}
BOOL CP2P_IMDlg::ADOCheckUser(Message *p_Userbuffer,int sign)
{
	vector<ST_TABLE> list;
	int fieldsize=0;
	CString userName ;
	CString password ;
	CString IDNumber ;
	CString bff ;  
	//CString password = p_Userbuffer->
	userName.Format("UserName = '%s'",p_Userbuffer->m_UserName);
	password = p_Userbuffer->m_PSW;
	IDNumber = p_Userbuffer->m_IDCard;
	CString sql=_T("select * from Users where "+userName);
	if(0 != AdoAccess.Open("test.mdb","","",""))
	{
		MessageBox((LPCTSTR)AdoAccess.GetLastErrCode().c_str());
		return FALSE;
	}

	if(0!=AdoAccess.Exectue((string)sql, list))
	{
		MessageBox((LPCTSTR)AdoAccess.GetLastErrCode().c_str());
	}
	fieldsize = list[0].value.size();
	if (sign==REGMSG)		//	ע����Ϣ��֤
	{
		if(fieldsize==0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	if(fieldsize<1)		//��¼��Ϣ��֤
	{
		return FALSE;
		
	}
	else
	{
		if (sign==LOGINMSG)
		{
			bff = list[1].value[0].c_str();
			if (bff==password)
			{
			//	password.ReleaseBuffer();
				return TRUE;
			}
			//password.ReleaseBuffer();
		}
		if (sign==FORGETMSG)
		{
			password = list[1].value[0].c_str();//��ȡ����
			bff = list[2].value[0].c_str();	//��ȡ�����Ϣ
			if (bff==IDNumber)
			{
				//	password.ReleaseBuffer();
				strcpy(p_Userbuffer->m_PSW,password.GetBuffer());
				password.ReleaseBuffer();
				return TRUE;
			}
			//password.ReleaseBuffer();
		}
		
	}
	return FALSE;
}

void CP2P_IMDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	POSITION pos = m_SockUserList.GetHeadPosition();
	POSITION posBuffer = NULL;
	Msg buffer;
	buffer.sign = ISALIVEMSG;
	buffer.servACK = m_ServData.servACK;	//	ACK��ֵ������

	switch(nIDEvent)
	{
	case 1:
			while(pos!=NULL)		//������ѯ��Ϣ
			{
				UserData* p_User = (UserData*)m_SockUserList.GetNext(pos);
				//if(p_User->userState)
				//{	
					p_User->servACK = m_ServData.servACK;
					UpdateUserList(&buffer);
					m_ServSock.SendTo((char*)&buffer, sizeof(buffer),(SOCKADDR*)&(p_User->userAddr),sizeof(SOCKADDR),0);
				//}
			}
			m_ServData.servACK++;
		break;
	case 2:			
			pos=m_SockUserList.GetHeadPosition();
			while(pos!=NULL)		//������ߵĿͻ���
			{	
				posBuffer = pos;
				UserData* p_User=(UserData*)m_SockUserList.GetNext(pos);
				if (p_User->servACK < m_ServData.servACK)
				{
					Stop(p_User->id);
				}
			}
		break;

	}
	
	refresh();
	CDialog::OnTimer(nIDEvent);
}
