/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        8/3/15
** Description: Assignment 4 - Stack Header File
*********************************************************************/
#include "Stack.hpp"

using namespace std;

Stack::Stack()
{
	origin = NULL;
}

void Stack::push( Creature *creature )
{
   	if ( origin == NULL )
	{
      	origin = new StackNode( creature );
	}

   	else
     {
       	StackNode *pointerToNode = origin;

		while ( pointerToNode->nextitem != NULL )
		{
          	pointerToNode = pointerToNode->nextitem;
     	}

     	pointerToNode->nextitem = new StackNode( creature );
     }
}

void Stack::displayStack() const
{
	if ( origin == NULL )
	{      
		cout << "Cannot display Stack items; Stack is empty!" << endl;
	}

  	else
	{
   		StackNode *pointerToNode = origin;
   		while (pointerToNode)
  		{
      			cout << pointerToNode->creature->getName() << ", ";
      			pointerToNode = pointerToNode->nextitem;
   		}
   	}
}




Creature * Stack::peek() const
{
	Creature *failPtr = NULL;
	if ( origin == NULL )
	{      
		cout << "Cannot peek Stack item; Stack is empty!" << endl;
	}
  	else
	{
		StackNode *pointerToNode = origin;
		while ( pointerToNode->nextitem != NULL )
		{
        		pointerToNode = pointerToNode->nextitem;
		}
		return pointerToNode->creature;
	}
	
	return failPtr;
}

void Stack::pop()
{
	StackNode *pointerToNode = origin;
	StackNode *previousPointer;
	int target = 0;
	int current = 0;

   	if ( origin == NULL )
	{      
		cout << "Cannot remove Stack item; Stack is empty!" << endl;
	}
  	else
	{
		while ( pointerToNode->nextitem != NULL )
		{
			pointerToNode = pointerToNode->nextitem;

			target ++;		
		}

		pointerToNode = origin;

		while ( current != ( target  )  )
		{
			previousPointer = pointerToNode;

        	pointerToNode = pointerToNode->nextitem;
	
			current ++;
		
		}

		previousPointer->nextitem = pointerToNode->nextitem;

		if ( target == 0 )
   		{
			origin = 0;
  		}
	}
}

void Stack::isEmpty()
{
   	if ( origin == NULL )
	{
		cout << "Stack is Empty!" << endl;
	}
}

Stack::~Stack()
{
  	StackNode *pointerToNode = origin;

  	while ( pointerToNode != NULL )
  	{
      		StackNode *target = pointerToNode;
      		pointerToNode = pointerToNode->nextitem;
      		delete target;
  	}
}
