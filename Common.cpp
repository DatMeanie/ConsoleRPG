#include "Common.h"
#include "Heroes.h"
#include <iostream>
using namespace std;

Room::Room(string _name, int _x, int _y) {
		name = _name;
		x = _x;
		y = _y;
	}
	string Room::GetName() {
		return name;
	}

	void EnterToContinue() { //empty input function, restrict flow of information
		cin.ignore(100, '\n');
		string input;
		getline(cin, input);
	}

		void Player::CreateCharacter(Hero hero) {
			name = hero.name;
			maxHealth = hero.health;
			health = maxHealth;
			maxStamina = hero.stamina;
			stamina = maxStamina;
			maxMana = hero.mana;
			mana = maxMana;
			staminaRegen = hero.staminaRegen;
			manaRegen = hero.manaRegen;
		}
		void Player::PrintStats() {
			cout << name << "\n\nHealth: " << health << "\nStamina: " << stamina << "\nMana: " << mana << "\n" << endl;
		}
