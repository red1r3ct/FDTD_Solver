/*
 * Updater1D.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#include "Updater1DTM.h"
#include <iostream>

Updater1DTM::Updater1DTM() : grid(NULL), source(NULL) {}

void Updater1DTM::addSource(Source* _source) {
	source = _source;
}

void Updater1DTM::addGrid(Grid1DTM* _grid) {
	grid = _grid;
	updaterEz.setParams(grid->Ez.getDevicePtr(),
						grid->Hy.getDevicePtr(),
						grid->Ceze.getDevicePtr(),
						grid->Cezh.getDevicePtr(),
						grid->size);
	updaterHy.setParams(grid->Ez.getDevicePtr(),
						grid->Hy.getDevicePtr(),
						grid->Chyh.getDevicePtr(),
						grid->Chye.getDevicePtr(),
						grid->size);
}

void Updater1DTM::updateFields() {
	updateHy();
	int xCoord = source->getPositionX();
	thrust::device_ptr<float> dptr = &(grid->Ez.getDevicePtr())[xCoord];
	source->updateField(dptr, grid->time);
	updateEz();
	(grid->time)++;
}

void Updater1DTM::updateSources() {}
