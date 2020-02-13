#include "SuperAnt.h"
#include "Organism.h"
#include "World.h"

SuperAnt::SuperAnt(World* aWorld, int xcoord, int ycoord):Organism(aWorld,xcoord,ycoord)
{

}

void SuperAnt::move()
{
	breedTicks++;
	deathTicks++;

	if (world->getAt(x, y + 1) != nullptr)
	{
		if (world->getAt(x, y + 1)->getType() == OrganismType::BUG)
		{
			deathTicks = 0;
			delete world->getAt(x, y + 1);
			movesTo(x, y + 1);
			return;
		}
	}

	if (world->getAt(x, y - 1) != nullptr)
	{
		if (world->getAt(x, y - 1)->getType() == OrganismType::BUG)
		{
			deathTicks = 0;
			delete world->getAt(x, y - 1);
			movesTo(x, y - 1);
			return;
		}
	}

	if (world->getAt(x - 1, y) != nullptr)
	{
		if (world->getAt(x - 1, y)->getType() == OrganismType::BUG)
		{
			deathTicks = 0;
			delete world->getAt(x - 1, y);
			movesTo(x - 1, y);
			return;
		}
	}
	if (world->getAt(x + 1, y) != nullptr)
	{
		if (world->getAt(x + 1, y)->getType() == OrganismType::BUG)
		{
			deathTicks = 0;
			delete world->getAt(x + 1, y);
			movesTo(x + 1, y);
			return;
		}
	}

	Move mover = world->randomMove();
	switch (mover) {
	case Move::UP:
		if (world->getAt(x, y + 1) == nullptr && in_range(x, y + 1))
		{
			movesTo(x, y + 1);
		}
		break;
	case Move::DOWN:
		if (world->getAt(x, y - 1) == nullptr && in_range(x, y - 1))
		{
			movesTo(x, y - 1);
		}
		break;
	case Move::LEFT:
		if (world->getAt(x - 1, y) == nullptr && in_range(x - 1, y))
		{
			movesTo(x - 1, y);
		}
		break;
	case Move::RIGHT:
		if (world->getAt(x + 1, y) == nullptr && in_range(x + 1, y))
		{
			movesTo(x + 1, y);
		}
		break;
	default:
		break;
	}
}

void SuperAnt::breed()
{
	//blank b/c SuperAnt does not breed
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
	return 0;
}

bool SuperAnt::in_range(int xx, int yy)
{
	return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);;
}

void SuperAnt::generateOffspring(int whereX, int whereY)
{
	if (eatBug==3)//if SuperAnt ate 3 bugs, spawn new SuperAnt
	{
		new SuperAnt(this->world,whereX,whereY);
		breedTicks = 0;
		eatBug = 0;
	}
}
