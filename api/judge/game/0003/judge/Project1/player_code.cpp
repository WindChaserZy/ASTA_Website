/* DAGAN 2017, player_code.cpp
*
* Game <-- Player_Ai ---> AI
*
*/
#include <time.h>
#include "player_code.h"
#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <chrono>
using std::thread;

#ifdef __GNUC__
unsigned long GetTickCount()
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
#endif //__GNUC__
#ifdef _DEBUG

#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif
namespace DAGAN {
	using namespace std;
	Player_Code::Player_Code()
	{
	}

	Player_Code::Player_Code(string file_name, int id)
		: id(id), file_name(file_name)
	{
		name = file_name;
		if (name.rfind('/') != string::npos) {          //rfind是返回待查字符的最后一次位置索引，即ai代码路径的最底层
			name = name.substr(name.rfind('/') + 1);
		}
		if (name.rfind('\\') != string::npos) {
			name = name.substr(name.rfind('\\') + 1);
		}

		player_ai = NULL;
		hDLL = NULL;
		load();
	}


	Player_Code::~Player_Code()
	{
	}

	bool Player_Code::load()
	{
		std::fstream file;
		file.open("error_log/error.log");
		string error = "";
		if (NULL != hDLL)                                          //重新加载，删除原来已经加载的动态链接库
		{
			_CLOSEDLL(hDLL);
			player_ai = NULL;
		}
		hDLL = _LOADDLL(file_name.c_str());                        //加载AI代码动态链接库（DLL）
		//cout << file_name << "being loading" << endl;
		if (NULL != hDLL)
		{
			player_ai = (TPlayerAi)_GETFUNC(hDLL, "player_ai");    //加载DLL成功，更新玩家ai代码的函数指针
		}
#ifndef ALL
		else
		{
			int err = GetLastError();
			error = "[ERROR] GetError:";
			error.append(std::to_string(err));
		}
#endif

		Valid = true;
		Valid = Valid && (NULL != player_ai);                      //检查玩家ai代码的函数指针是否可用

		if (NULL == hDLL) {
#ifndef ALL
			error = "[ERROR] Fail to load \"" + file_name + "\".";
#else
			error = std::to_string(id);
#endif
		}
		else
			cout << "Succeed to load \"" << file_name << "\". ";
		if (isValid())
			cout << "Player{" << (int)id << "} has been loaded. " << endl;
		else {
			file << error;
#ifndef ALL
			system("pause");
#endif
			exit(1);
		}
		return Valid;
	}
	
	bool Player_Code::run(IPlayer* player)
	{
		//【FC18】补充超时的判定
		//运行某位玩家ai代码，如果接到异常，则gameover，并报出异常代码玩家的序号
		std::fstream file;
		file.open("error_log/error.log");
		int err = 0;
#ifdef _DEBUG
		player_ai(player);
#endif
#ifndef _DEBUG
		std::thread t1([&]()
			{
				__try
				{
					player_ai(player);
				}
				__except (EXCEPTION_EXECUTE_HANDLER) {
					err = GetExceptionCode();
					
				}
			});
		auto result = WaitForSingleObject(t1.native_handle(), 2000);
		switch (result)
		{
		case WAIT_TIMEOUT:
			{
#ifndef ALL
				file << "[ERROR] player " << (int)id << " TLE.";
#else
				file << (int)id;
#endif

				TerminateProcess(t1.native_handle(), 1);
#ifdef _DEBUG
				_CrtDumpMemoryLeaks();
#endif
				exit(1);
			}
		case WAIT_FAILED:
			{
			err = GetLastError();
#ifndef ALL
				file << "[ERROR] Player " << (int)id << " raised an exception in run()." << endl;
				file << "Error code is " << err << endl;
#else
				file << int(id);
#endif
				kill();
#ifdef _DEBUG
				_CrtDumpMemoryLeaks();
#endif
				
				exit(1);
			}
		case WAIT_OBJECT_0:
			{
			if (err != 0)
			{
#ifndef ALL
				file << "[ERROR] Player " << (int)id << " raised an exception in run()." << endl;
				file << "Error code is " << err << endl;
#else
				file <<int(id);
#endif
				exit(1);
			}
			}
		}
		t1.join();
#endif

		//if (time_b - time_a > 2000) kill();
		return true;

	}

}
