/*********************************************************************
** Author:      Jeffrey Luong 
** Date:        8/6/15
** Description: Assignment 4 - main implemention file
** Note:		Search '//textenable//' and delete to enable text
*********************************************************************/
#include <iomanip>
#include "Creature.hpp"
#include "Barbarian.hpp"
#include "Goblin.hpp"
#include "ReptilePeople.hpp"
#include "BlueMen.hpp"
#include "Shadow.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

using std::cin;
using std::cout;
using std::endl;

//Define values for max hp
static const int MAX_BARB_HP = 12;
static const int MAX_GOB_HP  = 8;
static const int MAX_REP_HP  = 18;
static const int MAX_BLUE_HP = 12;
static const int MAX_SHAD_HP = 12;

//Prototypes
void selectWarriors(Queue &pQueue, int numCreatures, int playerNum);
void battle(Creature *c1, Creature *c2, Queue &p1queue, Queue &p2queue, int &p1Score, int &p2Score, Stack &loserStack);
void restoreHP(Creature *winner);
void printScore(int &p1Score, int &p2Score);
void printScoringTable();
int addPoints(Creature *c1, Creature *c2);

int main()
{
	srand(time(NULL));
	
	//Create queues to hold player's creatures.
	Queue player1;
	Queue player2;

	//Creates stack to hold losers
	Stack loserStack;

	int numCreatures; 	//Stores number of total creatures in each queue
	int p1Score = 0, 
		p2Score = 0;	//Stores score for teams
	int battleCount = 1;//Stores number of battles
	
	cout <<"Welcome to the Polymorphic Battlegrounds!"<<endl;
	cout <<"How many creatures would you like to duke it out with?" << endl;
	cin >> numCreatures;

	//Int validation
	while(!cin)
	{
    	cout << "That was no integer! Please enter an integer: ";
   	 	cin.clear();
    	cin.ignore();
    	cin >> numCreatures;
	}

	//Player1 select
	selectWarriors(player1, numCreatures, 1);
	cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	//Player2 select
	selectWarriors(player2, numCreatures, 2);

	printScoringTable();
	
	cout << endl;
	cout << "***********************************************" << endl;
	cout << "Let's get ready to RRRRRRUMMMMMMBBLLLEEEEE!!!!!" << endl;
	cout << "***********************************************" << endl 
		 << endl;

	cin.get();

	//So long as there are creatures in both queues, pit them against eachother
	while(player1.isEmpty() == false && player2.isEmpty() == false)
	{	
		cout <<"Battle " << battleCount<< "!" <<endl;
		//Assign temporary creature pointers
		Creature *p1Creature = player1.getFront();
		Creature *p2Creature = player2.getFront();

		//Remove from front of Queue
		player1.removeFront();
		player2.removeFront();

		battle(p1Creature, p2Creature, player1, player2, p1Score, p2Score, loserStack);

		cout << "Player1 Queue: "; player1.displayQueue(); cout << endl;
		cout << "Player2 Queue: "; player2.displayQueue(); cout << endl;
		cout << "Loser pile:   "; loserStack.displayStack(); cout << endl;

		cout << endl <<"--------------------------------------------"<<endl;

		battleCount++;
	}

	cout <<endl <<endl<< "FINAL RESULTS!!!\n" <<"********************************************" <<endl;

	printScore(p1Score, p2Score);
	cout<< "OVERAL RESULT: ";
	if(p1Score > p2Score)
	{
		cout <<"Team 1 Wins!" << endl;
	}
	else if(p2Score > p1Score)
	{
		cout <<"Team 2 Wins!" << endl;
	}
	else
	{
		cout <<"DRAW!" << endl;
	}

	//If Player 1 wins, push the remaining creatures onto the loser stack.
	while(player1.isEmpty() == false)
	{
		Creature *p1Creature = player1.getFront();
		player1.removeFront();
		loserStack.push(p1Creature);
	}	
	//If Player 2 wins, push the remaining creatures onto the loser stack.
	while(player2.isEmpty() == false)
	{
		Creature *p2Creature = player2.getFront();
		player2.removeFront();
		loserStack.push(p2Creature);
	}	

	//cout << endl <<"Loser Pile: "; loserStack.displayStack(); cout << endl << endl;

	//Print top 3 creatures
	cout << "Top 3 creatures" << endl;
	for(int x = 0; x < 3; x++)
	{
		Creature *tempCreature = loserStack.peek();
		if (tempCreature == NULL)
		{
			cout << "Not enough creatures to name top 3!"<<endl;
			exit(1);
		}
		cout << x+1 << ". " << tempCreature->getName() << endl;
		loserStack.pop();
	}

	cout <<"********************************************"<< endl << endl;

	return 0;
}

