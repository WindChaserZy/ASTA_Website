/**
 * This file is preprocessed by an amalgamater
 * to protect its copyright
 *
 * Please do not try to parse it
 * 
 * Amalgamater is written by Futrime<https://github.com/Futrime>
 */

#include "ai.h"

/**
 * @file 0.empty.ai.cpp
 * @author Futrime (futrime@outlook.com)
 * @brief Empty AI
 * @details This AI does nothing. It is for testing.
 * @version 1.0.0
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022 Futrime
 *
 */

#include <iostream>


/*** Start of inlined file: Game.cpp ***/
// #define ZOMBIE_TRACKING

#ifndef __GAME_CPP__
#define __GAME_CPP__

#include <algorithm>
#include <bitset>
#include <cmath>
#include <exception>
#include <iostream>
#include <string>
#include <vector>


/*** Start of inlined file: ai.h ***/
#ifndef _FC19_AI_H_
#define _FC19_AI_H_

/*** Start of inlined file: Interface.h ***/
#ifndef INTERFACE_H_
#define INTERFACE_H_
class ICamp
{
public:
	virtual int** getCurrentPlants() = 0;
	virtual int*** getCurrentZombies() = 0;
	virtual int getSun() = 0;
	virtual int* getPlantCD() = 0;
	virtual int* getLeftLines() = 0;
	virtual int getRows() = 0;
	virtual int getColumns() = 0;
	virtual int getCurrentType() = 0;
};
class IPlayer
{
public:
	ICamp* Camp;
	virtual void PlacePlant(int type, int x, int y) = 0;
	virtual void PlaceZombie(int type, int y) = 0;
	virtual int getTime() = 0;
	virtual int getScore() = 0;
	virtual int getKillPlantsScore() = 0;
	virtual int getKillZombiesScore() = 0;
	virtual int getNotBrokenLines() = 0;
	virtual int getBrokenLinesScore() = 0;
	virtual int getLeftPlants() = 0;
	virtual void removePlant(int x, int y) = 0;
};

#endif
/*** End of inlined file: Interface.h ***/


#ifdef _MSC_VER
extern "C" _declspec(dllexport) void  player_ai(IPlayer * Player);
#endif

#ifdef __GNUC__
extern "C" void player_ai(IPlayer * _Player);
#endif

#endif
/*** End of inlined file: ai.h ***/


/*** Start of inlined file: Entity.cpp ***/
#ifndef __ENTITY_CPP__
#define __ENTITY_CPP__

#include <string>


/*** Start of inlined file: Utility.cpp ***/
#ifndef __UTILITY_CPP__
#define __UTILITY_CPP__

#include <bitset>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

const struct
{
	int PLANT = 0;
	int ZOMBIE = 1;
} CAMP;

const struct
{
	int NOPLANT = 0;
	int SUNFLOWER = 1;
	int WINTERPEASHOOTER = 2;
	int PEASHOOTER = 3;
	int SMALLNUT = 4;
	int PEPPER = 5;
	int SQUASH = 6;
} PLANT;

const string PLANT_STRING[7] = {"NOPLANT", "SUNFLOWER", "WINTERPEASHOOTER", "PEASHOOTER", "SMALLNUT", "PEPPER", "SQUASH"};

const struct
{
	int NOZOMBIE = 0;
	int NORMAL = 1;
	int BUCKET = 2;
	int POLEVAULT = 3;
	int SLED = 4;
	int GARGANTUAR = 5;
} ZOMBIE;

const string ZOMBIE_STRING[6] = {"NOZOMBIE", "NORMAL", "BUCKET", "POLEVAULT", "SLED", "GARGANTUAR"};

const struct
{
	int SUNFLOWER = 300;
	int WINTERPEASHOOTER = 300;
	int PEASHOOTER = 300;
	int SMALLNUT = 4000;
	int PEPPER = 300;
	int SQUASH = 300;
	int operator[](int type) const
	{
		switch (type)
		{
		case 0: // NOPLANT
			return 0;
		case 1:
			return this->SUNFLOWER;
		case 2:
			return this->WINTERPEASHOOTER;
		case 3:
			return this->PEASHOOTER;
		case 4:
			return this->SMALLNUT;
		case 5:
			return this->PEPPER;
		case 6:
			return this->SQUASH;
		}

		/* Check legality */
		if (type < 1 || type > 6)
		{
			throw string("(PLANT_HP::[]) Wrong plant type!");
		}
		return 0;
	}
} PLANT_HP;

const struct
{
	int SUNFLOWER = 50;
	int WINTERPEASHOOTER = 400;
	int PEASHOOTER = 100;
	int SMALLNUT = 50;
	int PEPPER = 125;
	int SQUASH = 50;
	int operator[](int type) const
	{
		switch (type)
		{
		case 0: // NOPLANT
			return 0;
		case 1:
			return this->SUNFLOWER;
		case 2:
			return this->WINTERPEASHOOTER;
		case 3:
			return this->PEASHOOTER;
		case 4:
			return this->SMALLNUT;
		case 5:
			return this->PEPPER;
		case 6:
			return this->SQUASH;
		}

		/* Check legality */
		if (type < 1 || type > 6)
		{
			throw string("(PLANT_COST::[]) Wrong plant type!");
		}
		return 0;
	}
} PLANT_COST;

const struct
{
	int WINTERPEASHOOTER = 60;
	int PEASHOOTER = 20;
	int PEPPER = 1800;
	int SQUASH = 1800;
	int operator[](int type) const
	{
		switch (type)
		{
		case 0: // NOPLANT
			return 0;
		case 1: // SUNFLOWER
			return 0;
		case 2:
			return this->WINTERPEASHOOTER;
		case 3:
			return this->PEASHOOTER;
		case 4: // SMALLNUT
			return 0;
		case 5:
			return this->PEPPER;
		case 6:
			return this->SQUASH;
		}

		/* Check legality */
		if (type < 1 || type > 6)
		{
			throw string("(PLANT_ATK::[]) Wrong plant type!");
		}
		return 0;
	}
} PLANT_ATK;

const struct
{
	int SUNFLOWER = 10;
	int WINTERPEASHOOTER = 30;
	int PEASHOOTER = 10;
	int SMALLNUT = 40;
	int PEPPER = 60;
	int SQUASH = 60;
	int operator[](int type) const
	{
		switch (type)
		{
		case 0: // NOPLANT
			return 0;
		case 1:
			return this->SUNFLOWER;
		case 2:
			return this->WINTERPEASHOOTER;
		case 3:
			return this->PEASHOOTER;
		case 4:
			return this->SMALLNUT;
		case 5:
			return this->PEPPER;
		case 6:
			return this->SQUASH;
		}

		/* Check legality */
		if (type < 1 || type > 6)
		{
			throw string("(PLANT_CD::[]) Wrong plant type!");
		}
		return 0;
	}
} PLANT_CD;

const struct
{
	int WINTERPEASHOOTER = 3;
	int PEASHOOTER = 2;
	int operator[](int type) const
	{
		switch (type)
		{
		case 2:
			return this->WINTERPEASHOOTER;
		case 3:
			return this->PEASHOOTER;
		}

		/* Check legality */
		if (type != 2 && type != 3)
		{
			throw string("(PLANT_PERIOD::[]) Wrong plant type!");
		}
		return 0;
	}
} PLANT_PERIOD;

