/*
 * HxOutputRoutineTM.cpp
 *
 *  Created on: 03 февр. 2016 г.
 *      Author: aleksandr
 */

#include "HxOutputRoutineTM.h"

#include <fstream>
#include <cmath>

void HxOutputRoutineTM::print() {
	std::ofstream file;
	std::string currentFileName = fileName+"_"+std::to_string(currentTime) + ".txt";
	file.open(currentFileName, std::ofstream::trunc);
	if (!file.is_open()) {
		return;
	}
	grid->Hx.GPUtoCPU();
	float* Hx = grid->Hx.getHostPtr();
	int sizeHx = grid->Hx.getSize();
	#define Hx(M, N) Hx[(M) * (grid->sizeY-1) + (N)]
	for(int i = 0; i < sizeX*(sizeY-1); i++) {
		int xCoord = firstX+resolutionX*(i/(sizeY-1));
		int yCoord = firstY+resolutionY*(i%(sizeY-1));
		file << xCoord << " " << yCoord << " " << Hx(xCoord, yCoord) << std::endl;
	}
	file.close();
}

void HxOutputRoutineTM::compute(int time) {
	if (time > startTime && time < endTime) {
		if ((time-startTime)%period == 0) {
			print();
		}
	}
	currentTime++;
}
