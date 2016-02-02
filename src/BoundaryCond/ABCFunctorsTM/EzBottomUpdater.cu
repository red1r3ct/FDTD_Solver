/*
 * EzBottomUpdater.cpp
 *
 *  Created on: 23 янв. 2016 г.
 *      Author: aleksandr
 */

#include "EzBottomUpdater.h"
#include "SmartIndex.h"
#define EzBottom(N, Q, M) EzBottom[(M) * 6 + (Q) * 3 + (N)]
/*
 * indx должен пренадлежать участку от [0, sizeX-1]
 */
__device__
void EzBottomUpdater::operator() (const int indx) {
	int m = indx;
	Ez(m, 0) = coeff[0] * (Ez(m, 2) + EzBottom(0, 1, m)) +
			   coeff[1] * (EzBottom(0, 0, m) + EzBottom(2, 0, m) - Ez(m, 1) - EzBottom(1, 1, m)) +
			   coeff[2] * EzBottom(1, 0, m) - EzBottom(2, 1, m);
	for (int n = 0; n < 3; n++) {
		EzBottom(n, 1, m) = EzBottom(n, 0, m);
		EzBottom(n, 0, m) = Ez(m, n);
	}
}
