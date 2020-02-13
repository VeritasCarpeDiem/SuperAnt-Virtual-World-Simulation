#pragma once
#include "Organism.h"

#pragma region instructions
//Super Ant behaviour.
//
//• Move : Every time step, randomly try to make one move up, down, left, or right.If the cell in the selected direction is occupied or would move the ant oﬀ the grid, then the ant stays in the current cell.Super Ants move faster than other bugsand ants(more steps).
//
//• Starve : If a super ant has not eaten a bug within the last three time steps, then at the end of the third time step it will starve and die.The super ant should then be removed from the grid of cells.
//
//• Breed : If a Super Ant eats 5 bugs it can spawn another Super Ant.

//Allow the user to add the following to the simulation at run time :
//
//A: Add ant
//
//S : Add Super Ant
//
//B : Add Bug
#pragma endregion

class SuperAnt :public Organism
{
public:

	SuperAnt(World* aWorld, int xcoord, int ycoord);
	// In the given world moves this organism.
	void move();

	// Makes this organism breed.
	void breed();

	// Returns the type of this organism.
	OrganismType getType() const;

	// The character representation of this organism.
	char representation() const;

	// The size of this organism.
	int size() const;

	bool in_range(int xx, int yy);

private:
	//brace initialize
	int breedTicks{}; 
	int deathTicks{}; 
	int eatBug{}; //number of bugs SuperAnt has eaten

	void generateOffspring(int whereX, int whereY);
};
