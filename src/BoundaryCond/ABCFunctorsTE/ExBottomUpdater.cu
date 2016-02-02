/*
 * ExBottomUpdater.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "ExBottomUpdater.h"
#include "SmartIndex.h"
/*
 * indx должен пренадлежать участку от [0, sizeX-1]
 */
__device__
void ExBottomUpdater::operator() (const int indx) {
	int m = indx;
	Ex(m, 0) = coeff[0] * (Ex(m, 2) + ExBottom(0, 1, m)) +
			   coeff[1] * (ExBottom(0, 0, m) + ExBottom(2, 0, m) - Ex(m, 1) - ExBottom(1, 1, m)) +
			   coeff[2] * ExBottom(1, 0, m) - ExBottom(2, 1, m);
	for (int n = 0; n < 3; n++) {
		ExBottom(n, 1, m) = ExBottom(n, 0, m);
		ExBottom(n, 0, m) = Ex(m, n);
	}
}
