/*
 * HxUpdaterTM.cpp
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#include "HxUpdaterTM.h"
#include "SmartIndex.h"

#include <thrust/device_vector.h>
#include <thrust/functional.h>

//   o o o o o
//   o o o o o
//   o o o o o
//   o o o o o
//   x x x x x

__host__ __device__
void HxUpdaterTM::operator() (const int indx) {
	// m и n - индексы в полноценных массивах
	// sizeY - размер полноценнго массива
	int m = indx/(sizeY-1);
	int n = indx%(sizeY-1);
	float Chxe = S / 377.0;
	Hx(m, n) = Hx(m, n) - Chxe * (Ez(m, n+1) - Ez(m,n));
}
