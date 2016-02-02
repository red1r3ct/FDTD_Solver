/*
 * EyRightUpdater.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "EyRightUpdater.h"
#include "SmartIndex.h"

/*
 * indx должен пренадлежать участку от [0, sizeY-1]
 */
__device__
void EyRightUpdater::operator() (const int indx) {
	int n = indx;
	Ey(sizeX - 1, n) = coeff[0]*(Ey(sizeX - 3, n) + EyRight(0, 1, n)) +
			   coeff[1] * (EyRight(0, 0, n) + EyRight(2, 0, n) - Ey(sizeX - 2, n) - EyRight(1, 1, n)) +
			   coeff[2] * EyRight(1, 0, n) - EyRight(2, 1, n);
	for (int m = 0; m < 3; m++) {
		EyRight(m, 1, n) = EyRight(m, 0, n);
		EyRight(m, 0, n) = Ey(sizeX - 1 - m, n);
	}
}

