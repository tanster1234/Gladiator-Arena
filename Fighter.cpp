
#include "Fighter.h"

Fighter::Fighter() : name("None"), str(1), hp(60), money(1000), weapon(Weapon("None"))
{
}


Fighter::Fighter(string name, int str, int hp) : name(name), str(str), hp(hp), money(1000), weapon(Weapon("None"))
{
}

string Fighter::getName() const
{
	return name;
}
int Fighter::getStr() const
{
	return str;
}
int Fighter::getHp() const
{
	return hp;
}
Weapon& Fighter::getWeapon()
{
	return weapon;
}
int Fighter::getMoney() const
{
	return money;
}

void Fighter::addMoney(int amount)
{
		money = money + amount;
}

bool Fighter::removeMoney(int amount)
{
	if (money > 0){
		money = money - amount;
		return true;
	}
	return false;
}

bool Fighter::setWeapon(const Weapon& mWeapon)
{
	  weapon = mWeapon;
	  return true;
}

bool Fighter::removeWeapon()
{
	if (weapon.getName() == "None"){
		return false;
	} else{
		weapon = Weapon("None");
		return true;
	}
	
}

