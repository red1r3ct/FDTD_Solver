/*
 * HyOutputRoutineTM.cpp
 *
 *  Created on: 03 февр. 2016 г.
 *      Author: aleksandr
 */

#include "HyOutputRoutineTM.h"

#include <fstream>
#include <cmath>

void HyOutputRoutineTM::print() {
	std::ofstream file;
	std::string currentFileName = fileName+"_"+std::to_string(currentTime) + ".txt";
	file.open(currentFileName, std::ofstream::trunc);
	if (!file.is_open()) {
		return;
	}
	grid->Hy.GPUtoCPU();
	float* Hy = grid->Hy.getHostPtr();
	int sizeHy = grid->Hy.getSize();
	#define Hy(M, N) Hy[(M) * (grid->sizeY) + (N)]
	for(int i = 0; i < sizeX*sizeY; i++) {
		int xCoord = firstX+resolutionX*(i/sizeY);
		int yCoord = firstY+resolutionY*(i%sizeY);
		file << xCoord << " " << yCoord << " " << Hy(xCoord, yCoord) << std::endl;
	}
	file.close();
}

void HyOutputRoutineTM::compute(int time) {
	if (time > startTime && time < endTime) {
		if ((time-startTime)%period == 0) {
			print();
		}
	}
	currentTime++;
}
