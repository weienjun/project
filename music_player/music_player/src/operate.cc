#include<cstdlib>
#include"operate.h"
#include<vector>

namespace Music{
	//计算时间
	int Player::MusicTime(const string &filename){
		ifstream ifs;
		string line;
		int count = 0;

		ifs.open(filename.c_str());
		if(!ifs){
			printf(" %s open error\n",filename.c_str());
			return 0;
		}

		while(getline(ifs,line)){
			count++;
		}

		ifs.close();
		return count;
	}

	//判断歌曲是否在目录中
	bool Player::FindMusicFile(const string &file,const string &song){
		ifstream ifs;
		ifs.open(file.c_str());

		string read;
		while(getline(ifs,read)){
			if(read == song){
				ifs.close(); 
				return true;
			}
		}

		ifs.close();
		return false;
	}

	bool Player::MusicAddFile(const string &song){
		if(FindMusicFile(_music_file,song) == true){
			printf("The file already exists in the directory!\n");
			return false;
		}

		//查询打开，查看该文件能否操作
		ofstream fd;
		fd.open(song.c_str(),ios::in);
		if(!fd){
			printf(" %s  added to directory failed！\n",song.c_str());
			return false;
		}
		fd.clear();
		fd.close();

		//打开写入的目录文件
		fd.open(_music_file.c_str(),ios::app);
		if(!fd){
			printf("open error\n");
			return false;
		}

		fd << song.c_str() << endl;//追加到尾部
		fd.close();

		return true;
	}

	//添加到播放器列表，同时初始化音乐数据
	bool Player::MusicAddPlay(const string &filename){
		map<string ,Data>::iterator fm = _music.find(filename);
		if(fm != _music.end()){
			printf("Is already in list\n");
			return false;
		}
		//从文件中获取歌手，专辑，文件大小
		ifstream infile;	
		infile.open(filename.c_str());

		if(infile == NULL){
			printf(" %s File addition failed!!!!！\n",filename.c_str());
			return false;	
		}else{
			Data fd;
			//获取文件类型
			string type = filename.substr(filename.find_last_of('.')+1); //获取后缀
			fd._type = type;
			//从文件解析内容
			string line; //保存第一行
			getline(infile,line);//获取第一行
			istringstream instream(line);//字符串解析

			fd._name = filename; //曲名同于文件名

			getline(infile,line); //第一个单词--name
			instream >> fd._name;
			getline(infile,line); //第二个单词--singer
			instream >> fd._singer; //对获取的单词重定向
			getline(infile,line); //第三个单词--album
			instream >> fd._album;

			//获取大小
			struct stat info;
			stat(filename.c_str(),&info);
			fd._size = info.st_size;
			fd._time = MusicTime(filename);
			//添加到列表中
			_music[filename] = fd;	
		}
		infile.close();
		return true;
	}

	void Player::SongAddTrash(const string &filename ,const string &InOut){
			ofstream fd;
			fd.open(_delete_file.c_str(),ios::app);
			if(!fd){
				printf("open error\n");
			}
			
			if(FindMusicFile(_delete_file,InOut) == false)
				fd << InOut.c_str() << endl;//追加到尾部
			fd.close();   
	}

	//修改或删除文件 ---主要起始文件内容为空时
	void Player::Modifier(const string &filename,const string &InOut,int flag){
		ifstream in;
		string cur;

		in.open(filename.c_str());

		if(flag == 0){ // 0代表修改，1, 代表删除
			getline(in,cur);//获取首行（修改行）
			in.seekg(ios_base::beg); //文件指针重新指向开头
		}else{ //删除
			cur = InOut; //cur为要删除的文件
		}

		char line[1024]={'\0'};//获取文件行内容
		int i= cur.size();
		string tempStr; //保存新文件内容

		//i++ == 0 处理文件为空时，也可进入修改，否则将不会进入循环中
		while(in.getline(line,sizeof(line)) || i++ == 0){ //将原文件内容放到缓冲line中，并修改linenum行
			if(line == cur){
				if(flag == 0){ 
					tempStr+=InOut; //将修改的语句放到新内容中
				}else{ //1仅删除(修改时使用)，2删除后添加到回收站 
					//打开写入  的删除目录文件,写入到删除目录中
					if(flag == 2 && filename != _delete_file){ //如果是删除目录文件删除，则不执行
						SongAddTrash(filename,InOut);
					}  
					continue; //删除则忽略此行
				}  
			}else{
				tempStr+=line; //添加不修改的内容
			}
			tempStr+='\n'; 
		}
		in.close(); //关闭原文件

		ofstream out;
		out.open(filename.c_str()); //打开原文件
		out.flush(); //清空原文件内容

		out<<tempStr; //将新内容重定向到文件中
		out.close();
	}

