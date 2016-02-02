/*
 * ABC.h
 *
 *  Created on: 19 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef ABC_H_
#define ABC_H_

#include <thrust/device_vector.h>

#include "../Structures/HostDeviceVector.h"
#include "../Grids/GridTM.h"
#include "BoundaryCond.h"

#include "ABCFunctorsTM/EzBottomUpdater.h"
#include "ABCFunctorsTM/EzTopUpdater.h"
#include "ABCFunctorsTM/EzLeftUpdater.h"
#include "ABCFunctorsTM/EzRightUpdater.h"

/*
 * Поглащающие граничные условия. http://www.eecs.wsu.edu/~schneidj/ufdtd/chap8.pdf
 * Должен быть унаследован от BoundaryCond.
 */

typedef HostDeviceVector vector;

class ABCTM : public BoundaryCond {
public:
	ABCTM(GridTM* _grid);
	~ABCTM() {};

	void apply();

private:
	vector EzLeft, EzRight, EzTop, EzBottom;
	float coeff0, coeff1, coeff2;
	thrust::device_vector<float> coeffDevice;

	GridTM* grid;

	EzLeftUpdater leftUpdater;
	EzRightUpdater rightUpdater;
	EzTopUpdater topUpdater;
	EzBottomUpdater bottomUpdater;
};

#endif /* ABC_H_ */
