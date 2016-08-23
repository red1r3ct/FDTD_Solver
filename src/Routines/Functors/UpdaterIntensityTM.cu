/*
 * UpdaterEz1D.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#include "UpdaterIntensityTM.h"

__device__
void UpdaterIntensityTM::operator() (const int indx) {
	#define Ez(M, N) Ez[(M) * (gridSizeY) + (N)]
	const int n = indx % sizeY;
	const int m = indx / sizeY;
	intensity[indx] += Ez(firstX + m*stepX, firstY + n*stepX)*Ez(firstX + m*stepX, firstY + n*stepX);
}
