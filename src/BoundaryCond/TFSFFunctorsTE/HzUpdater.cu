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
	// correct Hz along left edge
	/*mm = firstX - 1;
	for (nn = firstY; nn < lastY; nn++)
	Hz(mm, nn) += Chze(mm, nn) * Ey1G(g1, mm + 1);
	// correct Hz along right edge
	mm = lastX;
	for (nn = firstY; nn < lastY; nn++)
	Hz(mm, nn) -= Chze(mm, nn) * Ey1G(g1, mm);*/
	float Chze = S/377.0;
	int m = firstX;
	Hz(m, indx) = Hz(m, indx) + Chze * Ey1D[m];
	m = lastX;
	Hz(m, indx) = Hz(m, indx) - Chze * Ey1D[m+1];
}
