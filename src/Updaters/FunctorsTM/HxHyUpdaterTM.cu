/*
 * HxHyUpdaterTM.cpp
 *
 *  Created on: 20 янв. 2016 г.
 *      Author: aleksandr
 */

#include "HxHyUpdaterTM.h"
#include "SmartIndex.h"

#include <thrust/device_vector.h>
#include <thrust/functional.h>


// indx - номер в массиве (1,1) .. (sizeX-1, sizeY-1), то есть без граничных областей
//   Hx
//   o o o o o
//   o o o o o
//   o o o o o
//   o o o o o
//   x x x x x
//   Hy
//   o o o o x
//   o o o o x
//   o o o o x
//   o o o o x
//   o o o o x
//
//   v v v v v
//
//   o o o o o
//   o o o o o
//   o o o o o
//   o o o o o
//   o o o o x


__host__ __device__
void HxHyUpdaterTM::operator() (const int indx) {
	// m и n - индексы в полноценных массивах
	// sizeY - размер полноценнго массива
	int m = indx/(sizeY);
	int n = indx%(sizeY);
	if (excluded(m, n) != 0) {
		return;
	}
	float Che = S / 377.0;
	if(m < sizeX-1) {
		Hy(m, n) = Hy(m, n) + Che * (Ez(m+1, n) - Ez(m,n));
	}
	if(n < sizeY-1) {
		Hx(m, n) = Hx(m, n) - Che * (Ez(m, n+1) - Ez(m,n));
	}
}
