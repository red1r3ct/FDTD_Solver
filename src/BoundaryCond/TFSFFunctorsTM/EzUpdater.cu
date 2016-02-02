/*
 * EzUpdater.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#include "EzUpdater.h"
#include "SmartIndex.h"

// indx - индекс вдоль правой или левой границы по y от firstY до lastY

__host__ __device__
void EzUpdater::operator() (const int indx) {
	/* correct Ez adjacent to TFSF boundary */
	// correct Ez field along left edge
	// mm = firstX;
	// for (nn = firstY; nn <= lastY; nn++)
	// Ez(mm, nn) -= Cezh(mm, nn) * Hy1G(g1, mm - 1);
	//
	// // correct Ez field along right edge
	// mm = lastX;
	// for (nn = firstY; nn <= lastY; nn++)
	// Ez(mm, nn) += Cezh(mm, nn) * Hy1G(g1, mm);
	float Cezh = S*377.0;
	int m = firstX;
	Ez(m, indx) = Ez(m, indx) - Cezh * Hy1D[m-1];
	m = lastX;
	Ez(m, indx) = Ez(m, indx) + Cezh * Hy1D[m];
}
