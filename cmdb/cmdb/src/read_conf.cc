#include"read_conf.h"

namespace RC{
	bool ReadConf::ReadConfInit(const string &conf_file){
		file_ = conf_file;
/*
		//初始化文件类型map
		all_type_["ini"] = INI;
		all_type_["conf"] = CONF;
		all_type_["json"] = JSON;
		all_type_["xml"] = XML;

		file_type_ = conf_file_.substr(conf_file_.find_last_of('.') + 1);
		if(file_type_.size() < 1){
			printf("file type error \n");
			return false;
		}
*/
		if(file_.size() < 1)
			return false;
			
		return true;
	}


	//注释处理
	string ReadConf::HandleComment(string msg,char c){
		string str;
		int end = msg.find(c);
		int first  = 0;

		while((first < (int)msg.size()) && (msg[first] == ' ' || msg[first] == '\t'))
			first++;

		if( first < (int)msg.size()){
			if(end > 0)
				str = msg.substr(first,end-first);
			else
				str = msg.substr(first,msg.size()-first-1);  //从first到末尾(不包含'\n')
			return str;
		}
		return str;
	}

	void ReadConf::Analysis(map<string , string> &kv,string& str,char c){
		char ch[100];
		str.copy(ch,str.size(),0);
		ch[str.size()] = '\0';
		char* first = ch;
		char* end = ch;

		while(*end != '\0'){
			while(*first == ' ' || *first == '\t'){
				end++;
				first++;
			}

			if(*end == ' '|| *end == c){
				*end++ = '\0';  //将key后面的空格变为'\0'
				while(*end == ' ' || *end == '=')  //让end从=后不为空格处开始
					end++;
				kv[first] = end;
				break;
			}
			end++;
		}

	}


	bool ReadConf::GetIniData(string& Out,char c,FILE* ifs){
		char line[1024] = {0};

		while(!feof(ifs)){
			fgets(line,1024,ifs);
			if(line[0] == c)
				continue;

			Out = HandleComment(line,c);
			if(Out.size() < 1)
				continue;

			return true;
		}

		return false;
	}

	map<string, map<string, string> >&  ReadConf::IniData(){
		string Out = "1133";
		char c = ';';
		FILE* ifs;

		ifs = fopen(file_.c_str(),"r");
		if(ifs == NULL){
			printf("conf_file open error\n");
			return ini_data_;
		}
		
		if(GetIniData(Out,c,ifs) == false){
			fclose(ifs);
			return ini_data_;
		}  

		while(1){
			if(Out[0] == '['){
				string key = Out;
				map<string,string> kv;

				while(1){
					if(GetIniData(Out,c,ifs) == false || Out[0] == '['){
						break;
					}
					//处理key ---value
					Analysis(kv,Out,'=');
				}

				if(Out[0] != '['){
					ini_data_[key] = kv;
					break;
				}

				ini_data_[key] = kv;
			}
		}
		fclose(ifs);
		return ini_data_;
	}

	void ReadConf::Print(){
		string key1;
		map<string, map<string,string> >::iterator mm = ini_data_.begin();
		while(mm != ini_data_.end()){
			cout << mm->first << endl;

			map<string ,string> kv = mm->second;
			map<string,string>::iterator m = kv.begin();

			while(m != kv.end()){
				cout << m->first << " = ";
				cout << m->second << endl;
				m++;
			}
			mm++;
		}
		
	}

	map<string, string>&  ReadConf::ConfData(){
		string Out;
		char c = '#';
		FILE* ifs;

		ifs = fopen(file_.c_str(),"r");
		if(ifs == NULL){
			printf("conf_file open error\n");
			return data_;
		}
		
		while(GetIniData(Out,c,ifs)){
			Analysis(data_,Out,c);
		}

		fclose(ifs);
		return data_;
	}

	void ReadConf::PrintConf(){
		map<string,string>::iterator m = data_.begin();

			while(m != data_.end()){
				cout << m->first << " = ";
				cout << m->second << endl;
				m++;
			}
	}
	
	void ReadConf::AnalysisJson(map<string, string> &kv, string str){
		char ch[100];
		str.copy(ch,str.size(),0);
		ch[str.size()] = '\0';
		char* first = ch;
		char* end = ch;

		while(*end != '\0'){
			while(*first == ' ' || *first == '\t' || *first == '{' || *first == '}'){			  
				end++;
				first++;
			}
			
			if(*end == ' '|| *end == ':'){
				*end++ = '\0';  //将key后面的空格变为'\0'
				while(*end == ' ' || *end == ':')  //让end从=后不为空格处开始
					end++;
				//处理末尾读入的'\n'
				char value[1024] = {0};
				strncpy(value,end,strlen(end)-1);
				
				//去除""
				int size = strlen(first);
				char key[100] = {0};
				strncpy(key,++first,size-2);
				
				if(end[0] == '"'){
					size = strlen(end);
					memset(value,0,sizeof(value));  //清空数组
					strncpy(value,++end,size-3);
					kv[key] = value;
					break;
				}
				
				kv[key] = value;
				break ;   
			}
			end++;
		}

	}

	map<string, string>&  ReadConf::JsonData(){
		char line[1024] = {0};
	
		FILE* ifs;
		ifs = fopen(file_.c_str(),"r");
		if(ifs == NULL){
			printf("conf_file open error\n");
			return data_;
		}
		
		while(!feof(ifs)){
			fgets(line,1024,ifs);
			if(line[0] == '{' || line[0] == '}')
				continue;
			AnalysisJson(data_,line);
		}

		fclose(ifs);
		return data_;
	}

	map<string, map<string, string> >& ReadConf::PutIniData(){
		return ini_data_;
	}


	string ReadConf::PutIniValue(string key,string key2){
		IniData();
		string value;
		
		map<string, map<string,string> >::iterator mm = ini_data_.find(key);
		if(mm == ini_data_.end()){
			return value;
		}
		
		map<string ,string> kv = mm->second;
		map<string,string>::iterator m = kv.find(key2);
		if(m == kv.end())
			return value;
		
		value = m->second;
		return value;			
	}

	string ReadConf::PutConfValue(string key){
		ConfData();
		string value;
		map<string,string>::iterator m = data_.find(key);
		
		if(m == data_.end())
			return value;
		
		value = m->second;
		return value;		
	}

	string ReadConf::PutJsonValue(string key){
		JsonData();
		string value;
		map<string,string>::iterator m = data_.find(key);
		
		if(m == data_.end())
			return value;
		
		value = m->second;
		return value;			
	}

}

/*

	bool ReadConf::GetConfData(string Out){
		Out = HandleComment("fffff",'c');
		return true;
	}

	bool ReadConf::GetJsonData(string Out){
		Out = HandleComment("fffff",'c');
		return true;
	}

	//读取的数据以参数传出（出注释空格外）
	bool ReadConf::SelectParsedWay(string& Out){
		switch(all_type_[file_type_]){
			case INI:
				cout << "INI" << endl;
				IniData();
				return true;
			case CONF:
				cout << "CONF" << endl;
				return GetConfData(Out);
			case JSON:
				cout << "JSON" << endl;
				return GetJsonData(Out);
			default :
				printf("file type error\n");
				return false;
		}  
	}
*/
