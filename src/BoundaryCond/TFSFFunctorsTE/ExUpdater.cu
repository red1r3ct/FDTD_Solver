/*
 * ExUpdater.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "ExUpdater.h"
#include "SmartIndex.h"

// indx - индекс вдоль правой или левой границы по y от firstY до lastY

__host__ __device__
void ExUpdater::operator() (const int indx) {
	// correct Ex along the bottom
	/*nn = firstY;
	for (mm = firstX; mm < lastX; mm++)
	Ex(mm, nn) -= Cexh(mm, nn) * Hz1G(g1, mm);
	// correct Ex along the top
	nn = lastY;
	for (mm = firstX; mm < lastX; mm++)
	Ex(mm, nn) += Cexh(mm, nn) * Hz1G(g1, mm);*/
	float Cexh = S*377.0;
	int n = firstY;
	Ex(indx, n) = Ex(indx, n) - Cexh * Hz1D[indx];
	n = lastY;
	Ex(indx, n) = Ex(indx, n) + Cexh * Hz1D[indx];
}

