/*
 * TFSFCond.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef TFSFCOND_H_
#define TFSFCOND_H_

#include "BoundaryCond.h"
#include "TFSFFunctorsTM/EzUpdater.h"
#include "TFSFFunctorsTM/HyUpdater.h"
#include "TFSFFunctorsTM/HxUpdater.h"
#include "../Structures/HostDeviceVector.h"
#include "../Grids/Grid1DTM.h"
#include "../Grids/GridTM.h"
#include "../Sources/Source.h"
#include "../Updaters/Updater1DTM.h"


typedef HostDeviceVector vector;

class TFSFCondTM: public BoundaryCond {
public:
	TFSFCondTM(GridTM* _grid, int _firstX, int _lastX, int _firstY, int _lastY);
	~TFSFCondTM() {};

	void apply();

	void addSource(Source* _source);

private:
	void updateHy();
	void updateHx();
	void updateEz();
	GridTM* grid;
	Grid1DTM grid1D;
	Updater1DTM updater;
	Source* source;

	EzUpdater EzUpdater;
	HxUpdater HxUpdater;
	HyUpdater HyUpdater;

	int firstX, lastX, firstY, lastY;
};

#endif /* TFSFCOND_H_ */
