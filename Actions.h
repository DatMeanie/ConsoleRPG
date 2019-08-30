#pragma once
#include <string>
#include "Common.h"
#include "Enemies.h"
class Action { //Actions = what a player can do in a turn (excluding using items)
public:
	std::string name, desc;
	int staminaCost, manaCost;
	virtual void EffectActivate(Player& p, Enemy& e);
	virtual void ToString();
};

class Attack : public Action { //basic attack
public:
	int damage;
	Attack(std::string _name, std::string _desc, int _damage, int _staminaCost, int _manaCost);
	void EffectActivate(Player& p, Enemy& e);
};

class Heal : public Action { //basic heal
public:
	int recover;
	Heal(std::string _name, std::string _desc, int _recover, int _staminaCost, int _manaCost);
	void EffectActivate(Player& p, Enemy& e);
};