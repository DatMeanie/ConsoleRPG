#pragma once
#include "Actions.h"
#include <string>
#include <vector>

class Hero {
public:
	std::string name;
	int health, stamina, mana, staminaRegen, manaRegen;
};

class Spellsword : public Hero {
public:
	std::vector<Action*> actions; //possible player actions
	Spellsword(std::string _name);
};

class Warrior : public Hero {
public:
	std::vector<Action*> actions; //possible player actions
	Warrior(std::string _name);
};

class Wizard : public Hero {
public:
	std::vector<Action*> actions; //possible player actions
	Wizard(std::string _name);
};