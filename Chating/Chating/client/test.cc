//单例模式

//恶汉模式单例
//在进程中有且只有一份
class Test{
private:
	int data;
	//xxxx
};
class Object{
private:
	static Object obj;
public:
	static Object* Instance(){
	return &obj;
	}
};

//懒汉模式
//在第一次使用时创建对象
class Singletion{
	private:
	class Object{
	private:
		int data;
		//xxx
	};
	volatile static Object* obj;//防止编译器优化

public:
	static Object* Instance(){
		lock()；
		if(obj == NULL){
			obj = new Object();
		}
		unlock();//使用锁进行线程安全。
		return obj;
	}
};

Object* Singletion::obj = NULL;
