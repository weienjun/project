#include"framework.h"
#include"log.h"
#include<fstream>

int main(){
	string path = "/home/weienjun/wiki/practice2.2/end/practice2.1/conf/path.conf";  //配置文件路径
	string log_file = "load_log";  //log key
	
	framework::FrameWork fw;

	if(fw.FrameworkInit(path,log_file) == false){
		printf("FrameworkInit error\n");
		return 0;
	}

	fw.Dispose();
	
	fw.Print();

//	map<string,string> data_ = fw.PutBusiness();

}