const struct
{
	int NORMAL = 270;
	int BUCKET = 550 + 270;
	int POLEVAULT = 200;
	int SLED = 1600;
	int GARGANTUAR = 3000;
	int operator[](int type) const
	{
		switch (type)
		{
		case 0: // NOZOMBIE
			return 0;
		case 1:
			return this->NORMAL;
		case 2:
			return this->BUCKET;
		case 3:
			return this->POLEVAULT;
		case 4:
			return this->SLED;
		case 5:
			return this->GARGANTUAR;
		}

		/* Check legality */
		if (type < 1 || type > 5)
		{
			throw string("(ZOMBIE_HP::[]) Wrong zombie type!");
		}
		return 0;
	}
} ZOMBIE_HP;

const struct
{
	int NORMAL = 50;
	int BUCKET = 125;
	int POLEVAULT = 125;
	int SLED = 300;
	int GARGANTUAR = 300;
	int operator[](int type) const
	{
		switch (type)
		{
		case 0: // NOPLANT
			return 0;
		case 1:
			return this->NORMAL;
		case 2:
			return this->BUCKET;
		case 3:
			return this->POLEVAULT;
		case 4:
			return this->SLED;
		case 5:
			return this->GARGANTUAR;
		}

		/* Check legality */
		if (type < 1 || type > 5)
		{
			throw string("(ZOMBIE_COST::[]) Wrong zombie type!");
		}
		return 0;
	}
} ZOMBIE_COST;

const struct
{
	int NORMAL = 75;
	int BUCKET = 75;
	int POLEVAULT = 75;
	int SLED = 999999;
	int GARGANTUAR = 999999;
	int operator[](int type) const
	{
		switch (type)
		{
		case 0: // NOPLANT
			return 0;
		case 1:
			return this->NORMAL;
		case 2:
			return this->BUCKET;
		case 3:
			return this->POLEVAULT;
		case 4:
			return this->SLED;
		case 5:
			return this->GARGANTUAR;
		}

		/* Check legality */
		if (type < 1 || type > 5)
		{
			throw string("(ZOMBIE_ATK::[]) Wrong zombie type!");
		}
		return 0;
	}
} ZOMBIE_ATK;

const struct
{
	int NORMAL = 15;
	int BUCKET = 20;
	int POLEVAULT = 20;
	int SLED = 25;
	int GARGANTUAR = 25;
	int operator[](int type) const
	{
		switch (type)
		{
		case 0: // NOPLANT
			return 0;
		case 1:
			return this->NORMAL;
		case 2:
			return this->BUCKET;
		case 3:
			return this->POLEVAULT;
		case 4:
			return this->SLED;
		case 5:
			return this->GARGANTUAR;
		}

		/* Check legality */
		if (type < 1 || type > 5)
		{
			throw string("(ZOMBIE_CD::[]) Wrong zombie type!");
		}
		return 0;
	}
} ZOMBIE_CD;

const struct
{
	double DEFAULT = 0.2;
	double POLEVAULT[2] = {0.4, 0.2222222222222222};
	double SLED[5] = {0.3333333333333333, 0.28125, 0.2291666666666667, 0.1770833333333333, 0.125};
} ZOMBIE_SPEED;

template <typename T>
class Position
{
public:
	T x, y;

	/**
	 * @brief Construct a new Position object
	 *
	 */
	Position()
	{
		this->x = -1;
		this->y = -1;
	}

	/**
	 * @brief Construct a new Position object
	 *
	 * @param x
	 * @param y
	 */
	Position(T x, T y) : x(x), y(y)
	{
	}

	friend ostream& operator<<(ostream &os, Position<T> pos)
	{
		return cout << "<" << pos.x << ", " << pos.y << ">";
	}
};

class Action
{
protected:
	bitset<7> plant_switch_;
	bitset<6> zombie_switch_;
	Position<int> plant_position_[7];
	Position<int> zombie_position_[6];
	vector<Position<int>> plant_removal_;

public:
	/**
	 * @brief Construct a new Action object
	 *
	 */
	Action()
	{
	}

	/**
	 * @brief Get removal actions of plant camp
	 *
	 * @return vector<Position<int>> A vector of removal actions
	 */
	vector<Position<int>> getRemoval()
	{
		return this->plant_removal_;
	}

	/**
	 * @brief Check if a slot is set in this action
	 *
	 * @param camp The camp, either CAMP.PLANT or CAMP.ZOMBIE
	 * @param slot The slot, within [0, 6] for plant camp or [0, 5] for zombie camp
	 * @return true The slot is set
	 * @return false The slot is not set
	 */
	bool isSet(int camp, int slot)
	{
		/* Check legality */
		if (camp < 0 || camp > 1)
		{
			throw string("(Action::isSet) Invalid camp!");
		}
		if (camp == CAMP.PLANT && (slot < 0 || slot > 6))
		{
			throw string("(Action::isSet) Invalid slot!");
		}
		if (camp == CAMP.ZOMBIE && (slot < 0 || slot > 5))
		{
			throw string("(Action::isSet) Invalid slot!");
		}

		if (camp == CAMP.PLANT)
		{
			return this->plant_switch_[slot];
		}
		else if (camp == CAMP.ZOMBIE)
		{
			return this->zombie_switch_[slot];
		}

		return false; // to avoid compilation warning
	}

	/**
	 * @brief Get the target position of a slot
	 *
	 * @param camp The camp, either CAMP.PLANT or CAMP.ZOMBIE
	 * @param slot The slot, within [0, 6] for plant camp or [0, 5] for zombie camp
	 * @return Position<int> The target position
	 */
	Position<int> getPosition(int camp, int slot)
	{
		/* Check legality */
		if (camp < 0 || camp > 1)
		{
			throw string("(Action::getPosition) Invalid camp!");
		}
		if (camp == CAMP.PLANT && (slot < 0 || slot > 6))
		{
			throw string("(Action::getPosition) Invalid slot!");
		}
		if (camp == CAMP.ZOMBIE && (slot < 0 || slot > 5))
		{
			throw string("(Action::getPosition) Invalid slot!");
		}

		if (camp == CAMP.PLANT)
		{
			return this->plant_position_[slot];
		}
		else if (camp == CAMP.ZOMBIE)
		{
			return this->zombie_position_[slot];
		}

		return Position<int>(); // to avoid compilation warning
	}

	/**
	 * @brief Remove a plant. Plant placement is prior to plant removal.
	 *
	 * @param x The x position to place, within [0, 4]
	 * @param y The y position to place, within [0, 9]
	 */
	void removePlant(int x, int y)
	{
		/* Check legality */
		if (x < 0 || x > 4 || y < 0 || y > 9)
		{
			throw string("(Action::removePlant) Out of map!");
		}
		for (int i = 0; i < this->plant_removal_.size(); ++i)
		{
			if (plant_removal_[i].x == x &&
				plant_removal_[i].y == y)
			{
				throw string("(Action::removePlant) Duplicated plant removal!");
			}
		}

		this->plant_removal_.push_back(Position<int>(x, y));
	}

