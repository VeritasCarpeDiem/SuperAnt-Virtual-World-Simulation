#include <iostream>
#include <cstdlib>// for rand
#include "World.h"
#include "Ant.h"
#include "Bug.h"
#include "changeColor.h"
#include "BombBug.h"
#include <conio.h>
#include "XY.h"
#include "SuperAnt.h"
using namespace std;

///////////////////
// Public functions
///////////////////

// Default constructor: creates and initializes the world
// the seed is used for seeding the random behaviour.
World::World(unsigned int seed)
{
	// seed the random generator
	srand(seed);
	// Create an empty world
	for (int i = 0; i < WORLDSIZE; i++)
	{
		for (int j = 0; j < WORLDSIZE; j++)
		{
			grid[i][j] = NULL;
		}
	}
	// creates the ants = 3
	createOrganisms(OrganismType::ANT, INITIAL_ANTS);
	// creates the bugs = 8
	createOrganisms(OrganismType::BUG, INITIAL_BUGS);

	createOrganisms(OrganismType::BombBug, INITIAL_BOMBBUGS);

	createOrganisms(OrganismType::SuperAnt, initial_SuperAnts);
}

// Deallocate memory allocated to organisms in this world.
World::~World()
{
	for (int i = 0; i < WORLDSIZE; i++)
	{
		for (int j = 0; j < WORLDSIZE; j++)
		{
			if (grid[i][j] != NULL)
			{
				delete grid[i][j];
			}
		}
	}
}

// Return the organism at the given coordinates
// If the coordinates are not valid, returns NULL
Organism* World::getAt(int x, int y) const
{
	if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) //if position is within array gride, return array
	{
		return grid[x][y];
	}
	else
	{
		return nullptr;
	}
}

// Sets the entry at x,y to the value passed in.
void World::setAt(int x, int y, Organism* org)
{
	if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE))
	{
		grid[x][y] = org;
	}
}

// Displays the world in ASCII.
void World::display() const
{
	displayGUI();
	int numAnts{}, numBugs{}, numBombBugs{}, numSuperAnts{};

	int x = 10;
	int y=10;

	changeColor c;
	XY xy;

	cout << endl << endl;
	for (int j = 0; j < WORLDSIZE; j++)
	{
		xy.gotoXY(x, y);
		for (int i = 0; i < WORLDSIZE; i++)
		{

			if (grid[i][j] == NULL)
			{
				cout << " . ";
			}
			else
			{
				if (grid[i][j]->getType() == OrganismType::ANT)
				{
					c.changeTextColor(Colors::RED);
					numAnts++;
				}
				else if (grid[i][j]->getType() == OrganismType::BUG)
				{
					c.changeTextColor(Colors::BLUE);
					numBugs++;
				}
				else if (grid[i][j]->getType() == OrganismType::BombBug)
				{
					c.changeTextColor(Colors::GREEN);
					numBombBugs++;
				}
				else if (grid[i][j]->getType() == OrganismType::SuperAnt)
				{
					c.changeTextColor(Colors::YELLOW);
					numSuperAnts++;
				}
				cout << " " << grid[i][j]->representation() << " ";
			
				c.changeTextColor(Colors::WHITE);
			}
		}
		
		y++;
		x = 10;
	}
	xy.gotoXY(20, 2);
	cout << "Jin Kim" << endl;
	xy.gotoXY(20, 3);
	c.changeTextColor(Colors::RED);
	cout << "Ants: " << numAnts;
	xy.gotoXY(20, 4);
	c.changeTextColor(Colors::BLUE);
	cout << "Bugs: " << numBugs;
	xy.gotoXY(20, 5);
	c.changeTextColor(Colors::GREEN);
	cout << "BombBugs: " << numBombBugs;
	xy.gotoXY(20, 6);
	c.changeTextColor(Colors::YELLOW);
	cout << "SuperAnts: " << numSuperAnts;
	c.changeTextColor(Colors::WHITE);
	xy.gotoXY(20, 20);
	cout << "Press: " << endl;
	xy.gotoXY(20, 21);
	cout << "a: add Ant";
	xy.gotoXY(20, 22);
	cout << "b: add Bug";
	xy.gotoXY(20, 23);
	cout << "B: add BombBug";
	xy.gotoXY(20, 24);
	cout<<"s: add SuperAnt";
	xy.gotoXY(20, 25);
}

