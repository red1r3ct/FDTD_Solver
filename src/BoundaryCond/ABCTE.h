/*
 * ABCTE.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef ABCTE_H_
#define ABCTE_H_

#include <thrust/device_vector.h>

#include "../Structures/HostDeviceVector.h"
#include "../Grids/GridTE.h"
#include "BoundaryCond.h"

#include "ABCFunctorsTE/ExBottomUpdater.h"
#include "ABCFunctorsTE/ExTopUpdater.h"
#include "ABCFunctorsTE/EyLeftUpdater.h"
#include "ABCFunctorsTE/EyRightUpdater.h"

/*
 * Поглащающие граничные условия. http://www.eecs.wsu.edu/~schneidj/ufdtd/chap8.pdf
 * Должен быть унаследован от BoundaryCond.
 */

typedef HostDeviceVector vector;

class ABCTE : public BoundaryCond {
public:
	ABCTE(GridTE* _grid);
	~ABCTE() {};

	void apply();

private:
	vector EyLeft, EyRight, ExTop, ExBottom;
	float coeff0, coeff1, coeff2;
	thrust::device_vector<float> coeffDevice;

	GridTE* grid;

	EyLeftUpdater leftUpdater;
	EyRightUpdater rightUpdater;
	ExTopUpdater topUpdater;
	ExBottomUpdater bottomUpdater;
};

#endif /* ABCTE_H_ */
