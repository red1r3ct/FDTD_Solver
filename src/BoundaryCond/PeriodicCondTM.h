/*
 * PeriodicCond.h
 *
 *  Created on: 04 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef PERIODICCONDTM_H_
#define PERIODICCONDTM_H_

#include "BoundaryCond.h"
#include "../Structures/HostDeviceVector.h"
#include "../Grids/GridTM.h"

#include "ABCFunctorsTM/EzLeftUpdater.h"
#include "ABCFunctorsTM/EzRightUpdater.h"
#include "PeriodicCondFunctorsTM/TopBottomUpdater.h"

/*
 * Периодические граничные условия должны обновлять
 * Ez на границах области исходя из Hx и Hy вблизи
 * других границ.
 * Работают сверху и снизу.
 * Вводится промежутоный массив Hx
 */

typedef HostDeviceVector vector;

class PeriodicCondTM: public BoundaryCond {
public:
	PeriodicCondTM(GridTM* _grid);
	~PeriodicCondTM() {};

	void apply();
private:
	vector EzLeft, EzRight, HxTemp;
	float coeff0, coeff1, coeff2;
	thrust::device_vector<float> coeffDevice;

	GridTM* grid;

	EzLeftUpdater leftUpdater;
	EzRightUpdater rightUpdater;
	TopBottomUpdater topBottomUpdater;
};

#endif /* PERIODICCONDTM_H_ */
