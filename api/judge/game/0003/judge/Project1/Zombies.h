#ifndef ZOMBIES_H
#define ZOMBIES_H
#include <iostream>

#include "cmath"



enum ZombieType { NOZOMBIE = 0, NORMAL, BUCKET, POLEVAULT, SLED, GARGANTUAR }; //僵尸种类
const int infinity = 4000;
const float improvement = 1.0; //线性增长数值调控
const int rowsize = 10;//行规格

//注：该脚本所有僵尸的冷却时间均是自由定义，需后期校验更正
class zombies {
protected:
	
	int SUN;//阳光
	int HP;//血量
	int Lost_HP;
	int Original_HP;
	int Improved_HP;
	int DPS;//伤害
	int Improved_DPS;
	int Original_DPS;
	int Posi_x;//x位置（整数，与格子对应）
	float x;//x浮点坐标（浮点数）；Posi_x是x向下取整
	int Posi_y;//y位置（整数，与格子对应）
	int CD_zombie;//放置冷却
	int CD_attack;//攻击冷却
	int Time_zombie;//记录已经放置僵尸的时间
	float Speed;//（当前的）移动速度，输入时输入走完一格所需步数，初始时编译为移动速度
	float Original_Speed;//未被冰冻减速时的速度
	float Improved_Speed;
	int No_Frozen_DPS;//未被冰冻时的攻击伤害
	int Index = -1;//僵尸编号
	int type = 0;//僵尸类型
	bool IsFrozen;
	int FrozenTime;
	bool able_plant = true;//本回合能否放置僵尸
	// bool able_attack = true;//本回合能否攻击
	// int attack_CD_step = 0;//已经攻击冷却的回合数
	int plant_CD_step = 0;//已经放置冷却的回合数（好像和CD_attack重了？）
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
	};//更改、查看当前僵尸编号，查看时无需输入
	int getHP() { return this->HP; };//查看当前血量
	int getSun() { return this->SUN; };
	virtual int getHurt(int attack) { this->Lost_HP += attack; HP = Original_HP - Lost_HP + Improved_HP; return this->HP; };//受到伤害调用此函数，血量减少
	int getDPS() { return DPS; };//查看伤害
	int getCD_zombie() { return CD_zombie; };//查看放置冷却时间
	int getCD_attack() { return CD_attack; };//查看攻击冷却时间
	int getTime_zombie() { return Time_zombie; };//查看已放置时间
	float getfx() { return x; };
	float getspeed() { return Speed; }//查看速度
	virtual void Improve(int t) = 0;
	int getx() { return Posi_x; };//查看x坐标
	int gety() { return Posi_y; };//查看y坐标
	// bool get_able_attack() { return able_attack; };//查看能否攻击
	bool get_able_plant() { return able_plant; }; //查看能否种植
	void move() { x -= this->Speed; Posi_x = floor(x + 0.001 * (x > 0)); };//僵尸移动函数,向左移动故用-号；同时更新两种x坐标
	// //每回合更新攻击CD
	// void renew_attack_CD() {
	// 	attack_CD_step += 1;
	// 	if(attack_CD_step > CD_attack){
	// 		attack_CD_step = 0;
	// 		able_attack = true;
	// 	}
	// };
	// //攻击时调用，重新开始冷却
	// void attack(){able_attack = false; attack_CD_step = 0;};
	//每回合更新种植CD
	// void renew_plant_CD() {
	// 	plant_CD_step += 1;
	// 	// able_plant = false;
	// 	if(plant_CD_step > CD_zombie){
	// 		plant_CD_step = 0;
	// 		able_plant = true;
	// 	}		
	// };
	// //放置时调用，重新开始冷却
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
				Speed = Original_Speed;
				DPS = Original_DPS + Improved_DPS;
			}
		}
	}
	virtual ZombieType getZombie_Type() = 0; // 查看僵尸种类函数
	// virtual void Pole(){};
	// virtual void slowdown(){};
};

class NormalZombies :public zombies {
public:
	NormalZombies(int t, int y, int index) :zombies(50, 270, 75, 15, 10, 5.0, t, rowsize, y, index) {};//t为构建该僵尸时输入的构建时刻,x固定为行边界，y为位置。
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
};//普通僵尸

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
	};//t为构建该僵尸时输入的构建时刻,x固定为行边界，y为位置。。
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
	};//铁桶僵尸先破坏铁桶再扣血
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
};//铁通僵尸

class PolevaultZombies :public zombies {
public:
	PolevaultZombies(int t, int y, int index) :zombies(125, 200, 75, 20, 10, 2.5, t, rowsize, y, index) { Ifpole = 1; };//t为构建该僵尸时输入的构建时刻,x固定为行边界，y为位置。
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
	bool Ifpole;//表示是否跳过第一株植物
};//撑杆跳僵尸

class SledZombies :public zombies {
public:
	SledZombies(int t, int y, int index) :zombies(300, 1600, infinity, 25, 10, 3.0, t, rowsize, y, index) { Ifsled = 1; };//t为构建该僵尸时输入的构建时刻,x固定为行边界，y为位置。
	void slowdown() { if (this->Posi_x > 6) this->Original_Speed = 0.125 + ((float)5 / (float)24) * (this->Posi_x - 6.0) / 4.0; else this->Original_Speed = 0.125; };//雪橇车减速函数，参数需要调整
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
};//雪橇车僵尸

class gargantuar :public zombies {
public:
gargantuar(int t, int y, int index) :zombies(300, 3000, infinity, 25, 10, 5.0, t, rowsize, y, index) {};//t为构建该僵尸时输入的构建时刻,x固定为行边界，y为位置。
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