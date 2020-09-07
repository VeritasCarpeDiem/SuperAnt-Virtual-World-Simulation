#include <iostream>
#include <ctime>// for time
#include "World.h"
#include <Windows.h>
#include <conio.h>
#include "Organism.h"
#include "XY.h"
using namespace std;


int main()
{
    World myWorld(unsigned int(time(0)));

    myWorld.display();
	
	PlaySound("Music.wav", NULL, SND_ASYNC| SND_LOOP);

    while (true) 
	{  
		system("cls");
		myWorld.simulateOneStep();
        myWorld.display();

		Sleep(1000);

		//allows User to add ants,bugs,superants,bombBugs
		if (_kbhit())
		{
			//system("pause");
			char input = _getch();
			if (input == 'a')
			{
				myWorld.createOrganisms(OrganismType::ANT, 1);
			}
			else if (input == 's')
			{
				myWorld.createOrganisms(OrganismType::SuperAnt, 1);
			}
			else if (input == 'b')
			{
				myWorld.createOrganisms(OrganismType::BUG, 1);
			}
			else if (input == 'B')
			{
				myWorld.createOrganisms(OrganismType::BombBug, 1);
			}
		}

    }
	return 0;
    
}

