#ifndef __CONTROL2_H__
#define __CONTROL2_H__

#include<iostream>
using namespace std;
#include"framework.h"
#include"log.h"
#include"singleton.h"

namespace framework{
	class Control{
		public:
			Control()
			{}

			virtual ~Control()
			{}
		
			static void handler2(int asg);

			bool Init(string path);
			bool ControlStart();
			string GetCurrentTime();
			time_t CurFileTime(string filename);
			void CheckUpdate();
			void Delayed(int ms);
			void BackControl();
			long long GetTimestamp(); 
			void ControlLoad();
			void BackDesk();
			void Quit();
			void Start(char c);
			void Update(string so,string conf);
			void ChildFork();

			void TimeInit();			

		private:
			MyLog load_log_;  //加载日志
			MyLog timestamp_log_;  //时间戳日志
			vector<time_t> last_time_;
			FrameWork fw_;
			static bool flag_;
			string pid_file_;  //配置文件路径
			string load_file_;
	};

}

#endif
