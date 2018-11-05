//Arena cpp file to set up the arena dimensions
#include "Arena.h"

Arena::Arena() : weapons(NULL), fighters(NULL), fighterCount(0), weaponCount(0), reward(1000), mode("armed")
{
}

Arena::Arena(const Arena& a) {
	weaponCount = a.weaponCount;
	Weapon** newWeapons = new Weapon*[weaponCount];
	for (int i = 0; i < weaponCount; i++) {
		Weapon* newWeapon = a.weapons[i];
		newWeapons[i] = new Weapon(*a.weapons[i]);
		//newWeapons[i] = newWeapon;
	}
	weapons = newWeapons;

	fighterCount = a.fighterCount;
	Fighter** newFighters = new Fighter*[fighterCount];
	for (int i = 0; i < fighterCount; i++) {
		Fighter* newFighter = a.fighters[i];
		newFighters[i] = new Fighter(*a.fighters[i]);
		//newFighters[i] = a.fighters[i];
	}
	fighters = newFighters;
	reward = a.reward;
	mode = a.mode;
}

Arena::~Arena()
{
	for(int i=0; i<fighterCount; i++)
	{
		delete fighters[i];
	}
	delete [] fighters;

	for(int i=0; i<weaponCount; i++)
	{
		delete weapons[i];
	}
	delete [] weapons;
}

bool Arena::addFighter(string name, int str, int hp) 
{
	//return false if the name already exists
	if(doesFighterExist(name))
		return false;

	//now add the fighter
	Fighter* newFighter = new Fighter(name, str, hp);
	Fighter** newFighters = new Fighter*[++fighterCount];
	for(int i=0; i<fighterCount-1; i++)
		newFighters[i] = fighters[i];
	newFighters[fighterCount-1] = newFighter;
	delete [] fighters;
	fighters = newFighters;
	return true;
}

bool Arena::addWeapon(string name, string type, int power)
{
	//return false if the name already exists
	if(doesWeaponExist(name))
		return false;
	//check if the type is valid
	if (type != "melee" && type != "ranged" && type != "magic" && type != "unarmed")
		return false;
	//now add the weapon
	Weapon* newWeapon = new Weapon(name, type, power, "None");
	Weapon** newWeapons = new Weapon*[++weaponCount];
	for(int i=0; i<weaponCount-1; i++)
		newWeapons[i] = weapons[i];
	newWeapons[weaponCount-1] = newWeapon;
	delete [] weapons;
	weapons = newWeapons;
	return true;
}

bool Arena::giveWeaponToFighter(string fighterName, string weaponName)
{
	int weaponIndex = findIndexOfWeapon(weaponName);
	//weapon exists
	if (weaponIndex >= 0){
		for(int i=0; i<fighterCount; i++)
		{

			if(fighters[i]->getName() == fighterName)
			{
				//Remove previous owners weapon
				if (weapons[weaponIndex]->getFighterName() != "None") {
					for (int j = 0; j<fighterCount; j++) {
						if (fighters[j]->getName() == weapons[weaponIndex]->getFighterName()) {
							fighters[j]->setWeapon(Weapon("None"));

						}
					}
				}
				//Fighter already have a weapon
				//replace previous weapons owner to none
				if (fighters[i]->getWeapon().getName() != "None"){
					for (int j=0 ; j<weaponCount; j++){
						if(weapons[j]->getName() == fighters[i]->getWeapon().getName()){
							weapons[j]->setFighterName("None");
						}
					}
				}
				weapons[weaponIndex]->setFighterName(fighterName);
				fighters[i]->setWeapon(*weapons[weaponIndex]);
				return true;
			}
		}
	}
	return false; //name is not found
}

bool Arena::removeFighter(string name) 
{
	for(int i=0; i<fighterCount; i++)
	{
		if(fighters[i]->getName() == name) //found the name
		{
			//remove the weapons owner
			if (fighters[i]->getWeapon().getName() != "None"){
				for(int j=0; j < weaponCount; j++){
					if (fighters[i]->getWeapon().getName() == weapons[j]->getName()){
						weapons[j]->setFighterName("None");
					}	
				}
			}
			
			//remove it
			Fighter** newFighters = new Fighter*[fighterCount-1];
			for(int j=0;j<fighterCount;j++)
			{
				if(j < i) newFighters[j] = fighters[j];
				else if(j > i) newFighters[j - 1] = fighters[j];
				else if(j == i)
				{
					delete fighters[j];
				}
			}
			fighterCount--;
			delete [] fighters;
			fighters = newFighters;
			return true;
		}
	}
	return false; //name is not found
}

bool Arena::removeWeaponFromFighter(string fighterName){
	for(int i=0; i<fighterCount; i++)
	{
		if(fighters[i]->getName() == fighterName) //found the name
		{
			//Check if the fighter is unarmed
			if (fighters[i]->getWeapon().getName() != "None"){
				//remove the weapons owner
				for (int j = 0; j < weaponCount ; j++){
					if (weapons[j]->getName() == fighters[i]->getWeapon().getName())
					{
						weapons[j]->setFighterName("None");
					}
				}
				return fighters[i]->setWeapon(Weapon("None"));
			}
		}
	}
	return false;
}

