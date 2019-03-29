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

//用于打洞过程
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

#ifndef FUN_H				//条件编译救我一命		结构体后头不要自定义变量 否则会重定义
#define FUN_H

class CP2PChatDlg;
class CP2PFILEMSGDlg;


enum FILEMSG{ NONE, SEND, RECV };

//自定义文件结构体
struct Fileinfo {
	long count = 0;			//数据包序列号
	bool lose = false;		//是否丢包
	char FileName[MAXLONG]; //文件名
	ULONGLONG FileSize = 0; //文件大小
	char file[MAXSIZE];		//文件内容
};

//文件信息
struct FileMsg {
	char FileName[MAXLONG];
	ULONGLONG FileSize;
};


//用户数据
typedef struct UserData
{
	int id;				//用户id
	char userName[20];	//用户名
	bool isAlive;		//用户私聊界面状态
	int servACK;		//保护器
	CString strIP;      //服务器的ip
	CString strPort;    //服务器port
	CString ServChat;   //服务器消息
	int idFlag ;		// 0表示普通用户，1表示临时服务器
	bool selFlag ;		//是否已经投票
};

//传递的数据包
typedef struct Message
{
	int sign;				//消息状态代码       1表示登陆  2表示发送消息，...
	int id;					//计数器
	int userNum;			//用户在线数量
	int servACK;			//服务器返回的状态码，-1表示客户端错误
	int peerACK;			//节点的状态码
	char chat[100];			//用户传递的消息
	char m_UserName[20];	//节点用户名（登录时本节点的用户名，通信时为目标节点用户名）
	char m_PSW[20];			//密码（用于服务器检测用户是否存在）
	char m_IDCard[20];		//用户手机号
	sockaddr_in userAddr;	//用户的网络数据：ip/port（保存获取的节点ip/port）
	char OLUserList[MAXUSERS][20];  //在线用户列表
	bool READ = true;				//标记文件消息是否读取
	bool isSave = false;			//保存
	struct Fileinfo File;			//文件数据
};

//服务器数据
typedef struct ServerData
{
	int userNum;				//在线人数
	bool state;					//服务器状态
	CString servLog;			//服务器消息
	sockaddr_in addrServ;		//服务器的地址信息
	SOCKET ClientSock;          //客户的连接请求
	SOCKET ServerSock;          //服务器的连接请求          
	UserData OLUserList[MAXUSERS];	//在线用户列表
};

//节点信息数据
typedef struct PeerData
{
	char peerName[20];		//节点名		
	bool state;				//节点状态
	BOOL isRead;			//节点消息是否已读
	CString peerMsgLog;				//节点消息
	sockaddr_in peerAddr;			//Peer的地址信息
	CP2PChatDlg *peerChatDlg;		//节点私聊对象
	CP2PFILEMSGDlg *peerMsgFileDlg; //节点文件信息对象
};

#endif