#include"control.h"
#include<signal.h>
#include<fstream>
#include<sys/wait.h>
#include<sys/types.h>

//bool flag = true;
//string path_;  //配置文件路径
//string load_file_;  //加载日志文件
//map<string,string> data_;  //业务及配置文件路径

//退出
//void handler2(int asg){
//	flag = false;
//	cout << "flag: " << flag << endl;
//}

/*
//信号处理
void handler(int asg){
//重新加载
ControlLoad();
}
*/
namespace framework{
	bool Control::flag_ = true;

	void Control::handler2(int asg){
		flag_ = false;
	}

	void Control::ControlLoad(){
	//	framework::FrameWork f;

	//	f.FrameworkInit(path_,"load_log");
		fw_.Dispose();
		fw_.Print();
	//	data_ = f.PutBusiness(); 
	}

	bool Control::Init(string path){
		//初始化框架对象	
		if(fw_.FrameworkInit(path,"load_log") == false){
			printf("FrameworkInit error\n");
			return false;
		}
		
		//初始化加载日志目录
		RC::ReadConf rcf;
		rcf.ReadConfInit(path);
	
		load_file_ = rcf.PutConfValue("load_log");
		string timestamp_file = rcf.PutConfValue("timestamp_log");
		pid_file_ = rcf.PutConfValue("pid_file");

		if(load_file_.size() < 1){
			printf("load_log error\n");
			return false;
		}
		
		if(timestamp_file.size() < 1){
			printf("timestamp_file error\n");
			return false;
		}
	
		//初始化加载日志对象
		if(load_log_.LogInit(load_file_) == false){
			printf("load_log LogInit error\n");
			return false;
		}
		//初始化时间戳日志对象
		if(timestamp_log_.LogInit(timestamp_file) == false){
			load_log_.Log("timestamp_log LogInit error\n");
			return false;
		}
		//加载配置
		ControlLoad();
	
		//初始化文件时间
		TimeInit();
		return true;
	}

	string Control::GetCurrentTime(){
		time_t t = time(NULL);
		struct tm* c_t = localtime(&t);
		char buf[20];

		snprintf(buf,sizeof(buf),"%d-%d-%d %d:%d:%d",c_t->tm_year+1900, c_t->tm_mon, c_t->tm_mday, c_t->tm_hour,c_t->tm_min,c_t->tm_sec);

		return string(buf);
	}

	long long Control::GetTimestamp(){
		struct timeval tv;
		gettimeofday(&tv,NULL);

		return tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}

	time_t Control::CurFileTime(string filename){
		struct stat buf;
		if(stat(filename.c_str(),&buf) < 0){
			return 0;
		}
		time_t cur_file_time = buf.st_ctime;	
		return cur_file_time; 
	}

	void Control::Update(string so,string conf){
		fw_._Dispose(so,conf);
		fw_.Print();
	}

	void Control::CheckUpdate(){
		map<string,string> data = fw_.PutBusiness();

		map<string, string>::iterator bs = data.begin();

		int i = 0;
		while(bs != data.end()){
			string conf = bs->second;
			string so = bs->first;
			
			time_t cur_time = CurFileTime(conf);
			
			if(cur_time > last_time_[i]){
				//	kill(getpid(),SIGHUP);
				last_time_[i] = cur_time;
				fw_._Delete(so,conf);  //销毁对象	
				data.erase(bs++);   //从map中删除so节点,注此处必须bs++，否则迭代器失效
				Update(so,conf);
			}else{
				bs++;
			}
			i++;
		}
	}

	void Control::Delayed(int ms){
		struct timeval delay;
		delay.tv_sec = 0;
		delay.tv_usec = ms*1000; //ms

		select(0,NULL,NULL,NULL,&delay); 
	}

	void Control::BackControl(){
		while(flag_){
			CheckUpdate();
			sleep(1);
		}
	}

	//获取最初配置文件时间
	void Control::TimeInit(){
		map<string,string> data = fw_.PutBusiness();
		map<string, string>::iterator bs = data.begin();

		while(bs != data.end()){
			string conf = bs->second;
			last_time_.push_back(CurFileTime(conf));
	
			bs++;
		}
	}

	void Control::ChildFork(){
		signal(SIGTERM,handler2);  //子进程处理退出信号 
		while(flag_){
			timestamp_log_.Log(" %ld\n",GetTimestamp());  //写日志

			Delayed(50);
		}  
		load_log_.Log("close child pid : %d\n",getpid());
	}

	void Control::BackDesk(){

		//转后台
		framework::Singleton singleton;
		if(singleton.SingletonInit(pid_file_,load_file_) == false){
			load_log_.Log("AliveInit error\n");
			return;
		}

		singleton.KeepAlive();
		load_log_.Log("Turn the background success\n");

		pid_t pid = fork();
		if(pid < 0){
			load_log_.Log("fork error\n");
			exit(1);
		}

		//子进程--循环打印时间戳
		if(pid == 0){
			ChildFork();
			exit(0);
		}

		if(pid >  0){  //父进程
			//	signal(SIGHUP,handler);  //更新
			signal(SIGTERM,handler2);  //父进程处理退出信号 
			BackControl();  //父进程检测更新及重加载

			kill(pid,SIGTERM);  //给子进程发送退出信号

			wait(NULL);
			load_log_.Log("close father pid : %d\n",getpid());
		}
	}

	void Control::Quit(){
		ifstream ifs;
		string line;

		ifs.open(pid_file_.c_str());
		if(!ifs){
			load_log_.Log("open pid_file error\n");
			return ;
		}

		getline(ifs,line);
		ifs.close();

		int pid_num = atol(line.c_str());

		kill(pid_num,SIGTERM);  //给父进程发送退出信号
	}

	void Control::Start(char c){
		switch(c){
			case 'q':
				Quit();
				break;
			case 'd':
				BackDesk();
				break;

			default:
				printf("input error\n");
				break;
		}
	}
}
