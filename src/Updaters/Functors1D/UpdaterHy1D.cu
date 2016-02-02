/*
 * UpdaterHy1D.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#include "UpdaterHy1D.h"
__device__
void UpdaterHy1D::operator() (const int indx) {
	Hy[indx] = Chyh[indx]*Hy[indx] + Chye[indx]*(Ez[indx+1] - Ez[indx]);
}
