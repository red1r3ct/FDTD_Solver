/*
 * ExUpdater3D.cpp
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#include "ExUpdater3D.h"
#include "SmartIndex.h"

__device__
void ExUpdater3D::operator() (const int indx) {
	int m = (indx / sizeZ) / sizeY;
	int n = (indx / sizeZ) % sizeY;
	int p = indx % sizeZ;
	float Cexe = 1.0;
	float Cexh = S*377.0;
	if (m<(sizeX-1) && n > 0 && n < (sizeY-1) && p > 0 && p < (sizeZ-1)) {
		Ex(m,n,p) = Cexe*Ex(m,n,p) + Cexh*( (Hz(m,n,p) - Hz(m,n-1,p)) - (Hy(m,n,p) - Hy(m,n,p-1)) );
	}
}
