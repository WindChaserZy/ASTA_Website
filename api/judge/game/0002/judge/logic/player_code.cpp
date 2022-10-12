/* DAGAN 2017, player_code.cpp
*
* Game <-- Player_Ai ---> AI
*
*/
#include <time.h>
#include "player_code.h"
#include <iostream>

#ifdef __GNUC__
unsigned long GetTickCount()
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
#endif //__GNUC__

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
		//hDLL = NULL;
		load();
	}


	Player_Code::~Player_Code()
	{
	}

	bool Player_Code::load()
	{
		// we don't need to load dll online -- swm_sxt
		Valid = true;
		return true;
		/*
		if (NULL != hDLL)                                          //���¼��أ�ɾ��ԭ���Ѿ����صĶ�̬���ӿ�
		{
			_CLOSEDLL(hDLL);
			player_ai = NULL;
		}
		hDLL = _LOADDLL(file_name.c_str());                        //����AI���붯̬���ӿ⣨DLL��
		//cout << file_name << "being loading" << endl;
		if (NULL != hDLL)
		{
			player_ai = (TPlayerAi)_GETFUNC(hDLL, "player_ai");    //����DLL�ɹ����������ai����ĺ���ָ��
		}

		Valid = true;
		Valid = Valid && (NULL != player_ai);                      //������ai����ĺ���ָ���Ƿ����

		if (NULL == hDLL)
			cout << "[ERROR] failed to load \"" << file_name << "\"" << endl;
		else
			cout << "Succeed to load \"" << file_name << "\". ";
		if (isValid())
			cout << "Player{" << (int)id << "} has been loaded. " << endl;
		else
			cout << "[ERROR] failed to load Player{" << (int)id << "} !" << endl;

		return Valid;
		*/
	}

	bool Player_Code::run(Info &info)
	{
		/*
		//��FC18�����䳬ʱ���ж�
		int time_a = GetTickCount();              //����ĳλ���ai���뿪ʼ������ʱ��ʱ���
		int time_b;
		//����ĳλ���ai���룬����ӵ��쳣����gameover���������쳣������ҵ����
#if (!defined _MSC_VER) //|| (defined _DEBUG)
		try {
			player_ai(info);
		}
		catch (exception e) {
			cout << "[ERROR] Player " << (int)id << " raised an exception in run()." << endl;
			cout << e.what() << endl;
			kill(); return false;
		}
#else 
		__try {
			player_ai(info);//ͨ������ָ��ֱ���������ai����
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			cout << "[ERROR] Player " << (int)id << " raised an exception in run()." << endl;
			kill(); return false;
		}
#endif

		time_b = GetTickCount();
		//if (time_b - time_a > 2000) kill();
		*/
		//output info --swm_sxt
		Json::FastWriter write;
		printf("%d\n", info.myID - 1);
		fflush(stdout);
		
		ios::sync_with_stdio(false);
		cout << write.write(info.asJson());
		fflush(stdout);
		
		//����commandList ���� swm_sxt
		string commandListString;
		cin >> commandListString;
		Json::Reader reader;
		Json::Value commandListJson;
		if (reader.parse(commandListString.data(), commandListJson));
		info.myCommandList = CommandList(commandListJson);
		return true;

	}

}
