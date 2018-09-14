#include<iostream>
using namespace std;
#include<map>
#include<string.h>
#include"base_class.hpp"
#include"read_conf.h"

//配置对象1，ini数据
//namespace so{
class ConfObjectFirst : public BaseClass{
	public:	
	ConfObjectFirst()
	{}

	virtual ~ConfObjectFirst()
	{}

	void PutInformation(){ //虚函数，形成多态
		cout << "***********ConfObjectFirst Data**********"<< endl;
		cout << "Map Size : " << data_.size() << endl;
	
		map<string, map<string,string> >::iterator nature = data_.begin();
	
		while(nature != data_.end()){
			string key = nature->first;
			cout << key << endl;

			map<string,string> map_value = nature->second;
			map<string,string>::iterator kv = map_value.begin();

			while(kv != map_value.end()){
				cout << kv->first << " : " << kv->second << endl;
				kv++;
			}
			nature++;
		}
	}

	void GetData(string path){ //虚函数
		RC::ReadConf read_ini_conf;
		
		read_ini_conf.ReadConfInit(path);
		data_ = read_ini_conf.IniData();
	}

	private:
	map<string, map<string,string> > data_;

};
//}

