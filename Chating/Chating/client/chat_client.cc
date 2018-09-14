#include"chat_client.h"
//#include"../server/api.hpp"

namespace client{
	//ip和port通过命令行参数来传递
	//如果使用从配置文件中读取ip和port，可采用json方式组织数据，并通过json解析
	int ChatClient::Init(const std::string &server_ip,short server_port){
		sock_ = socket(AF_INET,SOCK_DGRAM,0);
		if(sock_ < 0){
			
		}
		server_addr_.sin_family = AF_INET;
		server_addr_.sin_addr.s_addr = inet_addr(server_ip.c_str());
		server_addr_.sin_port = htons(server_port);
		return 0;
	}

	int ChatClient::SetUserInfo(const std::string &name,const std::string &school){
		name_ = name;
		school_ = school;
		return 0;
	}
	//向文件中打日志
	void Print(const std::string &log){
		FILE*  fp = fopen("./log.txt","a");
		fwrite(log.c_str(),log.size(),1,fp);
		fclose(fp);
	}

	void ChatClient::SendMsg(const std::string &msg){
		//按照下面这种方式来发送，是错误的
		//客户端和服务器交互接口要严格按照服务器提供的api进行操作
		//这样的约定相当于自定义了一种应用层的协议
		//sendto(sock_,msg.cstr(),msg.size(),0,(sockaddr*)&server_addr_,sizeof(server_addr_));
		//数据处理
		server::Data data;
		data.name = name_;
		data.school = school_;
		data.msg = msg;	
		if(data.msg == "quit" || data.msg == "exit" || data.msg == "Q"){
			data.cmd = "quit";
		}
		std::string str;
		data.Serialize(&str);

		//正真发送数据,发送的是一个json序列化的字符串，接收处str也是一个字符串形式接收
		sendto(sock_,str.c_str(),str.size(),0,(sockaddr*)&server_addr_,sizeof(server_addr_));
		return ;
	}
	void ChatClient::RecvMsg(server::Data* data){
		char buf[5*1024] = {0};
		ssize_t read_size = recvfrom(sock_,buf,sizeof(buf)-1,0,NULL,NULL);//由于对端的ip端口号就是服务器的端口号，之前已知（连接参数），不需要在获取
		if(read_size < 0){

		}
	  	buf[read_size] = '\0';
		//打客户端日志到文件中
		Print(buf);
        data->UnSerialize(buf);//字符串解析成数值
		return ;
	}
};


#ifdef TEST_CHAT_CLIENT
//简易版本客户端测试

void* Send(void* arg){
//	(void*)arg;
	//循环发送数据
	client::ChatClient* client = reinterpret_cast<client::ChatClient*>(arg);
	while(true){
		std::string str;
		std::cin>>str;
		client->SendMsg(str);
	}
	return NULL;
}

void* Recv(void* arg){
//	(void*)arg;
	//循环接收
	client::ChatClient* client = reinterpret_cast<client::ChatClient*> (arg);
	while(true){
		server::Data data;
		client->RecvMsg(&data);
		std::cout << "[" << data.name<< "|"<<data.school<<"]"<<data.msg<<"\n";
	}
	return NULL;
}

int main(int argc,char* argv[]){
	if(argc != 3){
		perror("error\n");
		return 1;
	}
	client::ChatClient client;
	client.Init(argv[1],atoi(argv[2]));
	
	std::cout<<"用户名";
	std::string name;
	std::cin>>name;
	std::string school;
	std::cout <<"输入学校";
	std::cin>>school;

	client.SetUserInfo(name,school);
	
	//消息的发送和接收各自使用一个线程，互不干扰
	//创建二个线程
	pthread_t stid,rtid;
	pthread_create(&stid,NULL,Send,&client);
	pthread_create(&rtid,NULL,Recv,&client);
	pthread_join(stid,NULL);
	pthread_join(rtid,NULL);
	return 0;
}

#endif
