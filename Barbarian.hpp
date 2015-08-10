/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        7/18/15
** Description: Assignment 2 - Barbarian Header File
*********************************************************************/
#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP

#include <iostream>
#include "Creature.hpp"


class Barbarian : public Creature
{
	public:
		Barbarian(int armorIn = 0, int strengthIn = 12, std::string nameIn = "Barbarb") : Creature (armorIn, strengthIn, nameIn){};
		virtual int attack();
		virtual int defend();
};

#endif
