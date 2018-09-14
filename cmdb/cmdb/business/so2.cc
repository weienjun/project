#include"read_conf.h"
#include<stdio.h>
#include<stdlib.h>
#include"conf_object_second.hpp"

class So2{
	public:
		So2()
		{}

		void  ReadConf(){ //读取文件实现
			RC::ReadConf rcf;
			rcf.ReadConfInit(so_conf_);

			object_conf_ = rcf.PutConfValue("others_conf"); //获取os配置文件中的其他配置文件路径
		}

		void Init(string path){
			so_conf_ = path;
		}

		BaseClass* CreateObject(){
			ConfObjectSecond* object = new ConfObjectSecond;
			if(object_conf_.size() > 0)
				object->GetData(object_conf_);  //从配置对象的配置文件中获取数据
			return object;
		}

	protected:
		string so_conf_;
		string object_conf_;
};

extern "C" BaseClass* create(string path){
	So2* o2 = new So2;
	o2->Init(path);
	o2->ReadConf();
	return  o2->CreateObject();
}

extern "C" void destroy(BaseClass* p){ //销毁父类对象
	delete p;
}

