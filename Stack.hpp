/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        8/3/15
** Description: Assignment 4 - Stack Implementation File
*********************************************************************/
#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "Creature.hpp"

using namespace std;

class Stack
{
	protected:
    	 struct StackNode
    	 {
         	Creature *creature;

       		StackNode *nextitem;

       		StackNode(Creature *creatureIn, StackNode *nextitem1 = NULL)
       		{
          		creature = creatureIn;

          		nextitem = nextitem1;
       		}      
    	 };

    	 StackNode *origin;

	public:
	    Stack();
	    ~Stack();                   
      void displayStack() const;  	
	    void push(Creature *creature);
      Creature * peek() const;
    	void pop();
    	void isEmpty();
};

#endif
