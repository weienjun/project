#pragma once
#include<iostream>
//using namespace std;
#include<ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<deque>
#include<set>

namespace client{

class Window{
public:
	Window();

	~Window();

	//绘制标题子窗口
	void DrawHeader();

	//绘制输入窗口
	void DrawInput();

	//绘制输出窗口
	void DrawOutput();

	//绘制好友列表
	void DrawFriendList();

	//向窗口中写字符串
	void PutStrToWin(WINDOW* win,int y,int x,const std::string &str);

	//从窗口中读取字符串
	void GetstrFromWin(WINDOW* win,std::string* str);
	
	void AddMsg(const std::string& msg);
	 
	void AddrFriend(const std::string &friend_info);

	void DelFriend(const std::string &friend_info);

public:
	WINDOW* header_win_;
	WINDOW* input_win_;
	WINDOW* output_win_;
	WINDOW* friend_list_win_;
	std::deque<std::string> msgs_; //保存当前要显示的消息
	std::unordered_set<std::string> friend_list_; //好友列表
};

};	
