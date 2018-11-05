
#include "Weapon.h"
Weapon::Weapon() : name("None"), power(1), fighterName("None"), type("unarmed")
{
}

Weapon::Weapon(string name, string type, int power, string fighterName) : name(name), type(type), power(power), fighterName(fighterName)
{
}
Weapon::Weapon(string name) : name(name), power(1), fighterName("None"), type("unarmed")
{
}
string Weapon::Weapon::getType() const
{
	return type;
}
string Weapon::Weapon::getName() const
{
	return name;
}
int Weapon::Weapon::getPower() const
{
	return power;
}

void Weapon::setFighterName (string mFighterName){
	fighterName = mFighterName;
}

string Weapon::getFighterName() const
{
	return fighterName;
}
