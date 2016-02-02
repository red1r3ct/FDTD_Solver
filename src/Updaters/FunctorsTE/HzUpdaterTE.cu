/*
 * HzUpdaterTE.cpp
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: aleksandr
 */

#include "HzUpdaterTE.h"
#include "SmartIndex.h"
//   o o o o x
//   o o o o x
//   o o o o x
//   o o o o x
//   x x x x x

__host__ __device__
void HzUpdaterTE::operator() (const int indx) {
	// m и n - индексы в полноценных массивах
	// sizeY - размер полноценнго массива
	int m = indx/(sizeY);
	int n = indx%(sizeY);
	float Chze = S / 377.0;
	if ( (m<sizeX-1) && (n<sizeY-1) ) {
		Hz(m, n) = Hz(m, n) + Chze*((Ex(m, n + 1) - Ex(m, n)) - (Ey(m + 1, n) - Ey(m, n)));
	}
}
