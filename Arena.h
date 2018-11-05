
#ifndef ARENA_H
#define ARENA_H
#include "Fighter.h"

class Arena
{
  public:
    Arena();  // Constructor; hint: remember to initialize weaponCount, fighterCount to 0 and weapons, fighters to NULL, reward = 1000, mode = "armed"
	Arena(const Arena& a); // Copy constructor, deep copy dynamically allocated memory
	~Arena(); // Destructor; hint: remember to deallocate any dynamically-allocated memory

    /*
	 * Add a fighter and return true if the fighter can be added successfully
	 * Do nothing and return false otherwise - that means the fighter name already exists (i.e. same as one of the existing fighters')
	 */
    bool addFighter(string name, int str, int hp);

	/*
	 * Add a new weapon. Do not forget that a newly forged weapon does not have to have a owner.
	 * Do nothing and return false if:
	 * (1) the type is wrong(not one of "melee", "ranged", "magic", "unarmed") 
	 * (2) if the weapon already exists
	 */
	bool addWeapon(string name, string type, int power);

    /*
	 * Give a weapon for the specified fighter and return true if it can be done successfully
	 * Do nothing and return false otherwise - that means either
	 * (1) the weapon cannot be found by the given name
	 * (2) the person cannot be found by the given name
	 * If fighter already has a weapon, remove the weapon from fighters inventory, change the owner of the previous weapon,\
	 * If the weapon that is being transferred already has an owner, empty the weapon of the previous owner.
	 * and add the new weapon to fighters inventory.
	 */
    bool giveWeaponToFighter(string personName, string weaponName);

    /*
	 * Remove the specified fighter and return true if it can be done successfully
	 * Do nothing and return false if it cannot be done - which means the fighter cannot be found by the given name
	 * Dont forget to modify the weapons owner if, the fighter has a weapon
	 */
    bool removeFighter(string name);

    /*
	 * Remove the specified weapon from the specified fighter and return true if it can be done successfully
	 * Do nothing and return false if it cannot be done - that means either
	 * (1) the fighter cannot be found by the given name
	 * (2) calling the function removeWeapon on the found fighter object returns false (which signals that it is unarmed)
	 */
    bool removeWeaponFromFighter(string fighterName);

	/*
	 * Destroy the specified weapon. and return true if it can be done succesfully
	 * Do nothing and return false if it cannot be done - that means
	 * there is no weapon by that name
	 * Do not forget to remove the weapon from it' s owner if the weapon has a owner.
	 */
	bool destroyWeapon(string weaponName);

    /*
     * Return true if a person with the given name exists already
     * Return false otherwise
     */
    bool doesFighterExist(string name) const;

	/*
     * Return true if a person with the given name exists already
     * Return false otherwise
     */
    bool doesWeaponExist(string name) const;

    /*
     * Set / Change the reward that fighters will earn after each fight
	 * Return false if input is smaller than 0, this is reward not punishment
     */
    bool setReward(int mReward);

	/* 
	 * Set the fighting mode, can only be armed or unarmed. 
	 * Return false if input is anything different than "armed" or "unarmed"
	 */
	bool setMode(string mMode);
	
