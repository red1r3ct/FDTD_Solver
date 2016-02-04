/*
 * UpdaterTM.cpp
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#include "UpdaterTM.h"

#include <iostream>
#include <cmath>

#include "thrust/for_each.h"
#include <thrust/iterator/counting_iterator.h>
#include <thrust/device_ptr.h>

void UpdaterTM::addRoutine(Routine* routine) {
	routines.push_back(routine);
}

void UpdaterTM::addGrid(GridTM* _grid) {
	grid = _grid;
	EzUpdater.setParams(grid->Ez.getDevicePtr(),
			   	   	   	grid->Hx.getDevicePtr(),
			   	   	   	grid->Hy.getDevicePtr(),
			   	   	   	grid->epsilon.getDevicePtr(),
			   	   	   	grid->sigma.getDevicePtr(),
			   	   	   	grid->sizeX,
			   	   	   	grid->sizeY,
			   	   	   	1/sqrt(2));
	HxHyUpdater.setParams(grid->Ez.getDevicePtr(),
					   	  grid->Hx.getDevicePtr(),
					   	  grid->Hy.getDevicePtr(),
					   	  grid->epsilon.getDevicePtr(),
					   	  grid->sizeX,
					   	  grid->sizeY,
					   	  1/sqrt(2));
}

void UpdaterTM::addBoundaryCond(BoundaryCond* boundaryCond) {
	boundaryConds.push_back(boundaryCond);
}

void UpdaterTM::addSource(Source* source) {
	sources.push_back(source);
}

void UpdaterTM::updateFields() {
	updateH();
	if (tfsfCond != nullptr) {
		updateTFSF();
	}
	updateE();
}

void UpdaterTM::updateSources() {
	for(auto source : sources) {
		int xCoord = source->getPositionX();
		int yCoord = source->getPositionY();
		int linearIndex = xCoord * (grid->sizeY) + yCoord;
		auto dptr = &(grid->Ez.getDevicePtr())[linearIndex];
		source->updateField(dptr, grid->time);
	}
}


void UpdaterTM::updateRoutines() {
	for(auto routine: routines) {
		routine->compute(grid->time);
	}
	(grid->time)++;
}

void UpdaterTM::updateBoundaryCond() {
	for (auto boundaryCond: boundaryConds) {
		boundaryCond->apply();
	}
}

void UpdaterTM::addTFSF(TFSFCondTM* _tfsfCond) {
	tfsfCond = _tfsfCond;
}

void UpdaterTM::updateTFSF() {
	tfsfCond->apply();
}

void UpdaterTM::run( int num) {
	unsigned int start_time =  clock(); // начальное время
	for (int i = 0; i < num; i++) {
		iterate();
		if (i%100 == 0) {
			std::cout << "Step " << i << " complete \n";
		}
	}
	unsigned int end_time = clock(); // конечное время
	unsigned int time = end_time - start_time; // искомое время
    std::cout <<"step per second : "<< num/((float)(time)/CLOCKS_PER_SEC) << std::endl;
}
