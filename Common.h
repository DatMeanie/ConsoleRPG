#pragma once
#include "Heroes.h"
#include <string>
class Room { //basic room
private:
	std::string name;
public:
	int x, y; //location for room
	Room(std::string _name, int _x, int _y);
	std::string GetName();
};

class Player {
public:
	//STATS
	std::string name;
	int health, stamina, mana, maxHealth, maxStamina, maxMana, staminaRegen, manaRegen;

	void CreateCharacter(Hero hero);
	void PrintStats();
};

void EnterToContinue();