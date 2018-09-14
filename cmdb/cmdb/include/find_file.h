/*************************************************************************
	> File Name: framework.h
	> Author: weienjun
	> Mail: weienjun@360.net
	> Created Time: Tue 07 Aug 2018 02:12:41 PM CST
 ************************************************************************/
#ifndef __FINDFILE_H__
#define __FINDFILE_H__

#include<iostream>
using namespace std;
#include<map>
#include<string.h>
#include<vector>
#include<dirent.h>
#include<stdio.h>
#include<dlfcn.h>
#include"read_conf.h"

namespace framework{

class FindFile{
	public:
	FindFile()
	{}
	virtual ~FindFile()
	{}

	bool FindFileInit(string so_path,string conf_path);
	string GetConfName(string name,vector<string>& file);
	void GetConfFile(string& filename,vector<string>& file);
	void GetSoFile(vector<string>& file);
	void Print();
	int GetFile();
	int _GetFile(string path,vector<string> &file);

	map<string, string >& Put(); //输出接口
	
	private:
	string so_path_;
	string conf_path_;
	map<string, string > so_;//一个os key=os名，value=配置文件
};
}

#endif
