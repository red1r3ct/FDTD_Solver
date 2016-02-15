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
	float Ceyh = S*377.0;
	int m = firstX;
	Ey(m, indx) = Ey(m, indx) + Ceyh * Hz1D[m-1];
	m = lastX;
	Ey(m, indx) = Ey(m, indx) - Ceyh * Hz1D[m];
}
