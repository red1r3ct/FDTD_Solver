/*
 * TFSFCond.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#include "TFSFCondTM.h"


TFSFCondTM::TFSFCondTM(GridTM* _grid, int _firstX, int _lastX, int _firstY, int _lastY) :
													grid(_grid), grid1D(_grid->sizeY, _grid->S),
													source(NULL), firstX(_firstX), lastX(_lastX),
													firstY(_firstY), lastY(_lastY)
{
	updater.addGrid(&grid1D);
	EzUpdater.setParams(grid->Ez.getDevicePtr(),
					   grid1D.Hy.getDevicePtr(),
					   grid->sizeX,
					   grid->sizeY,
					   grid->S ,
					   firstX,
					   lastX);
	HxUpdater.setParams(grid->Hx.getDevicePtr(),
	   	   	   	   	   grid1D.Ez.getDevicePtr(),
	   	   	   	   	   grid->sizeX,
	   	   	   	   	   grid->sizeY,
	   	   	   	   	   grid->S ,
	   	   	   	   	   firstY,
	   	   	   	   	   lastY);
	HyUpdater.setParams(grid->Hy.getDevicePtr(),
   	   	   	   	   	   grid1D.Ez.getDevicePtr(),
   	   	   	   	   	   grid->sizeX,
   	   	   	   	   	   grid->sizeY,
   	   	   	   	   	   grid->S ,
   	   	   	   	   	   firstX,
   	   	   	   	   	   lastX);
}

void TFSFCondTM::apply() {
	updateHx();
	updateHy();
	updater.iterate();
	updateEz();
}

void TFSFCondTM::addSource(Source* _source) {
	source = _source;
	updater.addSource(source);
}