/*********************************************************************
**Function:     battle()
**Description:  Does all calculations for battle until one creature 
**				wins. The loser is returned to be pushed into the 
**				loser stack.
**				To enable text search '//textenable//'
**Parameters:   Creature*, Creature*, Queue&, Queue&, int&, int&,
**				Stack&
**Returns:      Creature*
*********************************************************************/
void battle(Creature *c1, Creature *c2, Queue &player1, Queue &player2, int &p1Score, int &p2Score, Stack &loserStack)
{
	int roundCount = 1;			//Round Tracker
	bool battleDone = false;	//Turns true when one creature dies

	cout << endl <<"Player 1's "<< c1->getName() << " VS " <<"Player 2's " << c2->getName() << endl;
	while(!battleDone)
	{	
		//Hold the damage and defense values in these variables for calculations and printing
		int dmg1, dmg2, def1, def2, atk1, atk2;

		//textEnable//cout <<"Round " << roundCount <<"!"<<endl << endl;


		///////////////////////////////////////////////////////////////////////////////////
		//Battle Phase - Attack Calculation
		///////////////////////////////////////////////////////////////////////////////////

		//Do an achilles check to reduce damage if necessary
		//Round damage up after typecasting to int
		if(c1->getAchilles() == true)
		{
			atk1 = int(.5*(c1->attack()));
			//textEnable//cout << c1->getName() << " attack was halved to " << atk1 << "!" << endl;
		}
		else	
		{
			atk1 = c1->attack();
		}

		if(c2->getAchilles() == true)
		{
			atk2 = int(.5*(c2->attack()));
			//textEnable//cout << c2->getName() << " attack was halved to " << atk2 << "!" << endl;
		}
		else
		{
			atk2 = c2->attack();
		}

		///////////////////////////////////////////////////////////////////////////////////
		//Battle Phase - Defense Calculation
		///////////////////////////////////////////////////////////////////////////////////
		def2 = c2->defend() + c2->getArmor();
		def1 = c1->defend() + c1->getArmor();


		///////////////////////////////////////////////////////////////////////////////////
		//Goblin Vs Non-Goblin Only - Achilles Tear Phase
		///////////////////////////////////////////////////////////////////////////////////
		
		//Check to see if someone tore their achilles yet to skip this portion
		if(c1->getAchilles() == true || c2->getAchilles() == true)
		{
			//continue
		}
		//Check if first creature is a goblin and they attack with 12..
		else if((c1->getName() == "Gobgob") && atk1 == 12)
		{	
			//Make sure they only affect non-goblins
			if(c2->getName() == "Gobgob")
			{
				//continue
			}
			else
			{
				//Tear the other contestants achilles
				c2->setAchilles(true);
				//textEnable//cout << c2->getName() << " has torn their achilles!" << endl
				//textEnable//	<<"Attack reduced to half starting next round!" << endl;
			}
		}
		//Check if second creature is a goblin and they attack with 12..
		else if((c2->getName() == "Gobgob") && atk1 == 12)
		{	
			//Make sure they only affect non-goblins
			if(c1->getName() == "Gobgob")
			{
				//continue
			}
			else
			{	
				//Tear the other contestant's achilles
				c1->setAchilles(true);
				//textEnable//cout << c1->getName() << " has torn their achilles!" << endl
				//textEnable//	<<"Attack reduced to half starting next round!" << endl;
			}
		}

		///////////////////////////////////////////////////////////////////////////////////
		//Damage Calculation Phase
		///////////////////////////////////////////////////////////////////////////////////

		//Damage calculation: Attack - (Defense + Armor)
		dmg1 = (atk1) - (def2);
		dmg2 = (atk2) - (def1);

		//Apply damage to 0 if negative damage incurred
		if(dmg1 < 0)
		{
			dmg1 = 0;
		}

		if (dmg2 < 0)
		{
			dmg2 = 0;
		}


		///////////////////////////////////////////////////////////////////////////////////
		//Battle Results Print Phase -- 
		///////////////////////////////////////////////////////////////////////////////////
		
		//Creature 1 attack against Creature 2 output
		//textEnable//cout << c1->getName() << " attacks for " << atk1 << " damage!" << endl;
		//All other creatures but Shadow will fall in this category
		if (def2 < 18) 
		{
			//textEnable//cout << c2->getName() << " defends for " << def2 << " damage!" << endl;
		}
		//Shadow has 50% chance to achieve a 9999 defense roll for "dodge"
		else 
		{
			//textEnable//cout <<c1->getName() << " hit " <<c2->getName() << "'s shadow!" << endl;
			//textEnable//cout <<c2->getName() << " avoided all damage!" << endl;
		}	
		//Make sure there is no negative damage. Only apply strength reduction in positive damage.
		if(dmg1 > 0)
		{	
			c2->setStrength((c2->getStrength())-dmg1);
		}
		else
		{
			//textEnable//cout << c2->getName() << " fully defended attack!" << endl;
		}

		//Creature 2 attack against Creature 1 output
		//textEnable//cout << endl << c2->getName() << " attacks for " << atk2 << " damage!" << endl;
		//All other creatures but Shadow will fall in this category
		if(def1 <18)
		{
			//textEnable//cout << c1->getName() << " defends for " << def1 << " damage!" << endl;
		}	
		//Shadow has 50% chance to achieve a 9999 defense roll for "dodge". Only Shadow should be able to get here
		else
		{
			//textEnable//cout <<c2->getName() << " hit " <<c1->getName() << "'s shadow!" << endl;
			//textEnable//cout <<c1->getName() << " avoided all damage!" << endl;
		}
		//Make sure there is no negative damage. Only apply strength reduction in positive damage.
		if(dmg2 > 0)
		{
			c1->setStrength((c1->getStrength())-dmg2);
		}
		else
		{
			//textEnable//cout << c1->getName() << " fully defended attack!" << endl;			
		}

		//textEnable//cout << endl;

		///////////////////////////////////////////////////////////////////////////////////
		//Results Phase
		///////////////////////////////////////////////////////////////////////////////////

		//textEnable//cout <<c1->getName() << " has " << c1->getStrength() << " Strength left."<< endl;
		//textEnable//cout <<c2->getName() << " has " << c2->getStrength() << " Strength left."<< endl;

		//Draw
		if (c1->getStrength() <= 0 && c2->getStrength() <= 0)
		{
			//Player 1's creature goes first. Sorry Player 1.
			cout << "Draw! Both creatures killed each other :O" << endl;
			loserStack.push(c1);
			loserStack.push(c2);
			printScore(p1Score, p2Score);
			battleDone = true;
		}
		//Creature 1 victorius
		//Restore 1/3 HP
		//Add the score
		//Push loser onto stack
		else if (c2->getStrength() <= 0 && c1->getStrength() >= 0)
		{
			cout <<"Player 1's " << c1->getName() << " is victorius!" << endl;
			restoreHP(c1);
			player1.enqueue(c1);
			p1Score += addPoints(c1, c2);
			printScore(p1Score, p2Score);
			loserStack.push(c2);
			battleDone = true;
		}
		//Creature 2 is victorius
		//Restore 1/3 HP
		//Add the score
		//Push loser onto stack
		else if (c1->getStrength() <= 0 && c2->getStrength() >= 0)
		{
			cout <<"Player 2's " << c2->getName() << " is victorius!" << endl;
			restoreHP(c2);
			player2.enqueue(c2);
			p2Score += addPoints(c2, c1);
			printScore(p1Score, p2Score);
			loserStack.push(c1);	
			battleDone = true;
		}
		else
		{
			// Disabled
			// cout<<"Hit enter for the next round!" << endl;
			// cin.get();

			roundCount++;
		}

		//textEnable//cout << endl;

	}//while
}

