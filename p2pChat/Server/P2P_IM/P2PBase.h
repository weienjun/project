#define MAXUSERS 100  //����û���
#define LOGINMSG 1    //��¼
#define MULCHATMSG 2  //��������
#define P2PCHATMSG 3  //��Ե�����
#define P2PHOLETO 4  
#define ISALIVEMSG 5  //������Ϣ
#define PEERLOGINMSG 6  
#define REGMSG 7      //ע����Ϣ
#define FORGETMSG 8   //��������
#define EXITMSG 0     //�˳���Ϣ

//���ڴ򶴹���
#define CONNECT_RES 9
#define CONNECT1 10
#define CONNECT_QUEST 11
#define CONNECT2 12




typedef struct UserData
{
	int id;  
	char userName[20];
	bool isAlive;
	int servACK;
	sockaddr_in userAddr;
	bool userState ;
	//UINT userPort;
	//struct UserData *FNode;  //ȡ�����ѻ���
	int idFlag ;   // 0��ʾ��ͨ�û���1��ʾ��ʱ������
	bool selFlag ;   //�Ƿ��Ѿ�ͶƱ

}User,UserData;

//ͨ�����ݽṹ
typedef struct Message   
{
	int sign;				//��Ϣ����       1��ʾ��½  2��ʾ������Ϣ
	int id;
	int userNum;
	int servACK;
	int peerACK;
	char chat[100];			//�û����ݵ���Ϣ
	char m_UserName[20];
	char m_PSW[20];
	char m_IDCard[20];
	sockaddr_in userAddr;
	char OLUserList[MAXUSERS][20];
}Msg;

//����������
typedef struct ServerData
{
	int userNum;				//�û�����
	bool state;					//������״̬
	CString servLog;			//��������ʾ����Ϣ
	int userID;					//�û�id
	int servACK;		        //����У���û��Ƿ����ߵļ�����	
	sockaddr_in addrServ;		//�������ĵ�ַ��Ϣ
	//SOCKET ClientSock;        //�ͻ�����������
	//SOCKET ServerSock;                 
	User OLUserList[MAXUSERS];	//�����û��б�����������İ汾
}ServerData;