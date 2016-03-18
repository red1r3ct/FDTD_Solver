/*
 * UpdaterTE.cpp
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: aleksandr
 */

#include "UpdaterTE.h"


#include <iostream>
#include <cmath>

#include "thrust/for_each.h"
#include <thrust/iterator/counting_iterator.h>
#include <thrust/device_ptr.h>

void UpdaterTE::addRoutine(Routine* routine) {
	routines.push_back(routine);
}

void UpdaterTE::addGrid(GridTE* _grid) {
	grid = _grid;
	ExUpdater.setParams(grid->Ex.getDevicePtr(),
			   	   	   	grid->Hz.getDevicePtr(),
			   	   	   	grid->epsilon.getDevicePtr(),
			   	   	   	grid->sizeX,
			   	   	   	grid->sizeY,
			   	   	   	1/sqrt(2));
	EyUpdater.setParams(grid->Ey.getDevicePtr(),
					   	grid->Hz.getDevicePtr(),
					 	grid->epsilon.getDevicePtr(),
					   	grid->sizeX,
					   	grid->sizeY,
					   	1/sqrt(2));
	HzUpdater.setParams(grid->Ex.getDevicePtr(),
						grid->Ey.getDevicePtr(),
					   	grid->Hz.getDevicePtr(),
					 	grid->epsilon.getDevicePtr(),
					   	grid->sizeX,
					   	grid->sizeY,
					   	1/sqrt(2));
}

void UpdaterTE::addBoundaryCond(BoundaryCond* boundaryCond) {
	boundaryConds.push_back(boundaryCond);
}

void UpdaterTE::addSource(Source* source) {
	sources.push_back(source);
}

void UpdaterTE::updateFields() {
	updateH();
	if (tfsfCond != NULL) {
		updateTFSF();
	}
	updateE();
}

void UpdaterTE::updateSources() {
	for ( int i = 0; i < sources.size(); i++ ){
		int xCoord = (sources[i])->getPositionX();
		int yCoord = (sources[i])->getPositionY();
		int linearIndex = xCoord * (grid->sizeY-1) + yCoord;
		thrust::device_ptr<float> dptr = &(grid->Ey.getDevicePtr())[linearIndex];
		sources[i]->updateField(dptr, grid->time);
	}
}


void UpdaterTE::updateRoutines() {
	for ( int i = 0; i < routines.size(); i++ ){
		routines[i]->compute(grid->time);
	}
	(grid->time)++;
}

void UpdaterTE::updateBoundaryCond() {
	for ( int i = 0; i < boundaryConds.size(); i++ ){
		boundaryConds[i]->apply();
	}
}

void UpdaterTE::addTFSF(TFSFCondTE* _tfsfCond) {
	tfsfCond = _tfsfCond;
}

void UpdaterTE::updateTFSF() {
	tfsfCond->apply();
}

void UpdaterTE::run( int num) {
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