    /*
	 * If there are no such fighters with corresponding names, return false,
	 * else you will implement the function descripted below.
     * This is the function where you will define the rules of the fight. The two fighter who are given as inputs will fight to death
     * This function will calculate each fighters power with the formula:
     * Damage = (Str + Weapon Power) * Handicap
	 * Where Handicap is the superiority of the weapon type. You can use helper function computeMultiplier to get the value.
	 * You will implement a loop. Loop will decrease the health points of the opponent by the amount of their dmg
	 * Ex:
	 * Fighter1 dmg = 50, hp = 500. Fighter2 dmg = 25, hp = 700;
	 * after 1st turn
	 * Figther1 hp = 500-25 = 475, Fighter2 hp = 700 - 50 = 650
	 * after 2nd turn
	 * Figther1 hp = 475-25 = 450, Fighter2 hp = 650 - 50 = 600, continiue until one of the fighters drop below 0 or turns >10
	 * 
	 * There are three outcomes of a fight 
	 * 1) The fighter wins, at the end of the turns his hp is > 0, and opponent has hp <= 0
	 * 2) The fighter loses, at the end of the turns his hp <= 0, and opponent has hp > 0
	 * 3) The fight is draw, either both fighters hp <= 0, or fight lasts longer than 5 turns.
	 *
	 * The winner fighter earns money equal to the amount of reward variable. Loser loses money equal to the amount of reward.
	 * If loser already has 0 or negative amount of money, no more money will be substracted but instead, the user will be asked a question to execute or let the fighter live.
	 * If the fighters money > 0, Money can go negative but in this case execution will not be asked.
	 * when money <= 0 before the fight and the fighter loses, this time money will not be deducted but execution will be asked.
     */
    bool fight(string fighter1Name, string fighter2Name);

    void printWeapons() const // Print the schedule of all persons one by one; already completed; do not modify
    {
    	if(weaponCount == 0) cout << "There is no weapon in the armory yet." << endl;
    	else
    	{
    		cout << "Listing all our weapons("<< weaponCount<< ") "<< (weaponCount>1?"weapons":"weapon") << "..." << endl;
    		for(int i=0; i<weaponCount; i++)
    		{
				cout << i << endl;
    			weapons[i]->print();
    		}
    	}
    }

	void printFighters() const // Print the schedule of all persons one by one; already completed; do not modify
    {
    	if(fighterCount == 0) cout << "There is no fighter in the arena yet." << endl;
    	else
    	{
    		cout << "Listing all the fighters(" << fighterCount << ") "<< (fighterCount>1?"fighters":"fighters") << "..." << endl;
    		for(int i=0; i<fighterCount; i++)
    		{
				cout << i << endl;
    			fighters[i]->print();
    		}
    	}
    }

	string getStringInput(string question) const
	{
		string input;
		cout << question << " ";
		cin >> input;
		return input;
	}
	
  private:
    Fighter** fighters; // The dynamic array, which is just big enough, that stores all the fighters in the system; it should be NULL at the beginning
    Weapon** weapons;   // The dynamic array, which is just big enough, that stores all the weapons in the system; it should be NULL at the beginning
	int fighterCount;   // The number of persons; it should be 0 at the beginning
	int weaponCount;    // The number of weapons; it should be 0 at the beginning
	int reward;         // The value of the reward after each fighter
	string mode;        // It can have two values "armed" or "unarmed". By default it is "armed"

	/* Helper function 
	 * If arena mode is "unarmed" no weapon will have any effect,
	 * return multiplier as 1
	 * else follow return a value according to guidelines below
	 * Computes multiplier according to weapon types.
	 * If type1 is stronger than type 2 multiplier will return 2.
	 * Otherwise return 1.
	 * Melee > Ranged, Ranged > Magic, Magic > Melee,
	 * Any weapon is stronger than unarmed.
	 *
	 * 2nd explanation
	 * Melee triumps over ranged due to their heavy shields, however are very weak to magic items big fireball.
	 * Ranged fighters on the other hand can eliminate magic users very fast, however have trouble with melee.
	 * Magic fighter can toy with their until they can reach them, only if the opponent is melee. If they are facing ranged opponents they have hard time.
	 * If a fighter is against an unarmed fighter they are automatically in advantage.
	 * We can summarize weapon types Melee > Ranged > Magic > Melee and Any Weapon >> Unarmed
	 * If a fighter has a weapon that is superior to their opponent their advantage multiplier is 2
	 */
	int computeMultiplier(string type1, string type2) const;

	// Find the index of the fighter object with the given name,
	// return -1 if no such fighter exists
	int findIndexOfFighter(string name) const;
	
	// Find the index of the weapon object with the given name,
	// return -1 if no such weapon exists
	int findIndexOfWeapon(string name) const;
};
#endif /*ARENA_H*/
