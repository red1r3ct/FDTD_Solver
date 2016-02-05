/*
 * Updater3D.cpp
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#include "Updater3D.h"

#include <iostream>
#include <cmath>

#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/device_ptr.h>

void Updater3D::addRoutine(Routine* routine) {
	routines.push_back(routine);
}

void Updater3D::addGrid(Grid3D* _grid) {
	grid = _grid;
}

void Updater3D::addBoundaryCond(BoundaryCond* boundaryCond) {
	boundaryConds.push_back(boundaryCond);
}

void Updater3D::addSource(Source* source) {
	sources.push_back(source);
}

void Updater3D::updateFields() {
	updateH();
	updateE();
}

void Updater3D::updateSources() {
	for(auto source : sources) {
		int xCoord = source->getPositionX();
		int yCoord = source->getPositionY();
		int linearIndex = xCoord * (grid->sizeY) + yCoord;
		auto dptr = &(grid->Ez.getDevicePtr())[linearIndex];
		source->updateField(dptr, grid->time);
	}
}


void Updater3D::updateRoutines() {
	for(auto routine: routines) {
		routine->compute(grid->time);
	}
	(grid->time)++;
}

void Updater3D::updateBoundaryCond() {
	for (auto boundaryCond: boundaryConds) {
		boundaryCond->apply();
	}
}

void Updater3D::run( int num) {
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
