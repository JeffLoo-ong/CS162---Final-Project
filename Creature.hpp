/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        7/18/15
** Description: Assignment 2 - Creature Header File
*********************************************************************/
#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <iostream>
#include <cstdlib>
#include <string>

using std::string;

class Creature
{
	protected:
		int armor,
			strength;

		string name;

		bool achillesTorn;

	public:
		Creature(int armorIn, int strengthIn, string nameIn)
		{
			this->setArmor(armorIn);
			this->setStrength(strengthIn);
			this->setName(nameIn);
			this->setAchilles(false);
		};

		void setAchilles(bool tornStatus)
		{
			achillesTorn = tornStatus;
		}

		bool getAchilles()
		{
			return achillesTorn;
		}

		void setArmor(int armorIn)
		{
			armor = armorIn;
		};

		int rollDice(int numFace)
		{
			int result = rand() % numFace + 1;	
			return result;
		}

		virtual int getArmor()
		{
			return armor;
		};

		void setStrength(int strengthIn)
		{
			strength = strengthIn;
		};
		
		virtual int getStrength()
		{
			return strength;
		};

		void setName(string nameIn)
		{
			name = nameIn;
		}

		virtual string getName()
		{
			return name;
		}

		virtual int attack() = 0;
		virtual int defend() = 0;
};

#endif
