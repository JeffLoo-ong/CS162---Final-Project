/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        7/18/15
** Description: Assignment 2 - Blue Men Header File
*********************************************************************/
#ifndef BLUEMEN_HPP
#define BLUEMEN_HPP

#include <iostream>
#include "Creature.hpp"


class BlueMen : public Creature
{
	public:
		BlueMen(int armorIn = 3, int strengthIn = 12, std::string nameIn = "BluesMan") : Creature (armorIn, strengthIn, nameIn){};
		virtual int attack();
		virtual int defend();
};

#endif