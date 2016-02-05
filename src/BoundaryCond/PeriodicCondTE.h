/*
 * PeriodicCondTE.h
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef PERIODICCONDTE_H_
#define PERIODICCONDTE_H_

#include "BoundaryCond.h"
#include "../Structures/HostDeviceVector.h"
#include "../Grids/GridTE.h"

#include "ABCFunctorsTE/EyLeftUpdater.h"
#include "ABCFunctorsTE/EyRightUpdater.h"
#include "PeriodicCondFunctorsTE/TopBottomUpdaterTE.h"

/*
 * Периодические граничные условия должны обновлять
 * Ez на границах области исходя из Hx и Hy вблизи
 * других границ.
 * Работают сверху и снизу.
 * Вводится промежутоный массив Hx
 */

typedef HostDeviceVector vector;

class PeriodicCondTE: public BoundaryCond {
public:
	PeriodicCondTE(GridTE* _grid);
	~PeriodicCondTE() {};

	void apply();
private:
	vector EyLeft, EyRight;
	float coeff0, coeff1, coeff2;
	thrust::device_vector<float> coeffDevice;

	GridTE* grid;

	EyLeftUpdater leftUpdater;
	EyRightUpdater rightUpdater;
	TopBottomUpdaterTE topBottomUpdater;
};

#endif /* PERIODICCONDTE_H_ */