/*********************************************************************
**Function:     restoreHP()
**Description:  Restores 1/3 HP for the winner of the battle (floor div) 
**Parameters:   Creature*
**Returns:      none
*********************************************************************/
void restoreHP(Creature *winner)
{
	int tempStrength;	//Hold current str of winner

	if (winner->getName() == "Barbarb")
	{
		tempStrength = winner->getStrength();
		tempStrength = tempStrength*.3;

		//Prevent strength limit break
		if(tempStrength > MAX_BARB_HP)
		{
			tempStrength = MAX_BARB_HP;
		}	

		winner->setStrength(tempStrength);
	}
	else if(winner->getName() == "BluesMan")
	{
		tempStrength = winner->getStrength();
		tempStrength = tempStrength*.3;

		//Prevent strength limit break
		if(tempStrength > MAX_BLUE_HP)
		{
			tempStrength = MAX_BLUE_HP;
		}	

		winner->setStrength(tempStrength);
	}
	else if(winner->getName() == "Gobgob")
	{
		tempStrength = winner->getStrength();
		tempStrength = tempStrength*.3;

		//Prevent strength limit break
		if(tempStrength > MAX_GOB_HP)
		{
			tempStrength = MAX_GOB_HP;
		}	

		winner->setStrength(tempStrength);
	}
	else if(winner->getName() == "ReptileDude")
	{
		tempStrength = winner->getStrength();
		tempStrength = tempStrength*.3;

		//Prevent strength limit break
		if(tempStrength > MAX_REP_HP)
		{
			tempStrength = MAX_REP_HP;
		}	

		winner->setStrength(tempStrength);
	}
	else if(winner->getName() == "Shadow")
	{
		tempStrength = winner->getStrength();
		tempStrength = tempStrength*.3;

		//Prevent strength limit break
		if(tempStrength > MAX_SHAD_HP)
		{
			tempStrength = MAX_SHAD_HP;
		}	

		winner->setStrength(tempStrength);
	}
	else
	{
		cout <<"Something went wrong in restoreHP()" << endl;
	}
}

