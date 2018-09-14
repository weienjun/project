#ifndef __READCONF_H__
#define __READCONF_H__

//配置文件解析工具
//将配置文件内容统一处理为 key--value格式
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<map>
#include<string.h>

using namespace std;

namespace RC{
//enum Type{INI,CONF,JSON,XML,};
class ReadConf{
	public:
	ReadConf()
	{}

	~ReadConf()
	{}

	bool ReadConfInit(const string &conf_path);	  //初始化
	void Analysis(map<string,string> &kv,string &str,char c);  //解析一行的 key---value
	string HandleComment(string msg,char c);  //处理注释和空行
	
	void Print();  //输出ini的所有数据
	map<string, map<string, string> >& PutIniData();  //返回ini数据
	bool GetIniData(string& Out,char c,FILE* ifs);  //获取ini文件中的内容
	map<string, map<string, string> >&  IniData();   //解析Ini文件数据

	map<string, string>&  ConfData();
//	bool SelectParsedWay(string& Out);  //解析方式	
	bool GetConfData(string Out);
	void PrintConf();

	bool GetJsonData(string Out);
	void AnalysisJson(map<string,string> &kv,string str);	
	map<string, string>& JsonData();	

	string PutIniValue(string key,string key2);
	string PutConfValue(string key);
	string PutJsonValue(string key);
	
	private:
	string file_ ;   //配置文件路径
	//string file_type_;
	map<string, map<string, string> > ini_data_;  //保存ini格式数据
	map<string, string> data_;  //conf/json 格式数据
	//key--parament  value--section
	//map<string,Type> all_type_;
};
}

#endif
