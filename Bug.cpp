#include "Bug.h"
#include "Organism.h"
#include "changeColor.h"
using namespace std;

Bug::Bug(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
    death_tik = 0;
}

void Bug::move()
{
    breedTicks++;
    death_tik++;
    
    if(world->getAt(x, y + 1) != NULL)
    {
        if(world->getAt(x, y + 1)->getType() == OrganismType::ANT)
        {
            death_tik = 0;
            delete world->getAt(x, y + 1);
            movesTo(x, y + 1);
            return;
        }
    }
    
    if(world->getAt(x, y - 1) != NULL)
    {
        if(world->getAt(x, y - 1)->getType() == OrganismType::ANT)
        {
            death_tik = 0;
            delete world->getAt(x, y - 1);
            movesTo(x, y - 1);
            return;
        }
    }
    
    if(world->getAt(x - 1, y) != NULL)
    {
        if(world->getAt(x - 1, y)->getType() == OrganismType::ANT)
        {
            death_tik = 0;
            delete world->getAt(x - 1, y);
            movesTo(x - 1, y);
            return;
        }
    }
    if(world->getAt(x + 1, y) != NULL)
    {
        if(world->getAt(x + 1, y)->getType() == OrganismType::ANT)
        {
            death_tik = 0;
            delete world->getAt(x + 1, y);
            movesTo(x + 1, y);
            return;
        }
    }
    
    Move mover = world->randomMove();
    switch (mover){
	case Move::UP:
            if(world->getAt(x, y + 1) == NULL && in_range(x, y + 1))
            {
                movesTo(x, y + 1);
            }
            break;
        case Move::DOWN:
            if(world->getAt(x, y - 1) == NULL && in_range(x, y - 1))
            {
                movesTo(x, y - 1);
            }
            break;
        case Move::LEFT:
            if(world->getAt(x - 1, y) == NULL && in_range(x - 1, y))
            {
                movesTo(x - 1, y);
            }
            break;
        case Move::RIGHT:
            if(world->getAt(x + 1, y) == NULL && in_range(x + 1, y))
            {
                movesTo(x + 1, y);
            }
            break;
        default:
            break;
    }
}

void Bug::generateOffspring(int whereX, int whereY)
{
    new Bug(this->world, whereX, whereY);
    breedTicks = 0;
}

void Bug::breed()
{
    if(breedTicks >= BREED_BUGS)
    {
        breedAtAdjacentCell();
    }
    
}

bool Bug::isDead() const
{
    if(death_tik >= STARVE_BUGS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

OrganismType Bug::getType() const
{
    return OrganismType::BUG;
}


char Bug::representation()const
{
    return 'B';
}

int Bug::size() const
{
    return 30;
}

bool Bug::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}
