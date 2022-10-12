#ifndef PLANTS_H
#define PLANTS_H

enum PlantType { NOPLANT = 0, SUNFLOWER, WINTERPEASHOOTER, PEASHOOTER, SMALLNUT, PEPPER, SQUASH }; // ֲ������

class plants {
protected:
	int SUN;//����
	int HP;//Ѫ��
	int DPS;//�˺�
	int Posi_x;//xλ��
	int Posi_y;//yλ��
	int CD_plant;//��ֲ��ȴ
	int CD_attack;//������ȴ
	int Time_plant;//��¼��ʼ��ֲ��ʱ��
	int Index = -1;//ֲ����
	bool able_attack = true;//��¼���غ��Ƿ��ܹ�����
	int attack_CD_step = 0;//Ŀǰ�Ѿ���ȴ�Ĺ����غ���
	// bool able_plant = true;//��¼���غ��ܷ���ֲ
	// int plant_CD_step = 0;//Ŀǰ�Ѿ���ȴ����ֲ�غ���
public:
	plants(int sun, int hp, int dps, int cd_plant, int cd_attack, int time_plant, int posix, int posiy, int index) {
		SUN = sun; HP = hp; DPS = dps; CD_attack = cd_attack; CD_plant = cd_plant; Time_plant = time_plant; Posi_x = posix; Posi_y = posiy; Index = index;
		able_attack = true; attack_CD_step = 0;
	}
	int getIndex(int PlantIndex = -1) {
		if (PlantIndex != -1)
		{
			this->Index = PlantIndex;
		}
		return this->Index;
	};//���ġ��鿴��ǰֲ���ţ��鿴ʱ��������
	int getHP() { return this->HP; };//�鿴��ǰѪ��
	int getSun() { return this->SUN; };
	int getHurt(int attack) { this->HP -= attack; if (this->HP < 0)this->HP = 0; return this->HP; };//�ܵ���ʬ�˺����ô˺���
	int getDPS() { return DPS; };//�鿴�˺�
	int getCD_plant() { return CD_plant; };//�鿴��ֲ��ȴʱ��
	int getCD_attack() { return CD_attack; };//�鿴������ȴʱ��
	int getTime_plant() { return Time_plant; };//�鿴��ֲʱ��
	int getx() { return Posi_x; };//�鿴x����
	int gety() { return Posi_y; };//�鿴y����
	bool get_able_attack() { return able_attack; };//�鿴�ܷ񹥻�
	// bool get_able_plant() { return able_plant; }; //�鿴�ܷ���ֲ
	//ÿ�غϸ��¹���CD
	void renew_attack_CD() {
		attack_CD_step += 1;
		if (attack_CD_step > CD_attack) {
			attack_CD_step = 0;
			able_attack = true;
		}
	};
	//����ʱ���ã����¿�ʼ��ȴ
	virtual void attack() { able_attack = false; attack_CD_step = 0; };
	// //ÿ�غϸ�����ֲCD
	// void renew_plant_CD() {
	// 	plant_CD_step += 1;
	// 	// able_plant = false;
	// 	if(plant_CD_step > CD_plant){
	// 		plant_CD_step = 0;
	// 		able_plant = true;
	// 	}		
	// };
	// //��ֲʱ���ã����¿�ʼ��ȴ
	// void plant(){able_plant = false; plant_CD_step = 0;};
	virtual PlantType getPlant_Type() = 0; // �鿴ֲ������
	virtual int GetOrignalHP() = 0;
};

class Sunflower :public plants {
public:
	Sunflower(int t, int x, int y, int index) :plants(50, 300, 0, 10, 20, t, x, y, index) { Sun_Produce = 25; IfProduced = false; };//tΪ������ֲ��ʱ����Ĺ���ʱ��,x,yΪλ�á�
	int getSun_Produce() { return Sun_Produce; }
	PlantType getPlant_Type() {
		return SUNFLOWER;
	}
	bool IfProduced;
	void attack()
	{
		IfProduced = true;
		able_attack = false; attack_CD_step = 0;
	}
	int GetOrignalHP()
	{
		return 300;
	}
private:
	int Sun_Produce;
};

class WinterPeaShooter :public plants {
public:
	WinterPeaShooter(int t, int x, int y, int index) :plants(400, 300, 60, 30, 3, t, x, y, index) {};//tΪ������ֲ��ʱ����Ĺ���ʱ��,x,yΪλ�á�
	PlantType getPlant_Type() {
		return WINTERPEASHOOTER;
	}
	int GetOrignalHP()
	{
		return 300;
	}
private:
};

class PeaShooter :public plants {
public:
	PeaShooter(int t, int x, int y, int index) :plants(100, 300, 20, 10, 2, t, x, y, index) {};//tΪ������ֲ��ʱ����Ĺ���ʱ��,x,yΪλ�á�
	PlantType getPlant_Type() {
		return PEASHOOTER;
	}
	int GetOrignalHP()
	{
		return 300;
	}
private:
};

class SmallNut :public plants {
public:
	SmallNut(int t, int x, int y, int index) :plants(50, 4000, 0, 40, 0, t, x, y, index) {};//tΪ������ֲ��ʱ����Ĺ���ʱ��,x,yΪλ�á�
	PlantType getPlant_Type() {
		return SMALLNUT;
	}
	int GetOrignalHP()
	{
		return 4000;
	}
private:
};

class Pepper :public plants {
public:
	Pepper(int t, int x, int y, int index) :plants(125, 300, 1800, 60, 0, t, x, y, index) {};//tΪ������ֲ��ʱ����Ĺ���ʱ��,x,yΪλ�á�
	PlantType getPlant_Type() {
		return PEPPER;
	}
	void attack()
	{
		this->HP = 0;
	}
	int GetOrignalHP()
	{
		return 300;
	}
private:
};

class Squash :public plants {
public:
	Squash(int t, int x, int y, int index) :plants(50, 300, 1800, 60, 0, t, x, y, index) {};//tΪ������ֲ��ʱ����Ĺ���ʱ��,x,yΪλ�á�
	PlantType getPlant_Type() {
		return SQUASH;
	}
	int GetOrignalHP()
	{
		return 300;
	}
	void attack()
	{
		this->HP = 0;
	}
private:
};

#endif // !PLANTS_H