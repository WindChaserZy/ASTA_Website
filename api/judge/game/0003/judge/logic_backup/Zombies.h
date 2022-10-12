#ifndef ZOMBIES_H
#define ZOMBIES_H
#include <iostream>

#include "cmath"



enum ZombieType { NOZOMBIE = 0, NORMAL, BUCKET, POLEVAULT, SLED, GARGANTUAR }; //��ʬ����
const int infinity = 4000;
const float improvement = 1.0; //����������ֵ����
const int rowsize = 10;//�й��

//ע���ýű����н�ʬ����ȴʱ��������ɶ��壬�����У�����
class zombies {
protected:
	
	int SUN;//����
	int HP;//Ѫ��
	int Lost_HP;
	int Original_HP;
	int Improved_HP;
	int DPS;//�˺�
	int Improved_DPS;
	int Original_DPS;
	int Posi_x;//xλ�ã�����������Ӷ�Ӧ��
	float x;//x�������꣨����������Posi_x��x����ȡ��
	int Posi_y;//yλ�ã�����������Ӷ�Ӧ��
	int CD_zombie;//������ȴ
	int CD_attack;//������ȴ
	int Time_zombie;//��¼�Ѿ����ý�ʬ��ʱ��
	float Speed;//����ǰ�ģ��ƶ��ٶȣ�����ʱ��������һ�����貽������ʼʱ����Ϊ�ƶ��ٶ�
	float Original_Speed;//δ����������ʱ���ٶ�
	float Improved_Speed;
	int No_Frozen_DPS;//δ������ʱ�Ĺ����˺�
	int Index = -1;//��ʬ���
	int type = 0;//��ʬ����
	bool IsFrozen;
	int FrozenTime;
	bool able_plant = true;//���غ��ܷ���ý�ʬ
	// bool able_attack = true;//���غ��ܷ񹥻�
	// int attack_CD_step = 0;//�Ѿ�������ȴ�Ļغ���
	int plant_CD_step = 0;//�Ѿ�������ȴ�Ļغ����������CD_attack���ˣ���
public:
	zombies(int sun, int hp, int dps, int cd_plant, int cd_attack, float speed, int time_plant, int posix, int posiy, int index) {
		SUN = sun; Original_HP = hp; Original_DPS = dps; CD_attack = cd_attack; CD_zombie = cd_plant; Time_zombie = time_plant; Posi_x = posix; x = posix; Posi_y = posiy; Speed = 1.0 / speed; Index = index;
		Original_Speed = Speed; IsFrozen = false; FrozenTime = -1;
		Lost_HP = 0;
		if (time_plant >= 1000) {
			Improved_DPS = ((double)(improvement * (time_plant - 1000))/1000)*(Original_DPS);
			Improved_HP= ((double)(improvement * (time_plant - 1000)) / 1000) * (Original_HP);
		}
		else {
			Improved_DPS = 0;
			Improved_HP = 0;
			Improved_Speed = 0;
		}
		HP = Original_HP  + Improved_HP - Lost_HP;
		DPS = Original_DPS + Improved_DPS;
		Speed = Original_Speed;
		No_Frozen_DPS = DPS;
	};
	int getIndex(int ZombieIndex = -1) {
		if (ZombieIndex != -1)
		{
			this->Index = ZombieIndex;
		}
		return this->Index;
	};//���ġ��鿴��ǰ��ʬ��ţ��鿴ʱ��������
	int getHP() { return this->HP; };//�鿴��ǰѪ��
	int getSun() { return this->SUN; };
	virtual int getHurt(int attack) { this->Lost_HP += attack; HP = Original_HP - Lost_HP; return this->HP; };//�ܵ��˺����ô˺�����Ѫ������
	int getDPS() { return DPS; };//�鿴�˺�
	int getCD_zombie() { return CD_zombie; };//�鿴������ȴʱ��
	int getCD_attack() { return CD_attack; };//�鿴������ȴʱ��
	int getTime_zombie() { return Time_zombie; };//�鿴�ѷ���ʱ��
	float getfx() { return x; };
	float getspeed() { return Speed; }//�鿴�ٶ�
	virtual void Improve(int t) = 0;
	int getx() { return Posi_x; };//�鿴x����
	int gety() { return Posi_y; };//�鿴y����
	// bool get_able_attack() { return able_attack; };//�鿴�ܷ񹥻�
	bool get_able_plant() { return able_plant; }; //�鿴�ܷ���ֲ
	void move() { x -= this->Speed; Posi_x = floor(x); };//��ʬ�ƶ�����,�����ƶ�����-�ţ�ͬʱ��������x����
	// //ÿ�غϸ��¹���CD
	// void renew_attack_CD() {
	// 	attack_CD_step += 1;
	// 	if(attack_CD_step > CD_attack){
	// 		attack_CD_step = 0;
	// 		able_attack = true;
	// 	}
	// };
	// //����ʱ���ã����¿�ʼ��ȴ
	// void attack(){able_attack = false; attack_CD_step = 0;};
	//ÿ�غϸ�����ֲCD
	// void renew_plant_CD() {
	// 	plant_CD_step += 1;
	// 	// able_plant = false;
	// 	if(plant_CD_step > CD_zombie){
	// 		plant_CD_step = 0;
	// 		able_plant = true;
	// 	}		
	// };
	// //����ʱ���ã����¿�ʼ��ȴ
	// void plant(){able_plant = false; plant_CD_step = 0;};
	void frozen()
	{
		IsFrozen = true;
		FrozenTime = 0;
	}
	void unfrozen() {
		
		if (IsFrozen) {
			FrozenTime++;
			if (FrozenTime > 20) {
				IsFrozen = false;
				Speed = Original_Speed + Improved_Speed;
				DPS = Original_DPS + Improved_DPS;
			}
		}
	}
	virtual ZombieType getZombie_Type() = 0; // �鿴��ʬ���ຯ��
	// virtual void Pole(){};
	// virtual void slowdown(){};
};

