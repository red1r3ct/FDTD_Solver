/*
 * GridTE.h
 *
 *  Created on: 28 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef GRIDTE_H_
#define GRIDTE_H_

#include "../Structures/HostDeviceVector.h"

#include <string>

typedef HostDeviceVector vector;

class GridTE {
public:
	GridTE(std::size_t _sizeX, std::size_t _sizeY, float _S);
	~GridTE() {};

	void readEpsilon(const std::string& fileName);

	int sizeX, sizeY;
	float S;
	vector Hz, Ex, Ey, epsilon;
	int time;
};

#endif /* GRIDTE_H_ */
