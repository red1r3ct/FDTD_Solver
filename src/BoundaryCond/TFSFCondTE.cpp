/*
 * TFSFCondTE.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "TFSFCondTE.h"


TFSFCondTE::TFSFCondTE(GridTE* _grid, int _firstX, int _lastX, int _firstY, int _lastY) :
													grid(_grid), grid1D(_grid->sizeY, _grid->S),
													source(NULL), firstX(_firstX), lastX(_lastX),
													firstY(_firstY), lastY(_lastY)
{
	updater.addGrid(&grid1D);
	HzUpdater.setParams(grid->Hz.getDevicePtr(),
					   grid1D.Ey.getDevicePtr(),
					   grid->sizeX,
					   grid->sizeY,
					   grid->S ,
					   firstX,
					   lastX);
	EyUpdater.setParams(grid->Ey.getDevicePtr(),
	   	   	   	   	   grid1D.Hz.getDevicePtr(),
	   	   	   	   	   grid->sizeX,
	   	   	   	   	   grid->sizeY,
	   	   	   	   	   grid->S ,
	   	   	   	   	   firstX,
	   	   	   	   	   lastX);
	ExUpdater.setParams(grid->Ex.getDevicePtr(),
   	   	   	   	   	   grid1D.Hz.getDevicePtr(),
   	   	   	   	   	   grid->sizeX,
   	   	   	   	   	   grid->sizeY,
   	   	   	   	   	   grid->S ,
   	   	   	   	   	   firstY,
   	   	   	   	   	   lastY);
}

void TFSFCondTE::apply() {
	updateHz();
	updater.iterate();
	updateEx();
	updateEy();
}

void TFSFCondTE::addSource(Source* _source) {
	source = _source;
	updater.addSource(source);
}