class NormalZombies :public zombies {
public:
	NormalZombies(int t, int y, int index) :zombies(50, 270, 75, 15, 10, 5.0, t, rowsize, y, index) {};//tΪ�����ý�ʬʱ����Ĺ���ʱ��,x�̶�Ϊ�б߽磬yΪλ�á�
	ZombieType getZombie_Type() {
		return NORMAL;
	}
	void Improve(int t)
	{
		if (t >= 1000) {
			Improved_DPS = ((double)(improvement * (t - 1000)) / 1000) * (Original_DPS);
			Improved_HP = ((double)(improvement * (t - 1000)) / 1000) * (Original_HP);
		}
		HP = Improved_HP + Original_HP - Lost_HP;
		DPS = Original_DPS + Improved_DPS;
		if (IsFrozen) {
			Speed = this->Original_Speed / 2;
			DPS = (this->Original_DPS + this->Improved_DPS) / 2;
		}
	}
};//��ͨ��ʬ

class BucketZombies :public zombies {
private:
	int BucketHp;
	int Original_BucketHp;
	int Lost_BucketHp;
	int Improved_BucketHp;
public:
	BucketZombies(int t, int y, int index) :zombies(125, 270, 75, 20, 10, 5.0, t, rowsize, y, index)
	{
		Original_BucketHp = 550;
		Lost_BucketHp = 0;
		if(t > 1000)
		{
			Improved_BucketHp = (float)(t - 1000) / 1000.0 * (float)Original_BucketHp;
		}
		else
		{
			Improved_BucketHp = 0;
		}
		BucketHp = Original_BucketHp + Improved_BucketHp;
	};//tΪ�����ý�ʬʱ����Ĺ���ʱ��,x�̶�Ϊ�б߽磬yΪλ�á���
	int getHurt(int attack) {
		if (this->BucketHp > 0)
		{
			if (this->BucketHp > attack) {
				this->BucketHp -= attack;
				this->Lost_BucketHp += attack;
				return this->BucketHp + this->HP;
			}
			this->BucketHp = 0;

			this->Lost_HP += attack - this->BucketHp;
			this->HP = this->Original_HP + this->Improved_HP - this->Lost_HP;
			return this->HP;
		}
		else
		{
			this->Lost_HP += attack;
			this->HP = this->Original_HP + this->Improved_HP - this->Lost_HP;
			return this->HP;
		}
	};//��Ͱ��ʬ���ƻ���Ͱ�ٿ�Ѫ
	int Bucket() { return BucketHp; }
	ZombieType getZombie_Type() {
		return BUCKET;
	}
	void Improve(int t)
	{
		if (t >= 1000) {
			Improved_DPS = ((double)(improvement * (t - 1000)) / 1000) * (Original_DPS);
			Improved_HP = ((double)(improvement * (t - 1000)) / 1000) * (Original_HP);
			if(this->BucketHp > 0)
			{
				Improved_BucketHp = ((double)(improvement * (t - 1000)) / 1000) * (Original_BucketHp);
			}
		}
		HP = Improved_HP + Original_HP - Lost_HP;
		DPS = Original_DPS + Improved_DPS;
		if(BucketHp > 0)
		{
			BucketHp = Improved_BucketHp + Original_BucketHp - Lost_BucketHp;
		}
		if (IsFrozen) {
			Speed = this->Original_Speed / 2;
			DPS = (this->Original_DPS + this->Improved_DPS) / 2;
		}
	}
};//��ͨ��ʬ

