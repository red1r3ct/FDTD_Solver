/*
 * UpdaterEy1D.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "UpdaterEy1D.h"


__device__
void UpdaterEy1D::operator() (const int indx) {
	Ey[indx] = Ceye[indx] * Ey[indx] - Ceyh[indx]*(Hz[indx] - Hz[indx-1]);
}

