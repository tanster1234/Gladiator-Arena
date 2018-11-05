
#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <string>

using namespace std;

class Weapon
{
public:
	Weapon();                                                        // Empty constructor
	                                                                 // name = "None", power = 1, fighterName = "None", type = "unarmed"
    Weapon(string name, string type, int power, string fighterName); // Constructor
	Weapon(string name);                                             // Constructor Overloading, if the object is created only with a name initialize as 
	                                                                 // power = 1, fighterName = "None", type = "unarmed"
    string getName() const;                                          // Return the weapon's name
	string getType() const;                                          // Return the weapon' s type can only be "melee", "ranged", "magic", "unarmed"
	int getPower() const;                                            // Return the weapons's power
	string getFighterName() const;                                   // Return the weapons current owner
	void setFighterName(string mfighterName);
    void print() const                                               // Print the name and timeslot of the activity; already completed; do not modify
    {
        cout << "" << name << endl;
		cout << "Owner: " << fighterName <<  endl;
		cout << "Power: " << power << "(" << type << ")" << endl << endl;
    }

private: 
    string name;        // The string that stores the weapon's name
	string type;        // The string that stores weapons type
	int power;          // The string that stores weapons power
    string fighterName; // The fighter that currently owns the weapon.
};
#endif /*WEAPON_H*/