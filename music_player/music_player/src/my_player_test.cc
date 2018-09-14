#include"my_player.h"
#include<iostream>
using namespace std;
#include<string.h>

bool FindFile(string file,string sfile){
	ifstream ifs;
	ifs.open(file.c_str());
	if(ifs == NULL){
		printf("open error\n");
		return false;
	}
	
	string str;
	while(getline(ifs,str)){
		if(str == sfile){
			ifs.close();
			return true;
		}
	}

	ifs.close();
	return false;
}

bool FindMusic(Music::MyPlayer* mp,string music){ //查看某音乐是否在播放器中
	vector<string> v;
	mp->MusicFilePut(v);

	vector<string>::iterator mv = v.begin();
	while(mv != v.end()){
		if(*mv == music){
			return true;
		}
		mv++;
	}
	return false;
}

//清空文件
bool CleanFile(string file){
	ofstream ifs;
	ifs.open(file.c_str());
	if(ifs == NULL){
		printf("CleanFile open error\n");
		return false;
	}

	ifs.flush();
	ifs.close();
	return true;
}

void MusicInit_test(){
	//无文件测试是否正确
	Music::MyPlayer mp;
	//先清空原有内容	
	string musicfile = mp.FileNamePut();
	if(CleanFile(musicfile) == false){
		return ;
	}

	mp.Init();

	ifstream ifs;
	
	ifs.open(mp.FileNamePut().c_str());
	if(!ifs){
		printf("open1 error!\n");
		return ;
	}
	string line;
	getline(ifs,line);
	
	if(ifs != NULL){
		printf("file should NULL but is not NULL is: %s\n",line.c_str());
		ifs.close();
		return ;
	}

	ifs.clear();
	ifs.close();

	//调用插入文件，后重新加载，看能否保留上次记录
	string file = "../music/m2.st2"; //插入已存在的文件
	mp.MusicInsert(file);
	mp.Init(); //重新加载
	
	ifs.open(mp.FileNamePut().c_str());
	if(ifs == NULL){
		printf("open2 error!\n");
		return ;
	}
	getline(ifs,line);
	
	if(ifs == NULL){
		printf("MusicInit error musicfile should not NULL ,but is NULL\n");
		return ;
		if(line != file)
		printf("MusicInit error file should: %s ,but is: %s\n",file.c_str(),line.c_str());
		ifs.close();
		return ;
	}

	ifs.close();

	printf("MusicInit OK\n");
}

void MusicInsert_test(){
	Music::MyPlayer mp;

	//清空原文件
	string musicfile = mp.FileNamePut();
	if(CleanFile(musicfile) == false){
		return ;
	}

	mp.Init(); //先初始化
	
	string add = "../music/"; //路径
	string name = "m1.st1";
	string filename = add + name;
	//注：文件首行 m.st1 m1 mm
	cout << filename << endl;
	mp.MusicInsert(filename);
	
	//判断插入到目录是否成功
	if(!FindFile(mp.FileNamePut(),filename)){
		printf("MusicInsert musicfile failed !\n");
		return ;
	}else{  //判断插入到播放器中是否成功
		if(mp.MusicPut(filename)->_name != name){
			printf("MusicInsert name error should is `m1.st1` but is: %s\n",mp.MusicPut(filename)->_name.c_str() );
			return ;
		}
		if(mp.MusicPut(filename)->_singer != "m1"){
			printf("MusicInsert singer error,should is `m1` but is: %s\n",mp.MusicPut(filename)->_singer.c_str());
			return ;
		}
		if(mp.MusicPut(filename)->_album != "mm"){
			printf("MusicInsert album error,should is `mm` but is: %s\n",mp.MusicPut(filename)->_album.c_str());
			return ;
		}

		struct stat info;
		stat(filename.c_str(),&info);
		int size = (int)info.st_size;
		
		if(size != (int)mp.MusicPut(filename)->_size){
			printf("MusicInsert size error , should is %d buf is: %d\n",size,(int)mp.MusicPut(filename)->_size);
			return ;
		}

	}

	printf("MusicInsert OK\n");
}

void MusicErase_test(){
	//文件不为空删除成功返回true
	Music::MyPlayer mp;
	//获取存储文件，并清空
	string file = mp.FileNamePut();
	if(CleanFile(file) == false){
		return;
	}
	
	string delfile = mp.DelFilePut();
	if(CleanFile(delfile) == false){
		return;
	}

	mp.Init();
	string file1 = "../music/m1.st1";
	string file2 = "../music/m2.st2";

	mp.MusicInsert(file1);
	mp.MusicInsert(file2);

	bool b = mp.MusicErase(file1);
	string musicfile = mp.FileNamePut();
	
	//判断返回值
	if(b == false)
	{
		printf("MusicErase `file1` error, return value should `true` but is `false`\n");
		return ;
	}
	//判断内容
	if(FindFile(musicfile,file1)){
		printf("MusicErase `file1` error\n");
		return;
	}
	if(FindFile(musicfile,file2) == false){
		printf("MusicErase `file1` but `file2` Delete\n");
		return;
	}
	//判断是否从播放器中删除	
	if(FindMusic(&mp,file1) == true){
		printf("MusicErase `file1` error, `file1` should not in _music_file\n");
		return;
	}
	//判断是否放到回收站文件中
	if(FindFile(delfile,file1) == false){
		printf("MusicErase `dile1` error, %s not found %s\n",delfile.c_str(),file1.c_str());
		return ;
	}

	string nfile = "../music/m.st1"; //删除不存在的文件
	b = mp.MusicErase(nfile);
	if(b == true){
		printf("MusicErase `nfile` error return value should `false` but is `false` \n");
		return ;
	}

	b = mp.MusicErase(file2);
	if(b == false){
		printf("MusicErase `file2` error, return value should `true` but is `false`\n");
		return ;
	}

	if(FindFile(musicfile ,file2) == true){
		printf("MusicErase `file2` error\n");
		return ;
	}

	if(FindMusic(&mp,file2) == true){
		printf("MusicErase `file2` error, `file2` should not in _music_file\n");
		return;
	}

	//判断是否放到回收站文件中
	if(FindFile(delfile,file2) == false){
		printf("MusicErase `file2` error, %s not found %s\n",delfile.c_str(),file2.c_str());
		return ;
	}

	printf("MusicErase OK\n");
}

