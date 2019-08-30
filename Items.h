#pragma once
#include "Common.h"
#include "Enemies.h"
class Item {
public:
	std::string name, desc, used;
	virtual void EffectActivate(Player& p, Enemy& e);
};

class HealthPotion : public Item { //basic health potion
public:
	int recover;
	HealthPotion(std::string _name, std::string _desc, std::string _used, int _recover);
	void EffectActivate(Player& p, Enemy& e);
};