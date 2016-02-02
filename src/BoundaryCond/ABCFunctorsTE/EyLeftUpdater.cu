/*
 * EyLeftUpdater.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "EyLeftUpdater.h"
#include "SmartIndex.h"

/*
 * indx должен пренадлежать участку от [0, sizeY-1]
 */
__device__
void EyLeftUpdater::operator() (const int indx) {
	int n = indx;
	Ey(0, n) = coeff[0]*(Ey(2, n) + EyLeft(0, 1, n)) +
			   coeff[1] * (EyLeft(0, 0, n) + EyLeft(2, 0, n) - Ey(1, n) - EyLeft(1, 1, n)) +
			   coeff[2] * EyLeft(1, 0, n) - EyLeft(2, 1, n);
	for (int m = 0; m < 3; m++) {
		EyLeft(m, 1, n) = EyLeft(m, 0, n);
		EyLeft(m, 0, n) = Ey(m, n);
	}
}
