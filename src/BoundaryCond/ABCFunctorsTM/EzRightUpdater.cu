/*
 * EzRightUpdater.cpp
 *
 *  Created on: 23 янв. 2016 г.
 *      Author: aleksandr
 */

#include "EzRightUpdater.h"
#include "SmartIndex.h"

/*
 * indx должен пренадлежать участку от [0, sizeY-1]
 */
__device__
void EzRightUpdater::operator() (const int indx) {
	int n = indx;
	Ez(sizeX - 1, n) = coeff[0]*(Ez(sizeX - 3, n) + EzRight(0, 1, n)) +
			   coeff[1] * (EzRight(0, 0, n) + EzRight(2, 0, n) - Ez(sizeX - 2, n) - EzRight(1, 1, n)) +
			   coeff[2] * EzRight(1, 0, n) - EzRight(2, 1, n);
	for (int m = 0; m < 3; m++) {
		EzRight(m, 1, n) = EzRight(m, 0, n);
		EzRight(m, 0, n) = Ez(sizeX - 1 - m, n);
	}
}

