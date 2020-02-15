#include "BombBug.h"
#include "Organism.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#pragma comment(lib, "Winmm.lib") //static windows library for playing .wav music files
using namespace std;

//constructor that sends these 3 parameters to Organism's constructor
BombBug::BombBug(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
	death_tik = 5;
}

void BombBug::move()
{
	death_tik--;

	if (death_tik == 0)
	{
		if (world->getAt(x, y + 1) != nullptr)
		{
			delete world->getAt(x, y + 1);
			world->setAt(x, y + 1, nullptr);
		}
		if (world->getAt(x, y - 1) != nullptr)
		{
			delete world->getAt(x, y - 1);
			world->setAt(x, y - 1, nullptr);
		}
		if (world->getAt(x + 1, y) != NULL)
		{
			delete world->getAt(x + 1, y);
			world->setAt(x + 1, y, nullptr);
		}
		if (world->getAt(x - 1, y) != nullptr)
		{
			delete world->getAt(x - 1, y);
			world->setAt(x - 1, y, nullptr);
		}
		
	}
}

OrganismType BombBug::getType() const
{
	return OrganismType::BombBug;
}

char BombBug::representation() const
{
	return 48+death_tik; //ascii value for the number 5
}

int BombBug::size() const
{
	return 20;
}

//bool BombBug::in_range(int xx, int yy)
//{
//	return false;
//}


bool BombBug::isDead() const
{
	if (death_tik == 0)
	{
		PlaySound("Bomb+1.wav", NULL, SND_ASYNC);
		return true;
	}
	else
	{
		return false;
	}
	
}




