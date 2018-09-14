#include"log.h"

namespace framework{
	string MyLog::FileName(){
		struct tm *now;
		struct timeb tb;

		ftime(&tb);
		now=localtime(&tb.time);

		char add[200] = {0};  //文件名添加时间
		snprintf(add,sizeof(add),"%02d%02d%02d%02d%02d",now->tm_year+1900,now->tm_mon+1,now->tm_mday,now->tm_hour,now->tm_min);
			
		string log_file = log_path_  + "_" + add;
		cout << "log_file" << log_file << endl;
		
		return log_file;
	}

	//在配置文件中，寻找日志文件名
	bool MyLog::LogInit(string log_path){

		log_path_ = log_path;
		log_file_ = log_path;//FileName();

		if(log_file_.size() < 1){
			printf("log_file_ error\n");
			return false;
		}

		MAXLOGSIZE_ = 10240000; //日志文件大小
		time(&start_time_);

		return true;
	}

	bool MyLog::TimeArrival(){
		time_t end_time;
		double subtime = 0.0;
		time(&end_time);

		subtime = difftime(end_time,start_time_);

		if(subtime == 3600.0){  //每1小时翻转一次,注时间至少要大于60s
			start_time_ = end_time;
			return true;
		}
		return false;
	}

	string  MyLog::GetMessage(const char *pszFmt, va_list argp){
		string msg;
		char str[1024] = {0};
		if(NULL == pszFmt || 0 == pszFmt[0]) 
			return msg;

		//将可变参数列表中的参数全放到logstr中，并在末尾+'/0'
		vsnprintf(str,MAXLOGSIZE_,pszFmt,argp); 
		msg = str;
		return msg;
	}

	void MyLog::WriteLog(const string &msg) {
		char mss[4];
		char timestr[100];
		char datestr[100];

		struct tm *now;
		struct timeb tb;

		ftime(&tb);
		now=localtime(&tb.time);

		snprintf(datestr,sizeof(datestr),"%04d-%02d-%02d",now->tm_year+1900,now->tm_mon+1,now->tm_mday);
		snprintf(timestr,sizeof(timestr),"%02d:%02d:%02d",now->tm_hour     ,now->tm_min  ,now->tm_sec );
		snprintf(mss,sizeof(mss),"%03d",tb.millitm); 
		
		FILE *flog=fopen(log_file_.c_str(),"a+");

		if(flog == NULL){
			printf("fopen error!\n");
			return ;
		}
		fseek(flog,0,SEEK_END);
		//打印日志	
		//printf("%s %s.%s : %s\n",datestr,timestr,mss,msg.c_str());
			
		fprintf(flog,"%s %s.%s %s",datestr,timestr,mss,msg.c_str());	
		
		if (ftell(flog)>MAXLOGSIZE_ || TimeArrival()) { //route处理
			//cout << ftell(flog) << endl;
			fclose(flog);
/*		
			string new_file = log_file_ + "1";
			if(rename(log_file_.c_str(), new_file.c_str())){
				remove(new_file.c_str());
				rename(log_file_.c_str(),new_file.c_str());
			}
*/			
			
		 // 创建新的文件保存日志	
			string new_file  = FileName() + ".log";
			if(!access(new_file.c_str(),F_OK)){
				printf("create log file error\n");
				return ;
			}

			string tmp_file = "/home/weienjun/wiki/practice2.1/data/tme.log";  //中间文件 
			rename(log_file_.c_str(),tmp_file.c_str()); 
			rename(new_file.c_str(),log_file_.c_str());
			rename(tmp_file.c_str(),new_file.c_str());
		
		}else{
			fclose(flog);
		}
	}

	//va_list va_start va_end 用于解析可变参数 
	void MyLog::Log(const char *pszFmt,...){
		pthread_mutex_t cs_log;
		va_list argp;

		pthread_mutex_init(&cs_log,NULL);
		pthread_mutex_lock(&cs_log);

		va_start(argp,pszFmt);
		string msg = GetMessage(pszFmt,argp);
		WriteLog(msg);
		va_end(argp);

		pthread_mutex_unlock(&cs_log);
		pthread_mutex_destroy(&cs_log);
	}
}
