/*
 * ExOutputRoutineTE.cpp
 *
 *  Created on: 03 февр. 2016 г.
 *      Author: aleksandr
 */

#include "ExOutputRoutineTE.h"

#include <fstream>
#include <cmath>

void ExOutputRoutineTE::print() {
	std::ofstream file;
	std::string currentFileName = fileName+"_"+std::to_string(currentTime) + ".txt";
	file.open(currentFileName, std::ofstream::trunc);
	if (!file.is_open()) {
		return;
	}
	grid->Ex.GPUtoCPU();
	float* Ex = grid->Ex.getHostPtr();
	int sizeEx = grid->Ex.getSize();
	#define Ex(M, N) Ex[(M) * (grid->sizeY) + (N)]
	for(int i = 0; i < (sizeX-1)*sizeY; i++) {
		int xCoord = firstX+resolutionX*(i/sizeY);
		int yCoord = firstY+resolutionY*(i%sizeY);
		file << xCoord << " " << yCoord << " " << Ex(xCoord, yCoord) << std::endl;
	}
	file.close();
}

void ExOutputRoutineTE::compute(int time) {
	if (time > startTime && time < endTime) {
		if ((time-startTime)%period == 0) {
			print();
		}
	}
	currentTime++;
}

