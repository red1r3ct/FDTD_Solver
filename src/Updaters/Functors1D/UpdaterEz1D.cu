/*
 * UpdaterEz1D.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#include "UpdaterEz1D.h"
__device__
void UpdaterEz1D::operator() (const int indx) {
	Ez[indx] = Ceze[indx] * Ez[indx] + Cezh[indx]*(Hy[indx] - Hy[indx-1]);
}
