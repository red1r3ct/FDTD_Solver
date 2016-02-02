/*
 * HyUpdater.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#include "HyUpdater.h"
#include "SmartIndex.h"

// indx - индекс вдоль правой или левой границы по y от firstY до lastY

__host__ __device__
void HyUpdater::operator() (const int indx) {
	// correct Hy along left edge
	// mm = firstX - 1;
	// for (nn = firstY; nn <= lastY; nn++)
	// Hy(mm, nn) -= Chye(mm, nn) * Ez1G(g1, mm + 1);
	//
	// // correct Hy along right edge
	// mm = lastX;
	// for (nn = firstY; nn <= lastY; nn++)
	// Hy(mm, nn) += Chye(mm, nn) * Ez1G(g1, mm);
	float Chye = S/377.0;
	int m = firstX - 1;
	Hy(m, indx) = Hy(m, indx) - Chye * Ez1D[m+1];
	m = lastX;
	Hy(m, indx) = Hy(m, indx) + Chye * Ez1D[m];
}

