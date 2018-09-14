#pragma once
#include<iostream>
using namespace std;
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unordered_map>
#include"block_queue.hpp"
#include<sys/types.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

namespace server{
struct Context{ //上下文类型
	std::string str; 
	sockaddr_in addr;
};
class ChatServer{
public:
	//启动服务器
	int Start(const std::string &ip,short port);
	//接收消息
	int RecvMSg();

	//广播消息
	int BroadCast();

private:
	static void* Consume(void*);//消费者线程
	static void* Product(void*);//生产者线程

	void AddUser(sockaddr_in addr,const std::string &name);
	void DelUser(sockaddr_in addr,const std::string &name);
	void SendMsg(const std::string& str,sockaddr_in addr);

	//key 内容，用户标识，ip+昵称
	//value ip+端口号（struct sockaddr_in）
	std::unordered_map<std::string,sockaddr_in> online_friend_list;
	//TOD此处使用一个阻塞队列作为生产者消费者模型的交易场所
	//暂定队列中元素类型是std::string
	BlockQueue<Context> queue_;
	int sock_; //服务器绑定的文件描述符
};
};
