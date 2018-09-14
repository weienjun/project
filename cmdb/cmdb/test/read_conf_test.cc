#include"read_conf.h"

int main(){
	string conf_path = "/home/weienjun/wiki/others/readconf/test.ini" ;
	RC::ReadConf rc;

	rc.ReadConfInit(conf_path);

	string msg;
	rc.IniData();
	rc.Print();	
		
	cout << "找r = " << rc.PutIniValue("[ip]","r") << endl;
	cout << "找c = " << rc.PutIniValue("[name]","c") << endl;
	////////////////////////////////////////////////////////////////////
	map<string, map<string, string> >ini_data_ = rc.PutIniData();
	string key1;
	
	map<string, map<string,string> >::iterator mm = ini_data_.begin();
	while(mm != ini_data_.end()){
		cout << mm->first << endl;

		map<string ,string> kv = mm->second;
		map<string,string>::iterator m = kv.begin();

		while(m != kv.end()){
			cout << m->first << " = ";
			cout << m->second << endl;
			m++;
		}
		mm++;
	}
	///////////////////////////////////////////////////////////////////////

	string conf_path_conf = "/home/weienjun/wiki/others/readconf/test.conf" ;
	RC::ReadConf rf;

	rf.ReadConfInit(conf_path_conf);

	rf.ConfData();
	rf.PrintConf();	

	cout << "找a = " << rf.PutConfValue("a") << endl;
	///////////////////////////////////////////////////////////////////////

	string conf_path_json = "/home/weienjun/wiki/others/readconf/test.json" ;
	RC::ReadConf rj;

	rj.ReadConfInit(conf_path_json);

	rj.JsonData();
	rj.PrintConf();	
	
	cout << "b : " << rj.PutJsonValue("b") << endl;

	return 0;
}
