#pragma once
#include "P2PBase.h"

#define TRUE 1
#define READSIZE 10240
#define MAXTIME 1000

// CP2P_FILEDlg dialog
class CP2PChatDlg;  //ǰ������
class CP2PFILEMSGDlg;
class CP2P_FILEDlg : public CDialog
{
	DECLARE_DYNAMIC(CP2P_FILEDlg)

public:
	CString filePath;  //�ļ�·��
	CString fileName;  //�ļ���
	CString fileSize;  //�ļ���С
	Fileinfo fileinfo; //�ļ�����

	BOOL isActive;              //�����Ƿ��
	int SendOrRecv = 0;			//�ļ�����������0--Ĭ�ϣ�1--���գ�2--����
	BOOL Download = false;		//�����Ƿ�����
	char m_PeerName2[20];		//ͨ���û���
	Message m_SaveMsg2;			//�������ݣ�����/�������ݰ���
	sockaddr_in sendToPeer;		//Ŀ�Ľڵ�ĵ�ַ
	CP2PChatDlg *m_pParent2 = NULL;     //˽�Ľ���
	CP2PFILEMSGDlg *m_pParent3 = NULL;  //�ļ���Ϣ����
	//CClientSock* Esock3;
	bool fileView = false;  //�ļ��Ի����Ƿ��
	bool fileSend = false;  //�ļ�����
	bool fileRecv = false;  //�ļ�����

	//bool getData();
	bool RequestMsg();
	//void FileRecv();
	void recvResponse();
	void OnPeerChatMsgSend();
	void OnPeerFileMsgSend();

	void sendFile();
	void recvFile();
	void sendFileMsg();
	void Send();
	void getFileState();
	void modifyState();
	void OnBnClickedRemove2();
	void InitState();
	bool getData2();

	CP2P_FILEDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CP2P_FILEDlg();

	void AddRecvMsg2(CString *p_MsgLog, char *userName, CString *chat);

	void SetParentDlg2(CP2PChatDlg* p_Parent);
	void SetParentDlg3(CP2PFILEMSGDlg* p_Parent);


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_FileSize;  //�ļ���С�ؼ�
	CEdit m_FileMsg;   //��Ϣ�ؼ�
	CEdit m_FilePath;  //·���ؼ�

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeFilePath();
	afx_msg void OnBnClickedFileBp();
	afx_msg void OnStnClickedFileSize();
	afx_msg void OnEnChangeFeditSize();
	afx_msg void OnStnClickedFileBit();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedFileClose();
	afx_msg void OnEnChangeFileMsg();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedFileSend();
	afx_msg void OnBnClickedFileOk();
	afx_msg void OnBnClickedChooseRecv();
	afx_msg void OnBnClickedChooseSend();
	afx_msg void OnBnClickedFileStart();
	afx_msg void OnBnClickedRemove();
};
