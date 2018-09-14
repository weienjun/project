#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/file.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<iostream>
#include"log.h"


#include<iostream>
using namespace std;

namespace framework{
class Singleton{
	public:
	Singleton()
	{}
	virtual ~Singleton()
	{}
	
	bool SingletonInit(string pid_file,string log_file);
	bool Exit(pid_t pid);
	bool LockFile(int &fd,string &lock_file);
	void Daemonize();
	bool KeepAlive();

	private:
	string pid_file_;
	string log_file_;
};

}

#endif 
