
#include <iostream
#include <string>
#include "Arena.h"

using namespace std;

// A helper function to help with getting an integer input with validation
int getIntegerInput(string question, int lowerBound, int upperBound)
{
    int input = lowerBound - 1;
    while(input<lowerBound || input>upperBound)
    {
        cout << question << " [" << lowerBound << "-" << upperBound << "]? ";
        cin >> input;
    }
    return input;
}

// A helper function to help with getting an string input
string getStringInput(string question)
{
	string input;
	cout << question << " ";
	cin >> input;
	return input;
}

// main is the entry point of the program
int main()
{
    Arena arena;
    cout << "Welcome to the ARENA" << endl << endl;

    while(true)
    {
        cout << "1. Check Fighters" << endl;
        cout << "2. Go to Armory" << endl;
        cout << "3. Recruit fighter" << endl;
        cout << "4. Dismiss a fighter" << endl;
        cout << "5. Arena Options" << endl;
        cout << "6. Fight" << endl;
        cout << "7. Recruit basic legion and stock weapons" << endl;
		cout << "8. Test copy constructor" << endl;
        cout << "0. Quit" << endl;

        int option = getIntegerInput("What would you like to do, your grace?", 0, 8);
    	cout << endl;

        switch(option)
        {
        	case 0:
        	{
        	    cout << "Till next time" << endl;
        		return 0; //quit
        	}
            case 1:
            {
                arena.printFighters();
                break;
            }
            case 2:{
            	cout << "What would you like to do in armory, your highness?" << endl;
                cout << "1. View Weapons" << endl;
                cout << "2. Forge a new Weapon" << endl;
                cout << "3. Arm a Fighter" << endl;
                cout << "4. Destroy a Weapon" << endl;
                cout << "0. Return" << endl;

                int optionArmory = getIntegerInput("", 0, 4);
                switch(optionArmory){
					case 0:{
						cout << "Returning to arena" << endl;
						break;
					}
					case 1:{
						arena.printWeapons();
						break;
					}
					case 2:{
						string weaponName = getStringInput("How would you like to name the weapon?");
						string weaponType = getStringInput("What is the type of the weapon?");
						int weaponPower = getIntegerInput("How powerful is the weapon?", 0,15);

						if(arena.addWeapon(weaponName, weaponType, weaponPower)){
						  cout << weaponName << " has been added." << endl;
						} else{
							cout << weaponName << " cannot be added due to an name/type conflict." << endl;
						}
						break;
					}
					case 3:{
						string weaponName = getStringInput("What is the name of weapon, you want to give, your majesty? ");
						string fighterName = getStringInput("What is the name of fighter, you want to give, your majesty? ");
						if(arena.giveWeaponToFighter(fighterName,weaponName)){
							cout << weaponName << " has been given to " << fighterName << endl;
						} else {
							cout << "My biggest regrets my lord, there is no such" << fighterName << "\\" << weaponName << endl;
						}
						break;
					}
					case 4:{
						string weaponName = getStringInput("What is the name of weapon, you do not fancy anymore?, your majesty? ");
						if(arena.destroyWeapon(weaponName)){
							cout << weaponName << " has been destroyed" << endl;
						} else {
							cout << weaponName << " Unfortunately there is no such weapon, my lord." << endl;
						}
						break;
					}
                }
                break;
            }
            case 3:
            {
            	string fighterName = getStringInput("What is the name of this mighty warrior? ");
            	int fighterStrength = getIntegerInput("What is the strength of the fighter?", 1, 20);
            	int fighterHp = getIntegerInput("How durable is the warrior?", 60,250);

            	if(arena.addFighter(fighterName, fighterStrength, fighterHp)){
				  cout << fighterName << " has been added." << endl;
            	} else{
            		cout << fighterName << " cannot be recruited due to name conflict." << endl;
            	}
            	break;
            }
            case 4:
            {
            	cout << "My lord, which warrior dissappointed you, give me the name and I will get rid of him." << endl;
            	string fighterName = getStringInput("");
                if(arena.removeFighter(fighterName))
                {
                	 cout << fighterName << " has been removed." << endl;
                } else {
                	 cout << fighterName << " Unfortunately there is no such warrior, my lord." << endl;
                }
                break;
            }
            case 5:
            {
            	cout << "My lord you want to change the rules of the arena?" << endl;
				int reward = getIntegerInput("My lord, what shall be the new reward?", 1, 1000);
				int mode = getIntegerInput("My lord, please select the rules for fighting:  unarmed[0], armed[1]", 0, 1);
				if (arena.setReward(reward)) {
					cout << "New reward is set to " << reward << endl;
				}
				else {
					cout << "Invalid reward" << endl;
				}
				if (mode == 0) {
					arena.setMode("unarmed");
					cout << "Rule has been set to unarmed" << endl;
				}
				else if (mode == 1) {
					arena.setMode("armed");
					cout << "Rule has been set to armed" << endl;
				}
				else {
					cout << "Invalid rules my lord, (servant slowly fades away)" << endl;
				}
                break;
            }
            case 6:
            {
            	cout << "Your highness i require the name of the contestants: " << endl;
            	string fighterName1 = getStringInput("What is the first fighters's name?");
				string fighterName2 = getStringInput("What is the second fighter's name?");
                if(!arena.fight(fighterName1, fighterName2))
                {
                    cout << "My lord my apologies, there are no such fighters in the arena." << endl ;
                }
                break;
            }
            case 7:
            {
            	arena.addWeapon("Sword", "melee", 10);
            	arena.addWeapon("Bow", "ranged", 10);
            	arena.addWeapon("Staff", "magic", 10);


            	arena.addFighter("Warrior", 10, 60);
            	arena.addFighter("Ranger", 10, 60);
            	arena.addFighter("Mage", 10, 60);

            	arena.giveWeaponToFighter("Warrior", "Sword");
            	arena.giveWeaponToFighter("Ranger", "Bow");
            	arena.giveWeaponToFighter("Mage", "Staff");

            	cout << "Legion recruited" << endl;
            }
			case 8:
			{
				/*
				 *testing copy constructor
				 */
				cout << "Testing copy constructor, otherwise functionless" << endl;
				Arena arena2;
				arena2.addWeapon("Sword", "melee", 10);
				arena2.addWeapon("Bow", "ranged", 10);
				arena2.addWeapon("Staff", "magic", 10);


				arena2.addFighter("Warrior", 10, 60);
				arena2.addFighter("Ranger", 10, 60);
				arena2.addFighter("Mage", 10, 60);

				arena2.giveWeaponToFighter("Warrior", "Sword");
				arena2.giveWeaponToFighter("Ranger", "Bow");
				arena2.giveWeaponToFighter("Mage", "Staff");
				
				Arena arena3 = arena2; 

				cout << "Printing Arena2" << endl;
				arena2.printFighters();
				cout << "Printing Arena3" << endl;
				arena3.printFighters();

				cout << endl << "Making changes" << endl;
				arena2.removeFighter("Warrior");
				arena2.removeFighter("Ranger");
				arena2.removeFighter("Mage");

				cout << "Printing Arena2" << endl;
				arena2.printFighters();
				cout << "Printing Arena3" << endl;
				arena3.printFighters();

				cout << endl << "Copy constructors tested" << endl;
			}
        }

        cout << endl;
    }
    return 0;
}
