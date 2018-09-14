#include"my_player.h"
#include<signal.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/wait.h>

namespace Music{

	void MyPlayer::CleanTrash(){
		int  count = CheckDelFile();
		if(count == 0){
			cout << "Trash is empty!" << endl;
			return;
		}	

		printf("Trash file number：%d\n",count);
		printf("Empty the recycle bin（Y/N）:");
		char c;

		cin >> c;
		if(c != 'y' && c != 'Y')
			return;

		ofstream out;
		out.open(_delete_file.c_str()); //打开文件
		if(!out)
			return;

		out.flush(); //清空文件内容
		out.close();

		cout << "Clean Trash success!" << endl;
	}

	bool MyPlayer::FileType(const string &filename){	
		string type = filename.substr(filename.find_last_of('.')+1); //获取后缀
		if(((type == "st1")|| (type == "st2")) || ((type == "st3") || (type == "st4"))){
			return true;
		}
		if(type == "st5")
			return true;
		return false;
	}

	void MyPlayer::UpdateMusic(){
		//清空原有文件内容
		ofstream out;
		out.open(_music_file.c_str()); //打开文件
		out.flush(); //清空文件内容
		out.clear();
		out.close();

		//清空播放器中的数据
		_music.clear();

		DIR *directory_pointer;
		struct dirent* entry;

		if((directory_pointer=opendir(_path.c_str())) == NULL){
			printf("error open\n");
			return ;
		}
		//循环读取该位置的文件
		while((entry=readdir(directory_pointer))!=NULL){
			if(entry->d_name[0] == '.') continue;
			if(FileType(entry->d_name)){
				string infile = _path + entry->d_name; //加上路径
				MusicInsert(infile);
			}
		}
		cout << "Update success!" << endl;
	}

	bool MyPlayer::InputMusicData(const string &filename, vector<string>& v){	
		map<string,Data>::iterator fm = _music.find(filename);
		if(fm == _music.end()){
			printf("The song is not on the player\n");
			return false;
		}

		printf("Enter modified content（notice：Separate items with spaces）\n");
		printf("musicname\tmusicsinger\tmusicalbum\n");

		string name;
		string singer;
		string album;
		std::cin >> name >> singer >> album;

		string oldName = filename.substr(filename.find_last_of('/')+1); //获取歌曲名
		string newName = (filename.substr(0,filename.size()-oldName.size()) )+ name;

		FILE* fd = fopen(newName.c_str(),"r");
		if(fd){
			printf("The file already exists，Replace（Y/N）:");
			char c;
			cin >> c;
			if(c == 'n' || c == 'N'){
				fclose(fd); 
				return false ; 
			}
		}

		v.push_back(newName);
		v.push_back(singer);
		v.push_back(album);

		//fclose(fd); //注文件打开失败不可调用，否则错误
		return true;
	}

	//输入处理，处理父进程输入阻塞问题
	char MyPlayer::GetHandle(pid_t wid){
		fd_set rfds;
		struct timeval tv;
		int retval;
		char c = 0;

		FD_ZERO(&rfds); //所有位设置为0
		FD_SET(0,&rfds); //设置第0位

		//设置超时时间
		tv.tv_sec = 0.5; //子进程退出后，0.5s无输入动作，返回q,退出父进程
		tv.tv_usec = 0;

		retval = select(1,&rfds,NULL,NULL,&tv); //监听1号文件描述符，以读方式监听
		if(retval == -1){
			printf("select error!\n");
			return 'q';
		}

		if(retval){ //监听到输入动作
			cin >> c; //获取缓冲区的内容
			return c;
		}

		else if(wid != 0) //超时且子进程退出，通知父进程退出
			return 'q';
		return c;
	}

	//处理输入回车确认及隐藏输入问题
	char MyPlayer::Getch(pid_t wid){ 
		struct termios term_old;
		//用户空间从内核中读取数据（从标准输入中读）
		ioctl( STDIN_FILENO, TCGETS, &term_old );
		struct termios term_new = term_old;
		term_new.c_lflag &= ~( ECHO | ICANON ); //ECHO-显示，ICANON-规范输入，
		//将用户数据写到内核中
		ioctl( STDIN_FILENO, TCSETS, &term_new );
		//int ch = getchar();
		int ch = GetHandle(wid); //调用输入
		ioctl(STDIN_FILENO, TCSETS, &term_old);
		return ch;
	}

