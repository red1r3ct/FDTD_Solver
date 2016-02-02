/*
 * HxUpdater.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#include "HxUpdater.h"
#include "SmartIndex.h"

// indx - индекс вдоль правой или левой границы по y от firstY до lastY

__host__ __device__
void HxUpdater::operator() (const int indx) {
	// correct Hx along the bottom
	// nn = firstY - 1;
	// for (mm = firstX; mm <= lastX; mm++)
	// Hx(mm, nn) += Chxe(mm, nn) * Ez1G(g1, mm);
	//
	// // correct Hx along the top
	// nn = lastY;
	// for (mm = firstX; mm <= lastX; mm++)
	// Hx(mm, nn) -= Chxe(mm, nn) * Ez1G(g1, mm);
	float Chxe = S/377.0;
	Hx(indx, firstY - 1) = Hx(indx, firstY - 1) + Chxe * Ez1D[indx];
	Hx(indx, lastY) = Hx(indx, lastY) - Chxe * Ez1D[indx];
}

