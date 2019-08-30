#include "Actions.h"
#include "Heroes.h"
#include <vector>

	Spellsword::Spellsword(std::string _name) {
		//SET STATS
		name = _name + " The Spellsword";
		health = 100;
		stamina = 100;
		mana = 100;
		staminaRegen = 10;
		manaRegen = 10;
		//ADD POSSIBLE PLAYER ACTIONS
		actions.push_back(new Attack("Slash", "Attack for 10 damage", 10, 10, 0));
		actions.push_back(new Attack("Cut", "Attack for 50 damage", 50, 40, 0));
		actions.push_back(new Attack("Fireblast", "Attack for 10 damage", 10, 0, 10));
		actions.push_back(new Attack("Magicbomb", "Attack for 50 damage", 50, 0, 40));
		actions.push_back(new Heal("Strong Heal", "Heal to 100 Health", 100, 0, 20));
		actions.push_back(new Heal("Bandage", "Heal to 100 Health", 100, 20, 0));
	}

	Warrior::Warrior(std::string _name) {
		//SET STATS
		name = _name + " The Warrior";
		health = 200;
		stamina = 200;
		mana = 0;
		staminaRegen = 10;
		manaRegen = 0;
		//ADD POSSIBLE PLAYER ACTIONS
		actions.push_back(new Attack("Punch", "Attack for 20 damage", 20, 20, 0));
		actions.push_back(new Attack("Crush", "Attack for 100 damage", 60, 30, 0));
		actions.push_back(new Heal("Weak Heal", "Heal to 50 Health", 100, 20, 00));
	}

	Wizard::Wizard(std::string _name) {
		//SET STATS
		name = _name + " The Wizard";
		health = 60;
		stamina = 0;
		mana = 200;
		staminaRegen = 0;
		manaRegen = 40;
		//ADD POSSIBLE PLAYER ACTIONS
		actions.push_back(new Attack("Waterbolt", "Attack for 20 damage", 20, 0, 40));
		actions.push_back(new Attack("Fireball", "Attack for 100 damage", 100, 0, 80));
		actions.push_back(new Heal("Strong Heal", "Heal to 100 Health", 100, 0, 20));
	}
