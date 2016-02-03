/*
 * HzOutputRoutineTE.cpp
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: aleksandr
 */

#include "HzOutputRoutineTE.h"

#include <fstream>
#include <cmath>

void HzOutputRoutineTE::print() {
	std::ofstream file;
	std::string currentFileName = fileName+"_"+std::to_string(currentTime) + ".txt";
	file.open(currentFileName, std::ofstream::trunc);
	if (!file.is_open()) {
		return;
	}
	grid->Hz.GPUtoCPU();
	float* Hz = grid->Hz.getHostPtr();
	int sizeHz = grid->Hz.getSize();
	#define Hz(M, N) Hz[(M) * (grid->sizeY-1) + (N)]
	for(int i = 0; i < (sizeX-1)*(sizeY-1); i++) {
		int xCoord = firstX+resolutionX*(i/(sizeY-1));
		int yCoord = firstY+resolutionY*(i%(sizeY-1));
		file << xCoord << " " << yCoord << " " << Hz(xCoord, yCoord) << std::endl;
	}
	file.close();
}

void HzOutputRoutineTE::compute(int time) {
	if (time > startTime && time < endTime) {
		if ((time-startTime)%period == 0) {
			print();
		}
	}
	currentTime++;
}
