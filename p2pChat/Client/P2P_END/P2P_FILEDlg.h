#pragma once
#include "P2PBase.h"

#define TRUE 1
#define READSIZE 10240
#define MAXTIME 1000

// CP2P_FILEDlg dialog
class CP2PChatDlg;  //前置声明
class CP2PFILEMSGDlg;
class CP2P_FILEDlg : public CDialog
{
	DECLARE_DYNAMIC(CP2P_FILEDlg)

public:
	CString filePath;  //文件路径
	CString fileName;  //文件名
	CString fileSize;  //文件大小
	Fileinfo fileinfo; //文件变量

	BOOL isActive;              //界面是否打开
	int SendOrRecv = 0;			//文件操作方法：0--默认，1--接收，2--发送
	BOOL Download = false;		//反馈是否下载
	char m_PeerName2[20];		//通信用户名
	Message m_SaveMsg2;			//保存数据（发送/接收数据包）
	sockaddr_in sendToPeer;		//目的节点的地址
	CP2PChatDlg *m_pParent2 = NULL;     //私聊界面
	CP2PFILEMSGDlg *m_pParent3 = NULL;  //文件消息界面
	//CClientSock* Esock3;
	bool fileView = false;  //文件对话框是否打开
	bool fileSend = false;  //文件发送
	bool fileRecv = false;  //文件接收

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
	CEdit m_FileSize;  //文件大小控件
	CEdit m_FileMsg;   //消息控件
	CEdit m_FilePath;  //路径控件

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
