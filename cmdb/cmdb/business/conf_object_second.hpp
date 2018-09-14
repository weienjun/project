#include<iostream>
using namespace std;
#include<map>
#include<string.h>
#include"base_class.hpp"
#include"read_conf.h"

//配置对象1，conf数据
//namespace so{
class ConfObjectSecond : public BaseClass{
	public:	
		ConfObjectSecond()
		{}

		virtual ~ConfObjectSecond()
		{}

		void PutInformation(){ //虚函数，形成多态
			cout << "***********ConfObjectSecond Data**********"<< endl;
			cout << "Map Size : " << data_.size() << endl;

			map<string,string>::iterator kv = data_.begin();

			while(kv != data_.end()){
				cout << kv->first << " : " << kv->second << endl;
				kv++;
			}
		}

		void GetData(string path){  //虚函数
			RC::ReadConf read_ini_conf;

			read_ini_conf.ReadConfInit(path);
			data_ = read_ini_conf.ConfData();
		}

	private:
		map<string,string> data_;

};
//}

