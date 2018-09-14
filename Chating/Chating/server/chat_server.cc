#include"chat_server.h"
#include"../common/util.hpp"
#include"api.hpp"
#include<pthread.h>

#include<sstream>
namespace server{
int ChatServer::Start(const std::string &ip,short port){
	//启动服务器，并进入循环
	//使用UDP作为通信协议
	int fd = socket(AF_INET,SOCK_DGRAM,0);
	if(fd < 0 ){

	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	addr.sin_port = htons(port);
	
	int ret = bind(sock_,(sockaddr*)&addr,sizeof(addr));
	if (ret < 0){

	}
//	printf("**********************\n");
//	LOG(INFO) << "Server Start OK!\n"; //保存日志

	//创建两个线程，一个用于读sock，一个用于从队列取数并广播
	pthread_t productor;
	pthread_t consumer;
	pthread_create(&productor,NULL,Product,this);
	pthread_create(&consumer,NULL,Consume,this);
	pthread_join(productor,NULL);
	//pthread_join(consumer,NULL);
	cout << ip << endl;
	return 0;
}
	void* ChatServer::Product(void* arg){
		//生产者线程，主要做的事情读sock中的数据，并且写入到BlockQueue
		ChatServer* server = reinterpret_cast<ChatServer*> (arg);
		while(true)
		//读取一次数据并写到BlockQueue
			server->RecvMSg();
		return NULL;
	}
	
	void* ChatServer::Consume(void* arg){
		ChatServer* server = reinterpret_cast<ChatServer*>(arg);
		while(true)
			server->BroadCast();
		return NULL;
	}

	int ChatServer::RecvMSg(){
		//1、丛socket 中读取数据
		char buf[1024] = {0};
		sockaddr_in perr;
		socklen_t len = sizeof(perr);
		ssize_t read_size = recvfrom(sock_,buf,sizeof(buf)-1,0,(sockaddr*)&perr,&len);	
		if(read_size < 0){

		}
		buf[read_size] = '\0';
  		printf("%s\n",buf);		
		//2、把数据插入到BlockQueue中
		Context context;
		context.addr = perr;
		context.str = buf;

		queue_.PushBack(context);
//		printf("***************************\n");
		return 0;
	}

	int ChatServer::BroadCast(){
		//1、从队列中读取一个元素
		Context context;
		queue_.PopFront(&context);
	
		//2、对取出的字符串进行反序列化
		Data data;
		data.UnSerialize(context.str);

		//3、根据消息更新在线的好友
		if(data.cmd == "quit"){
		//	如果这个成员当前是下线（command是一个特殊值）,从列表中删除
			DelUser(context.addr,data.name);
		}else{
		//	如果这个成员当前不在列表中，则加入
			AddUser(context.addr,data.name);
		}

		//4、办理遍历在线好友，把这个数据依次发生给每个客户端
		//	由于发送消息的用户也存在于好友列表中，因此遍历列表时也会给自己发送消息，
		//	从而达到发送者能够看到自己发送过的消息，
		//	但这种方法比较差，完全可以控制客户端，不经过网络传输就可以实现这个功能，此处按原来的方法写
		//
		
		for(auto item : online_friend_list){
			SendMsg(context.str,item.second);		
		}
//		printf("**********************************");
		return 0;
	}	
	
	void ChatServer::AddUser(sockaddr_in addr,const std::string &name){
		std::stringstream ss;
		ss << name <<":"<<addr.sin_addr.s_addr; //将name和地址拼接，处理ip重复问题
		//[]map unordered_map
		//1、如果不存在，就插入
		//2、如果不存在，就修改
		
		online_friend_list[ss.str()] = addr;
	}	
	
	void ChatServer::DelUser(sockaddr_in addr,const std::string &name){
		std::stringstream ss;
		ss << name <<":"<<addr.sin_addr.s_addr;
		online_friend_list.erase(ss.str());
	}
	
	void ChatServer::SendMsg(const std::string& str,sockaddr_in addr){
		//将此数据通过 sendto 发送给客户端
		sendto(sock_,str.data(),str.size(),0,(sockaddr*)&addr,sizeof(addr));
		//LOG(INFO) << "[Response]" <<inet_nota(addr.sin_addr)<<":"<<ntos(add.sin_port) << " "<<data<<"\n";
	}	
};
