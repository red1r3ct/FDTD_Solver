/*
 * UpdaterHz1D.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "UpdaterHz1D.h"

__device__
void UpdaterHz1D::operator() (const int indx) {
	Hz[indx] = Chzh[indx] * Hz[indx] - Chze[indx]*(Ey[indx+1] - Ey[indx]);
}
