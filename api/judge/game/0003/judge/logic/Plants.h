#ifndef PLANTS_H
#define PLANTS_H

enum PlantType { NOPLANT = 0, SUNFLOWER, WINTERPEASHOOTER, PEASHOOTER, SMALLNUT, PEPPER, SQUASH }; // 植物种类

class plants {
protected:
	int SUN;//阳光
	int HP;//血量
	int DPS;//伤害
	int Posi_x;//x位置
	int Posi_y;//y位置
	int CD_plant;//种植冷却
	int CD_attack;//攻击冷却
	int Time_plant;//记录初始种植的时刻
	int Index = -1;//植物编号
	bool able_attack = true;//记录本回合是否能够攻击
	int attack_CD_step = 0;//目前已经冷却的攻击回合数
	// bool able_plant = true;//记录本回合能否种植
	// int plant_CD_step = 0;//目前已经冷却的种植回合数
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
	};//更改、查看当前植物编号，查看时无需输入
	int getHP() { return this->HP; };//查看当前血量
	int getSun() { return this->SUN; };
	int getHurt(int attack) { this->HP -= attack; if (this->HP < 0)this->HP = 0; return this->HP; };//受到僵尸伤害调用此函数
	int getDPS() { return DPS; };//查看伤害
	int getCD_plant() { return CD_plant; };//查看种植冷却时间
	int getCD_attack() { return CD_attack; };//查看攻击冷却时间
	int getTime_plant() { return Time_plant; };//查看种植时间
	int getx() { return Posi_x; };//查看x坐标
	int gety() { return Posi_y; };//查看y坐标
	bool get_able_attack() { return able_attack; };//查看能否攻击
	// bool get_able_plant() { return able_plant; }; //查看能否种植
	//每回合更新攻击CD
	void renew_attack_CD() {
		attack_CD_step += 1;
		if (attack_CD_step > CD_attack) {
			attack_CD_step = 0;
			able_attack = true;
		}
	};
	//攻击时调用，重新开始冷却
	virtual void attack() { able_attack = false; attack_CD_step = 0; };
	// //每回合更新种植CD
	// void renew_plant_CD() {
	// 	plant_CD_step += 1;
	// 	// able_plant = false;
	// 	if(plant_CD_step > CD_plant){
	// 		plant_CD_step = 0;
	// 		able_plant = true;
	// 	}		
	// };
	// //种植时调用，重新开始冷却
	// void plant(){able_plant = false; plant_CD_step = 0;};
	virtual PlantType getPlant_Type() = 0; // 查看植物种类
	virtual int GetOrignalHP() = 0;
};

class Sunflower :public plants {
public:
	Sunflower(int t, int x, int y, int index) :plants(50, 300, 0, 10, 20, t, x, y, index) { Sun_Produce = 25; IfProduced = false; };//t为构建该植物时输入的构建时刻,x,y为位置。
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
	WinterPeaShooter(int t, int x, int y, int index) :plants(400, 300, 60, 30, 3, t, x, y, index) {};//t为构建该植物时输入的构建时刻,x,y为位置。
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
	PeaShooter(int t, int x, int y, int index) :plants(100, 300, 20, 10, 2, t, x, y, index) {};//t为构建该植物时输入的构建时刻,x,y为位置。
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
	SmallNut(int t, int x, int y, int index) :plants(50, 4000, 0, 40, 0, t, x, y, index) {};//t为构建该植物时输入的构建时刻,x,y为位置。
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
	Pepper(int t, int x, int y, int index) :plants(125, 300, 1800, 60, 0, t, x, y, index) {};//t为构建该植物时输入的构建时刻,x,y为位置。
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
	Squash(int t, int x, int y, int index) :plants(50, 300, 1800, 60, 0, t, x, y, index) {};//t为构建该植物时输入的构建时刻,x,y为位置。
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