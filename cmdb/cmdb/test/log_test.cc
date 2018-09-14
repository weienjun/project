#include"log.h"	
#include"read_conf.h"


int main() {
	int i;
//	pthread_mutex_init(&cs_log,NULL);
	
	framework::MyLog L;
	string path = "/home/weienjun/wiki/practice2.1/conf/path.conf";
	string file_name = "log_path";

	RC::ReadConf rcf;
	rcf.ReadConfInit(path);
	string log_path = "/home/weienjun/wiki/practice2.1/data/mylog.log"; //rcf.PutConfValue(file_name);
	if(L.LogInit(log_path) == false)
		cout << "error" << endl;
	for (i=0;i<1000;i++) {
		L.Log("This is a Log %04d from FILE\n",i);
		sleep(1);
	}
	
//	L.Time();
//	pthread_mutex_destroy(&cs_log);
	return 0;
}

