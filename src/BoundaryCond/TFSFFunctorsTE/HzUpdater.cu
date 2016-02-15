/*
 * HzUpdater.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "HzUpdater.h"
#include "SmartIndex.h"

// indx - индекс вдоль правой или левой границы по y от firstY до lastY

__host__ __device__
void HzUpdater::operator() (const int indx) {
	float Chze = S/377.0;
	int m = firstX-1;
	Hz(m, indx) = Hz(m, indx) + Chze * Ey1D[m+1];
	m = lastX;
	Hz(m, indx) = Hz(m, indx) - Chze * Ey1D[m];
}
