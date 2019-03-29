#define MAXUSERS 100
#define LOGINMSG 1
#define MULCHATMSG 2
#define P2PCHATMSG 3
#define P2PHOLETO 4
#define ISALIVEMSG 5
#define PEERLOGINMSG 6
#define REGMSG 7
#define FORGETMSG 8
#define EXITMSG 0
#define QUIT 20

#define FILEQEUST 100

//���ڴ򶴹���
#define CONNECT_RES 9
#define CONNECT1 10
#define CONNECT_QUEST 11
#define CONNECT2 12
#define CONNECT_ACK1 13
#define CONNECT_ACK2 14
#define CONNECT_START 15
#define CONNECT_OK 16

#define MAXSIZE 10240
#define MAXLONG 100

#ifndef FUN_H				//�����������һ��		�ṹ���ͷ��Ҫ�Զ������ ������ض���
#define FUN_H

class CP2PChatDlg;
class CP2PFILEMSGDlg;


enum FILEMSG{ NONE, SEND, RECV };

//�Զ����ļ��ṹ��
struct Fileinfo {
	long count = 0;			//���ݰ����к�
	bool lose = false;		//�Ƿ񶪰�
	char FileName[MAXLONG]; //�ļ���
	ULONGLONG FileSize = 0; //�ļ���С
	char file[MAXSIZE];		//�ļ�����
};

//�ļ���Ϣ
struct FileMsg {
	char FileName[MAXLONG];
	ULONGLONG FileSize;
};


//�û�����
typedef struct UserData
{
	int id;				//�û�id
	char userName[20];	//�û���
	bool isAlive;		//�û�˽�Ľ���״̬
	int servACK;		//������
	CString strIP;      //��������ip
	CString strPort;    //������port
	CString ServChat;   //��������Ϣ
	int idFlag ;		// 0��ʾ��ͨ�û���1��ʾ��ʱ������
	bool selFlag ;		//�Ƿ��Ѿ�ͶƱ
};

//���ݵ����ݰ�
typedef struct Message
{
	int sign;				//��Ϣ״̬����       1��ʾ��½  2��ʾ������Ϣ��...
	int id;					//������
	int userNum;			//�û���������
	int servACK;			//���������ص�״̬�룬-1��ʾ�ͻ��˴���
	int peerACK;			//�ڵ��״̬��
	char chat[100];			//�û����ݵ���Ϣ
	char m_UserName[20];	//�ڵ��û�������¼ʱ���ڵ���û�����ͨ��ʱΪĿ��ڵ��û�����
	char m_PSW[20];			//���루���ڷ���������û��Ƿ���ڣ�
	char m_IDCard[20];		//�û��ֻ���
	sockaddr_in userAddr;	//�û����������ݣ�ip/port�������ȡ�Ľڵ�ip/port��
	char OLUserList[MAXUSERS][20];  //�����û��б�
	bool READ = true;				//����ļ���Ϣ�Ƿ��ȡ
	bool isSave = false;			//����
	struct Fileinfo File;			//�ļ�����
};

//����������
typedef struct ServerData
{
	int userNum;				//��������
	bool state;					//������״̬
	CString servLog;			//��������Ϣ
	sockaddr_in addrServ;		//�������ĵ�ַ��Ϣ
	SOCKET ClientSock;          //�ͻ�����������
	SOCKET ServerSock;          //����������������          
	UserData OLUserList[MAXUSERS];	//�����û��б�
};

//�ڵ���Ϣ����
typedef struct PeerData
{
	char peerName[20];		//�ڵ���		
	bool state;				//�ڵ�״̬
	BOOL isRead;			//�ڵ���Ϣ�Ƿ��Ѷ�
	CString peerMsgLog;				//�ڵ���Ϣ
	sockaddr_in peerAddr;			//Peer�ĵ�ַ��Ϣ
	CP2PChatDlg *peerChatDlg;		//�ڵ�˽�Ķ���
	CP2PFILEMSGDlg *peerMsgFileDlg; //�ڵ��ļ���Ϣ����
};

#endif