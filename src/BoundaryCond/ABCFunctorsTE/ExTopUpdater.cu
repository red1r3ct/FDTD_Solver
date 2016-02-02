/*
 * ExTopUpdater.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "ExTopUpdater.h"
#include "SmartIndex.h"

/*
 * indx должен пренадлежать участку от [0, sizeX-1)
 */
__device__
void ExTopUpdater::operator() (const int indx) {
	int m = indx;
	Ex(m, sizeY - 1) = coeff[0]*(Ex(m, sizeY - 3) + ExTop(0, 1, m)) +
			   coeff[1] * (ExTop(0, 0, m) + ExTop(2, 0, m) - Ex(m, sizeY - 2) - ExTop(1, 1, m)) +
			   coeff[2] * ExTop(1, 0, m) - ExTop(2, 1, m);
	for (int n = 0; n < 3; n++) {
		ExTop(n, 1, m) = ExTop(n, 0, m);
		ExTop(n, 0, m) = Ex(m, sizeY - 1 - n);
	}
}

