#include "SuperAnt.h"
#include "Organism.h"
#include "World.h"

SuperAnt::SuperAnt(World* aWorld, int xcoord, int ycoord) :Organism(aWorld, xcoord, ycoord)
{
	deathTicks = 0;
	eatBug = 0;
}

void SuperAnt::move()
{
	deathTicks++;

	if (world->getAt(x, y + 2) != nullptr)
	{
		if (world->getAt(x, y + 2)->getType() == OrganismType::BUG)
		{
			deathTicks = 0;
			delete world->getAt(x, y + 2);
			movesTo(x, y + 2);
			eatBug++;
			return;
		}
	}

	if (world->getAt(x, y - 2) != nullptr)
	{
		if (world->getAt(x, y - 2)->getType() == OrganismType::BUG)
		{
			deathTicks = 0;
			delete world->getAt(x, y - 2);
			movesTo(x, y - 2);
			eatBug++;
			return;
		}
	}

	if (world->getAt(x - 2, y) != nullptr)
	{
		if (world->getAt(x -2, y)->getType() == OrganismType::BUG)
		{
			deathTicks = 0;
			delete world->getAt(x - 2, y);
			movesTo(x - 2, y);
			eatBug++;
			return;
		}
	}
	if (world->getAt(x + 2, y) != nullptr)
	{
		if (world->getAt(x + 2, y)->getType() == OrganismType::BUG)
		{
			deathTicks = 0;
			delete world->getAt(x + 2, y);
			movesTo(x + 2, y);
			eatBug++;
			return;
		}
	}

	Move mover = world->randomMove();
	switch (mover)
	{
	case Move::UP:
		if (world->getAt(x, y + 2) == nullptr && in_range(x, y + 2))
		{
			movesTo(x, y + 2);
		}
		break;
	case Move::DOWN:
		if (world->getAt(x, y - 2) == nullptr && in_range(x, y - 2))
		{
			movesTo(x, y - 2);
		}
		break;
	case Move::LEFT:
		if (world->getAt(x - 2, y) == nullptr && in_range(x - 2, y))
		{
			movesTo(x - 2, y);
		}
		break;
	case Move::RIGHT:
		if (world->getAt(x + 2, y) == nullptr && in_range(x + 2, y))
		{
			movesTo(x + 2, y);
		}
		break;
	default:
		break;
	}
}

void SuperAnt::breed()
{
	if (eatBug >= 3 )//if SuperAnt ate 3 bugs, spawn new SuperAnt
	{
		breedAtAdjacentCell();
	}
}

OrganismType SuperAnt::getType() const
{
	return OrganismType::SuperAnt;
}

char SuperAnt::representation() const
{
	return 'S';
}

int SuperAnt::size() const
{
	return 15;
}

bool SuperAnt::in_range(int xx, int yy)
{
	return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);;
}

bool SuperAnt::isDead() const
{
	if (deathTicks >= starve_SuperAnts)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SuperAnt::generateOffspring(int whereX, int whereY)
{

	new SuperAnt(this->world, whereX, whereY);
	breedTicks = 0;
	eatBug = 0;

}
