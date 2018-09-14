#pragma once 
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"../server/api.hpp"

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

namespace client{
class ChatClient{
public:
	//客户端初始化
	int Init(const std::string &_ip,short server_port);

	//设置用户信息
	int SetUserInfo(const std::string &name,const std::string &school);

	//发送消息
	void SendMsg(const std::string &msg);

	//接收消息
	void RecvMsg(server::Data* data);

private:
	int sock_;
	sockaddr_in server_addr_;
	std::string name_;
	std::string school_;
};
};
