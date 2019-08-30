#include "Items.h"
#include <string>
void Item::EffectActivate(Player&, Enemy&)
{
}

	HealthPotion::HealthPotion(std::string _name, std::string _desc, std::string _used, int _recover) {
		name = _name;
		desc = _desc;
		used = _used;
		recover = _recover;
	}
	void HealthPotion::EffectActivate(Player& p, Enemy& e)
	{
		if (p.health < p.maxHealth - recover) {
			p.health += recover;
		}
		else {
			p.health = 100;
		}
	}