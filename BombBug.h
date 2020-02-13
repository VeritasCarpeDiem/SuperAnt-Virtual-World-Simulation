#pragma once
#include "Organism.h"
#include "World.h"

//Download the given code for the Bug / Ant problem and perform the following :
//
//1 - ) Change the interface to a graphical(or text graphic) interface
//
//2 - ) Add a BOMB bug.A BOMB bug should show up randomly in on the screen, count down from 5 to 0, then explode. When exploding it should DELETE all bugsand antsaround it.
//
//P.S.You can be very innovative in here.For example :
//
//1 - ) Add sound of explosion when BUG explodes.
//
//2 - ) Add explosion graphics

class BombBug : public Organism
{
public:

	BombBug(World* aWorld, int xcoord, int ycoord);

	// In the given world moves this organism.
	void move();//no code because BombBug does not move

	// Makes this organism breed.
	void breed(){}//BombBug does not breed

	// Returns the type of this organism.
	OrganismType getType() const;

	// The character representation of this organism.
	char representation() const;

	// The size of this organism.
	int size() const;

	bool in_range(int xx, int yy) {};

	bool isDead() const;

private:
	void generateOffspring(int whereX, int whereY) {} //BombBUG doesn't generate offspring
	int death_tik;
};
