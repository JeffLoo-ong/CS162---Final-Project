/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        8/3/15
** Description: Assignment 4 - Queue Header File
*********************************************************************/
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include "Creature.hpp"

using namespace std;

class Queue
{
	protected:
    	struct QueueNode
    	{
       		Creature *creature;
       		QueueNode *nextCreature;
       		QueueNode(Creature *creatureIn, QueueNode *nextCreature1 = NULL)
       		{
          		creature = creatureIn;
          		nextCreature = nextCreature1;
       		}      
    	};

    	QueueNode *front;
      QueueNode *rear;

	public:
      Queue(); 
	     ~Queue();                   
      void displayQueue() const; 	
	    void enqueue(Creature *creature);
    	Creature* getFront() ;
    	void removeFront();
    	bool isEmpty();
};

#endif
