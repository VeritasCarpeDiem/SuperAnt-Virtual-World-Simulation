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
	
	//PlaySound("love.wav", NULL, SND_ASYNC | SND_LOOP);

    while (true)
	{  
		
		system("cls");
		myWorld.simulateOneStep();
        myWorld.display();

		Sleep(1000);

#pragma region pause program
		if (_kbhit())//if key is pressed, pause program
		{
			XY xy;
			xy.gotoXY(6, 6);
			system("pause");
			
		}
#pragma endregion

    }

	return 0;
    
}

