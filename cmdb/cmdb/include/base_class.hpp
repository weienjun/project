#ifndef __BASECLASS_H__
#define __BASECLASS_H__

/***********************************************
 *父类文件：为纯虚函数，提供读取文件接口，子类实现具体方法
 *父类对外提供接口，供框架使用（框架接收类型），返回子类对象
 ***********************************************/


#include<iostream>
using namespace std;
#include<string.h>

class BaseClass{  //接口类中的所有方法，子类必须实现
	public:
	BaseClass()
	{}

	virtual ~BaseClass()
	{}

	virtual void PutInformation() = 0; //虚函数，形成多态

	virtual void GetData(string path) = 0; //虚函数

};

typedef BaseClass* (*Pointer)(string path); //基类接口

typedef void Destroy(BaseClass*); //销毁基类

#endif

