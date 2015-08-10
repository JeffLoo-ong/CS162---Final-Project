/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        8/3/15
** Description: Assignment 4 - Queue Implementation File
*********************************************************************/
#include "Queue.hpp"

using namespace std;

Queue::Queue()
{
	front = NULL;
	rear = NULL;
}

void Queue::enqueue( Creature *creature )
{
   	if ( front == NULL )
	{
      	front = new QueueNode( creature );
      	rear = front;
      	//cout <<"New head created"<<endl;
	}

   	else
     {

     	rear->nextCreature = new QueueNode(creature);
     	rear = rear->nextCreature;

     	//Old Working code for static Queue
  //      	QueueNode *pointerToNode = front;

  //      	//This part ensures that we are adding on to the last node 
  //      	//of the current linked list
		// while ( pointerToNode->nextCreature != NULL )
		// {
  //         	pointerToNode = pointerToNode->nextCreature;
  //    	}

  //    	pointerToNode->nextCreature = new QueueNode( creature );
  //      	//cout <<"Another creature was added!" << endl;
     }
}

void Queue::displayQueue() const
{
	if ( front == NULL )
	{      
		cout << "Cannot display Queue items; Queue is empty!";
	}

  	else
	{
   		QueueNode *pointerToNode = front;

   		while (pointerToNode)
  		{
      			cout << pointerToNode->creature->getName() << ", ";

      			pointerToNode = pointerToNode->nextCreature;
   		}
   	}
}

Creature * Queue::getFront() 
{

	if ( front != NULL )
	{ 
		return front->creature;
	}

	else
	{
		cout << "Can't get Front of Queue, Queue is empty!";
		exit(1);	
	}
}

//Book has an int& as a param and sets the value within front to this
//Not sure why yet...
void Queue::removeFront()
{
	QueueNode *temp;
	if( front == NULL)
	{
		cout <<"The Queue is empty.\n";
	}
	else
	{
		temp = front;
		front = front->nextCreature;
		delete temp;
	}

	// Old working code for static Queue
	// QueueNode *pointerToNode = front;

	// QueueNode *previousPointer;

 //   	if ( front == NULL )
	// {      
	// 	cout << "Can't remove Front of Queue, Queue is empty!" << endl;
	// }

 //  	else
	// {
	// 	previousPointer = pointerToNode;

	// 	previousPointer->nextCreature = front->nextCreature;
		
	// 	delete front;

	// 	front = previousPointer->nextCreature;
	// }
}

bool Queue::isEmpty()
{
   	if ( front == NULL )
	{
		return true;
	}
	return false;
}

Queue::~Queue()
{
  	QueueNode *pointerToNode = front;

  	while ( pointerToNode != NULL )
  	{
      		QueueNode *target = pointerToNode;
     
      		pointerToNode = pointerToNode->nextCreature;

      		delete target;
  	}
}
