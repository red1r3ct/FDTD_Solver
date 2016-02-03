/*
 * EzOutputRoutineTM.cpp
 *
 *  Created on: 21 янв. 2016 г.
 *      Author: aleksandr
 */

#include "EzOutputRoutineTM.h"

#include <fstream>
#include <cmath>

void EzOutputRoutineTM::print() {
	std::ofstream file;
	std::string currentFileName = fileName+"_"+std::to_string(currentTime) + ".txt";
	file.open(currentFileName, std::ofstream::trunc);
	if (!file.is_open()) {
		return;
	}
	grid->Ez.GPUtoCPU();
	float* Ez = grid->Ez.getHostPtr();
	int sizeEz = grid->Ez.getSize();
	#define Ez(M, N) Ez[(M) * (grid->sizeY) + (N)]
	for(int i = 0; i < sizeX*sizeY; i++) {
		int xCoord = firstX+resolutionX*(i/sizeY);
		int yCoord = firstY+resolutionY*(i%sizeY);
		file << xCoord << " " << yCoord << " " << Ez(xCoord, yCoord) << std::endl;
	}
	file.close();
}

void EzOutputRoutineTM::compute(int time) {
	if (time > startTime && time < endTime) {
		if ((time-startTime)%period == 0) {
			print();
		}
	}
	currentTime++;
}
