#include"find_file.h"

int main(){
	string path = "/home/weienjun/wiki/practice2.1/conf/path.conf";

	RC::ReadConf rcf;
	if(rcf.ReadConfInit(path) == false)
		return 0;

	string so_path = rcf.PutConfValue("so_path");
	string conf_path = rcf.PutConfValue("conf_path");

	framework::FindFile f;
	if(f.FindFileInit(so_path,conf_path) == false)
		return 0;

	f.GetFile();
	f.Print();
	f.Put();
	
	return 0;
}
