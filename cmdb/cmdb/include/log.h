#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
#include <time.h>
#include <sys/timeb.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

namespace framework{
class MyLog{
	public:
	MyLog()
	{}

	virtual ~MyLog()
	{}

	bool TimeArrival();
	void WriteLog(const string& msg);
	string GetMessage(const char *pszFmt,va_list argp);
	void Log(const char *pszFmt,...);
	bool LogInit(string log_path);
	string FileName();

	private:
	string log_path_;  //log文件的路径
	string log_file_;  //log文件名
	time_t start_time_;
	int MAXLOGSIZE_ ; //最大日志条数
		
};

}

#endif
