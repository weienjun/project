/*************************************************************************
	> File Name: mymusic.h
	> Author: weienjun
	> Mail: weienjun@360.net
	> Created Time: Sun 19 Aug 2018 11:29:49 AM CST
 ************************************************************************/

#include"operate.h"
#include<dirent.h>
#include<dlfcn.h>
#include<stdio.h>

namespace Music{
class MyPlayer : public Player{
	public:
	MyPlayer(string path = "../music/")  //默认音乐文件路径
		:_path(path)
	{}
	
	~MyPlayer()
	{}

	void Init();
	void TrashFile();   //回收站		
	void CleanTrash();  //清空回收站	
	void UpdateMusic(); //更新列表
	void Menu();  //主菜单
	void Play();  //播放控制
	void Insert();
	void Erase();
	void Modifier();

	
	bool InputMusicData(const string &filename,vector<string>& v); //输入修改数据
	bool FileType(const string &filename); //类型判断
	char Getch(pid_t wid);		
	char GetHandle(pid_t wid);
	
	//数据接口函数，供外部使用
	string FileNamePut(); //返回目录文件名
	string DelFilePut(); //返回删除目录文件名
	Data* MusicPut(string &filename); //返回歌曲数据
	int MusicFilePut(vector<string> &v); //返回播放器中的歌曲
	
	private:
	string _path;
};
}


