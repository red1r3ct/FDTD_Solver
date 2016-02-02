/*
 * Grid1D.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef GRID1D_H_
#define GRID1D_H_

#include "../Structures/HostDeviceVector.h"

typedef HostDeviceVector vector;

class Grid1DTM {
public:
	Grid1DTM(std::size_t _size, float _S, std::size_t _nLoss = 20, float _maxLoss = 0.35);

	~Grid1DTM() {};

	std::size_t size, time, nLoss;
	vector Hy, Ez, Chyh, Chye, Ceze, Cezh;
	float S, maxLoss;
};

#endif /* GRID1D_H_ */
