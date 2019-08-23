// ConsoleRPG.cpp : Basic console RPG
// Abstract classes for increased flexibility

#include <iostream>
#include <vector>
#include <time.h>
#include <cstring>
#include <sstream>

using namespace std;

void EnterToContinue() { //empty input function, restrict flow of information
	cin.ignore(100, '\n');
	string input;
	getline(cin, input);
}

// ENEMY CLASSES
class Enemy {
protected:
	int minAttack, maxAttack;
public:
	string name;
	int health;
	//vector<Item*> dropList;
	virtual int Attack(); //attack player
	virtual void PrintStats(); //print stats
	virtual void ResetStats(); //stats back to default
	void Die() { //print out enemy died
		//cout << name << " dropped " << dropList[rand() % dropList.size()]->name << "!" << endl;
		system("cls"); //clear console
		cout << name << " has died!" << endl;
		EnterToContinue();
	}
};

class Minotaur : public Enemy {
public:
	Minotaur() {
		name = "Minotaur";
		health = 200;
		minAttack = 10;
		maxAttack = 20;
		//dropList.push_back(new HealthPotion("Healing potion", "Heals you for 50 health", 50));
	}
	 int Attack() override {
		srand(unsigned(time(0))); //time to randomize new value
		int damage = rand() % maxAttack + minAttack; // random attack value
		return damage;
	}
	void PrintStats() override {
		cout << name << "\n\nHealth: " << health << "\n"<< endl;
	}
	void ResetStats() override {
		name = "Minotaur";
		health = 200;
		minAttack = 10;
		maxAttack = 20;
	}
};

// PLAYER CLASSES

class Hero {
public:
	string name;
	int health, stamina, mana, staminaRegen, manaRegen;
};

class Player {
public:
	//STATS
	string name;
	int health, stamina, mana, maxHealth, maxStamina, maxMana, staminaRegen, manaRegen;
	
