/*
 * EyUpdater.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "EyUpdater.h"
#include "SmartIndex.h"

// indx - индекс вдоль правой или левой границы по y от firstY до lastY

__host__ __device__
void EyUpdater::operator() (const int indx) {
	// correct Ey field along left edge
	/*mm = firstX;
	for (nn = firstY; nn < lastY; nn++)
	Ey(mm, nn) += Ceyh(mm, nn) * Hz1G(g1, mm - 1);
	 // correct Ey field along right edge
	mm = lastX;
	for (nn = firstY; nn < lastY; nn++)
	Ey(mm, nn) -= Ceyh(mm, nn) * Hz1G(g1, mm);*/
	float Ceyh = S*377.0;
	int m = firstX;
	Ey(m, indx) = Ey(m, indx) + Ceyh * Hz1D[m-1];
	m = lastX;
	Ey(m, indx) = Ey(m, indx) - Ceyh * Hz1D[m];
}