	/**
	 * @brief Place a plant. Plant placement is prior to plant removal.
	 *
	 * @param type The type of the plant, should be PLANT.X
	 * @param x The x position to place, within [0, 4]
	 * @param y The y position to place, within [0, 9]
	 */
	void placePlant(int type, int x, int y)
	{
		/* Check legality */
		if (type < 1 || type > 6)
		{
			throw string("(Action::placePlant) Wrong plant type!");
		}
		if (x < 0 || x > 4 || y < 0 || y > 9)
		{
			throw string("(Action::placePlant) Out of map!");
		}
		if (this->plant_switch_[type])
		{
			throw string("(Action::placePlant) Duplicated plant placement!");
		}

		this->plant_switch_[type] = true;
		this->plant_position_[type].x = x;
		this->plant_position_[type].y = y;
	}

	/**
	 * @brief Place a zombie
	 *
	 * @param type The type of the zombie, should be ZOMBIE.x
	 * @param x The x position to place, within [0, 4]
	 */
	void placeZombie(int type, int x)
	{
		/* Check legality */
		if (type < 0 || type > 5)
		{
			throw string("(Action::placeZombie) Wrong plant type!");
		}
		if (x < 0 || x > 4)
		{
			throw string("(Action::placeZombie) Out of map!");
		}
		if (this->zombie_switch_[type])
		{
			throw string("(Action::placeZombie) Duplicated zombie placement!");
		}

		this->zombie_switch_.set(type, true);
		this->zombie_position_[type].x = x;
		this->zombie_position_[type].y = 10;
	}
};

int generateID()
{
	static int id = 0;
	++id;
	return id;
}

#endif
/*** End of inlined file: Utility.cpp ***/

using namespace std;

/****************
 * Declarations
 ****************/

class Entity
{
protected:
	int spawn_time_;
	int type_;
	int hp_;
	int id_;
	Position<int> position_;

public:
	/**
	 * @brief Construct a new Entity object
	 *
	 * @param spawn_time The spawning time of the entity
	 * @param type The type of the entity, within [0, 6] for plants or [0, 5] for zombies
	 * @param position The position of the entity
	 */
	Entity(int spawn_time, int type, Position<int> position);

	/**
	 * @brief Get the spawning time of the entity
	 *
	 * @return int The spawning time
	 */
	int getSpawnTime();

	/**
	 * @brief Get the type of the entity, within [0, 6] for plants or [0, 5] for zombies
	 *
	 * @return int The type of the entity, fitting PLANT.X or ZOMBIE.X
	 */
	int getType();

	/**
	 * @brief Get the health of the entity
	 *
	 * @return int The health of the entity, >= 0
	 */
	virtual int getHealth();

	/**
	 * @brief Reduce the health of the entity
	 *
	 * @param value The number of health to reduce
	 * @return int The health left
	 */
	int reduceHealth(int value);

	/**
	 * @brief Get the position of the entity
	 *
	 * @return Position<int> The position of the entity
	 */
	Position<int> getPosition();

	/**
	 * @brief Get the id of the entity
	 *
	 * @return int The id
	 */
	int getID();
};

class Plant : public Entity
{
protected:
	int last_attack_time_ = -999999;
public:
	/**
	 * @brief Construct a new Plant object
	 *
	 */
	Plant();

	/**
	 * @brief Construct a new Plant object
	 *
	 * @param spawn_time The spawing time of the plant
	 * @param type The type of the plant
	 * @param position The position of the plant
	 */
	Plant(int spawn_time, int type, Position<int> position);

	/**
	 * @brief Get last attack time
	 *
	 * @return int Last attack time
	 */
	int getLastAttackTime();

	/**
	 * @brief Set last attack time
	 *
	 * @param time Last attack time
	 */
	void setLastAttackTime(int time);

	/**
	 * @brief Print a plant object
	 *
	 * @param oss The output stream
	 * @param plant The plant
	 * @return ostream& The result output stream
	 */
	friend ostream &operator<<(ostream &oss, Plant plant);
};

class Zombie : public Entity
{
protected:
	Position<double> position_real_;
	int state_ = 0; // Polevault and Sled's state
	int frozen_state_ = 0;
	int time_;

public:
	/**
	 * @brief Construct a new Zombie object
	 *
	 */
	Zombie();

	/**
	 * @brief Construct a new Zombie object
	 *
	 * @param spawn_time The spawning time of the zombie
	 * @param type The type of the zombie
	 * @param position The position of the zombie
	 */
	Zombie(int spawn_time, int type, Position<int> position);

	/**
	 * @brief Construct a new Zombie object
	 *
	 * @param spawn_time The spawning time of the zombie
	 * @param type The type of the zombie
	 * @param position The position of the zombie
	 */
	Zombie(int spawn_time, int type, Position<double> position);

	/**
	 * @brief Get the health of the zombie
	 *
	 * @return int The health of the zombie, >= 0
	 */
	int getHealth();

	/**
	 * @brief Set the current time for calculating health
	 *
	 * @param time The current time
	 */
	void setNowTime(int time);

	/**
	 * @brief Get the position of the zombie
	 *
	 * @return Position<int> The position of the zombie
	 */
	Position<int> getPosition();

	/**
	 * @brief Get the real position of the zombie
	 *
	 * @return Position<double> The real position of the zombie
	 */
	Position<double> getRealPosition();

	/**
	 * @brief Set the real position of the zombie
	 *
	 * @param position The real position of the zombie
	 */
	void setRealPosition(Position<double> position);

	/**
	 * @brief Get the state of the zombie
	 *
	 * @return int The state number
	 */
	int getState();

	/**
	 * @brief Set the state of the zombie
	 *
	 * @param state The state number
	 */
	void setState(int state);

	/**
	 * @brief Get if the zombie is frozen
	 *
	 * @return int The ticks from unfreezing
	 */
	int getFrozenState();

	/**
	 * @brief Set if the zombie is frozen
	 *
	 * @param state int The ticks from unfreezing
	 */
	void setFrozenState(int state);

	/**
	 * @brief Print a zombie object
	 *
	 * @param oss The output stream
	 * @param plant The zombie
	 * @return ostream& The result output stream
	 */
	friend ostream &operator<<(ostream &oss, Zombie zombie);
};

/****************
 * Definitions
 ****************/

Entity::Entity(int spawn_time, int type, Position<int> position)
	: spawn_time_(spawn_time), type_(type), position_(position), id_(generateID())
{
}

int Entity::getSpawnTime()
{
	return this->spawn_time_;
}

int Entity::getType()
{
	return this->type_;
}

int Entity::getHealth()
{
	return this->hp_;
}

int Entity::reduceHealth(int value)
{
	this->hp_ -= value;
	return this->hp_;
}

Position<int> Entity::getPosition()
{
	return this->position_;
}

int Entity::getID()
{
	return this->id_;
}

Plant::Plant() : Plant(0, PLANT.NOPLANT, Position<int>())
{
}

Plant::Plant(int spawn_time, int type, Position<int> position)
	: Entity(spawn_time, type, position)
{
	this->hp_ = PLANT_HP[type];
}

int Plant::getLastAttackTime()
{
	return this->last_attack_time_;
}

void Plant::setLastAttackTime(int time)
{
	this->last_attack_time_ = time;
}

ostream &operator<<(ostream &oss, Plant plant)
{
	oss << "Plant(type=" << PLANT_STRING[plant.getType()]
		<< ", position=" << plant.getPosition()
		<< ", health=" << plant.getHealth()
		<< ", spawn_time=" << plant.getSpawnTime()
		<< ")";
	return oss;
}

Zombie::Zombie() : Zombie(0, ZOMBIE.NOZOMBIE, Position<double>())
{
}

