/*
 * HyUpdaterTM.cpp
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#include "HyUpdaterTM.h"
#include "SmartIndex.h"

#include <thrust/device_vector.h>
#include <thrust/functional.h>

//   o o o o x
//   o o o o x
//   o o o o x
//   o o o o x
//   o o o o x

__host__ __device__
void HyUpdaterTM::operator() (const int indx) {
	// m и n - индексы в полноценных массивах
	// sizeY - размер полноценнго массива
	int m = indx/(sizeY);
	int n = indx%(sizeY);
	if (excluded(m, n) != 0) {
		return;
	}
	float Chye = S / 377.0;
	Hy(m, n) = Hy(m, n) + Chye * (Ez(m+1, n) - Ez(m,n));
}
