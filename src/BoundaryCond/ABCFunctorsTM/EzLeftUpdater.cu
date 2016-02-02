/*
 * EzLeftUpdater.cpp
 *
 *  Created on: 23 янв. 2016 г.
 *      Author: aleksandr
 */

#include "EzLeftUpdater.h"
#include "SmartIndex.h"

/*
 * indx должен пренадлежать участку от [0, sizeY-1]
 */
__device__
void EzLeftUpdater::operator() (const int indx) {
	int n = indx;
	Ez(0, n) = coeff[0]*(Ez(2, n) + EzLeft(0, 1, n)) +
			   coeff[1] * (EzLeft(0, 0, n) + EzLeft(2, 0, n) - Ez(1, n) - EzLeft(1, 1, n)) +
			   coeff[2] * EzLeft(1, 0, n) - EzLeft(2, 1, n);
	for (int m = 0; m < 3; m++) {
		EzLeft(m, 1, n) = EzLeft(m, 0, n);
		EzLeft(m, 0, n) = Ez(m, n);
	}
}
