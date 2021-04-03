//#2021-1-19 <JYP> ��Ϥ���룬����ע��


#include "game.h"
#include "player_code.h"
#include "../controller/Controller.h"
#include <time.h>
#include <stdio.h>


using namespace DAGAN;

//��FC18�������������ļ�
void outputResult(Game& game, vector<Player_Code>& players) {
	//�޸�Ϊ��׼�������������� ���� swn_sxt
	vector<int> score = game.getScore();
	for (size_t i = 0; i < score.size(); ++i){
		printf("%d ", score[i]);
	}
	fflush(stdout);
	/*
	ofstream ofs("../log_txt/result.txt",ios::trunc);//��txt�ļ�

	vector<TPlayerID> rank = game.getRank();   //��Ϸ�������(vector)
	for (size_t i = 0; i < rank.size(); ++i) {
		if (rank[i] > players.size() || rank[i] <= 0) continue;
		ofs << " rank��" << i + 1 << " --> " << players[rank[i] - 1].getName() << endl;   //���������ÿ�����ε����name
	}
	*/
}

int main(int argc, char** argv)
{
	//char buffer[1024];
	time_t t = time(0);//��¼ʱ��
	//strftime(buffer, sizeof(buffer), "../log_txt/log_%Y%m%d_%H%M%S.txt", localtime(&t));
#ifdef FC15_DEBUG
	//freopen(buffer, "w", stdout);  //Debugģʽ��д���µ�txt���ļ�
#endif // FC15_DEBUG
	char log_filename[1024];
	//�ɴ���//strftime(json_filename, sizeof(json_filename), "../log_json/log_%Y%m%d_%H%M%S.json", localtime(&t));
	//strftime(log_filename, sizeof(log_filename), "record", localtime(&t));
	//if (0 != _access(log_filename, 0)) _mkdir(log_filename);
	//�ĸ����� ���� swm_Sxt
	string  config_filename = "config18.ini";
	/*
#ifdef _MSC_VER
		//�ɴ���//"../config_msvc.ini";
		"../config18_msvc.ini";
#endif
#ifdef __GNUC__
		//�ɴ���//"../config_gnu.ini";
		"../config18_gnu.ini";
#endif
	if (argc == 2) {
		config_filename = argv[1];
	}
	else if (argc >= 2) {
#ifdef OUTPUT_DETAIL
		cout << "usage:												" << endl
			<< "DAGAN						Load config file	" << endl;
#endif
	}
	*/

	//��txt�浵�ļ�����������
	string cmd_txt_name = "log_info.txt";
	string info_txt_name = "everyround_info.txt";
	ofstream cmdWriter(cmd_txt_name, ios::app);
	ofstream infoWriter(info_txt_name, ios::app);
	char bufferTXT[64];
	sprintf(bufferTXT, "round %d\n", 0);
	cmdWriter << bufferTXT;
	infoWriter << bufferTXT;


	vector<Player_Code>  players;                       //��FC18�����AI������
	string          map_filename;                       //��FC18����Ϸ��ͼ�ļ���
	vector<string>  players_filename;                   //��FC18�����AI�ļ���
	vector<string>  players_name;                       //��FC18��������������ڳ�ʼ��
	int player_size;                                    //��FC18��Game�е��������

	// load config file
	ifstream ifs(config_filename.c_str());
	if (!ifs.is_open()) {
#ifdef OUTPUT_DETAIL
		cout << "Failed to load \"" << config_filename << "\". Aborted. " << endl;
#endif
		return 1;
	}

	// read config file
	//�����ļ�
	//��һ�У���ͼ�ļ�·��
	//�ڶ��У��������
	//�����У�ÿ����ҵ�ai·��
	ifs >> map_filename >> player_size;
	int cnt = 0;
	while (!ifs.eof() && cnt < player_size) {
		string player_filename;
		ifs >> player_filename;
		if (!player_filename.empty()) players_filename.push_back(player_filename);
		cnt++;
	}
	if (players_filename.size() == 0) {
#ifdef OUTPUT_DETAIL
		cout << "[Error] player_ai file names expected." << endl;
#endif
		return 2;
	}
	else if (players_filename.size() != player_size)
	{
#ifdef OUTPUT_DETAIL
		cout << "[Error]" << player_size << " player_ai file required." << endl;
#endif
		return 3;
	}


	//�������AI����
	int valid_cnt = 0; //��Чai������
	for (size_t i = 0; i < players_filename.size(); ++i) {
		//�ɴ���//Player_Code player(players_filename[i], i);
		Player_Code player(players_filename[i], i + 1);                     //�����Ŵ�1 ��ʼ
		string player_name;
		if (ifs >> player_name && !player_name.empty())
			player.setName(player_name);
		if (player.isValid())                //���ai��all���سɹ��᷵��true
		{
			players.push_back(player);
			players_name.push_back(player_name);
			valid_cnt++;
		}
		else {
			players.push_back(player); //ѹ��ȥ��������ʱ���ai�������ValidΪfalse
			cout << "[Warning] failed to load player_ai " << players_filename[i] << endl;
			player.setName(player.getName() + "//NOT_VALID");
			players_name.push_back(player_name+"[N/A]");
#if (defined _MSC_VER && defined _DEBUG)
			//system("pause");
#endif
		}
	}
	//�ɴ���//if (players.size() <= 1) {
		//�ɴ���//cout << "[Error] Not enough player_ais to start the game." << endl;
		//�ɴ���//return 5;
	//�ɴ���//}
	if (players.size() != 4) 
	{
#ifdef OUTPUT_DETAIL
		cout << "[Error] Player num not accord with requirements!\n";
		cout << "Player num should be 4, however, there are " << players.size() << " players." << endl;
#endif
		return 5;
	}
#ifdef OUTPUT_DETAIL
	cout << "[Info] " << valid_cnt << " players loaded." << endl;
#endif


	// load map
	//��ʼ����ͼ����ҵ��������򡢷����������ŵ���ս��ϵ���ȵ�
	Game G;
	if (!G.init(map_filename, log_filename, players_name,cmdWriter,infoWriter)) {
#ifdef OUTPUT_DETAIL
		cout << "[Error] failed to load " << map_filename << endl;
#endif
		return 4;
	}


	// game and controller

	Controller controller(G, players);

	//�ɴ���//for (int i = 0; i < players.size(); i++)
	//�ɴ���//{
		//�ɴ���//controller.getData()->root["head"]["playerInfo"][i]["name"] = players[i].getName();
		//�ɴ���//controller.getData()->commandJsonRoot["head"]["playerInfo"][i]["name"] = players[i].getName();
	//�ɴ���//}
	// main
	//һ���غ�һ���غϵ���
	//system("pause");
	while (controller.isValid())
	{
		for (int i = 1; i <= 4; i++)
		{
			controller.run(i,cmdWriter,infoWriter);   //ÿ������������У��������ID�����и����ָ��
			if (G.goNext() == false ) {
				break;
			}
		}
		//�ɴ���//controller.run(json_filename);
	}


	// output the result
	cmdWriter.close();
	infoWriter.close();
	outputResult(G, players);
	//G.printJson();

	return 0;

}
