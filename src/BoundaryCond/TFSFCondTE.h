/*
 * TFSFCondTE.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef TFSFCONDTE_H_
#define TFSFCONDTE_H_

#include "BoundaryCond.h"

#include "BoundaryCond.h"
#include "TFSFFunctorsTE/HzUpdater.h"
#include "TFSFFunctorsTE/EyUpdater.h"
#include "TFSFFunctorsTE/ExUpdater.h"
#include "../Structures/HostDeviceVector.h"
#include "../Grids/Grid1DTE.h"
#include "../Grids/GridTE.h"
#include "../Sources/Source.h"
#include "../Updaters/Updater1DTE.h"


typedef HostDeviceVector vector;

class TFSFCondTE: public BoundaryCond {
public:
	TFSFCondTE(GridTE* _grid, int _firstX, int _lastX, int _firstY, int _lastY);
	~TFSFCondTE() {};

	void apply();

	void addSource(Source* _source);

private:
	void updateEy();
	void updateEx();
	void updateHz();
	GridTE* grid;
	Grid1DTE grid1D;
	Updater1DTE updater;
	Source* source;

	EyUpdater EyUpdater;
	ExUpdater ExUpdater;
	HzUpdater HzUpdater;

	int firstX, lastX, firstY, lastY;
};

#endif /* TFSFCONDTE_H_ */
