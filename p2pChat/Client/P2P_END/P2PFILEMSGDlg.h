#pragma once

#include "afxwin.h"
#include "P2P_ENDDlg.h"
#include "P2PBase.h"
#include "P2P_FILEDlg.h"

// CP2PFILEMSGDlg dialog
class CP2P_ENDDlg;
class CP2PFILEMSGDlg : public CDialog
{
	DECLARE_DYNAMIC(CP2PFILEMSGDlg)

public:
	CP2PFILEMSGDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CP2PFILEMSGDlg();

	char m_PeerNameMsgFile[20];  //���ڻظ����ڼ�������
	CP2P_ENDDlg *m_pParentMsgFile;  //����

	Message m_SaveMsgFile;  //�������/���͵�����
	FileMsg files;
	BOOL isActiveMsgFile;
	bool isSave = false;
	
	CP2P_FILEDlg *m_FileMsgDlg2 = NULL;  //�ļ���

	void SetMsgFileParentDlg(CP2P_ENDDlg*);

	void OnPeerMsgSend();
	void CreateP2PFileDlg();

// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Msg;
	afx_msg void OnBnClickedFileSave();
	afx_msg void OnBnClickedFileIgno();
	afx_msg void OnEnChangeFileMsg();
};
