/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        7/18/15
** Description: Assignment 2 - Shadow Header File
*********************************************************************/
#ifndef SHADOW_HPP
#define SHADOW_HPP

#include <iostream>
#include "Creature.hpp"


class Shadow : public Creature
{
	public:
		Shadow(int armorIn = 0, int strengthIn = 12, std::string nameIn = "Shadow") : Creature (armorIn, strengthIn, nameIn){};
		virtual int attack();
		virtual int defend();
};

#endif