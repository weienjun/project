chat_server:chat_server.cc chat_server_main.cc
	g++ $^ -o $@ -std=c++11 -lpthread -ljsoncpp #-lboost_filesystem -lboost_system

.PHONY:clean
clean:
	rm -f chat_server
