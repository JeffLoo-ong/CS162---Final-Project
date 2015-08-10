/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        7/18/15
** Description: Assignment 2 - Reptile People Implementation File
*********************************************************************/
#include "ReptilePeople.hpp"

int ReptilePeople::attack()
{
	int numDiceFace = 6;
	int numDice = 3;

	int attackTotal = 0; 
			
	for(int x = 0; x < numDice; x++)
	{
		attackTotal += rollDice(numDiceFace);
	}
	return attackTotal;
};

int ReptilePeople::defend()
{
	int numDiceFace = 6;
	int numDice = 1;

	int defendTotal = 0; 
			
	for(int x = 0; x < numDice; x++)
	{
		defendTotal += rollDice(numDiceFace);
	}
	return defendTotal;
};