Zombie::Zombie(int spawn_time, int type, Position<int> position)
	: Entity(spawn_time, type, position), position_real_(position.x, position.y), time_(spawn_time)
{
	this->hp_ = ZOMBIE_HP[type];
}

Zombie::Zombie(int spawn_time, int type, Position<double> position)
	: Entity(spawn_time, type, Position<int>(static_cast<int>(position.x), static_cast<int>(position.y))), position_real_(position.x, position.y), time_(spawn_time)
{
	this->hp_ = ZOMBIE_HP[type];
}

int Zombie::getHealth()
{
	return this->hp_ + static_cast<int>(ZOMBIE_HP[this->type_] * (max(1.0, this->time_ / 1000.0) - 1.0));
	// doubt: what the fuck is the algorithm of Game.exe!
}

void Zombie::setNowTime(int time)
{
	this->time_ = time;
}

ostream &operator<<(ostream &oss, Zombie zombie)
{
	oss << "Zombie(type=" << ZOMBIE_STRING[zombie.getType()]
		<< ", position=" << zombie.getRealPosition()
		<< ", health=" << zombie.getHealth()
		<< ", spawn_time=" << zombie.getSpawnTime()
		<< ")";
	return oss;
}

Position<int> Zombie::getPosition()
{
	return this->position_;
}

Position<double> Zombie::getRealPosition()
{
	return this->position_real_;
}

void Zombie::setRealPosition(Position<double> position)
{
	this->position_.x = static_cast<int>(floor(position.x + 0.001));
	this->position_.y = static_cast<int>(floor(position.y + 0.001));
	this->position_real_.x = position.x;
	this->position_real_.y = position.y;
}

int Zombie::getState()
{
	return this->state_;
}

void Zombie::setState(int state)
{
	this->state_ = state;
}

int Zombie::getFrozenState()
{
	return this->frozen_state_;
}

void Zombie::setFrozenState(int state)
{
	this->frozen_state_ = state;
}

#endif
/*** End of inlined file: Entity.cpp ***/

using namespace std;

/****************
 * Declarations
 ****************/

class GameState
{
protected:
	/* Global Information */
	IPlayer *player_;
	int time_ = 0;
	bitset<5> broken_lines_;

	/* Camp Information */
	int camp_;
	int other_camp_;
	vector<Plant> plant_;
	vector<Zombie> zombie_;
	int sun_plant_ = 400;
	int sun_zombie_ = 299; // at tick 0
	int cd_plant_[7] = {0};
	int cd_zombie_[6] = {0};
	int score_plant_ = 0;
	int score_zombie_ = 0;

public:
	/**
	 * @brief Construct a new Game State object
	 *
	 * @param camp The current camp
	 */
	GameState(int camp);

	/**
	 * @brief Destroy the Game State object
	 *
	 */
	~GameState();

	/**
	 * @brief Get the battlefront of a line
	 *
	 * @param x The line
	 * @return int The y position of the battlefront, 10 if no zombie on this row
	 */
	int getBattlefront(int x);

	/**
	 * @brief Get the broken lines
	 *
	 * @return bitset<5> True if broken
	 */
	bitset<5> getBrokenLines();

	/**
	 * @brief Get the current camp
	 *
	 * @return int The current camp, either CAMP.PLANT or CAMP.ZOMBIE
	 */
	int getCamp();

	/**
	 * @brief Get the left cooldown time of a slot
	 *
	 * @param camp The camp
	 * @param slot The slot
	 * @return int The left cooldown time
	 */
	int getCD(int camp, int slot);

	/**
	 * @brief Get the zombie appeared earliest
	 *
	 * @param row The row to query
	 * @return Zombie The zombie, Zombie(0, ZOMBIE.NOZOMBIE, Position<double>(row, 10)) if no zombie
	 */
	Zombie getEarliestZombie(int row);

	/**
	 * @brief Get the zombie whose y position >= col and closest to the house
	 *
	 * @param row The row to query
	 * @param col The col
	 * @return Zombie The zombie, Zombie(0, ZOMBIE.NOZOMBIE, Position<double>(row, 10)) if no zombie
	 */
	Zombie getFirstZombie(int row, int col);

	/**
	 * @brief Get the other camp
	 *
	 * @return int The other camp, either CAMP.PLANT or CAMP.ZOMBIE
	 */
	int getOtherCamp();

	/**
	 * @brief Get the plant at the position
	 *
	 * @param x The x position
	 * @param y The y position
	 * @return Plant The plant
	 */
	Plant getPlant(int x, int y);

	/**
	 * @brief Get plants fitting the query
	 *
	 * @param x The x position, -1 for all (optional)
	 * @param y The y position, -1 for all (optional)
	 * @param type The plant type, -1 for all (optional)
	 * @return vector<Plant>
	 */
	vector<Plant> getPlantList(int x = -1, int y = -1, int type = -1);

	/**
	 * @brief Get the IPlayer handler
	 *
	 * @return IPlayer* The handler
	 */
	IPlayer *getPlayer();

	/**
	 * @brief Get the score
	 *
	 * @param camp The camp
	 * @return int The score of the camp
	 */
	int getScore(int camp);

	/**
	 * @brief Get the sun count
	 *
	 * @param camp The camp
	 * @return int The sun count of the camp
	 */
	int getSun(int camp);

	/**
	 * @brief Get the time
	 *
	 * @return int The time
	 */
	int getTime();

	/**
	 * @brief Get zombies fitting the query
	 *
	 * @param x The x position, -1 for all (optional)
	 * @param y The y position, -1 for all (optional)
	 * @param type The zombie type, -1 for all (optional)
	 * @return vector<Zombie>
	 */
	vector<Zombie> getZombieList(int x = -1, int y = -1, int type = -1);

	/**
	 * @brief Generate a predicted state after applying an action
	 *
	 * @param action The action to apply
	 * @return GameState* The predicted state
	 */
	GameState *generateSuccessor(Action action);

	/**
	 * @brief Infer the next state
	 *
	 */
	void infer();

	/**
	 * @brief Update the state
	 *
	 * @param player The IPlayer object
	 */
	void update(IPlayer *player);

	/**
	 * @brief Print the game state
	 *
	 * @param os The ostream
	 * @param game_state The game state
	 * @return ostream& The result ostream
	 */
	friend ostream &operator<<(ostream &os, GameState *game_state);
};

class Game
{
protected:
	IPlayer *player_;
	GameState *game_state_;

public:
	/**
	 * @brief Construct a new Game object
	 *
	 * @param player The IPlayer object
	 */
	Game(IPlayer *player);

	/**
	 * @brief Destroy the Game object
	 *
	 */
	~Game();

	/**
	 * @brief Get the current state
	 *
	 * @return GameState* The current state
	 */
	GameState *getGameState();

	/**
	 * @brief Update the game environment
	 *
	 * @param player The IPlayer object
	 */
	void update(IPlayer *player);

	/**
	 * @brief Apply an action
	 *
	 * @param action The action to apply
	 * @param force true Force to apply regardless of legality
	 */
	void applyAction(Action action, bool force = false);
};

/****************
 * Definitions
 ****************/

GameState::GameState(int camp) : camp_(camp), other_camp_(1 - camp)
{
	/* Check legality */
	if (camp < 0 || camp > 1)
	{
		throw string("(GameState::GameState) Invalid camp!");
	}
}

GameState::~GameState()
{
}

