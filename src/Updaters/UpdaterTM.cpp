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
			   	   	    grid->excluded.getDevicePtr(),
			   	   	   	grid->sizeX,
			   	   	   	grid->sizeY,
			   	   	   	1/sqrt(2));
	HxHyUpdater.setParams(grid->Ez.getDevicePtr(),
					   	  grid->Hx.getDevicePtr(),
					   	  grid->Hy.getDevicePtr(),
					   	  grid->epsilon.getDevicePtr(),
					   	  grid->excluded.getDevicePtr(),
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
	if (tfsfCond != NULL) {
		updateTFSF();
	}
	updateE();
}

void UpdaterTM::updateSources() {
	for ( int i = 0; i < sources.size(); i++ ){
		int xCoord = sources[i]->getPositionX();
		int yCoord = sources[i]->getPositionY();
		int linearIndex = xCoord * (grid->sizeY) + yCoord;
		thrust::device_ptr<float> dptr = &(grid->Ez.getDevicePtr())[linearIndex];
		sources[i]->updateField(dptr, grid->time);
	}
}


void UpdaterTM::updateRoutines() {
	for ( int i = 0; i < routines.size(); i++ ){
		routines[i]->compute(grid->time);
	}
	(grid->time)++;
}

void UpdaterTM::updateBoundaryCond() {
	for ( int i = 0; i < boundaryConds.size(); i++ ){
		boundaryConds[i]->apply();
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
		if (i%100 == 0 && i != 0) {
			std::cout << "Step " << i << " complete, " << 100/((float)(clock() - start_time)/CLOCKS_PER_SEC) << " steps/secs\n";
			start_time =  clock();
		}
	}
}
