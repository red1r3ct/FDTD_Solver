/*
 * EyUpdaterTE.cpp
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: aleksandr
 */

#include "EyUpdaterTE.h"
#include "SmartIndex.h"
//   x o o o x
//   x o o o x
//   x o o o x
//   x o o o x
//   x x x x x

__host__ __device__
void EyUpdaterTE::operator() (const int indx) {
	// m и n - индексы в полноценных массивах
	// sizeY - размер полноценнго массива
	int m = indx/(sizeY);
	int n = indx%(sizeY);
	float Ceyh = S * 377.0;
	if ( (m>0 && m<sizeX-1) && (n<sizeY-1) ) {
		Ey(m, n) = Ey(m, n) - Ceyh/epsilon(m, n)*(Hz(m, n) - Hz(m-1, n));
	}
}
