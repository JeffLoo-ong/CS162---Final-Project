/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        7/18/15
** Description: Assignment 2 - Shadow Implementation File
*********************************************************************/
#include "Shadow.hpp"

int Shadow::attack()
{
	int numDiceFace = 10;
	int numDice = 2;

	int attackTotal = 0; 
			
	for(int x = 0; x < numDice; x++)
	{
		attackTotal += rollDice(numDiceFace);
	}
	return attackTotal;
};

int Shadow::defend()
{
	int numDiceFace = 6;
	int numDice = 1;
	int defendTotal = 0; 
	int dodge = rand() % 2 + 1;	

	//50% chance to achieve dodge.
	if (dodge == 1)
	{	
		for(int x = 0; x < numDice; x++)
		{
			defendTotal += rollDice(numDiceFace);
		}
		return defendTotal;
	}
	else
	{
		//Shadow will have a impregnable armor to reduce damage
		defendTotal = 9999;
		return defendTotal;
	}
};
