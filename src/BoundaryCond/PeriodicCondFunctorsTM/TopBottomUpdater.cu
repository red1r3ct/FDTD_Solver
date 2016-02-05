/*
 * TopBottomUpdater.cpp
 *
 *  Created on: 04 февр. 2016 г.
 *      Author: aleksandr
 */

#include "TopBottomUpdater.h"

#define Hx(M, N) Hx[(M) * (sizeY-1) + (N)]
#define Hy(M, N) Hy[(M) * (sizeY) + (N)]
#define Ez(M, N) Ez[(M) * (sizeY) + (N)]
#define epsilon(M, N) epsilon[(M) * (sizeY) + (N)]
#define sigma(M, N) sigma[(M) * (sizeY) + (N)]

__device__
void TopBottomUpdater::operator() (const int indx) {
	int m = indx;
	// Обновляю промежуточный массив
	float Chxe = S / 377.0;
	HxTemp[m] = HxTemp[m] - Chxe*(Ez(m,0) - Ez(m, sizeY-1));

	float loss = sigma(m, 0)/(2*epsilon(m, 0));
	float Cezh = S * 377.0 / epsilon(m,0) / (1+loss);
	float Ceze = (1-loss)/(1+loss);
	// Обновляет по нижней границе
	Ez(m, 0) = Ceze*Ez(m, 0) + Cezh * ((Hy(m, 0) - Hy(m-1, 0)) - (Hx(m, 0) - HxTemp[m]));

	loss = sigma(m, sizeY-1)/(2*epsilon(m, sizeY-1));
	Cezh = S * 377.0 / epsilon(m,sizeY-1) / (1+loss);
	Ceze = (1-loss)/(1+loss);
	// Обновляет по верхней границе
	Ez(m, sizeY-1) = Ceze*Ez(m, sizeY-1) + Cezh * ((Hy(m, sizeY-1) - Hy(m-1, sizeY-1)) - (HxTemp[m] - Hx(m, sizeY - 2)));
}