IPlayer *GameState::getPlayer()
{
	return this->player_;
}

int GameState::getTime()
{
	return this->time_;
}

bitset<5> GameState::getBrokenLines()
{
	return this->broken_lines_;
}

int GameState::getCamp()
{
	return this->camp_;
}

int GameState::getOtherCamp()
{
	return this->other_camp_;
}

Plant GameState::getPlant(int x, int y)
{
	/* Check legality */
	if (x < 0 || x > 4 || y < 0 || y > 10)
	{
		throw string("(GameState::getPlant) Out of map!");
	}

	for (vector<Plant>::iterator iter = this->plant_.begin();
		 iter != this->plant_.end();
		 ++iter)
	{
		if (x == iter->getPosition().x &&
			y == iter->getPosition().y)
		{
			return *iter;
		}
	}

	return Plant(); // if there exists no plant
}

vector<Plant> GameState::getPlantList(int x, int y, int type)
{
	/* Check legality */
	if (x < -1 || x > 4 || y < -1 || y > 10)
	{
		throw string("(GameState::getPlantList) Out of map!");
	}
	if (type < -1 || type > 6)
	{
		throw string("(GameState::getPlantList) Invalid type!");
	}

	vector<Plant> result;
	for (vector<Plant>::iterator iter = this->plant_.begin();
		 iter != this->plant_.end();
		 ++iter)
	{
		if (x != -1 && iter->getPosition().x != x)
		{
			continue;
		}
		if (y != -1 && iter->getPosition().y != y)
		{
			continue;
		}
		if (type != -1 && iter->getType() != type)
		{
			continue;
		}
		result.push_back(*iter);
	}
	return result;
}

vector<Zombie> GameState::getZombieList(int x, int y, int type)
{
	/* Check legality */
	if (x < -1 || x > 4 || y < -1 || y > 10)
	{
		throw string("(GameState::getZombieList) Out of map!");
	}
	if (type < -1 || type > 5)
	{
		throw string("(GameState::getZombieList) Invalid type!");
	}

	vector<Zombie> result;
	for (vector<Zombie>::iterator iter = this->zombie_.begin();
		 iter != this->zombie_.end();
		 ++iter)
	{
		if (x != -1 && iter->getPosition().x != x)
		{
			continue;
		}
		if (y != -1 && iter->getPosition().y != y)
		{
			continue;
		}
		if (type != -1 && iter->getType() != type)
		{
			continue;
		}
		result.push_back(*iter);
	}
	return result;
}

Zombie GameState::getFirstZombie(int row, int col)
{
	vector<Zombie> possible_zombie_list = this->getZombieList(row, this->getBattlefront(row));
	Zombie first_zombie(0, ZOMBIE.NOZOMBIE, Position<double>(row, 999999));
	for (vector<Zombie>::iterator it = possible_zombie_list.begin();
		 it != possible_zombie_list.end();
		 ++it)
	{
		if (it->getPosition().y < col)
		{
			continue;
		}
		if (abs(it->getRealPosition().y - first_zombie.getRealPosition().y) < 0.001)
		{ // to avoid floating point comparison error
			if (it->getSpawnTime() < first_zombie.getSpawnTime())
			{
				first_zombie = *it;
			}
		}
		else if (it->getRealPosition().y < first_zombie.getRealPosition().y)
		{
			first_zombie = *it;
		}
	}
	return first_zombie;
}

Zombie GameState::getEarliestZombie(int row)
{
	vector<Zombie> possible_zombie_list = this->getZombieList(row);
	Zombie earliest_zombie(this->getTime(), ZOMBIE.NOZOMBIE, Position<double>(row, 10));
	for (vector<Zombie>::iterator it = possible_zombie_list.begin();
		 it != possible_zombie_list.end();
		 ++it)
	{
		if (it->getSpawnTime() <= earliest_zombie.getSpawnTime())
		{
			earliest_zombie = *it;
		}
	}
	return earliest_zombie;
}

int GameState::getSun(int camp)
{
	/* Check legality */
	if (camp < 0 || camp > 1)
	{
		throw string("(GameState::getCD) Invalid camp!");
	}

	if (camp == CAMP.PLANT)
	{
		return this->sun_plant_;
	}
	else if (camp == CAMP.ZOMBIE)
	{
		return this->sun_zombie_;
	}

	return 0; // to avoid compilation warning
}

int GameState::getCD(int camp, int slot)
{
	/* Check legality */
	if (camp < 0 || camp > 1)
	{
		throw string("(GameState::getCD) Invalid camp!");
	}
	if (camp == CAMP.PLANT && (slot < 0 || slot > 6))
	{
		throw string("(GameState::getCD) Invalid slot!");
	}
	if (camp == CAMP.ZOMBIE && (slot < 0 || slot > 5))
	{
		throw string("(GameState::getCD) Invalid slot!");
	}

	if (camp == CAMP.PLANT)
	{
		return this->cd_plant_[slot];
	}
	else if (camp == CAMP.ZOMBIE)
	{
		return this->cd_zombie_[slot];
	}

	return 0; // to avoid compilation warning
}

int GameState::getScore(int camp)
{
	/* Check legality */
	if (camp < 0 || camp > 1)
	{
		if (camp < 0 || camp > 1)
		{
			throw string("(GameState::getScore) Invalid camp!");
		}
	}

	if (camp == CAMP.PLANT)
	{
		return this->score_plant_;
	}
	else if (camp == CAMP.ZOMBIE)
	{
		return this->score_zombie_;
	}

	return 0; // to avoid compilation warning
}

int GameState::getBattlefront(int x)
{
	/* Check legality */
	if (x < 0 || x > 4)
	{
		throw string("(GameState::getBattlefront) Out of map!");
	}

	int battle_front = 10;
	for (vector<Zombie>::iterator iter = this->zombie_.begin();
		 iter != this->zombie_.end();
		 ++iter)
	{
		if (iter->getPosition().x == x)
		{
			battle_front = min(battle_front, iter->getPosition().y);
		}
	}
	return battle_front;
}

