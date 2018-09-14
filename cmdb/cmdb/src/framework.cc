
#include"framework.h"
#include<algorithm>
#include"log.h"

namespace framework{

	bool FrameWork::FrameworkInit(string path,string log_file){
		path_ = path;
		
		//初始化log目录
		RC::ReadConf rcf;
		if(rcf.ReadConfInit(path) == false)
			return false;
			  
		log_file_ = rcf.PutConfValue(log_file);

		return true; 
	}

	void FrameWork::Print(){
		cout << "对象数目："<< so_.size() << endl;
//		int i = 0;

		map<string,BaseClass*>::iterator so = so_.begin();
		while(so != so_.end()){
			so->second->PutInformation();
			so++;
		}

//		for(i = 0; i < (int)so_.size(); i++)
//			so_[i]->PutInformation();
	}

	void FrameWork::GetSoAndConf(){
		RC::ReadConf rcf;
		rcf.ReadConfInit(path_);		
		string so_path = rcf.PutConfValue("so_path");
		string conf_path = rcf.PutConfValue("conf_path");

		framework::MyLog L;
		L.LogInit(log_file_);

		FindFile find_file;
		
		if(find_file.FindFileInit(so_path,conf_path) == false){
			L.Log("so_path or conf_path error\n");
			return ;
		}
		
		find_file.GetFile(); //执行读取文件
		business_ = find_file.Put();//获取so及其配置文件
	}

	void FrameWork::Dispose(){
		GetSoAndConf();

		map<string, string>::iterator sof = business_.begin();

		while(sof != business_.end()){ //循环加载每个so
			string filename = sof->first; //此处不能直接传，需先转成string
			string conf = sof->second;
			
			//cout << "文件名："<<filename << endl;
			//cout << "配置文件名" << conf << endl;

			_Dispose(filename,conf);
			sof++;
		}  
	}

	//动态加载某个os
	bool FrameWork::_Dispose(string& filename,string& cf){
		framework::MyLog L;
		L.LogInit(log_file_);
		
		cout << "filename: " << filename << endl;
		//链接并打开动态库,使用全路径，编译可不用包含库路径
		void *handle = dlopen(filename.c_str(),RTLD_LAZY);

		if(handle == NULL){
			fprintf(stderr,"%s\n",dlerror());
			return false;	
		}else{
			//获取create函数（返回一个对象）
			//注：函数指针接收的参数要和返回类型一致
			Pointer create_func = (Pointer)dlsym(handle,"create"); //此处获取create地址，应为一个通用的接口
			char* szError = dlerror();
		
			if(szError != NULL){
			 	//printf("Error,Message(%s).\n",szError);
				L.Log("Error, Message(%s).\n",szError);
				dlclose(handle);
				return false; 
			}

			if(create_func != NULL){
				//cout << "配置文件个数：" << cf.size() << endl;
				BaseClass* oss = create_func(cf);
				
				MyLog L;
				L.LogInit(log_file_);

				L.Log("%s 添加配置文件%s\n",filename.c_str(),cf.c_str());//打印日志
				
			//	so_.push_back(oss);  //保存配置对象
				cout << "[filename] = " << filename << endl;
				so_[filename] = oss;
			}

		//	dlclose(handle);  //卸载动态库后，内存会被销毁，导致出现野指针问题
			
		}
		return true;
	}

//销毁
	void FrameWork::DeleteSo(){
		map<string, string>::iterator sof = business_.begin();

		while(sof != business_.end()){ //循环加载每个so
			string filename = sof->first; //此处不能直接传，需先转成string
			string conf = sof->second;
			
			//cout << "文件名："<<filename << endl;
		    //cout << "配置文件名" << conf << endl;

			_Delete(filename,conf);
			sof++;
		}  
	}

	void FrameWork::_Delete(string &filename,string &cf){
		framework::MyLog L;
		L.LogInit(log_file_);

		//链接并打开动态库
		void *handle = dlopen(filename.c_str(),RTLD_LAZY);

		if(handle == NULL){
			fprintf(stderr,"%s\n",dlerror());
			return ;	
		}else{
			//获取destory函数（销毁一个对象）
			//注：函数指针接收的参数要和返回类型一致
			Destroy* destroy_func = (Destroy*)dlsym(handle,"destroy");
			char* szError = dlerror();
	
			if(szError != NULL){
				L.Log("Error, Message(%s).\n",szError);
				dlclose(handle);
				return ; 
			}
			
			map<string,BaseClass*>::iterator bso = so_.begin();
			destroy_func(bso->second);  //删除对象指针
			so_.erase(bso->first);  //删除节点
			//destroy_func(so_[so_.size()-1]);
			//so_.pop_back();

	 }
 }
	map<string, string>& FrameWork::PutBusiness(){
		return business_;
	}

	map<string,BaseClass*>& FrameWork::PutSo(){
		return so_;
	}
	
}