/*********************************************************************
**Function:     selectWarriors()
**Description:  Allows players to select their creatures for battle
**				playerNum is hard coded in main since there's just two.
**Parameters:   Queue&, int, int
**Returns:      none
*********************************************************************/
void selectWarriors(Queue &playerQueue, int numCreatures, int playerNum)
{
	int menuOption;		//Menu Option for selecting Creatures

	cout << "Player "<< playerNum <<" please select your warriors" << endl;

	for (int x = 0; x < numCreatures; x ++)
	{
		cout<<"Enter the number for your warrior: " << endl 
		<<"1) Barbarian" << endl
		<<"2) Goblin" << endl
		<<"3) Reptile People" <<endl
		<<"4) Blue Men" << endl
		<<"5) The Shadow" << endl;

		cin >> menuOption;

		while(!cin || menuOption > 5)
		{
    		cout << "Invalid Entry! Please enter an integer between 1-5: ";
   	 		cin.clear();
    		cin.ignore();
    		cin >> menuOption;
		}

		if (menuOption == 1)
		{
			Creature *newCreature = new Barbarian();
			playerQueue.enqueue(newCreature);
		}
		else if (menuOption == 2)
		{
			Creature *newCreature = new Goblin();
			playerQueue.enqueue(newCreature);
		}
		else if (menuOption == 3)
		{
			Creature *newCreature = new ReptilePeople();
			playerQueue.enqueue(newCreature);
		}
		else if (menuOption == 4)
		{
			Creature *newCreature = new BlueMen();
			playerQueue.enqueue(newCreature);
		}
		else if(menuOption == 5)
		{
			Creature *newCreature = new Shadow();
			playerQueue.enqueue(newCreature);
		}
		else
		{
			cout << "Something went wrong in selectWarriors()" << endl;
		}

		//reset menuOption
		menuOption = NULL;
	}
}

