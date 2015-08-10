/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        7/18/15
** Description: Assignment 2 - Reptile People Header File
*********************************************************************/
#ifndef REPTILE_HPP
#define REPTILE_HPP

#include <iostream>
#include "Creature.hpp"


class ReptilePeople : public Creature
{
	public:
		ReptilePeople(int armorIn = 7, int strengthIn = 8, std::string nameIn ="ReptileDude") : Creature (armorIn, strengthIn, nameIn){};
		virtual int attack();
		virtual int defend();
};

#endif