#include"singleton.h"
#include"read_conf.h"

int main(){
	string path = "/home/weienjun/wiki/practice2.1/conf/path.conf";
	framework::Singleton back_alive;
	RC::ReadConf rcf;
	rcf.ReadConfInit(path);
	
	string pid_file = rcf.PutConfValue("pid_file");
	string log_file = rcf.PutConfValue("log_file");

	if(back_alive.SingletonInit(pid_file,log_file) == false){
		printf("AliveInit error\n");
		return 0;
	}
	
	back_alive.KeepAlive();
	
	while(1){
		cout << "************" << endl;
		sleep(1);
	}

	return 0;
}
