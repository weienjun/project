
#include"find_file.h"

namespace framework{

	bool FindFile::FindFileInit(string so_path,string conf_path){
		so_path_ = so_path;
		conf_path_ = conf_path;
		
		if(so_path.size() < 1 || conf_path.size() < 1){
			printf("so_path or conf_path error\n");
			return false;
		}

		return true;
	}

		string FindFile::GetConfName(string name,vector<string>&file){ //找so配置文件名
		//从所有文件中查找同名的配置文件
		int i = 0;
		string cfpath;
		for(; i < (int)file.size(); i++){
			string tmp = file[i].substr(file[i].find_last_of('/')+1); //获取同名配置文件	
			if((name + ".conf" == tmp) ||
			   (name + ".ini" == tmp) ||
			   (name + ".json" == tmp)){

				cfpath = conf_path_ + "/" + file[i];
			}
		}
		return cfpath;
	}
	//获取文件名（不带后缀）+ 获取配置文件
	void FindFile::GetConfFile(string& filename,vector<string>& file){
		string tmp = filename.substr(filename.find_last_of('/')+1); //获取同名配置文件
		char name[20];
		tmp.copy(name,tmp.size()-3,0);
		filename = so_path_+ "/" + filename;
	//	cout << filename << endl;
		so_[filename] = GetConfName(name,file);  //将配置文件放入到对应的so中
	}

	//判断so
	void FindFile::GetSoFile(vector<string>& file){
		int i = 0;
		while(i < (int)file.size()){ //寻找os文件
			string filename = file[i];

			string type = filename.substr(filename.find_last_of('.')+1); //获取后缀
			if(type == "so"){
				//获取 其os配置文件 
				GetConfFile(filename,file);
			}
			i++;
		}		
	}

	int FindFile::_GetFile(string path,vector<string>& file){
		DIR *directory_pointer;
		struct dirent *entry;
	
		if((directory_pointer=opendir(path.c_str()))==NULL){
			printf("Error open\n");
			return 0;
		} else {
			
			while((entry=readdir(directory_pointer))!=NULL){
				if(entry->d_name[0]=='.') continue;

			//	cout << "文件" << entry->d_name << endl;
				file.push_back(entry->d_name);
			}
		}
		return 1;
	}

	int FindFile::GetFile(){
		vector<string> file;
		if(_GetFile(so_path_,file)){
			 _GetFile(conf_path_,file);
			GetSoFile(file);
			return 1;
		}

		return 0;
	}

	void FindFile::Print(){
		map<string, string >::iterator mo = so_.begin();
		while(mo != so_.end()){
				
			cout << "so:" << mo->first << "----" ;
			cout << "conf:" << mo->second <<  endl;

			mo++;
		}
	}

	map<string, string >& FindFile::Put(){
		return so_;
	}
};
