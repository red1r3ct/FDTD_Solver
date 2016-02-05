/*
 * TopBottomUpdaterTE.cpp
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#include "TopBottomUpdaterTE.h"

#define Ex(M, N) Ex[(M) * (sizeY) + (N)]
#define Ey(M, N) Ey[(M) * (sizeY-1) + (N)]
#define Hz(M, N) Hz[(M) * (sizeY-1) + (N)]
#define epsilon(M, N) epsilon[(M) * (sizeY) + (N)]

__device__
void TopBottomUpdaterTE::operator() (const int indx) {
	int m = indx;
	// Обновление Ex на краях
	float Cexh = S * 377.0 / epsilon(m, 0);
	// По нижней границе
	Ex(m, 0) = Ex(m, 0) + Cexh*(Hz(m, 0) - Hz(m, sizeY - 2));
	// По верхней, значение на гранях должно быть равно!
	Ex(m, sizeY-1) = Ex(m,0);
}
