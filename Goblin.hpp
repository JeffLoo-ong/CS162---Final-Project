/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        7/18/15
** Description: Assignment 2 - Goblin Header File
*********************************************************************/
#ifndef GOBLIN_HPP
#define GOBLIN_HPP

#include <iostream>
#include "Creature.hpp"


class Goblin : public Creature
{
	public:
		Goblin(int armorIn = 3, int strengthIn = 8, std::string nameIn = "Gobgob") : Creature (armorIn, strengthIn, nameIn){};
		virtual int attack();
		virtual int defend();
};

#endif