void MusicModifier_test(){
	Music::MyPlayer mp;
	//清空原文件
	string musicfile = mp.FileNamePut();
	if(CleanFile(musicfile) == false){
		return ;
	}

	//文件不为空修改成功返回true，
	//原文件内容：m1.st1 m1 mm
	//修改后内容：f1.st1 f1 ff

	string filename = "../music/m3.st3";
	mp.Init();
	mp.MusicInsert(filename);

	string newName = "../music/f1.st1";
	vector<string> v; //修改的信息
	v.push_back(newName); //歌名
	v.push_back("f1"); //歌手
	v.push_back("ff"); //专辑

	bool b = mp.MusicModifier(filename,v);
	if(b == false){
		printf("MusicModifier error ,return value should be true but is false");
		return ;
	}
	//判断词曲中是否修改成功
	if(FindFile("../music/f1.st1","f1.st1 f1 ff") == false){
		printf("MusicModifier %s error\n",filename.c_str());
		return;
	}

	//判断播放器中是否修改成功
	string name = mp.MusicPut(newName)->_name;
	string singer = mp.MusicPut(newName)->_singer;
	string album = mp.MusicPut(newName)->_album;
	cout << name << endl;

	if(name != "../music/f1.st1" || singer != "f1" || album != "ff"){
		printf("MusicModifier in Player error\n");
		return ;
	}

	//文件为空，修改失败返回false
	string nfilename = "../music/m.st1"; //不存在的文件
	b = mp.MusicModifier(nfilename,v);
	if(b == true){
		printf("MusicModifier is error ,return value should be false but is true\n");
		return ;
	}

	printf("MusicModifier OK\n");
}

void MusicPlay_test(){
	Music::MyPlayer mp;
	//清空目录文件
	string musicfile = mp.FileNamePut();
	if(CleanFile(musicfile) == false){
		return ;
	}

	string file1 = "../music/m1.st1";
	string file2 = "../music/m2.st2";

	mp.Init();
	mp.MusicInsert(file1);
	mp.MusicInsert(file2);

	//播放只测试拼接是否正确
	string add1 = mp.AddJoint(file1);
	string add2 = mp.AddJoint(file2);
	
	if(add1 != "!!!!!"){
		printf("MusicPlay error, `m1.st1` should is `!!!!!` but is %s\n ",add1.c_str());
		return ;
	}
	if(add2 != "@@@@@"){
		printf("MusicPlay error, `m2.st2` should is `@@@@@` but is %s\n ",add2.c_str());
		return ;
	}

	printf("MusicPlay OK\n");
}

void Trash_test(){
	Music::MyPlayer mp;
	//清空目录文件
	string musicfile = mp.FileNamePut();
	if(CleanFile(musicfile) == false){
		return ;
	}
	string delfile = mp.DelFilePut();
	if(CleanFile(delfile) == false){
		return ;
	}

	string file1 = "../music/m1.st1";
	string file2 = "../music/m2.st2";

	mp.Init();

	mp.MusicInsert(file1);
	mp.MusicInsert(file2);
	
	mp.MusicErase(file1);
	mp.MusicErase(file2);

	mp.RecoveryFile(file1);
	mp.RecoveryFile(file2);

	if(FindFile(musicfile,file1) == false){
		printf("Trash error,RecoveryFile `m1.st1`to musicfile faild\n");
		return ;
	}
	if(FindMusic(&mp,file1) == false){
		printf("Trash error,RecoveryFile `m1.st1`to Player faild\n");
		return ;
	}

	if(FindFile(musicfile,file2) == false){
		printf("Trash error,RecoveryFile `m2.st2`to musicfile faild\n");
		return ;
	}
	if(FindMusic(&mp,file2) == false){
		printf("Trash error,RecoveryFile `m2.st2`to Player faild\n");
		return ;
	}

	//对不存在的文件进行回收操作
	string file3 = "../music/m.st1";
	mp.RecoveryFile(file3);

	if(FindFile(musicfile,file3) == true){
		printf("Trash error,RecoveryFile non-existent file `m.st1`,but into musicfile\n");
		return ;
	}
	if(FindMusic(&mp,file3) == true){
		printf("Trash error,RecoveryFile non-existent file `m1.st1`,but into Player\n");
		return ;
	}

	printf("Trash OK\n");
}

int main(){

	MusicInit_test();
	MusicInsert_test();
	//MusicErase_test();
	MusicModifier_test();
	MusicErase_test();
	MusicPlay_test();
	Trash_test();

	return 0;
}
