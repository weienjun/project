#include"chat_client.h"
#include"window.h"
#include"../common/util.hpp"
#include<signal.h>

client::ChatClient* g_client = NULL;
client::Window* g_window = NULL;
pthread_mutex_t g_lock;

void* Send(void* arg){
	//发送线程：读取输入数据，发送给服务器
	(void)arg;
	while(1){
		std::string msg;
		pthread_mutex_lock(&g_lock);
		g_window->DrawInput();
		pthread_mutex_unlock(&g_lock);
		g_window->GetstrFromWin(g_window->input_win_,&msg);
		g_client->SendMsg(msg);
	}
	return NULL;
}

void* Recv(void* arg){
	//接收线程：从服务器中读取数据，显示
	(void)arg;
	while(1){
		//此处需绘制两个窗口，因为收到一条数据之后
		//output窗口需要更新，好友列表窗口也可能需要更新
		pthread_mutex_lock(&g_lock);
		g_window->DrawOutput();
		pthread_mutex_unlock(&g_lock);
		g_window->DrawFriendList();
		server::Data data;
		g_client->RecvMsg(&data);
		if(data.cmd == "quot"){
			//删除的方式和插入的方式需对应
			g_window->DelFriend(data.name+"|"+data.school);
		}else{
			//相当于好友列表显示的格式如下
			//xxx|xxx
			g_window->AddrFriend(data.name+"|"+data.school);
			g_window->AddMsg(data.name+":"+data.msg);
		}
	}
	return NULL;
}

void Quit(int sig){
	(void)sig;
	//此处delete主要目地执行析构函数，尤其是
	//g_windows 的析构函数，因为这个函数对 ncurses 进行了销毁动作
	//如果不执行，可能导致终端显示混乱
	g_client->SendMsg("Quit");	//推出前发送quit
	delete g_window;
	delete g_client;
	exit(0);
}

void Run(const std::string &ip,short port){
	//信号处理
	signal(SIGINT,Quit);
	pthread_mutex_init(&g_lock,NULL);
	//、初始客户端核心模块
	g_client = new client::ChatClient();
	int ret = g_client->Init(ip,port);
	if(ret < 0){
		LOG(ERROR) << "client Init failed\n" ;//此方法打印日志的方式是自己封装的，模仿来源 glog
		return ;
	}
	//2、提示用户输入用户名，学校
	std::string name,school;
	std::cout << "学校："<<std::endl;
	std::cin>>school;
	std::cout << "名字" <<std::endl;
	std::cin>>name;
	g_client->SetUserInfo(name,school);

	//3、初始化用户界面模块
	g_window = new client::Window();
	g_window->DrawHeader();

	//4、创建两个线程
	pthread_t stid,rtid;
	pthread_create(&stid,NULL,Send,NULL);
	pthread_create(&rtid,NULL,Recv,NULL);
	pthread_join(rtid,NULL);
	pthread_join(stid,NULL);
	//	发送线程：读取输入数据，发送给服务器
	//	接收线程：从服务器中读取数据，显示
	//5、对进程退出时进行处
//	delete g_window;
//	delete g_client;
	pthread_mutex_destroy(&g_lock);
}

int main(int argc ,char* argv[]){
	if(argc != 3){
		LOG(ERROR) << "Usage ./.chat_client [ip] [port]\n";
		return 1;
	}

	Run(argv[1],atoi(argv[2]));

	return 0;
}
