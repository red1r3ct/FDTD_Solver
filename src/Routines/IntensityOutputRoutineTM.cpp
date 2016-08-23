/*
 * IntensityOutputRoutine.cpp
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#include "IntensityOutputRoutineTM.h"
#include <fstream>
#include <cmath>
#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>

void IntensityOutputRoutineTM::print() {
	std::ofstream file;
	std::string currentFileName = fileName+"_"+std::to_string(currentTime) + ".txt";
	file.open(currentFileName, std::ofstream::trunc);
	if (!file.is_open()) {
		std::cout << 'File' << currentFileName << ' not opened' << std::endl;
		return;
	}
	for(int i = 0; i < intensity.size(); i++) {
		int xCoord = i/sizeY;
		int yCoord = i%sizeY;
		file << firstX+resolutionX*xCoord << " " << firstY+resolutionY*yCoord << " " << intensity[i]/period << std::endl;
	}
	file.close();
}

void IntensityOutputRoutineTM::flushData() {
	if (copyEachIteration) {
		for(int i = 0; i < intensity.size(); i++) {
			intensity[i] = 0;
		}
		intensity.fill(0);
	} else {
		intensityGPU.fill(0);
	}
}

void IntensityOutputRoutineTM::collectData() {
	grid->Ez.GPUtoCPU();
	#define Ez(M, N) grid->Ez[(M) * (grid->sizeY) + (N)]
	for(int m = 0; m < sizeX; m++ ) {
		for(int n = 0; n < sizeY; n++ ){
			intensity(m, n) += Ez(firstX + m*resolutionX, firstY + n*resolutionX)*Ez(firstX + m*resolutionX, firstY + n*resolutionX);
		}
	}
}

void IntensityOutputRoutineTM::compute(int time) {
	if (time > startTime && time < endTime) {
		collectData();
		if ((time-startTime)%period == 0) {
			print();
			flushData();
		}
	}
	currentTime++;
}