	string Player::AddJoint(const string &filename){
		map<string,Data>::iterator fm = _music.find(filename);
		if(fm == _music.end()){
			printf("The song is not on the player\n");
			return 0;
		}

		string add ;
		string type = _music[filename]._type;

		if(type == "st1")
			add = "!!!!!";
		if(type == "st2")
			add = "@@@@@";
		if(type == "st3")
			add = "#####";
		if(type == "st4")
			add = "$$$$$";
		if(type == "st5")
			add = "%%%%%";

		return add;
	}

	//添加歌曲 1、添加到目录  2、初始Data   3、添加到播放器
	bool Player::MusicInsert(const string &filename){
		if(MusicAddFile(filename)){ //添加到目录
			if(MusicAddPlay(filename)); //添加到播放
			return true;
		}
		return false;
	}

	//删除	1、从播放器删除  2、从目录删除
	bool Player::MusicErase(const string &filename){
		map<string,Data>::iterator fm = _music.find(filename);
		if(fm == _music.end()){
			printf("The song is not on the player\n");
			return false;
		}

		_music.erase(fm); //从播放器删除 
		Modifier(_music_file,filename,2); //从目录移除
		return true;
	}

	//修改	1、修改文件内容	 2、重新添加到播放器（覆盖）
	bool Player::MusicModifier(const string &filename,vector<string> &send){
		string newName = send[0];
		string name = newName.substr(newName.find_last_of('/')+1); //获取后缀

		string strr = name + " "; //注歌词中不包具体路径
		strr +=  send[1] + " " ;
		strr += send[2];

		//修改文件名
		if (rename(filename.c_str(), newName.c_str())){
			printf("The song name modification failed\n");
			return false;
		}

		_music.erase(filename); //从播放器删除
		Modifier(_music_file,filename,1); //从目录移除
		//插入新歌曲名
		MusicInsert(newName);

		//修改歌词
		Modifier(newName,strr,0);

		_music[newName]._name = newName;
		_music[newName]._singer = send[1];
		_music[newName]._album = send[2];

		return true;
	}

	//播放	1、判断后缀，决定末尾添加内容	2、读取文件内容，拼接打印
	bool Player::Musicplay(const string &filename){
		map<string,Data>::iterator fm = _music.find(filename);
		if(fm == _music.end()){
			printf("The file is not in the list\n");
			return false;
		}

		string add = AddJoint(filename);
		if(add.size() < 1){
			printf("Unsupported playback type！\n");
			return false;
		}

		string name = filename.substr(filename.find_last_of('/')+1); //获取后缀
		printf("Playing song：\n%s\t",name.c_str()); 
		printf("singer：%s\t",_music[filename]._singer.c_str());
		printf("album：%s\n\n",_music[filename]._album.c_str());

		string read;
		ifstream ifs(filename.c_str());
		while(getline(ifs,read)){ //读取一行，直到遇到 \n 或 EOF 或达到最大值
			std::cout << read + add << std::endl;
			sleep(1);
		}

		ifs.close();
		return true;
	}

	//输出列表中歌曲信息
	void Player::MusicPrint(){
		map<string,Data>::iterator m = _music.begin();

		printf("name\t\tsinger\talbum\tsize\ttime\n");
		while(m != _music.end()){
			string filename  = m->first;
			string name = filename.substr(filename.find_last_of('/')+1); //获取后缀
			printf("%-16s%-4s\t%-4s\t%-4d\t%-4d\n",name.c_str(),\
					m->second._singer.c_str() ,m->second._album.c_str(),\
					(int)m->second._size,(int)m->second._time);
			m++;
		}
		return ;
	}

	//输出回收站文件
	int Player::CheckDelFile(){
		ifstream ifs(_delete_file.c_str());
		string readstr;
		int count  = 0;

		while(getline(ifs,readstr)){ //读取一行，直达遇到 \n 或 EOF 或达到最大值
			string name = readstr.substr(readstr.find_last_of('/')+1); //获取文件名
			std::cout << name << endl;
			count++;
		}

		ifs.close();
		return count;
	}

	//还原回收站文件
	bool Player::RecoveryFile(const string &filename){
		if(MusicInsert(filename)){
			Modifier(_delete_file,filename,2); //从删除目录中移除
			return true;
		}
		return false;
	}

}
