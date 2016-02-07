/*
 * EzUpdater3D.cpp
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#include "EzUpdater3D.h"
#include "SmartIndex.h"

__device__
void EzUpdater3D::operator() (const int indx) {
	int m = (indx / (sizeZ-1)) / sizeY;
	int n = (indx / (sizeZ-1)) % sizeY;
	int p = indx % (sizeZ-1);
	float Ceze = 1.0;
	float Cezh = S*377.0;
	if (m<(sizeX-1) && n > 0 && n < (sizeY-1) && m > 0 && p < (sizeZ-1)) {
		Ez(m,n,p) = Ceze*Ez(m,n,p) + Cezh*( (Hy(m,n,p) - Hy(m-1,n,p)) - (Hx(m,n,p) - Hx(m,n-1,p)) );
	}
}
