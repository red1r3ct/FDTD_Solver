
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Parser.h"
#include "../Updaters/UpdaterTE.h"
#include "../Grids/GridTE.h"
#include "../Routines/HzOutputRoutineTE.h"

#include <ctime>
#include <cmath>

int main(int argc, char **argv)
{
	/*int sizeX = 500;
	int sizeY = 500;
	int lambda = 100;
	GridTE grid(sizeX, sizeY, 1/sqrt(2));
	//grid.readEpsilon("single_particle"+std::to_string(sizeX-2000)+".txt");
	UpdaterTE updater;
	HarmonicSource hSource2(1, 4.44063/(float)(lambda), sizeX/4, sizeY/2);
	HzOutputRoutineTM Hzout("Hzout", &grid, 0, 500, 10, 0, 500, 10, 0, 1000, 20);
	updater.addGrid(&grid);
	updater.addSource(&hSource2);
	updater.addRoutine(&Hzout);
	unsigned int start_time =  clock(); // начальное время
	for(int i = 0; i < 2000; i++) {
		updater.iterate();
		if(i%10==0){
			std::cout<<"step :" << i << std::endl;
		}
	}
    unsigned int end_time = clock(); // конечное время
    unsigned int time = end_time - start_time; // искомое время
    std::cout <<"step per second : "<< 1000/((float)(time)/CLOCKS_PER_SEC) << std::endl;*/
	Parser parser;
	parser.runFile(argv[1]);

	return 0;
}
