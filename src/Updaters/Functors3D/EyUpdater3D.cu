/*
 * EyUpdater3D.cpp
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#include "EyUpdater3D.h"
#include "SmartIndex.h"

__device__
void EyUpdater3D::operator() (const int indx) {
	int m = (indx / sizeZ) / (sizeY-1);
	int n = (indx / sizeZ) % (sizeY-1);
	int p = indx % sizeZ;
	float Ceye = 1.0;
	float Ceyh = S*377.0;
	if (m > 0 && m < (sizeX-1) && n < (sizeY-1) && p > 0 && p < (sizeZ-1)) {
		Ey(m,n,p) = Ceye*Ey(m,n,p) + Ceyh*( (Hx(m,n,p) - Hx(m,n,p-1)) - (Hy(m,n,p) - Hy(m,n,p-1)) );
	}
}
