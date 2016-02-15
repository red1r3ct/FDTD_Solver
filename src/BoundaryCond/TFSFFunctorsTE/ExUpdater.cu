/*
 * ExUpdater.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "ExUpdater.h"
#include "SmartIndex.h"

// indx - индекс вдоль правой или левой границы по y от firstX до lastX

__host__ __device__
void ExUpdater::operator() (const int indx) {
	float Cexh = S*377.0;
	int n = firstY;
	Ex(indx, n) = Ex(indx, n) - Cexh * Hz1D[indx];
	n = lastY;
	Ex(indx, n) = Ex(indx, n) + Cexh * Hz1D[indx];
}

