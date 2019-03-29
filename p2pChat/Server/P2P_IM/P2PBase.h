#define MAXUSERS 100  //最多用户数
#define LOGINMSG 1    //登录
#define MULCHATMSG 2  //多人聊天
#define P2PCHATMSG 3  //点对点聊天
#define P2PHOLETO 4  
#define ISALIVEMSG 5  //心跳信息
#define PEERLOGINMSG 6  
#define REGMSG 7      //注册信息
#define FORGETMSG 8   //忘记密码
#define EXITMSG 0     //退出信息

//用于打洞过程
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
	//struct UserData *FNode;  //取消好友机制
	int idFlag ;   // 0表示普通用户，1表示临时服务器
	bool selFlag ;   //是否已经投票

}User,UserData;

//通信数据结构
typedef struct Message   
{
	int sign;				//消息代码       1表示登陆  2表示发送消息
	int id;
	int userNum;
	int servACK;
	int peerACK;
	char chat[100];			//用户传递的消息
	char m_UserName[20];
	char m_PSW[20];
	char m_IDCard[20];
	sockaddr_in userAddr;
	char OLUserList[MAXUSERS][20];
}Msg;

//服务器数据
typedef struct ServerData
{
	int userNum;				//用户个数
	bool state;					//服务器状态
	CString servLog;			//服务器显示的信息
	int userID;					//用户id
	int servACK;		        //用于校验用户是否在线的计数器	
	sockaddr_in addrServ;		//服务器的地址信息
	//SOCKET ClientSock;        //客户的连接请求
	//SOCKET ServerSock;                 
	User OLUserList[MAXUSERS];	//在线用户列表，丢到容器里的版本
}ServerData;