	void CreateCharacter(Hero hero) {
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
	void PrintStats() {
		cout << name << "\n\nHealth: " << health << "\nStamina: " << stamina << "\nMana: " << mana << "\n" << endl;
	}
};

// ITEM CLASSES

class Item {
public:
	string name, desc, used;
	virtual void EffectActivate(Player& p, Enemy& e);
};

class HealthPotion : public Item{ //basic health potion
public:
	int recover;
	HealthPotion(string _name, string _desc, string _used, int _recover) {
		name = _name;
		desc = _desc;
		used = _used;
		recover = _recover;
	}
	void EffectActivate(Player& p, Enemy& e)
	{
		if (p.health < p.maxHealth - recover) {
			p.health += recover;
		}
		else {
			p.health = 100;
		}
	}
};

// ATTACK CLASSES

class Action { //Actions = what a player can do in a turn (excluding using items)
public:
	string name, desc;
	int staminaCost, manaCost;
	virtual void EffectActivate(Player& p, Enemy& e);
	virtual void ToString();
};

class Attack : public Action { //basic attack
public:
	int damage;
	Attack(string _name, string _desc, int _damage, int _staminaCost, int _manaCost) {
		name = _name;
		desc = _desc;
		damage = _damage;
		staminaCost = _staminaCost;
		manaCost = _manaCost;
	}
	void EffectActivate(Player& p, Enemy& e) {
		if (p.stamina >= staminaCost && p.mana >= manaCost) { //if player has enough stamina or mana
			e.health -= damage; //enemy takes damage
			p.stamina -= staminaCost; //take player stamina
			p.mana -= manaCost; //take player stamina
		}
		else {
			cout << "Not enough stamina or mana! You did nothing instead" << endl;
			EnterToContinue();
		}
	}
};

class Heal : public Action { //basic heal
public:
	int recover;
	Heal(string _name, string _desc, int _recover, int _staminaCost, int _manaCost) {
		name = _name;
		desc = _desc;
		recover = _recover;
		staminaCost = _staminaCost;
		manaCost = _manaCost;
	}
	void EffectActivate(Player& p, Enemy& e) {
		if (p.stamina >= staminaCost && p.mana >= manaCost) { //if player has enough stamina or mana
			p.health += recover; //player recover health
			if (p.health > p.maxHealth) { //if health is above max health
				p.health = p.maxHealth; //reset to max health
			}
			p.stamina -= staminaCost; //take player stamina
			p.mana -= manaCost; //take player mana
		}
		else {
			cout << "Not enough stamina or mana! You did nothing instead" << endl;
			EnterToContinue();
		}
	}
};
// HERO CLASSES 
class Spellsword : public Hero {
public:
	vector<Action*> actions; //possible player actions
	Spellsword(string _name) {
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
};

class Warrior : public Hero {
public:
	vector<Action*> actions; //possible player actions
	Warrior(string _name) {
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
};

class Wizard : public Hero {
public:
	vector<Action*> actions; //possible player actions
	Wizard(string _name) {
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

};

class Inventory {
public:
	vector<Action*> actions; //Possible player actions
	vector<Item*> items; //Items in player inventory
	// ADD HERO ACTIONS AND BASIC ITEMS
	void AddActions(vector<Action*> a)  { //get actions from hero class
		for (int i = 0; i < a.size(); i++) { //add actions to inventory
			actions.push_back(a[i]);
		}
		//ADD BASIC ITEMS
		items.push_back(new HealthPotion("Healing potion", "Heals you for 50 health", "You used a health potion!", 50));
		items.push_back(new HealthPotion("Healing potion", "Heals you for 50 health", "You used a health potion!", 50));
		items.push_back(new HealthPotion("Healing potion", "Heals you for 50 health", "You used a health potion!", 50));
	}
	//PRINTING FUNCTIONS
	void ShowActions() {
		cout << "0) Inventory" << endl;
		for (int i = 0; i < actions.size(); i++) { //foreach action in actionlist
			cout << i + 1 << ") " << actions[i]->name<< " - " << actions[i]->desc << " - Stamina: " << actions[i]->staminaCost << " - Mana: " << actions[i]->manaCost << endl;
		}
	}
	void ShowInventory() {
		cout << "0) Back" << endl;
		for (int i = 0; i < items.size(); i++) { //foreach item in items
			cout << i + 1 << ") " << items[i]->name << " - " << items[i]->desc << endl;
		}
	}
	//Use item
	void UseItem(int number, Player& p, Enemy& enemy) {

		system("cls"); //clear console
		items[number]->EffectActivate(p, enemy); //apply item effect on player and enemy
		cout << items[number]->used; //print out used description

		EnterToContinue();

		items.erase(items.begin() + number); //remove item
	}
};

// FUNCTIONS

void BattleInfo(Enemy& enemy, Player& p, Inventory& inv) {

	//PRINT INFO
	enemy.PrintStats();
	p.PrintStats();
	inv.ShowActions();

	//PLAYER CHOOSE WHAT TO DO
	//converts string input into a number
	string choice;
	cin >> choice;
	int number;
	istringstream iss(choice);
	iss >> number;
	if (iss.fail()) {
		cout << "Invalid input" << endl;
	}
	else if (choice == "0") { // GO TO INVENTORY
		system("cls"); //clear console
		inv.ShowInventory(); //print inventory
		//converts string input into a number
		string choice2;
		cin >> choice2;
		int number;
		istringstream iss(choice2);
		iss >> number;
		if (iss.fail()) {
			cout << "Invalid input" << endl;
		}
		else if (number == 0) {
			system("cls"); //clear console
			BattleInfo(enemy, p, inv); //does not use item, back to battle
		}
		else if (number > 0 && number <= inv.items.size()) { //if number is in range of items vector
			inv.UseItem(number - 1, p, enemy); //use item
		}
		else {
			cout << "Invalid input" << endl;
		}
	}
	else if (number > 0 && number <= inv.actions.size()) { //if number is in range of actions vector
		inv.actions[number - 1]->EffectActivate(p, enemy);
	}
	else {
		cout << "Invalid input" << endl;
	}
}

void Battle(Enemy& enemy, Player& p, Inventory&inv) {
	while (enemy.health > 0) { //if enemy is not dead
		BattleInfo(enemy, p, inv);
		system("cls"); //clear console

	    // PLAYER TURN END
		p.stamina += p.staminaRegen;
		p.mana += p.manaRegen;
		if (enemy.health < 0) { //if enemy died
			enemy.Die();
		}
		else { //enemy attacks
			int enemyAttack = enemy.Attack(); //save random attack value
			p.health -= enemyAttack; //apply damage
			cout << enemy.name << " attacked you for " << enemyAttack << "\n" << endl;
		}
		if (p.health <= 0) { //if player died
			cout << "You lost! Try again." << endl;
			EnterToContinue();
			break;
		}		
	}
	cout << "You won over " << enemy.name;
	system("cls"); //clear console
}
class Room { //basic room
private:
	string name;
public:
	int x, y; //location for room
	Room(string _name, int _x, int _y) {
		name = _name;
		x = _x;
		y = _y;
	}
	string GetName() {
		return name;
	}
};
class MapGenerator {
private:
	vector<vector<Room*>> map; //contain rows of rooms
	int rows = 3;
	int length = 4;
public:
	int currentX = 0; //player X
	int currentY = 0; //player Y
	MapGenerator()
	{
		//ADD ROOMS
		int count = 0;
		for (int i = 0; i < rows; i++) { //Y
			vector<Room*> roomRow;
			for (int j = 0; j < length; j++) { //X
				count++;
				roomRow.push_back(new Room("Room " + to_string(count), j, i));
			}
			map.push_back(roomRow);
		}
	}
	void PrintLocation() {
		cout << "You are at: " << map[currentY][currentX]->GetName() << endl << endl;

		vector<Room*> availableRooms; //rooms able to go to

		if (currentY == 0 || currentY < rows - 1) {
			if (currentX == 0) {
				cout << map[currentY + 1][currentX]->GetName() << endl << "  |  " << endl;
			}
			else {
				cout << "         " << map[currentY + 1][currentX]->GetName() << endl << "           |  " << endl;
			}
			availableRooms.push_back(map[currentY + 1][currentX]);
		}
		if (currentX == 0) {
			cout << map[currentY][currentX]->GetName() << " - " << map[currentY][currentX + 1]->GetName() << endl;
			availableRooms.push_back(map[currentY][currentX + 1]);
		}
		else if (currentX > 0 && currentX < length - 1) {
			cout << map[currentY][currentX - 1]->GetName() << " - " << map[currentY][currentX]->GetName() << " - " << map[currentY][currentX + 1]->GetName() << endl;
			availableRooms.push_back(map[currentY][currentX - 1]);
			availableRooms.push_back(map[currentY][currentX + 1]);
		}
		else if (currentX == length - 1) {
			cout << map[currentY][currentX - 1]->GetName() << " - " << map[currentY][currentX]->GetName() << endl;
			availableRooms.push_back(map[currentY][currentX - 1]);
		}
		if (currentY > 0) {
			if (currentX == 0) {
				cout << "  |  " << endl << map[currentY - 1][currentX]->GetName() << endl;
			}
			else {
				cout << "           |  " << endl << "         " << map[currentY - 1][currentX]->GetName() << endl;
			}
			availableRooms.push_back(map[currentY - 1][currentX]);
		}

		cout << endl; //empty line
		for (int i = 0; i < availableRooms.size(); i++) { //add rooms able to go to
			cout << i << ") Go to " << availableRooms[i]->GetName() << endl;
		}

		while (true) {
			//convert input to number
			string input;
			cin >> input;
			int number;
			istringstream iss(input);
			iss >> number;
			if (iss.fail()) {
				cout << "Invalid input" << endl;
			}
			else if(number >= 0 && number < availableRooms.size()) { //if number is in range of availableRooms vector
				currentX = availableRooms[number]->x; //change player x
				currentY = availableRooms[number]->y; //change player y
				break;
			}
			else {
				cout << "Invalid input" << endl;
			}
		}
	}
};

//GAME
int main()
{
	//GLOBAL VARIABLES
	string pName;
	string pClass;
	Player p;
	Inventory inv;
	MapGenerator map;
	// PLAYER NAMING
	cout << "Enter your name: ";
	cin >> pName;
	system("cls"); //clear console
	// PLAYER CHARACTER CREATION
	//loop until valid hero is chosen
	//stats go to player class
	cout << "Choose a class \n 1) Spellsword - Beginner class \n 2) Warrior - Stamina focus \n 3) Wizard - Mana focus" << endl;;
	while (true) {
		cin >> pClass; //get input
		if (pClass == "1") {
			Spellsword* spellsword = new Spellsword(pName);
			inv.AddActions(spellsword->actions);
			p.CreateCharacter(*spellsword);
			break;
		}
		else if (pClass == "2") {
			Warrior* warrior = new Warrior(pName);
			inv.AddActions(warrior->actions);
			p.CreateCharacter(*warrior);
			break;
		}
		else if (pClass == "3") {
			Wizard* wizard = new Wizard(pName);
			inv.AddActions(wizard->actions);
			p.CreateCharacter(*wizard);
			break;
		}
		else {
			cout << "Wrong input, try again" << endl;
		}
	}
	while (p.health > 0) {
		Minotaur mino;
		system("cls"); //clear consoles
		map.PrintLocation();
		system("cls"); //clear consoles
		cout << "You encountered a minotaur!" << endl;
		Battle(mino, p, inv);
	}
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
void Action::EffectActivate(Player&, Enemy&)
{
}
void Action::ToString()
{
}
void Item::EffectActivate(Player&, Enemy&)
{
}