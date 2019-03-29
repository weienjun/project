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
	ON_WM_TIMER()  //��ʱ�����ȼ�
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

//��ȡ·��
void CP2P_FILEDlg::OnBnClickedFileBp()  //���Ŀ¼/�ļ�
{
	// TODO: Add your control notification handler code here
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (SendOrRecv == 0) {
		MessageBox("����ѡ��ʽ����");
		return;
	}
	if (SendOrRecv == 2) {  //����
		char* bufname;
		CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "�����ļ� (*.*)|*.*||", this);//�����ļ� (*.*)|*.*||
		if (dlg.DoModal() == IDOK)
		{
			filePath = dlg.GetPathName();//��ȡ�ļ�·��	
			CString name = dlg.GetFileName();//��ȡ�ļ���
			strcpy(fileinfo.FileName,name);

			CFile file(filePath, CFile::modeRead);//���ļ�	
			fileinfo.FileSize = file.GetLength();//��ȡ�ļ���С	
			file.Close();//�ر��ļ�

			//���ļ����ݸ��µ��ؼ���
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
		bInfo.lpszTitle = _T("��ѡ��·��:   ");
		bInfo.ulFlags = BIF_RETURNONLYFSDIRS;

		LPITEMIDLIST lpDlist;
		//�������淵����Ϣ��IDList��ʹ��SHGetPathFromIDList����ת��Ϊ�ַ��� 
		lpDlist = SHBrowseForFolder(&bInfo);   //��ʾѡ��Ի��� 
		if (lpDlist != NULL)
		{
			SHGetPathFromIDList(lpDlist, tchPath);//����Ŀ��ʶ�б�ת����Ŀ¼ 
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
		m_pParent3->OnBnClickedFileIgno();  //�ر����ѶԻ���
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
	SendOrRecv = 2; //����
	GetDlgItem(IDC_CHOOSE_RECV)->EnableWindow(FALSE);
}

//�ַ�������
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

//��˽�Ľ������
void CP2P_FILEDlg::OnPeerChatMsgSend()
{
	POSITION pos = m_pParent2->m_pParent->m_P2PChatList.GetHeadPosition();  //����һ�������������ͱ��� pos ��ȡ�����ͷ��
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
	POSITION pos = m_pParent3->m_pParentMsgFile->m_P2PChatList.GetHeadPosition();  //����һ�������������ͱ��� pos ��ȡ�����ͷ��
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

//�ղ�������Ϣ����
void CP2P_FILEDlg::recvResponse() {
	//��ʼ������
	m_SaveMsg2.READ = true;
	m_SaveMsg2.isSave = false;
	m_SaveMsg2.sign = P2PCHATMSG;
	m_SaveMsg2.File.lose = false;

	string str;;
	if (Download == true) {
		str = " �ѽ����ļ�: " + (string)fileinfo.FileName;
		strcpy(m_SaveMsg2.chat, str.c_str());
	}
	else {
		str = " δ�����ļ�: " + (string)fileinfo.FileName;
		strcpy(m_SaveMsg2.chat, str.c_str());
	}
	Send();
}

DWORD WINAPI thread_heart_proc(LPVOID pointer)
{
	//�ȴ����շ�����Ϣ
	//KillTimer(2);				// ���ö�ʱ��ʱ��
	CP2P_FILEDlg *arg = (CP2P_FILEDlg*)pointer;
	arg->SetTimer(3,100000,NULL);
	while (arg->getData2()) {
		if (arg->m_SaveMsg2.READ == true && arg->m_SaveMsg2.isSave == true && arg->m_SaveMsg2.sign == FILEQEUST) {
			arg->KillTimer(3);  //�رշ��Ͷ�ʱ��
			string str = "���ڷ����ļ�: " + (string)arg->fileinfo.FileName;
			arg->m_FileMsg.SetWindowText(str.c_str());
			arg->m_FileMsg.LineScroll(arg->m_FileMsg.GetLineCount());
			arg->sendFileMsg();
			break;
		}
		//��ֹ����
		if (arg->m_SaveMsg2.isSave == false && arg->m_SaveMsg2.READ == true  && arg->m_SaveMsg2.sign == FILEQEUST) {
			arg->modifyState();
			arg->KillTimer(3);  //�رշ��Ͷ�ʱ��
			return 0;
		}
		//��ֹ����
		if (arg->fileSend == false) { //��ֹ���ͻ��ܵ���ֹ������Ϣ
			arg->OnBnClickedRemove(); //��ʼ����ֹ������Ϣ
			arg->KillTimer(3);  //�رն�ʱ��
			return 0; //�˳������߳� 
		}
	}
	return 0;
}

void CP2P_FILEDlg::OnBnClickedFileStart()
{
	// TODO: Add your control notification handler code here
	//�����ļ�
	GetDlgItem(IDC_REMOVE)->EnableWindow(true);
	if (SendOrRecv == 2) {
		string str = "׼�������ļ�: " + (string)fileinfo.FileName;
		m_FileMsg.SetWindowText(str.c_str());
		GetDlgItem(IDC_FILE_START)->EnableWindow(false);
		m_FileMsg.LineScroll(m_FileMsg.GetLineCount());
		sendFile();
	}
	//�����ļ�
	else if (SendOrRecv == 1) {
		if (fileinfo.FileSize == 0) {
			MessageBox("���ļ��ɽ��գ�");
			return;
		}
		string str = "���������ļ�: " + (string)fileinfo.FileName;
		m_FileMsg.SetWindowText(str.c_str());
		GetDlgItem(IDC_FILE_START)->EnableWindow(false);
		m_FileMsg.LineScroll(m_FileMsg.GetLineCount());
		recvFile();
	}
	else {
		MessageBox("��Ч������");
		return;
	}
}

void CP2P_FILEDlg::sendFile() {
	//�����ļ���Ϣ
	strcpy(m_SaveMsg2.File.FileName, fileinfo.FileName);
	m_SaveMsg2.File.FileSize = fileinfo.FileSize;

	m_SaveMsg2.READ = false;
	m_SaveMsg2.isSave = false;
	m_SaveMsg2.File.lose = false;
	m_SaveMsg2.sign = P2PCHATMSG;

	//���ݶ���ѡ���ͷ���,ͬʱ�޸ķ���״̬
	fileSend = true;
	Send();
	//���������ļ��߳�
	HANDLE h_getList = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_heart_proc, this, 0, NULL);  //�˴����ó�CHECK_RESP																								 //FileMsgSend();
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
	CFile file(arg->filePath, CFile::modeCreate | CFile::modeWrite);  //�ڶ��ε�����ջ����
	{
		while (arg->fileinfo.FileSize > len) {
			//��ȡ����
			if (arg->getData2() == false) {
				arg->m_FileMsg.SetWindowText("��ȡ����ʧ�ܣ�");
				file.Close();//�ر��ļ�
				return 0;
			}
			//��ֹ����
			if (arg->fileRecv == false) { //��ֹ���ͻ��ܵ���ֹ������Ϣ
				//arg->OnBnClickedRemove2(); //��ʼ����ֹ������Ϣ
				file.Close();//�ر��ļ�

				arg->m_SaveMsg2.READ = true;
				arg->m_SaveMsg2.isSave = false;
				arg->m_SaveMsg2.sign = FILEQEUST;
				arg->Send();

				return 0; //�˳������߳�
			}

			//���Ͷ���ֹ����
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
					//��������
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
				arg->KillTimer(4);  //�رն�ʱ��
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

	file.Close();//�ر��ļ�
	string strs = "�ļ��������: " + (string)arg->fileinfo.FileName;
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
	//��ֹ����
	if (getData2() && m_SaveMsg2.isSave == false && m_SaveMsg2.READ == false && m_SaveMsg2.sign == FILEQEUST) {
		modifyState();
		return ;
	}
	
	//������Ϣ
	m_SaveMsg2.READ = true;
	m_SaveMsg2.isSave = true;
	m_SaveMsg2.sign = FILEQEUST;
	m_SaveMsg2.File.lose = false;
	strcpy(m_SaveMsg2.File.FileName, fileinfo.FileName);
	//���ݶ���ѡ���ͷ���,ͬʱ�޸ķ���״̬
	fileRecv = true;
	Send();
	SetTimer(4, 3000, NULL);  //�����ļ�ACK�ط���ʱ��

	HANDLE h_getList = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_heart_saveFile, this, 0, NULL);  //�˴����ó�CHECK_RESP	
	Download = false;
}


void CP2P_FILEDlg::sendFileMsg() {
	USES_CONVERSION;
	CFile file;
	if (!file.Open(filePath, CFile::modeRead | CFile::typeBinary))
	{
		string str = "�ļ���ʧ��: " + (string)fileinfo.FileName;
		AfxMessageBox(_T(str.c_str()));
		return;
	}
	char buf[READSIZE] = { 0 };
	file.Seek(0, CFile::begin);
	long nLen = 0;//��ȡ����
	long long nSize = 0;//���ͳ���
	DWORD dwCount = 0;
	strcpy(m_SaveMsg2.File.FileName, fileinfo.FileName);

	m_SaveMsg2.File.count = 0;
	m_SaveMsg2.File.lose = false;
	long n = 0;
	CString fileSize;
	CString str;
	int dn = 0;
	while (fileinfo.FileSize > nSize || (getData2() && m_SaveMsg2.File.lose == true)) {  //�������һ��������
		//��ֹ����
		if (fileSend == false) { //��ֹ���ͻ��ܵ���ֹ������Ϣ
			file.Close();
			m_SaveMsg2.READ = false;
			m_SaveMsg2.isSave = false;
			m_SaveMsg2.sign = FILEQEUST;
			Send();
			return; //�˳������߳�
		}

		//���ն���ֹ����
		if (getData2() && m_SaveMsg2.READ == true && m_SaveMsg2.isSave == false && m_SaveMsg2.sign == FILEQEUST) {
			modifyState();
			file.Close();
			return;
		}

		if (m_SaveMsg2.File.lose == true) {
			//��������
			n = m_SaveMsg2.File.count;
			file.Seek((n*READSIZE), CFile::begin); //�޸��ļ�ָ��λ��,�Ӷ�ʧλ���ش�
			nSize = n*READSIZE;
			dn++;
			m_SaveMsg2.File.lose = false;  //ע��˴�Ҫ�޸ĸ�Դ���ݣ������޸���Ч
			if (m_pParent2 != NULL) {
				m_pParent2->m_pParent->userMsg[m_PeerName2+(string)fileinfo.FileName].File.lose = false;
			}
			else {//if (m_pParent3 != NULL) {  //��������
				m_pParent3->m_pParentMsgFile->userMsg[m_PeerName2+(string)fileinfo.FileName].File.lose = false;
			}
		}

		//�����ļ�
		memset(m_SaveMsg2.File.file, 0, sizeof(m_SaveMsg2.File.file));
		nLen = file.Read(m_SaveMsg2.File.file, READSIZE);
		if (nLen > READSIZE) {
			MessageBox(_T("��ȡ��������"));
		}
		nSize += nLen;


		//�������һ����������
		if (nSize > fileinfo.FileSize) {
			long long ptr = fileinfo.FileSize - (READSIZE - (nSize - fileinfo.FileSize));
			file.Seek(ptr, CFile::begin); //�޸��ļ�ָ��λ��,�Ӷ�ʧλ���ش�
			nSize = ptr;
			//n  = m_SaveMsg2.File.count;		//��������
			memset(m_SaveMsg2.File.file, 0, sizeof(m_SaveMsg2.File.file));
			nLen = file.Read(m_SaveMsg2.File.file, READSIZE);
			nSize += nLen;
			dn++;
		}
		
		m_SaveMsg2.READ = false;
		m_SaveMsg2.isSave = true;
		m_SaveMsg2.sign = FILEQEUST;
		m_SaveMsg2.File.count = ++n;  //���к�
		m_SaveMsg2.File.FileSize = nLen;
		Send();  //����

		//���ļ����ݸ��µ��ؼ���
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
	string strs = "�ļ��������: " + (string)fileinfo.FileName;
	m_FileMsg.SetWindowText(strs.c_str());
	m_FileMsg.LineScroll(m_FileMsg.GetLineCount());
	//�޸�״̬����ֹ�´η���ʱ��ȡ�����ϴη�����Ϣ
	InitState();
}

void CP2P_FILEDlg::OnTimer(UINT_PTR nIDEvent)  //��ʱ��������
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 3:
		KillTimer(3);
		MessageBox("�ȴ�ȷ�Ͻ��ճ�ʱ��");
		fileSend = false;
		break;
	case 4:  //��ʱ�ش�ȷ������
		{
			KillTimer(4);
			m_SaveMsg2.READ = true;
			m_SaveMsg2.isSave = true;
			m_SaveMsg2.File.lose = false;
			m_SaveMsg2.sign = FILEQEUST;
			//���ݶ���ѡ���ͷ���
			Send();
			SetTimer(4, 3000, NULL);  //��ʱ��
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
	else if (m_pParent3 != NULL) {  //��������
		OnPeerFileMsgSend();
	}
	else {
		AfxMessageBox("�û���ȡ�쳣");
		return;
	}
}


//��ֹ����
void CP2P_FILEDlg::OnBnClickedRemove()
{
	// TODO: Add your control notification handler code here
	string str; 
	if (SendOrRecv == 0) {
		return;
	}
	if (SendOrRecv == 1) {  //����
		fileRecv = false;
		SendOrRecv = 0;
		str = "����ֹ�����ļ�: " + (string)fileinfo.FileName;
		m_FileMsg.SetWindowText(str.c_str());
	}
	else if (SendOrRecv == 2) {  //����
		fileSend = false;
		str = "����ֹ�����ļ�: " + (string)fileinfo.FileName;
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
	if (SendOrRecv == 1) {  //����
		fileRecv = false;
		SendOrRecv = 0;
		str = "���Ͷ�����ֹ�����ļ���" + (string)fileinfo.FileName;
		m_FileMsg.SetWindowText(str.c_str());
		m_FileMsg.LineScroll(m_FileMsg.GetLineCount());
	}
	else if (SendOrRecv == 2) {  //����
		fileSend = false;
		str = "���ն�����ֹ�����ļ�: " + (string)fileinfo.FileName;
		m_FileMsg.SetWindowText(str.c_str());
		m_FileMsg.LineScroll(m_FileMsg.GetLineCount());
		GetDlgItem(IDC_FILE_START)->EnableWindow(true);
	}
	InitState();  //��ʼԭ״̬
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
	//�޸ĸ�Դ��״̬,��������Ϣ
	string userNamef = m_PeerName2 + (string)fileinfo.FileName;
	if (m_pParent2 != NULL) {
		m_pParent2->m_pParent->userMsg[userNamef].sign = P2PCHATMSG;
		m_pParent2->m_pParent->userMsg[userNamef].READ = true;
		m_pParent2->m_pParent->userMsg[userNamef].isSave = false;
		m_pParent2->m_pParent->deleteUserMsg(userNamef);
	}
	else {
		//ע�⣺���ڶ��̹߳��������ԭ�򣬱����޸ĵ�˳��ֱ�ӻ�Ӱ�������߳�ִ�У�����Ҫ����Ҫ�ı����������
		m_pParent3->m_pParentMsgFile->userMsg[userNamef].sign = P2PCHATMSG;  //Ҫ����ǰ�ߣ������Ӱ�������̵߳��ж�
		m_pParent3->m_pParentMsgFile->userMsg[userNamef].READ = true;
		m_pParent3->m_pParentMsgFile->userMsg[userNamef].isSave = false;
		m_pParent3->m_pParentMsgFile->deleteUserMsg(userNamef);
	}
}