#pragma once
/* DAGAN 2017, player_code.h
*
*/

#ifndef _DAGAN_PLAYER_CODE_H__
#define _DAGAN_PLAYER_CODE_H__


#include<string>

#include"definition.h"

#include "ai.h"
/* do not need dll --swm_sxt
#ifdef _MSC_VER
// Du 2017.2.6
// EXCLUDE windows sockets
#define WIN32_LEAN_AND_MEAN
#include"windows.h"
#define _LOADDLL(x) LoadLibraryA(x)
#define _CLOSEDLL(x) FreeLibrary(x)
#define _GETFUNC GetProcAddress
typedef HMODULE _DLLHANDLE;
#endif
#ifdef __GNUC__
#include<dlfcn.h>
#define _LOADDLL(x) dlopen(x, RTLD_LAZY)
#define _CLOSEDLL(x) dlclose(x)
#define _GETFUNC dlsym
typedef void* _DLLHANDLE;
#endif
*/
namespace DAGAN {

	using namespace std;

	typedef void(*TPlayerAi)(Info& info);                   //��FC18��ָ�����ai����ĺ���ָ��

	class Player_Code                                       //��FC18����Ҵ������
	{
	public:
		Player_Code();                                      //��FC18�����ai�������Ĭ�Ϲ��캯��
		Player_Code(string file_name, int id);              //��FC18�����ai������Ĺ��캯������������ļ�����������
		~Player_Code();                                     //��FC18�����ai�������Ĭ����������

		bool run(Info &info);                               //��FC18�����볡�����ݣ�����ĳλ���ai����һ��

		bool load();                                        //��FC18���������ai���붯̬���ӿ⣨DLL��

		inline void kill() { Valid = false; }               //��FC18�������쳣��ǿ��game_over��λ��ҵĴ��룬���ұ���
		inline string getName() { return name; }            //��FC18����ȡ���ai����dll������
		inline bool isValid() { return Valid; }             //��FC18���ж���λ��ҵ�dll�����Ƿ�����
		void setName(string _name) { name = _name; }        //��FC18��������λ���dll���ļ���
	private:
		TPlayerAi        player_ai;                         //��FC18�����ai����ĺ���ָ��
		string           file_name;                         //��FC18�����ai�����·���ļ���
		string           name;                              //��FC18�����ai���뵥���ļ���
		TPlayerID        id;                                //��FC18����ҵ����
		bool             Valid;                             //��FC18����ҵ�dll�Ƿ���������
		//_DLLHANDLE       hDLL;                              //��FC18�����dll��ȡʱ���صľ�� do not need dll --swm_sxt
	};

}
#ifdef __GNUC__
unsigned long GetTickCount();
#endif // !__GNUC__




#endif