void GameState::update(IPlayer *player)
{
	GameState *prediction = this->generateSuccessor(Action());

	/* Update according to prediction */
	this->player_ = player;
	this->time_ = prediction->time_;
	this->broken_lines_ = prediction->broken_lines_;
	this->plant_ = prediction->plant_;
	this->zombie_ = prediction->zombie_;
	this->sun_plant_ = prediction->sun_plant_;
	this->sun_zombie_ = prediction->sun_zombie_;
	copy(prediction->cd_plant_, prediction->cd_plant_ + 7, this->cd_plant_);
	copy(prediction->cd_zombie_, prediction->cd_zombie_ + 6, this->cd_zombie_);
	this->score_plant_ = prediction->score_plant_;
	this->score_zombie_ = prediction->score_zombie_;

	delete prediction;

	/* Update according to player */
	/* Update plant list */
	int **raw_plant_map = player->Camp->getCurrentPlants();
	for (int x = 0; x <= 4; ++x)
	{
		for (int y = 0; y <= 9; ++y)
		{
			if (this->getPlant(x, y).getType() != raw_plant_map[x][y])
			{ // if the plant is removed or placed or changed
				if (this->getPlant(x, y).getType() != PLANT.NOPLANT)
				{ // if removed or changed
					for (vector<Plant>::iterator it = this->plant_.begin();
						 it != this->plant_.end();
						 ++it)
					{
						if (it->getPosition().x == x &&
							it->getPosition().y == y)
						{
							this->plant_.erase(it); // remove the plant from plant list
							break;
						}
					}
				}
				if (raw_plant_map[x][y] != PLANT.NOPLANT)
				{                                                 // if placed or changed
					this->plant_.push_back(Plant(this->time_ - 1, // place at last tick
												 raw_plant_map[x][y],
												 Position<int>(x, y)));
					this->cd_plant_[raw_plant_map[x][y]] = PLANT_CD[raw_plant_map[x][y]] - 1; // CD has already gone one tick
					this->sun_plant_ -= PLANT_COST[raw_plant_map[x][y]];
				}
			}
		}
	}

	/* Update zombie list */
	int ***raw_zombie_map = player->Camp->getCurrentZombies();
	for (int x = 0; x <= 4; ++x)
	{
		int zombie_cnt = 0;
		for (int z = 0; raw_zombie_map[x][9][z] != -1; ++z)
		{
			++zombie_cnt;
		}
		if (zombie_cnt > this->getZombieList(x, 9).size())
		{ // after inference, all zombies' y position will < 10
			for (size_t z = this->getZombieList(x, 9).size(); z < zombie_cnt; ++z)
			{
				this->zombie_.push_back(Zombie(
					this->time_ - 1, // place at last tick
					raw_zombie_map[x][9][z],
					Position<double>(x, 10)));
				this->cd_zombie_[raw_zombie_map[x][9][z]] = ZOMBIE_CD[raw_zombie_map[x][9][z]] - 1; // CD has already gone one tick;
				this->sun_zombie_ -= ZOMBIE_COST[raw_zombie_map[x][9][z]];
			}
		}
	}
}

