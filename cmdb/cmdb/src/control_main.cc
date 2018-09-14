#include"control.h"

int main(int argc, char* argv[]){
	string path = "/home/weienjun/wiki/practice2/conf/path.conf";  //配置文件路径
	framework::Control fc;
	fc.Init(path);
	 
	 if(argc != 2){
		 printf("Startup error [./test -d/q]\n");	
		 return 0;
	 }

	fc.Start(argv[1][1]);

	return 0;
}

