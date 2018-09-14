/*************************************************************************
	> File Name: framework.h
	> Author: weienjun
	> Mail: weienjun@360.net
	> Created Time: Tue 07 Aug 2018 02:12:41 PM CST

	> 需要知道so文件一下内容：
	> 1、类名	
	> 2、动态加载函数接口（返回对象）	  
	> 3、so中配置文件路径入口
 ************************************************************************/
#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#include<iostream>
using namespace std;
#include<stdio.h>
#include<dlfcn.h>
#include<string.h>
#include<map>
#include<vector>
#include"base_class.hpp"
#include"find_file.h"

//#include"readconf.h"

namespace framework{

class FrameWork{
//	typedef os*(*Pointer)(string path); //函数指针

	public:
	FrameWork() //默认路径
	{}

	virtual ~FrameWork(){
 		DeleteSo();
	}

	bool FrameworkInit(string path,string log_file);
	void Print();
	
	void GetSoAndConf();
	void Dispose();
	bool _Dispose(string& filename,string& cf);
	void Do(BaseClass *o1,vector<string>& cf);
	map<string,string>& PutBusiness();
	map<string,BaseClass*>& PutSo();
	void DeleteSo();
	void _Delete(string &filename,string &cf);
	void DetUpdate();//检测配置文件的更新

	private:
//	Pointer func_;	//获取so对象接口
//	vector<BaseClass*> so_;//对象指针（返回的指针对象）
	map<string,BaseClass*> so_;
	string path_;	//业务路径
	string log_file_;   //日志路径
	map<string, string> business_;  //业务和配置文件
};
}

#endif
