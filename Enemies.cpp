#include "Enemies.h"
#include "Common.h"
#include <iostream>
#include <time.h>

void Enemy::Die() { //print out enemy died
	//cout << name << " dropped " << dropList[rand() % dropList.size()]->name << "!" << endl;
	system("cls"); //clear console
	std::cout << name << " has died!" << std::endl;
	EnterToContinue();
}

	Minotaur::Minotaur() {
		name = "Minotaur";
		health = 200;
		minAttack = 10;
		maxAttack = 20;
		//dropList.push_back(new HealthPotion("Healing potion", "Heals you for 50 health", 50));
	}
	int Minotaur::Attack() {
		srand(unsigned(time(0))); //time to randomize new value
		int damage = rand() % maxAttack + minAttack; // random attack value
		return damage;
	}
	void Minotaur::PrintStats() {
		std::cout << name << "\n\nHealth: " << health << "\n" << std::endl;
	}
	void Minotaur::ResetStats() {
		name = "Minotaur";
		health = 200;
		minAttack = 10;
		maxAttack = 20;
	}

int Enemy::Attack()
{
	return 0;
}
void Enemy::PrintStats()
{
}
void Enemy::ResetStats()
{
}