/*
 * EyOutputRoutineTE.cpp
 *
 *  Created on: 03 февр. 2016 г.
 *      Author: aleksandr
 */

#include "EyOutputRoutineTE.h"

#include <fstream>
#include <cmath>

void EyOutputRoutineTE::print() {
	std::ofstream file;
	std::string currentFileName = fileName+"_"+std::to_string(currentTime) + ".txt";
	file.open(currentFileName, std::ofstream::trunc);
	if (!file.is_open()) {
		return;
	}
	grid->Ey.GPUtoCPU();
	float* Ey = grid->Ey.getHostPtr();
	int sizeEy = grid->Ey.getSize();
	#define Ey(M, N) Ey[(M) * (grid->sizeY-1) + (N)]
	for(int i = 0; i < sizeX*(sizeY-1); i++) {
		int xCoord = firstX+resolutionX*(i/(sizeY-1));
		int yCoord = firstY+resolutionY*(i%(sizeY-1));
		file << xCoord << " " << yCoord << " " << Ey(xCoord, yCoord) << std::endl;
	}
	file.close();
}

void EyOutputRoutineTE::compute(int time) {
	if (time > startTime && time < endTime) {
		if ((time-startTime)%period == 0) {
			print();
		}
	}
	currentTime++;
}
