/*
 * HyUpdater3D.cpp
 *
 *  Created on: 06 февр. 2016 г.
 *      Author: aleksandr
 */

#include "HyUpdater3D.h"
#include "SmartIndex.h"

__device__
void HyUpdater3D::operator() (const int indx) {
	int m = (indx / (sizeZ-1)) / (sizeY);
	int n = (indx / (sizeZ-1)) % (sizeY);
	int p = indx % (sizeZ-1);
	float Chyh = 1.0;
	float Chye = S/377.0;
	if (m < (sizeX-1) && p < (sizeZ-1)) {
		Hy(m,n,p) = Chyh*Hy(m,n,p) + Chye*( (Ez(m+1,n,p) - Ez(m,n,p)) - (Ex(m,n,p+1) - Ex(m,n,p)) );
	}
}
