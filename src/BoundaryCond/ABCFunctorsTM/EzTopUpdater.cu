/*
 * EzTopUpdater.cpp
 *
 *  Created on: 23 янв. 2016 г.
 *      Author: aleksandr
 */

#include "EzTopUpdater.h"
#include "SmartIndex.h"

/*
 * indx должен пренадлежать участку от [0, sizeX-1]
 */
__device__
void EzTopUpdater::operator() (const int indx) {
	int m = indx;
	Ez(m, sizeY - 1) = coeff[0]*(Ez(m, sizeY - 3) + EzTop(0, 1, m)) +
			   coeff[1] * (EzTop(0, 0, m) + EzTop(2, 0, m) - Ez(m, sizeY - 2) - EzTop(1, 1, m)) +
			   coeff[2] * EzTop(1, 0, m) - EzTop(2, 1, m);
	for (int n = 0; n < 3; n++) {
		EzTop(n, 1, m) = EzTop(n, 0, m);
		EzTop(n, 0, m) = Ez(m, sizeY - 1 - n);
	}
}