void World::displayGUI() const
{
	XY xy;
	xy.gotoXY(0, 0);

	// key = different states of the box
	int width = 52, key = 0;
	// print corner piece
	cout << char(201);
	for (int i = 0; i < 2; i++)
	{
		// print width amount of horizontal lines
		for (int j = 0; j < width; j++)
		{
			cout << char(205);
		}
		if (key == 0)
		{
			cout << char(187) << endl;
			width -= 4; key++;
			cout << char(186) << " " << char(201);
		}
		else
			cout << char(187) << " " << char(186) << endl;
	}
	width = 48;
	key = 0;
	// print vertical bars
	for (int i = 0; i < 24; i++)
	{
		cout << char(186) << " " << char(186);
		for (int j = 0; j < width; j++)
		{
			cout << " ";
		}
		cout << char(186) << " " << char(186) << endl;
	}
	// like the first loop but inverted for the bottom
	cout << char(186) << " " << char(200);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << char(205);
		}
		if (key == 0)
		{
			cout << char(188) << " " << char(186) << endl;
			width += 4; key++;
			cout << char(200);
		}
		else
			cout << char(188);
	}
}

void World::simulateOneStep()
{
	// The main routine that simulates one turn in the world:
	// 1. move bugs
	// 2. move ants
	// move BombBugs
	// 3. make bugs starve (which happends under a certain condition)
	// 4. make the organisms breed (again which happens under a certain
	// condition).

	// Reset all organisms to not moved
	resetOrganisms();

	
	// Move the bugs
	moveOrganism(OrganismType::BUG);

	// Move the ants
	moveOrganism(OrganismType::ANT);

	moveOrganism(OrganismType::BombBug);

	moveOrganism(OrganismType::SuperAnt);

	// Make the bugs starve
	cleanup();

	//Make them breed
	breedOrganisms();
}

Position World::randomPosition() const
{    // returns a random number in the range 0 to MAX-1
	Position p;
	p.x = rand() % WORLDSIZE;
	p.y = rand() % WORLDSIZE;
	return p;
}


Move World::randomMove() const
{
	return static_cast<Move>(rand() % 4);
}

////////////////////
// Private functions
////////////////////

void World::createOrganisms(OrganismType orgType, int count)
{
	int orgCount = 0;
	char c{};
	while (orgCount < count)
	{
		Position p = randomPosition();
		// Only put ant in empty spot
		if (grid[p.x][p.y] == NULL)
		{
			orgCount++;
			if (orgType == OrganismType::ANT)
			{
				new Ant(this, p.x, p.y);   // Create an Ant and put it into the world
			}
			else if (orgType == OrganismType::BUG)
			{
				new Bug(this, p.x, p.y);   // Create a Bug and put it into the world
			}
			else if (orgType == OrganismType::BombBug)
			{
				new BombBug(this, p.x, p.y);
			}
			else if (orgType == OrganismType::SuperAnt)
			{
				new SuperAnt(this, p.x, p.y);
			}

		}
	}
}

// Reset all organisms to not moved
void World::resetOrganisms()
{
	for (int i = 0; i < WORLDSIZE; i++)
	{
		for (int j = 0; j < WORLDSIZE; j++)
		{
			if (grid[i][j] != NULL)
			{
				grid[i][j]->setMoved(false);
			}
		}
	}
}

// Move all organisms of type aType
void World::moveOrganism(OrganismType aType)
{
	for (int i = 0; i < WORLDSIZE; i++)
	{
		for (int j = 0; j < WORLDSIZE; j++)
		{
			if (grid[i][j] != NULL)
			{
				if (grid[i][j]->getType() == aType && !(grid[i][j]->hasMoved()))
				{
					grid[i][j]->move();
				}
			}
		}
	}
}

// Remove all dead organisms from this world.
void World::cleanup()
{
	for (int i = 0; i < WORLDSIZE; i++)
	{
		for (int j = 0; j < WORLDSIZE; j++)
		{
			// Kill off any organisms that haven't eaten recently
			if ((grid[i][j] != NULL) && grid[i][j]->isDead())
			{
				delete grid[i][j];
				grid[i][j] = NULL;
			}
		}
	}
}

// Make the organisms breed
void World::breedOrganisms() {
	for (int i = 0; i < WORLDSIZE; i++)
	{
		for (int j = 0; j < WORLDSIZE; j++)
		{
			if (grid[i][j] != NULL)
			{
				grid[i][j]->breed();
			}
		}
	}
}
