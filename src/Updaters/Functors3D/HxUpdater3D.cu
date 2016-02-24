/*
 * HxUpdater3D.cpp
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#include "HxUpdater3D.h"
#include "SmartIndex.h"

__device__
void HxUpdater3D::operator() (const int indx) {
	int m = (indx / (sizeZ-1)) / (sizeY-1);
	int n = (indx / (sizeZ-1)) % (sizeY-1);
	int p = indx % (sizeZ-1);
	float Chxh = 1.0;
	float Chxe = S/377.0;
	if (n < (sizeY-1) && p < (sizeZ-1)) {
		Hx(m,n,p) = Chxh*Hx(m,n,p) + Chxe*( (Ey(m,n,p+1) - Ey(m,n,p)) - (Ez(m,n+1,p) - Ez(m,n,p)) );
	}
}