void GameState::infer()
{
	/* Update zombies' time property */
	for (vector<Zombie>::iterator it = this->zombie_.begin();
		 it != this->zombie_.end();
		 ++it)
	{
		it->setNowTime(this->time_); // because this->time_ is the time of last tick
	}

	/* Perform plant attack and sun production */
	for (vector<Plant>::iterator it = this->plant_.begin();
		 it != this->plant_.end();
		 ++it)
	{
		Position<int> pos = it->getPosition();
		if (it->getType() == PLANT.PEPPER)
		{
			for (vector<Zombie>::iterator it1 = this->zombie_.begin();
				 it1 != this->zombie_.end();
				 ++it1)
			{
				if (it1->getPosition().x == pos.x)
				{
					it1->reduceHealth(1800);
				}
			}
			it->reduceHealth(300); // pepper will kill itself
		}
		else if (it->getType() == PLANT.SQUASH)
		{
			for (vector<Zombie>::iterator it1 = this->zombie_.begin();
				 it1 != this->zombie_.end();
				 ++it1)
			{
				if (it1->getPosition().x == pos.x &&
					(it1->getPosition().y == pos.y ||
					 (it1->getPosition().y == 10 && pos.y == 9)))
				{
					it1->reduceHealth(1800);
					it->reduceHealth(300); // squash will kill itself
				}
			}
		}
		else if (it->getType() == PLANT.PEASHOOTER)
		{
			Zombie target = this->getFirstZombie(pos.x, pos.y);
			Zombie earliest = this->getEarliestZombie(pos.x);
			int reference_time = max(earliest.getSpawnTime(), it->getSpawnTime());
			if (((this->time_ - it->getLastAttackTime() > 3) && ((this->time_ - reference_time) % 3 == 1)) ||
				(this->time_ - it->getLastAttackTime() == 3))
			{
				for (vector<Zombie>::iterator it1 = this->zombie_.begin();
					 it1 != this->zombie_.end();
					 ++it1)
				{
					if (it1->getID() == target.getID())
					{
						it1->reduceHealth(20);
						it->setLastAttackTime(this->time_);
					}
				}
			}
		}
		else if (it->getType() == PLANT.WINTERPEASHOOTER)
		{
			Zombie target = this->getFirstZombie(pos.x, pos.y);
			Zombie earliest = this->getEarliestZombie(pos.x);
			int reference_time = max(earliest.getSpawnTime(), it->getSpawnTime());
			if (((this->time_ - it->getLastAttackTime() > 4) && ((this->time_ - reference_time) % 4 == 1)) ||
				(this->time_ - it->getLastAttackTime() == 4))
			{
				for (vector<Zombie>::iterator it1 = this->zombie_.begin();
					 it1 != this->zombie_.end();
					 ++it1)
				{
					if (it1->getID() == target.getID())
					{
						it1->reduceHealth(60);
						it1->setFrozenState(10); // freeze the zombie for 10 sec
						it->setLastAttackTime(this->time_);
					}
				}
			}
		}
		else if (it->getType() == PLANT.SUNFLOWER)
		{
			if ((this->getTime() - it->getSpawnTime()) % 21 == 1)
			{
				this->sun_plant_ += 25;
			}
		}
	}

	/* Remove dead zombies */
	for (vector<Zombie>::iterator it = this->zombie_.begin();
		 it != this->zombie_.end();)
	{
		if (it->getHealth() <= 0)
		{
			this->score_plant_ += ZOMBIE_COST[it->getType()]; // zombies' death contributes to plant camp's score
			it = this->zombie_.erase(it);
		}
		else
		{
			++it;
		}
	}

	/* Perform zombie attack */
	for (vector<Zombie>::iterator it = this->zombie_.begin();
		 it != this->zombie_.end();
		 ++it)
	{
		Position<int> pos = it->getPosition();
		if (it->getType() == ZOMBIE.NORMAL ||
			it->getType() == ZOMBIE.BUCKET ||
			it->getType() == ZOMBIE.POLEVAULT)
		{
			for (vector<Plant>::iterator it1 = this->plant_.begin();
				 it1 != this->plant_.end();
				 ++it1)
			{
				if (it1->getPosition().x == pos.x &&
					it1->getPosition().y == pos.y)
				{
					if (it->getFrozenState() == 0)
					{
						it1->reduceHealth(static_cast<int>(
							75 * max(1.0, this->time_ / 1000.0))); // zombies' ATK will increase after tick 1000
					}
					else
					{
						it1->reduceHealth(static_cast<int>(
							37 * max(1.0, this->time_ / 1000.0))); // zombies' ATK will increase after tick 1000
					}
				}
			}
		}
		else if (it->getType() == ZOMBIE.SLED ||
				 it->getType() == ZOMBIE.GARGANTUAR)
		{
			for (vector<Plant>::iterator it1 = this->plant_.begin();
				 it1 != this->plant_.end();
				 ++it1)
			{
				if (it1->getPosition().x == pos.x &&
					(it1->getPosition().y == pos.y ||
					 (it1->getPosition().y == 9 && pos.y == 10)))
				{
					it1->reduceHealth(999999);
				}
			}
		}
	}

	/* Remove dead plants */
	for (vector<Plant>::iterator it = this->plant_.begin();
		 it != this->plant_.end();)
	{
		if (it->getHealth() <= 0)
		{
			this->score_zombie_ += PLANT_COST[it->getType()]; // plants' death contributes to zombie camp's score
			this->sun_zombie_ += PLANT_COST[it->getType()] / 5 +
								 static_cast<int>(
									 sqrt(PLANT_HP[it->getType()]));
			it = this->plant_.erase(it);
		}
		else
		{
			++it;
		}
	}

	/* Perform zombie movement */
	for (vector<Zombie>::iterator it = this->zombie_.begin();
		 it != this->zombie_.end();
		 ++it)
	{
		Position<double> pos_real = it->getRealPosition();
		Position<int> pos = it->getPosition();

		if (it->getType() == ZOMBIE.NORMAL ||
			it->getType() == ZOMBIE.BUCKET)
		{

			if (this->getPlant(pos.x, pos.y).getType() == PLANT.NOPLANT)
			{ // if there's no plant, the zombie can move

				if (it->getFrozenState())
				{ // if the zombie is frozen, its speed cuts to half
					pos_real.y -= ZOMBIE_SPEED.DEFAULT * 0.5;
				}
				else
				{ // if the zombie is not frozen
					pos_real.y -= ZOMBIE_SPEED.DEFAULT;
				}
			}
		}
		else if (it->getType() == ZOMBIE.POLEVAULT)
		{
			if (this->getPlant(pos.x, pos.y).getType() == PLANT.NOPLANT)
			{ // if there's no plant, the zombie can move normally
				if (it->getFrozenState())
				{ // if the zombie is frozen, its speed cuts to half
					pos_real.y -= ZOMBIE_SPEED.POLEVAULT[it->getState()] * 0.5;
				}
				else
				{ // if the zombie is not frozen
					pos_real.y -= ZOMBIE_SPEED.POLEVAULT[it->getState()];
				}
			}
			else if (it->getState() == 0)
			{ // if there's plant and the zombie is not skipped, the zombie will skip the plant
				pos_real.y -= 1;
				it->setState(1); // set the zombie as skipped state
			}
		}
		else if (it->getType() == ZOMBIE.SLED)
		{
			if (it->getFrozenState())
			{ // if the zombie is frozen, its speed cuts to half
				pos_real.y -= ZOMBIE_SPEED.SLED[min(10 - pos.y, 4)] * 0.5;
			}
			else
			{ // if the zombie is not frozen
				pos_real.y -= ZOMBIE_SPEED.SLED[min(10 - pos.y, 4)];
			}
		}
		else if (it->getType() == ZOMBIE.GARGANTUAR)
		{
			if (it->getFrozenState())
			{ // if the zombie is frozen, its speed cuts to half
				pos_real.y -= ZOMBIE_SPEED.DEFAULT * 0.5;
			}
			else
			{ // if the zombie is not frozen
				pos_real.y -= ZOMBIE_SPEED.DEFAULT;
			}
		}

		it->setRealPosition(pos_real);

		/* Update frozen state */
		if (it->getFrozenState() > 0)
		{                                                 // if the zombie is frozen
			it->setFrozenState(it->getFrozenState() - 1); // reduce remaining frozen time
		}

		/* Update broken lines */
		if (pos_real.y < -0.001) // test: what is the condition?
		{
			this->broken_lines_.set(pos.x);
			this->score_zombie_ += 3000 - this->time_; // doubt: which tick to calculate?
		}
	}

	/* Remove entities in broken rows */
	for (int row = 0; row <= 4; ++row)
	{
		if (this->broken_lines_[row])
		{
			for (vector<Plant>::iterator it = this->plant_.begin();
				 it != this->plant_.end();)
			{ // remove plants in the broken line
				if (it->getPosition().x == row)
				{
					it = this->plant_.erase(it);
				}
				else
				{
					++it;
				}
			}
			for (vector<Zombie>::iterator it = this->zombie_.begin();
				 it != this->zombie_.end();)
			{ // remove zombies in the broken line
				if (it->getPosition().x == row)
				{
					it = this->zombie_.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
	}

	/* Perform CD reduction */
	for (int i = 1; i <= 6; ++i)
	{ // reduce plant CDs
		this->cd_plant_[i] = max(0, this->cd_plant_[i] - 1);
	}

	for (int i = 1; i <= 5; ++i)
	{ // reduce zombie CDs
		this->cd_zombie_[i] = max(0, this->cd_zombie_[i] - 1);
	}

	/* Perform zombie camp's sun increase */
	this->sun_zombie_ += this->time_ / 200 + 1;

	/* Perform zombie boost */
	if (this->time_ % 500 == 499)
	{ // trigger zombie boost
		for (int i = 1; i <= 5; ++i)
		{
			this->cd_zombie_[i] = 0;
		}
		this->sun_zombie_ += 200;
	}

	++this->time_;
}

GameState *GameState::generateSuccessor(Action action)
{
	GameState *next_game_state = new GameState(*this); // but here not inferred yet

	int camp = next_game_state->getCamp();

	/* Plant removal */
	for (int i = 0; i < action.getRemoval().size(); ++i)
	{
		Position<int> removal = action.getRemoval().at(i);

		/* Check legality */
		if (next_game_state->getPlant(removal.x, removal.y).getType() == PLANT.NOPLANT)
		{
			throw string("(GameState::generateSuccessor) Plant removal on empty place!");
		}

		for (vector<Plant>::iterator it = next_game_state->plant_.begin();
			 it != next_game_state->plant_.end();)
		{ // remove a plant
			if (it->getPosition().x == removal.x &&
				it->getPosition().y == removal.y)
			{
				it = next_game_state->plant_.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	/* Plant placement */
	int sun_consumption = 0;
	for (int slot = 1; slot <= 6; ++slot)
	{
		if (action.isSet(CAMP.PLANT, slot))
		{
			sun_consumption += PLANT_COST[slot];
			if (next_game_state->getBrokenLines()[action.getPosition(CAMP.PLANT, slot).x])
			{
				throw string("(GameState::generateSuccessor) Plant broken line!");
			}
			if (next_game_state->getCD(CAMP.PLANT, slot) > 0)
			{
				throw string("(GameState::generateSuccessor) Plant unfinished cooldown!");
			}
		}
	}
	if (sun_consumption > next_game_state->getSun(CAMP.PLANT))
	{
		throw string("(GameState::generateSuccessor) Plant insufficient sun!");
	}

	for (int slot = 1; slot <= 6; ++slot)
	{
		if (action.isSet(CAMP.PLANT, slot))
		{
			Position<int> position = action.getPosition(CAMP.PLANT, slot);

			for (vector<Plant>::iterator it = next_game_state->plant_.begin();
				 it != next_game_state->plant_.end();)
			{ // remove a plant
				if (it->getPosition().x == position.x &&
					it->getPosition().y == position.y)
				{
					it = next_game_state->plant_.erase(it);
				}
				else
				{
					++it;
				}
			}

			next_game_state->plant_.push_back(Plant(
				next_game_state->time_,
				slot,
				position));
			next_game_state->cd_plant_[slot] = PLANT_CD[slot] - 1; // CD has already gone one tick
		}
	}

	next_game_state->sun_plant_ -= sun_consumption;

	/* Zombie placement */
	sun_consumption = 0;
	for (int slot = 1; slot <= 5; ++slot)
	{
		if (action.isSet(CAMP.ZOMBIE, slot))
		{
			sun_consumption += ZOMBIE_COST[slot];
			if (next_game_state->getBrokenLines()[action.getPosition(CAMP.ZOMBIE, slot).x])
			{
				throw string("(GameState::generateSuccessor) Zombie broken line!");
			}
			if (next_game_state->getCD(CAMP.ZOMBIE, slot) > 0)
			{
				throw string("(GameState::generateSuccessor) Zombie unfinished cooldown!");
			}
		}
	}
	if (sun_consumption > next_game_state->getSun(CAMP.ZOMBIE))
	{
		throw string("(GameState::generateSuccessor) Zombie insufficient sun!");
	}

	for (int slot = 1; slot <= 5; ++slot)
	{
		if (action.isSet(CAMP.ZOMBIE, slot))
		{
			this->player_->PlaceZombie(slot, action.getPosition(CAMP.ZOMBIE, slot).x);
			next_game_state->zombie_.push_back(
				Zombie(
					next_game_state->time_,
					slot,
					action.getPosition(CAMP.ZOMBIE, slot)));
			next_game_state->cd_zombie_[slot] = ZOMBIE_CD[slot] - 1; // CD has already gone one tick
		}
	}

	next_game_state->sun_zombie_ -= sun_consumption;

	next_game_state->infer();

	return next_game_state;
}

ostream &operator<<(ostream &os, GameState *game_state)
{
	cout << "GameState(time_="
		 << game_state->time_
		 << ",\n          broken_lines_="
		 << game_state->broken_lines_
		 << ",\n          camp_="
		 << game_state->camp_
		 << ",\n          other_camp_="
		 << game_state->other_camp_
		 << ",\n          sun_plant_="
		 << game_state->sun_plant_
		 << ",\n          sun_zombie_="
		 << game_state->sun_zombie_
		 << ",\n          cd_plant_=[";
	for (int i = 0; i < 7; ++i)
	{
		cout << game_state->cd_plant_[i] << ", ";
	}
	cout << "],\n          cd_zombie_=[";
	for (int i = 0; i < 6; ++i)
	{
		cout << game_state->cd_zombie_[i] << ", ";
	}
	cout << "],\n          score_plant_="
		 << game_state->score_plant_
		 << ",\n          score_zombie_="
		 << game_state->score_zombie_
		 << ",\n          )\n";

	return cout;
}

Game::Game(IPlayer *player)
{
	this->player_ = player;
	this->game_state_ = new GameState(player->Camp->getCurrentType());
}

Game::~Game()
{
}

GameState *Game::getGameState()
{
	return this->game_state_;
}

void Game::update(IPlayer *player)
{
	this->player_ = player;
	this->game_state_->update(player);
}

void Game::applyAction(Action action, bool force)
{
	int camp = this->game_state_->getCamp();
	if (camp == CAMP.PLANT)
	{
		/* Check legality */
		for (int slot = 1; slot <= 5; ++slot)
		{
			if (action.isSet(CAMP.ZOMBIE, slot))
			{
				throw string("(Game::applyAction) No access!");
			}
		}

		/* Plant removal */
		for (int i = 0; i < action.getRemoval().size(); ++i)
		{
			Position<int> removal = action.getRemoval().at(i);

			/* Check legality */
			if (!force)
			{
				if (this->game_state_->getPlant(removal.x, removal.y).getType() == PLANT.NOPLANT)
				{
					throw string("(Game::applyAction) Removal on empty place!");
				}
			}

			this->player_->removePlant(removal.x, removal.y);
		}

		/* Plant placement */
		int sun_consumption = 0;
		for (int slot = 1; slot <= 6; ++slot)
		{
			if (action.isSet(CAMP.PLANT, slot))
			{
				sun_consumption += PLANT_COST[slot];
				if (!force)
				{
					if (this->game_state_->getBrokenLines()[action.getPosition(CAMP.PLANT, slot).x])
					{
						throw string("(Game::applyAction) Broken line!");
					}
					if (this->game_state_->getCD(CAMP.PLANT, slot) > 0)
					{
						throw string("(Game::applyAction) Unfinished cooldown!");
					}
				}
			}
		}
		if (!force)
		{
			if (sun_consumption > this->game_state_->getSun(CAMP.PLANT))
			{
				throw string("(Game::applyAction) Insufficient sun!");
			}
		}

		for (int slot = 1; slot <= 6; ++slot)
		{
			if (action.isSet(CAMP.PLANT, slot))
			{
				Position<int> position = action.getPosition(CAMP.PLANT, slot);
				if (this->game_state_->getPlant(position.x, position.y).getType() != slot)
				{ // if attempting to place a same plant, do nothing
					this->player_->removePlant(position.x, position.y);
					this->player_->PlacePlant(slot, position.x, position.y);
				}
			}
		}
	}
	else if (camp == CAMP.ZOMBIE)
	{
		/* Check legality */
		for (int slot = 1; slot <= 6; ++slot)
		{
			if (action.isSet(CAMP.PLANT, slot))
			{
				throw string("(Game::applyAction) No access!");
			}
		}

		int sun_consumption = 0;
		for (int slot = 1; slot <= 5; ++slot)
		{
			if (action.isSet(CAMP.ZOMBIE, slot))
			{
				sun_consumption += ZOMBIE_COST[slot];
				if (!force)
				{
					if (this->game_state_->getBrokenLines()[action.getPosition(CAMP.ZOMBIE, slot).x])
					{
						throw string("(Game::applyAction) Broken line!");
					}
					if (this->game_state_->getCD(CAMP.ZOMBIE, slot) > 0)
					{
						throw string("(Game::applyAction) Unfinished cooldown!");
					}
				}
			}
		}
		if (!force)
		{
			if (sun_consumption > this->game_state_->getSun(CAMP.ZOMBIE))
			{
				throw string("(Game::applyAction) Insufficient sun!");
			}
		}

		for (int slot = 1; slot <= 5; ++slot)
		{
			if (action.isSet(CAMP.ZOMBIE, slot))
			{
				this->player_->PlaceZombie(slot, action.getPosition(CAMP.ZOMBIE, slot).x);
			}
		}
	}
}

#endif
/*** End of inlined file: Game.cpp ***/


/*** Start of inlined file: PlantEmptyAgent.cpp ***/
class PlantAgent
{
public:
	Action getAction(GameState *game_state)
	{
		Action action;
		return action;
	}
};

static PlantAgent agent_plant;
/*** End of inlined file: PlantEmptyAgent.cpp ***/


/*** Start of inlined file: ZombieEmptyAgent.cpp ***/
class ZombieAgent
{
public:
	Action getAction(GameState *game_state)
	{
		Action action;
		return action;
	}
};

static ZombieAgent agent_zombie;
/*** End of inlined file: ZombieEmptyAgent.cpp ***/

using namespace std;

void player_ai(IPlayer *player)
{
	static Game *game = new Game(player);

	/* Start a new game when the camp swapped */
	if (player->Camp->getCurrentType() != game->getGameState()->getCamp())
	{
		delete game;
		game = new Game(player);
	}

	game->update(player);

	try
	{
		Action action;
		if (game->getGameState()->getCamp() == CAMP.PLANT)
		{
			action = agent_plant.getAction(game->getGameState());
		}
		else if (game->getGameState()->getCamp() == CAMP.ZOMBIE)
		{
			action = agent_zombie.getAction(game->getGameState());
		}

		game->applyAction(action);
	}
	catch (string e)
	{
		cerr << "******** " << game->getGameState()->getTime() << " ********" << endl;
		cerr << "[ERROR]<CAMP " << ((game->getGameState()->getCamp() == CAMP.PLANT) ? "Plant" : "Zombie") << ", Tick " << game->getGameState()->getTime() << "> " << e << endl << endl;
	}
}
