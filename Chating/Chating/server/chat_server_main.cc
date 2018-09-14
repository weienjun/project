#include"chat_server.h"
#include"../common/util.hpp"

int main(int argc,char* argv[]){
	if(argc != 3){
	//	LOG("ERROR) << Usage: ./chat_server [i] [port]\n");
		return 1;
	}
	server::ChatServer server;
	server.Start(argv[1],atoi(argv[2]));
	return 0;
}