bool  Arena::destroyWeapon(string weaponName){
	for (int i=0; i<weaponCount; i++){
		if(weapons[i]->getName() == weaponName){
			//remove the weapon from the fighter if weapon has owner
			cout << weapons[i]->getFighterName() << endl;
			if(weapons[i]->getFighterName() != "None"){
				for (int j=0; j<fighterCount; j++){
					if(fighters[j]->getName() == weapons[i]->getFighterName()){
						fighters[j]->setWeapon(Weapon("None"));

					}
				}
			}

			//Remove the weapon
			Weapon** newWeapons = new Weapon*[weaponCount-1];
			for(int j=0;j<weaponCount;j++)
			{
				if(j < i) newWeapons[j] = weapons[j];
				else if(j > i) newWeapons[j - 1] = weapons[j];
				else if(j == i)
				{
					delete weapons[j];
				}
			}
			weaponCount--;
			delete [] weapons;
			weapons = newWeapons;
			return true;
		}
	}
	return false;
}

bool Arena::doesFighterExist(string name) const
{
	for(int i=0; i<fighterCount; i++)
	{
		if(fighters[i]->getName() == name)
		{
			return true;
		}
	}
	return false; //name is not found
}

bool Arena::doesWeaponExist(string name) const
{
	for(int i=0; i<weaponCount; i++)
	{
		if(weapons[i]->getName() == name)
		{
			return true;
		}
	}
	return false; //name is not found
}

bool  Arena::setReward(int mReward){
	if (mReward > 0){
		reward = mReward;
		return true;
	}
	return false;
}

bool  Arena::setMode (string mMode){
   if (mMode == "armed"){
	   mode = mMode;
	   return true;
   } else if (mMode == "unarmed"){
	   mode = mMode;
	   return true;
   }
   return false;
}

bool  Arena::fight (string fighter1Name, string fighter2Name){
   //Find fighter 1 and 2
   int indexOfFighter1 = findIndexOfFighter(fighter1Name);
   int indexOfFighter2 = findIndexOfFighter(fighter2Name);
   int damage1; int hp1;
   int damage2; int hp2;
   int turn = 0;
   const int FINAL_TURN = 5;

   if ((indexOfFighter1 == -1) || (indexOfFighter2 == -1)){
	   return false;
   } else {
	Fighter* fighter1 = fighters[indexOfFighter1];
	Fighter* fighter2 = fighters[indexOfFighter2];
	//compute damage of each fighter
	damage1 = (fighter1->getStr() +
			  fighter1->getWeapon().getPower()) *
			  computeMultiplier(fighter1->getWeapon().getType(),fighter2->getWeapon().getType());

	damage2 = (fighter2->getStr() +
			  fighter2->getWeapon().getPower()) *
			  computeMultiplier(fighter2->getWeapon().getType(),fighter1->getWeapon().getType());
	//assign hps
	hp1 = fighter1->getHp();
	hp2 = fighter2->getHp();
	//let them fight to death
	cout << "Fighter 1: " << endl;
	fighter1->print();
	fighter2->print();
	while((hp1 > 0) && (hp2 > 0) && (turn < FINAL_TURN)){
		hp1 = hp1 - damage2;
		hp2 = hp2 - damage1;
		cout << fighter1->getName() << " hits " << fighter2->getName() << " for " << damage1 << " damage" << endl;
		cout << fighter2->getName() << " remaining hp: "<< hp2 << endl << endl;

		cout << fighter2->getName() << " hits " << fighter1->getName() << " for " << damage2 << " damage" << endl;
		cout << fighter1->getName() << " remaining hp: "<< hp1 << endl << endl;
		turn++;
	}

	//outcomes
		if (hp1 <= 0){
			//fighter 1 loses
			if (hp2 > 0){
				//add money to the winner, deduct from the loser
				cout << fighter2->getName() << " wins" << endl;
				fighters[indexOfFighter2]->addMoney(reward);
				//if the loser didnt have any more money left, ask for death
				if (!fighters[indexOfFighter1]->removeMoney(reward)){
					string decision = getStringInput("My lord shall we kill this(" + fighter1->getName() + ") moneyless loser?(y/n)");
					// kill
					if (decision == "y"){
						removeFighter(fighter1->getName());
					}
				}
			} else{
			//otherwise draw
			cout << "fight is concluded in draw" << endl;
			}
		}else if (hp2 <= 0){
			//fighter 2 loses
			if (hp1 > 0){
				//add money to the winner, deduct from the loser
				cout << fighter1->getName() << " wins" << endl;
				fighters[indexOfFighter1]->addMoney(reward);
				//if the loser didnt have any more money left, ask for death
				if (!fighters[indexOfFighter2]->removeMoney(reward)){
					string decision = getStringInput("My lord shall we kill this(" + fighter2->getName() + ") moneyless loser?(y/n)");
					// kill
					if (decision == "y"){
						removeFighter(fighter2->getName());
					}
				}
			} else {
			//otherwise draw
			cout << "fight is concluded in draw" << endl;
			}
		}
		else {
			//otherwise draw
			cout << "fight is concluded in draw" << endl;
		}
		return true;
	}
}

int  Arena::computeMultiplier (string type1, string type2) const{
   if (mode == "unarmed"){
	   return 1;
   } else {
	   if (type1 == "melee"){
		   if ((type2 == "ranged") || (type2 == "unarmed")){
			   return 2;
		   }
	   } else if (type1 == "ranged"){
			if ((type2 == "magic") || (type2 == "unarmed")){
			   return 2;
		   }
	   } else if (type1 == "magic"){
			if ((type2 == "melee") || (type2 == "unarmed")){
			   return 2;
		   }
	   }
	   return 1;
   }
}

int  Arena::findIndexOfFighter (string name) const{
	for (int i=0; i < fighterCount;i++){
		if(name == fighters[i]->getName()){
			return i;
		}
	}
	return -1;
}
int  Arena::findIndexOfWeapon (string name) const{
	for (int i=0; i<weaponCount;i++){
		if(name == weapons[i]->getName()){
			return i;
		}
	}
	return -1;
}
