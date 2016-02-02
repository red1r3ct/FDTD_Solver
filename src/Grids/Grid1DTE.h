/*
 * Grid1DTE.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef GRID1DTE_H_
#define GRID1DTE_H_

#include "../Structures/HostDeviceVector.h"

typedef HostDeviceVector vector;

class Grid1DTE {
public:
	Grid1DTE(std::size_t _size, float _S, std::size_t _nLoss = 20, float _maxLoss = 0.35);

	~Grid1DTE() {};

	std::size_t size, time, nLoss;
	vector Hz, Ey, Chzh, Chze, Ceye, Ceyh;
	float S, maxLoss;
};

#endif /* GRID1DTE_H_ */
