#include "Actions.h"
#include <iostream>

void Action::EffectActivate(Player&, Enemy&)
{
}
void Action::ToString()
{
}

	Attack::Attack(std::string _name, std::string _desc, int _damage, int _staminaCost, int _manaCost) {
		name = _name;
		desc = _desc;
		damage = _damage;
		staminaCost = _staminaCost;
		manaCost = _manaCost;
	}
	void Attack::EffectActivate(Player& p, Enemy& e) {
		if (p.stamina >= staminaCost && p.mana >= manaCost) { //if player has enough stamina or mana
			e.health -= damage; //enemy takes damage
			p.stamina -= staminaCost; //take player stamina
			p.mana -= manaCost; //take player stamina
		}
		else {
			std::cout << "Not enough stamina or mana! You did nothing instead" << std::endl;
			EnterToContinue();
		}
	}

	Heal::Heal(std::string _name, std::string _desc, int _recover, int _staminaCost, int _manaCost) {
		name = _name;
		desc = _desc;
		recover = _recover;
		staminaCost = _staminaCost;
		manaCost = _manaCost;
	}
	void Heal::EffectActivate(Player& p, Enemy& e) {
		if (p.stamina >= staminaCost && p.mana >= manaCost) { //if player has enough stamina or mana
			p.health += recover; //player recover health
			if (p.health > p.maxHealth) { //if health is above max health
				p.health = p.maxHealth; //reset to max health
			}
			p.stamina -= staminaCost; //take player stamina
			p.mana -= manaCost; //take player mana
		}
		else {
			std::cout << "Not enough stamina or mana! You did nothing instead" << std::endl;
			EnterToContinue();
		}
	}
