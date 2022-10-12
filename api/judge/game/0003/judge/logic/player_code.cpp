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
#include "../json/json.h"
#include "Player.h"
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
		if (name.rfind('/') != string::npos) {          //rfind�Ƿ��ش����ַ������һ��λ����������ai����·������ײ�
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
		//std::fstream file;
		//file.open("error_log/error.log");
		//string error = "";
		//if (NULL != hDLL)                                          //���¼��أ�ɾ��ԭ���Ѿ����صĶ�̬���ӿ�
		//{
		//	_CLOSEDLL(hDLL);
		//	player_ai = NULL;
		//}
		//hDLL = _LOADDLL(file_name.c_str());                        //����AI���붯̬���ӿ⣨DLL��
		////cout << file_name << "being loading" << endl;
		//if (NULL != hDLL)
		//{
		//	player_ai = (TPlayerAi)_GETFUNC(hDLL, "player_ai");    //����DLL�ɹ����������ai����ĺ���ָ��
		//}
		//else
		//{
		//	int err = GetLastError();
		//	error = "[ERROR] GetError:";
		//	error.append(std::to_string(err));
		//}
		//Valid = true;
		//Valid = Valid && (NULL != player_ai);                      //������ai����ĺ���ָ���Ƿ����

		//if (NULL == hDLL) {
		//	error ="[ERROR] failed to load \"" + file_name  + "\"";
		//}
		//else
		//	cout << "Succeed to load \"" << file_name << "\". ";
		//if (isValid())
		//	cout << "Player{" << (int)id << "} has been loaded. " << endl;
		//else {
		//	error = "[ERROR] failed to load Player{" + std::to_string(id) + "} !";
		//	file << error;
		//	system("pause");
		//	exit(1);
		//}
		//return Valid;
		Valid = true;
		return true;
	}
	
	bool Player_Code::run(IPlayer* iplayer)
	{
//		//��FC18�����䳬ʱ���ж�
//		//����ĳλ���ai���룬����ӵ��쳣����gameover���������쳣������ҵ����
//		std::fstream file;
//		file.open("error_log/error.log");
//		int err = 0;
//#ifdef _DEBUG
//		player_ai(player);
//#endif
//#ifndef _DEBUG
//		std::thread t1([&]()
//			{
//				__try
//				{
//					player_ai(player);
//				}
//				__except (EXCEPTION_EXECUTE_HANDLER) {
//					err = GetExceptionCode();
//					
//				}
//			});
//		auto result = WaitForSingleObject(t1.native_handle(), 2000);
//		switch (result)
//		{
//		case WAIT_TIMEOUT:
//			{
//				file << "[ERROR] player " << (int)id << " TLE.";
//				TerminateProcess(t1.native_handle(), 1);
//#ifdef _DEBUG
//				_CrtDumpMemoryLeaks();
//#endif
//				exit(1);
//			}
//		case WAIT_FAILED:
//			{
//			err = GetLastError();
//				file << "[ERROR] Player " << (int)id << " raised an exception in run()." << endl;
//				file << "Error code is " << err << endl;
//				kill();
//#ifdef _DEBUG
//				_CrtDumpMemoryLeaks();
//#endif
//				
//				exit(1);
//			}
//		case WAIT_OBJECT_0:
//			{
//				if(err != 0)
//				{
//					file << "[ERROR] Player " << (int)id << " raised an exception in run()." << endl;
//					file << "Error code is " << err << endl;
//					exit(1);
//				}
//			}
//		}
//		t1.join();
//#endif
//
//		//if (time_b - time_a > 2000) kill();
//		return true;
		printf("%d\n", id - 1);
		fflush(stdout);

		Player* player = (Player*)iplayer;
		Json::FastWriter write;
		ios::sync_with_stdio(false);
		Json::Value output;
		output["Camp"] = player->Camp->asJson();
		output["Player"] = player->asJson();
		cout << write.write(output);
		fflush(stdout);

		string actionListString;
		cin >> actionListString;
		Json::Reader reader;
		Json::Value actionListJson;
		reader.parse(actionListString.data(), actionListJson);
		player->doAction(actionListJson);
		return true;

	}

}