	void MyPlayer::Play(){
		string filename;
		cout << "Please enter the song name：" ;
		cin >> filename;
		filename = _path+filename;

		printf("s--stop  r--run  q--quit\n");

		pid_t pid = fork();
		if(pid < 0){
			printf("fork error\n");
			return;
		}

		//子进程执行播放动作
		//父进程执行控制
		if(pid == 0){ 
			cout << "\33[?25l"; //隐藏光标
			Musicplay(filename);
			exit(0);
		}

		if(pid > 0){
			pid_t wid = 0;
			while(wid == 0){ //等待子进程退出，子进程退出，父进程退出
				pid_t wid = waitpid(pid,NULL,WNOHANG);

				fflush(stdin);	
				char c = Getch(wid);

				if(c == 's'){
					kill(pid,SIGSTOP);
				}
				if(c == 'r')
					kill(pid,SIGCONT);
				if(c == 'q'){
					kill(pid,9);
					break;
				}
			}
		}
		cout << "\33[?25h"; //光标显示
	}

	void MyPlayer::Insert(){
		string filename;
		cout << "Please enter the song name：";
		cin >> filename;
		filename = _path + filename;

		if(MusicInsert(filename))
			cout << "Insert success!" << endl;
	}

	void MyPlayer::Erase(){
		string filename;
		cout << "Please enter delete song name：";
		cin >> filename;
		filename = _path + filename;

		if(MusicErase(filename))
			cout << "Erase success!" << endl;
	}

	void MyPlayer::Modifier(){
		string filename;
		std::cout << "Please enter modifier song name：";
		std::cin >> filename;
		filename = _path + filename;
		vector<string> v;

		if(InputMusicData(filename,v)){
			if(MusicModifier(filename,v))
				cout << "Modifier success" << endl;;
		}
	}

	void MyPlayer::TrashFile(){
		printf("********Trash File********\n");
		int count = CheckDelFile();
		if(count == 0){
			cout << "The Trash is empty" << endl;
			return ;
		}

		printf("Trash file number：%d\n",count);
		printf("Whether to restore（Y/N）:");

		char c;
		cin >> c;
		if(c != 'y' && c != 'Y')
			return ;

		string filename;
		cout <<"Please Enter recover file name：";
		cin >> filename;

		filename = _path+filename;
		if(RecoveryFile(filename))
			cout << "Recover success!" << endl;
	}

	void MyPlayer::Init(){
		ifstream fd;
		string line;
	
		fd.open(_music_file.c_str());
		if(fd == NULL){
			cout << "open _music_file error" << endl;
			return ;
		}
		//循环读取目录文件,添加到播放器
		while(getline(fd,line)){
			MusicAddPlay(line);
		}
	}

	//主控制，选择功能
	void MyPlayer::Menu(){
		system("clear");
		char i = 0;
		string filename;
	
			while(1){
			cout << "\033[0;0H";

			printf("\n*******************欢迎进入音乐播放器*******************\n");
			printf("0-->Quit\t 1-->Insert\t 2-->Erase\n3-->Modifier\t 4-->View\t "); 
			printf("5-->Play\n6-->Trash\t 7-->Update\t 8-->Clean Trash\n\n");
			printf("\n********************************************************\n");

			switch(i){
				case '0':{
					cout << "Quit!" << endl; ;
					system("clear");
					return ;
				}
				case '1': Insert();break;
				case '2': Erase(); break; 
				case '3': Modifier(); break; 
				case '4': MusicPrint(); break;
				case '5': Play();break;
				case '6': TrashFile(); break;   
				case '7': UpdateMusic(); break;
				case '8': CleanTrash(); break;

				default:{
					if(i != 0)
						std::cout << "Input error\n";
					break;
				}
			}

			cout << "\033[7;0H";
			cout << "Selection： ";
			fflush(stdin);
			cin >> i;

			system("clear");		
		} 
	}

	//数据输出接口，供外部测试调用
	string MyPlayer::FileNamePut(){
		return _music_file;
	}

	string MyPlayer::DelFilePut(){
		return _delete_file;
	}

	Player::Data* MyPlayer::MusicPut(string& filename){
		return &_music[filename];
	}

	int MyPlayer::MusicFilePut(vector<string >& v){
		map<string,Data>::iterator m = _music.begin();
		int count = 0;

		while(m != _music.end()){
			v.push_back(m->first);
			m++;count++;
		}
		return count;
	}

}