class PolevaultZombies :public zombies {
public:
	PolevaultZombies(int t, int y, int index) :zombies(125, 200, 75, 20, 10, 2.5, t, rowsize, y, index) { Ifpole = 1; };//tΪ�����ý�ʬʱ����Ĺ���ʱ��,x�̶�Ϊ�б߽磬yΪλ�á�
	void Pole() { this->Ifpole = false; this->Original_Speed = 1.0 / 4.5; this->x -= 1.0; this->Posi_x -= 1; };
	bool get_Ifpole() { return this->Ifpole; }
	ZombieType getZombie_Type() {
		return POLEVAULT;
	}
	void Improve(int t)
	{
		if (t >= 1000) {
			Improved_DPS = ((double)(improvement * (t - 1000)) / 1000) * (Original_DPS);
			Improved_HP = ((double)(improvement * (t - 1000)) / 1000) * (Original_HP);
		}
		HP = Improved_HP + Original_HP - Lost_HP;
		DPS = Original_DPS + Improved_DPS;
		Speed = Original_Speed;
		if (IsFrozen) {
			Speed = this->Original_Speed / 2;
			DPS = (this->Original_DPS + this->Improved_DPS) / 2;
		}
	}
private:
	bool Ifpole;//��ʾ�Ƿ�������һ��ֲ��
};//�Ÿ�����ʬ

class SledZombies :public zombies {
public:
	SledZombies(int t, int y, int index) :zombies(300, 1600, infinity, 25, 10, 3.0, t, rowsize, y, index) { Ifsled = 1; };//tΪ�����ý�ʬʱ����Ĺ���ʱ��,x�̶�Ϊ�б߽磬yΪλ�á�
	void slowdown() { if (this->Posi_x > 6) this->Original_Speed = 0.125 + ((float)5 / (float)24) * (this->Posi_x - 6.0) / 4.0; else this->Original_Speed = 0.125; };//ѩ�������ٺ�����������Ҫ����
	ZombieType getZombie_Type() {
		return SLED;
	}
	void Improve(int t)
	{
		slowdown();
		Improved_DPS = 0;
		if (t >= 1000) {
			Improved_HP = ((double)(improvement * (t - 1000)) / 1000) * (Original_HP);
		}
		HP = Improved_HP + Original_HP - Lost_HP;
		DPS = Original_DPS;
		Speed = Original_Speed;
		if (IsFrozen) {
			Speed = this->Original_Speed/2;
		}
	}
private:
	bool Ifsled;
};//ѩ������ʬ

class gargantuar :public zombies {
public:
gargantuar(int t, int y, int index) :zombies(300, 3000, infinity, 25, 10, 5.0, t, rowsize, y, index) {};//tΪ�����ý�ʬʱ����Ĺ���ʱ��,x�̶�Ϊ�б߽磬yΪλ�á�
	ZombieType getZombie_Type() {
		return GARGANTUAR;
	}
	void Improve(int t)
	{
		Improved_DPS = 0;
		if (t >= 1000) {
			Improved_HP = ((double)(improvement * (t - 1000)) / 1000) * (Original_HP);
		}
		HP = Improved_HP + Original_HP - Lost_HP;
		DPS = Original_DPS;
		if (IsFrozen) {
			Speed = this->Original_Speed / 2;
		}
	}
private:
};//

#endif // !ZOMBIES_H
