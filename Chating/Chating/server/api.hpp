#pragma once
#include<string.h>
#include<iostream>
#include<jsoncpp/json/json.h>

namespace server{
//服务器给客户端的API
struct Data{
	std::string name;
	std::string school;
	std::string msg;
	std::string cmd;

	//序列化----字符串--->数值
	void Serialize(std::string* output){
		//方法1：自己解析
		//char buf[1024] = {0};
		//sprintf(buf,"{name:%s,school:%s,msg:%s,cmd:%s}",name.c_str(),school.c_str(),msg.c_str(),cmd.c_str());
		//*output = buf;	
		
		//可以把Json::value 近似理解成一个 unordered_map
		//方法2：第三方库json
		Json::Value value;
		value["name"] = name;
		value["school"] = school;
		value["msg"] = msg;
		value["cmd"] = cmd;
		Json::FastWriter write;
		*output = write.write(value);
		return ;		
	}

	//反序列化---数值--->字符串
	void UnSerialize(const std::string &input){
		Json::Value value; //保存结果
		Json::Reader reader; //反序列化
		reader.parse(input,value);
		if(value["name"].isString()){ //判断类型是否正确可转，此处简写一个
			name = value["name"].asString();
			school = value["school"].asString();
			msg = value["msg"].asString();
			cmd = value["cmd"].asString();
			return ;
		} 
	}
};
};
