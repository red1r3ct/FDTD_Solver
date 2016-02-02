/*
 * ExUpdaterTE.cpp
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: aleksandr
 */

#include "ExUpdaterTE.h"
#include "SmartIndex.h"
//   x x x x x
//   o o o o x
//   o o o o x
//   o o o o x
//   x x x x x

__host__ __device__
void ExUpdaterTE::operator() (const int indx) {
	// m и n - индексы в полноценных массивах
	// sizeY - размер полноценнго массива
	int m = indx/(sizeY);
	int n = indx%(sizeY);
	float Cexh = S * 377.0;
	if ( m < (sizeX - 1) && n > 0 && n < (sizeX - 1) ) {
		Ex(m, n) = Ex(m, n) + Cexh/epsilon(m, n)*(Hz(m, n) - Hz(m, n - 1));
	}
}
