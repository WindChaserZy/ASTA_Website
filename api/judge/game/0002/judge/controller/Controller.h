//#2021-1-19 <JYP> ��Ϥ���룬���ע��
#include "../logic/game.h"
#include "../logic/player_code.h"
#include <vector>
#include <string>
#include <fstream>
#include "../json/json.h"

namespace DAGAN
{
	class Controller
	{
	public:
		Controller(Game& g, std::vector<Player_Code>& p)
			: game_(g)
			, data(&(g.getData()))
			, silent_mode_(
#ifdef NO_SILENT_MODE
				false
#else
				true
#endif
			), file_output_enabled_(true)
			, isValid_(true), debug_mode(
#ifdef FC15_DEBUG
		true
#else
		false
#endif
			)
			, players_(p) {
			Corpslastcmd.resize(5);
		}                              //��FC18����Ϸ���صĹ��캯�����������Ϊ��ǰ��Ϸ���̶����Լ����ai��vector�����뼰�����Ϣ��
											              //��FC18��Ĭ������ļ�����Ϸ��һ�غϿ�������
		                                                  //��FC18��NO_SILENT_MODE��FC15_DEBUG�����궨������Ƿ����debug��Ϣ
		void run(TPlayerID id,ofstream& cmdF, ofstream& infoF);      //@@@��FC18������ÿ����ҵ�ǰ����Ϸ�غϣ�С�غϣ���Ȼ���¼���ָ��Json�ͱ仯�����ϢJson
        //#Json�й�Json���ĺ���
		void jsonChange(TPlayerID id,Command& c,ofstream& cmdFile);                      //��FC18��������ִ����ϣ���֤��Ч���󣬴���������������Ӧ�޸�����Json������
		bool moreCommand(TPlayerID id,set<TTowerID>& tBanned,set<TCorpsID>& cBanned);//��FC18���ж�ĳλ����Ƿ��ܼ���ִ����һ��ָ��
		void killPlayers();                                  //��FC18���ж�����������
		int commandRead = 0;                                      //��FC18���Ѷ�ȡ��������
		void setValid(bool valid) { isValid_ = valid; }       //��FC18��������Ϸ���������ܼ���������
		bool handleCorpsCommand(TPlayerID ID, Command& c);                       //��FC18��ִ�е�ǰ����ָ��������Ƿ�ִ�гɹ�
		bool handleTowerCommand(TPlayerID ID, Command& c);                       //��FC18��ִ�е�ǰ������ָ��������Ƿ�ִ�гɹ�
		void getGameRank();                                                      //��FC18����ȡ������Ϸ����
		void outPutCommand(TPlayerID id,Command& c);                             //��FC18�������ǰ��ҵ�ָ��������ֻ�����ʵ��ִ�е�ָ��

		void testPlayerCommand(Info& info);                                      //��FC18�����ڵ��ԣ�ģ��AI�����������ŵ���Ϸ��ִ��
		void getCmdFromKeyboard(TPlayerID id, CommandList& commands);                          //��FC18��ͨ�����̶��������ָ��


		inline void setSilentMode(bool flag) { silent_mode_ = flag; }                         //��FC18������silent_mode
		inline void setFileOutputEnabled(bool flag) { file_output_enabled_ = flag; }          //��FC18���ļ�������أ�����file_output_enabled_
		inline bool isValid() const { return isValid_; }                                      //��FC18�������ǹ�game_over
		inline DATA::Data* getData() { return data; }                                         //��FC18��ͨ��Controller�������Ϸʵʱ������Data

	protected:
		bool debug_mode;                       //��FC18���Ƿ����ģʽ
		Game& game_;                           //��FC18����ǰ����Ϸ���̣��ṹ�壩
		DATA::Data *data;                      //��FC18��������Ϸ�У����ݵĴ洢�빲��
		std::ofstream ofs;                     //��FC18��һ��������������ڰ���Ϸ�����е���Ϣ���                 
		std::vector<Player_Code>& players_;    //��FC18���洢��ҵ�ai������������Ϣ��
		bool file_output_enabled_;             //��FC18���ļ����ʹ�ܣ��Ƿ������������ļ�
		bool silent_mode_;                     //��FC18��silent_mode_Ϊfalse������غ�����Ϣ��ÿ����ҵĲ�����Ϣ�ȣ�����debug
		bool isValid_;                         //��FC18����Ϸ�Ƿ��ܼ������У������ж�game_over
		vector<vector<Command>> Corpslastcmd;	//��FC18��������һ�غ����������Ҫ�ӳ�һ�غ���Ч������
		int stopRound = 1;                     //��FC18����Ϸֹͣ��������ָ��ʱ�Ļغ���
	};
}
