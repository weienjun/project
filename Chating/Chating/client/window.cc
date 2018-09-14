#include"window.h"
#include<locale.h>
#include"../common/util.hpp"
#include<iostream>
//using namespace std;
namespace client{
	Window::Window(){
		//支持中文编码 //编译加 库
		setlocale(LC_ALL,"");

		//对整个cursers初始化
		initscr();

		//隐藏光标
		curs_set(0);
	}

	Window::~Window(){
		//对整个ncursers进行销毁，不消毁会导致终端出错
		endwin();	
	}

	//绘制子窗口
	void Window::DrawHeader(){
		//最大窗口设置
		int h = LINES/5; //获取窗口最大行数（宏）
		int w = COLS; //获取最大列数（ncurses 提供的宏，动态大小）
		//窗口起始位置设置
		int y = 0;
		int x = 0;
		header_win_ = newwin(h,w,y,x);
		std::string title = "我的聊天室";
		PutStrToWin(header_win_,h/2,w/2-title.size()/2,title);
		box(header_win_,'|','-'); //设置边框
		wrefresh(header_win_);//刷新缓冲区显示

	}
	
	void Window::PutStrToWin(WINDOW* win,int y,int x,const std::string &str){
		//显示字符串
		mvwaddstr(win,y,x,str.c_str());
	}

	void Window::GetstrFromWin(WINDOW* win,std::string* str){
		char buf[1024*10] = {0};
		wgetnstr(win,buf,sizeof(buf)-1);
		*str = buf; //深拷贝（编译器优化的化是写诗时拷贝）
	}
	//输入窗口设置，注此时坐标系变为该窗口的坐标系，不是原窗口
	void Window::DrawInput(){	
		//输入窗口设置
		int h = LINES/5; //获取窗口最大行数（宏）
		int w = COLS; //获取最大列数（ncurses 提供的宏，动态大小）
		//窗口起始位置设置
		int y = LINES*4/5;
		int x = 0;  
		input_win_ = newwin(h,w,y,x);
		std::string title = "输入消息";
		//此处从1，1填充提示符，因为边框占了一个
		PutStrToWin(input_win_,1,2,title);
		box(input_win_,'|','-'); //设置边框
		wrefresh(input_win_);//刷新缓冲区显示
	}

	void Window::DrawOutput(){
		int h = LINES*3/5;
		int w = COLS*3/4;
		int y = LINES/5;
		int x = 0;
		output_win_ = newwin(h,w,y,x);
		box(output_win_,'|','-');
		int i = 0;
		//循环输出消息，思考如何处理一行显示不下的消息如何处理？
		for(i = 0; i < (int)msgs_.size(); i++)
			PutStrToWin(output_win_,i+1,2,msgs_[1]);
		wrefresh(output_win_);

	}

	void Window::AddMsg(const std::string &msg){
		//由于窗口显示的消息数目有限，不能无止境的插入新的消息
		//当 msg发送的消息超过一定阀值时，就把就消息删除
		msgs_.push_back(msg);
		int max_line = LINES *3/5-2;
		if(max_line < 3){ //行高不满足，退出
//			LOG(ERROR) << "max_line toot small\n";
			exit(0);
		}
		if((int)msgs_.size() > max_line){
			msgs_.pop_front();
		}
	}

	void Window::DrawFriendList(){
		int h = LINES*3/5;
		int w = COLS/4;
		int y = LINES/5;
		int x = COLS*3/4;
		friend_list_win_ = newwin(h,w,y,x); 
		box(friend_list_win_,'|','-');
		int i = 0;
		for(auto item : friend_list_){
			PutStrToWin(friend_list_win_,i+1,1,item);
			i++;
		}
		wrefresh(friend_list_win_);
		}

	void Window::AddrFriend(const std::string &friend_info){
		friend_list_.insert(friend_info);
	}

	void Window::DelFriend(const std::string &friend_info){
		friend_list_.erase(friend_info);
	}

};

#ifdef TEST_WINDOW

int main(){
	client::Window win;

	win.DrawHeader();
	win.DrawInput();
	win.DrawOutput();
	sleep(5);
	return 0;
}

#endif
