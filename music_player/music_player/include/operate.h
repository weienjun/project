#ifndef __MUSIC_H__

#define __MUSIC_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/ioctl.h>
#include<termios.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<stdexcept>
#include<map>
#include<vector>

using namespace std;

namespace Music{

struct MusicData{
	string _name;
	string _singer;
	string _album;
	string _type;
	size_t _size;
	size_t _time;

	MusicData()
		:_name("\0")
		 ,_singer("\0")
		 ,_album("\0")
		 ,_type("\0")
		 ,_size(0)
		 ,_time(0)
	{}

	~MusicData()
	{}
};

//父类接口类，提供基本功能
class Player{
	public:
	typedef MusicData Data;
	public:
	Player()
		:_music_file("../conf/musicfile")
		 ,_delete_file("../conf/deletefile")
		 ,_music()
	{}

	~Player()
	{}
		
	//基本功能函数接口
	bool MusicInsert(const string &filename); //插入
	bool MusicErase(const string &filename); //删除
	bool MusicModifier(const string &filename,vector<string>& send); //修改
	bool Musicplay(const string &filename); //播放
	void MusicPrint(); //输出
	int CheckDelFile(); //查看回收站 文件
	bool RecoveryFile(const string &filename); //还原文件

	//辅助实现函数
	void  MusicMessage(const string &filename,const Data &d); //读取歌曲信息
	string AddJoint(const string &filename); //拼接内容
	bool MusicAddFile(const string &filename); //添加到目录
	bool MusicAddPlay(const string &filename); //添加到播放器
	void Modifier(const string &filename,const string &InOut,int flag); //修改
	bool FindMusicFile(const string& file, const string &song); //查看音乐文件是否在目录中
	int MusicTime(const string &filename); //计算时间
	void SongAddTrash(const string &filename,const string &InOut);

	protected:
	string _music_file; //音乐目录文件
	string _delete_file;  //删除目录文件
	map<string,Data> _music; //音乐文件

};

}

#endif 
