#pragma once
#include <string>
class Enemy {
protected:
	int minAttack, maxAttack;
public:
	std::string name;
	int health;
	//vector<Item*> dropList;
	virtual int Attack(); //attack player
	virtual void PrintStats(); //print stats
	virtual void ResetStats(); //stats back to default
	void Die();
};

class Minotaur : public Enemy {
public:
	Minotaur();
	int Attack() override;
	void PrintStats() override;
	void ResetStats() override;
};