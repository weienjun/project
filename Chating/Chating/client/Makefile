.PHONY:all
all:test_win test_client 

chat_client:chat_client.cc window.cc chat_client_main.cc
	g++ $^ -o $@ -lpthread -ljsoncpp -lncursesw -std=c++11 #-lboost_filesystem -lboost_system

test_win:window.cc
	g++ $^ -o $@ -std=c++11 -lpthread -lncursesw -DTEST_WINDOW
test_client:chat_client.cc
	g++ $^ -o $@ -lpthread -ljsoncpp -DTEST_CHAT_CLIENT #-lboost_filesystem -lboost_system

.PHONY:clean
clean:
	rm test_client test_win 
