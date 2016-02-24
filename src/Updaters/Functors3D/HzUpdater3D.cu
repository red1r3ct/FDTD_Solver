/*
 * HzUpdater3D.cpp
 *
 *  Created on: 06 февр. 2016 г.
 *      Author: aleksandr
 */

#include "HzUpdater3D.h"
#include "SmartIndex.h"

__device__
void HzUpdater3D::operator() (const int indx) {
	int m = (indx / (sizeZ)) / (sizeY-1);
	int n = (indx / (sizeZ)) % (sizeY-1);
	int p = indx % (sizeZ-1);
	float Chzh = 1.0;
	float Chze = S/377.0;
	if (m < (sizeX-1) && n < (sizeY-1)) {
		Hz(m,n,p) = Chzh*Hz(m,n,p) + Chze*( (Ex(m,n+1,p) - Ex(m,n,p)) - (Ey(m+1,n,p) - Ey(m,n,p)) );
	}
}
