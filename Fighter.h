
#ifndef FIGHTER_H
#define FIGHTER_H

#include <iostream>
#include <string>
#include "Weapon.h"

using namespace std;

class Fighter
{
  public:
	Fighter();                             // Empty constructor
	                                       // name = "None", str = 1, hp = 60, weapon name "None"
    Fighter(string name, int str, int hp); // Constructor; money = 1000,  hint: remember to initialize a generic weapon with name "None"
    string getName() const;                // Return the person's name
	int getStr() const;                    // Return fighters strength
	int getHp() const;                     // Return fighters Health Points
	int getMoney() const;                  // Return fighters Money
	Weapon& getWeapon();                   // Return fighters weapon

    /*
     * Give a weapon
	 * Set fighters weapon
	 * Return true
     */
    bool setWeapon(const Weapon& weapon);

    /*
     * Remove the weapon and switch the fighters weapon into unarmed.
	 * Switch weapons owner to "None"
     * Do nothing and return false if it cannot be done - which means the fighter is already unarmed
     */
    bool removeWeapon();
	 
	/*
	 * Add the specified amount to the fighters money,
	 */
	void addMoney (int amount);
	
	/*
	 * Remove the specified amount to the fighters money,
	 * return false if:
	 * (1) fighter has money < 0
	 */
	bool removeMoney (int amount);

    void print() const  // Print the information of the fighter; already completed; do not modify
    {
        cout << name  << " :" << endl;
		cout << "Str: " << str << ", Hp: " << hp << endl;
		cout << "Weapon: " << weapon.getName() << "(" << weapon.getType() << ")" << endl;
		cout << "Money: " << money << endl << endl;
    }

  private:
    string name;   // The string that stores the person's name
	int str;       // Strenght of the Fighter
	int hp;        // Health Point of the Fighter
	int money;     // Should be 1000 at first initialization
	Weapon weapon; // The weapon fighter is already holding the base should be unarmed.
   
};
#endif /*FIGHTER_H*/