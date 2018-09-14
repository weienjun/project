#include"singleton.h"

namespace framework{
	bool Singleton::SingletonInit(string pid_file,string log_file){
		pid_file_ = pid_file;
		log_file_ = log_file;

		return true;
	}

	//将父进程杀死，保留子进程，则pid文件记录的父进程pid 错误？？
	void Singleton::Daemonize(){
		framework::MyLog ctrl_log;
		ctrl_log.LogInit(log_file_);

		pid_t pid = fork();
		if(pid < 0){
			ctrl_log.Log("daemonize fork error\n");
			exit(1);
		}

		if(pid > 0){  //父进程退出
			exit(0);
		}

		//子进程
		pid = fork();  //再次创建子进程，确保无终端控制

		if(pid < 0){
			ctrl_log.Log("daemonize fork error\n");
			exit(1);
		}

		if(pid > 0){
			exit(0);
		}

		chdir("/");

		//从定向/关闭终端文件描述符操作
		int fd = open("dev/null",O_RDWR);
		if(fd < 0){
			ctrl_log.Log("open dev/null error\n");
		}else{
			dup2(fd,0);
			dup2(fd,1);
			dup2(fd,2);
		}

		for(fd = sysconf(_SC_OPEN_MAX); fd >= 3; --fd){
			close(fd);
		}

		umask(0);  //设置文件权限掩码为0 
	}
	
	bool Singleton::LockFile(int& fd,string &lock_file){
		framework::MyLog singleton_log;
		singleton_log.LogInit(log_file_);

		fd = open(lock_file.c_str(), O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		if (fd < 0) {
			singleton_log.Log("can't open %s\n", lock_file.c_str());
			return false;
		}

		if (flock(fd, LOCK_EX|LOCK_NB) < 0) {
			singleton_log.Log(" can't lock %s\n", lock_file.c_str());
			return false;
		}
		return true;	
	}


	bool Singleton::Exit(pid_t pid){
		int fd;

		framework::MyLog singleton_log;
		singleton_log.LogInit(log_file_);

		fd = open(pid_file_.c_str(), O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		if (fd < 0) {
			singleton_log.Log("can't open %s\n", pid_file_.c_str());
			return false;
		}
/*
		if (flock(fd, LOCK_EX|LOCK_NB) < 0) {
			singleton_log.Log(" can't lock %s\n", pid_file_.c_str());
			return false;
		}
*/		
		char strpid[30] = {0};
		snprintf(strpid,sizeof(strpid),"%d",pid);
		strpid[strlen(strpid)] = '\0';

		ftruncate(fd ,0);  //截断文件（此处相当于清空文件）
		write(fd,strpid,strlen(strpid));
	
		close(fd);		
		return true;
	}  

	bool Singleton::KeepAlive(){
		//转后台
		Daemonize();

		framework::MyLog singleton_log;
		singleton_log.LogInit(log_file_);

		string lock_file = "/tmp/lock_file.lock";	
		int fd;

		if(LockFile(fd,lock_file) == false){
			singleton_log.Log("thread is exist\n");
			exit(0);
		}
		
		singleton_log.Log("lock file success\n");

		pid_t pid = fork();
		if(pid < 0){
			singleton_log.Log("fork error\n");
			exit(0);
		}

		if(pid >0){
			if(Exit(pid) == false){
				printf("write pid error\n");
				kill(pid,SIGTERM);	
				wait(NULL);
				exit(0);
			}

			wait(NULL);  //等待子进程退出
			flock(fd,LOCK_UN);
			close(fd);
			unlink(lock_file.c_str());  //删除文件

			exit(0);
		}

		return true;
	}
}