/*********************************************************************
**Function:     addPoints()
**Description:  Adds points to the winning team. Based on my own personal
**				scoring system of how many points I think a creature deserves
** 				based on match up. Returns -1 if error.
**Parameters:   Creature*, Creature*
**Returns:      int
*********************************************************************/
int addPoints(Creature *winner, Creature *opponent)
{
	if (winner->getName() == "Gobgob")
	{
		if(opponent->getName() == "Gobgob")
		{
			return 1;
		}
		else if(opponent->getName() == "Barbarb")
		{
			return 2;
		}
		else if (opponent->getName() == "ReptileDude")
		{
			return 4;
		}
		else if (opponent->getName() == "Shadow")
		{
			return 4;
		}
		else if (opponent->getName() == "BluesMan")
		{
			return 6;
		}
	}
	else if (winner->getName() == "Barbarb")
	{
		if(opponent->getName() == "Gobgob")
		{
			return 1;
		}
		else if(opponent->getName() == "Barbarb")
		{
			return 2;
		}
		else if (opponent->getName() == "ReptileDude")
		{
			return 3;
		}
		else if (opponent->getName() == "Shadow")
		{
			return 4;
		}
		else if (opponent->getName() == "BluesMan")
		{
			return 6;
		}
	}
	else if (winner->getName() == "ReptileDude")
	{
		if(opponent->getName() == "Gobgob")
		{
			return 1;
		}
		else if(opponent->getName() == "Barbarb")
		{
			return 2;
		}
		else if (opponent->getName() == "ReptileDude")
		{
			return 3;
		}
		else if (opponent->getName() == "Shadow")
		{
			return 4;
		}
		else if (opponent->getName() == "BluesMan")
		{
			return 5;
		}
	}
	else if (winner->getName() == "BluesMan")
	{
		if(opponent->getName() == "Gobgob")
		{
			return 1;
		}
		else if(opponent->getName() == "Barbarb")
		{
			return 1;
		}
		else if (opponent->getName() == "BluesMan")
		{
			return 4;
		}
		else if (opponent->getName() == "Shadow")
		{
			return 4;
		}
		else if (opponent->getName() == "ReptileDude")
		{
			return 3;
		}
	}
		else if (winner->getName() == "Shadow")
	{
		if(opponent->getName() == "Gobgob")
		{
			return 1;
		}
		else if(opponent->getName() == "Barbarb")
		{
			return 2;
		}
		else if (opponent->getName() == "BluesMan")
		{
			return 5;
		}
		else if (opponent->getName() == "Shadow")
		{
			return 3;
		}
		else if (opponent->getName() == "ReptileDude")
		{
			return 3;
		}
	}

	return -1;
}

/*********************************************************************
**Function:     printScore()
**Description:  Prints out the current score
**Parameters:   int&, int&
**Returns:      NONE
*********************************************************************/
void printScore(int &p1Score, int &p2Score)
{
	cout<< "Team 1 Score: " << p1Score << endl
		<< "Team 2 Score: " << p2Score << endl;
}

/*********************************************************************
**Function:     printScoringTable()
**Description:  Prints out the scoring system
**Parameters:   
**Returns:      NONE
*********************************************************************/
void printScoringTable()
{
	cout <<"Scoring Table"<<endl;
	
	cout << "            Opponent " << endl;
	cout << std::setw(11);
	cout << "Fighter  "<<"            |" <<" Goblin |" << " Barbarian |" << " ReptileMan |" << " BlueMan |" << " Shadow |" <<endl;
	cout <<"-------------------------------------------------------------------------------"<<endl;
	cout << std::setw(11);
	cout <<"          | Goblin     |" <<setw(9)<< " 1 |" <<setw(12)<< " 1 |" <<setw(13)<< " 1 |" <<setw(10)<< " 1 |" <<setw(9)<< " 1 |" << endl;
	cout <<"-------------------------------------------------------------------------------"<<endl;	
	cout <<"          | Barbarian  |" <<setw(9)<< " 2 |" <<setw(12)<< " 2 |" <<setw(13)<< " 2 |" <<setw(10)<< " 1 |" <<setw(9)<< " 2 |" << endl;
	cout <<"-------------------------------------------------------------------------------"<<endl;	
	cout <<"          | ReptileMan |" <<setw(9)<< " 4 |" <<setw(12)<< " 3 |" <<setw(13)<< " 3 |" <<setw(10)<< " 3 |" <<setw(9)<< " 3 |" << endl;	
	cout <<"-------------------------------------------------------------------------------"<<endl;
	cout <<"          | BlueMan    |" <<setw(9)<< " 6 |" <<setw(12)<< " 6 |" <<setw(13)<< " 5 |" <<setw(10)<< " 4 |" <<setw(9)<< " 5 |" << endl;
	cout <<"-------------------------------------------------------------------------------"<<endl;	
	cout <<"          | Shadow     |" <<setw(9)<< " 4 |" <<setw(12)<< " 4 |" <<setw(13)<< " 4 |" <<setw(10)<< " 4 |" <<setw(9)<< " 3 |" << endl;	
}