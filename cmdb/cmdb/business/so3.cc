#include"read_conf.h"
#include<stdio.h>
#include<stdlib.h>
#include"conf_object_three.hpp"

class So3{
	public:
		So3()
		{}
		
		virtual ~So3()
		{}

		void Init(string path){
			so_conf_ = path;
		}

		void  ReadConf(){ //读取文件实现
			RC::ReadConf rcf;
			rcf.ReadConfInit(so_conf_);

			object_conf_ = rcf.PutConfValue("others_conf"); //获取os配置文件中的其他配置文件路径
		}

		BaseClass* CreateObject(){  //生成配置对象
			ConfObjectThree* object = new ConfObjectThree;
			if(object_conf_.size() > 0)
				object->GetData(object_conf_);  //从配置对象的配置文件中获取数据
			return object;
		}

	protected:
		string so_conf_;
		string object_conf_;
};

extern "C" BaseClass* create(string path){
	So3* o3 = new So3;
	o3->Init(path);
	o3->ReadConf();
	return  o3->CreateObject();
}

extern "C" void destroy(BaseClass* p){ //销毁父类对象
	delete p;
}

