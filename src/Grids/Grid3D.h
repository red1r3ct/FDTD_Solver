/*
 * Grid3D.h
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef GRID3D_H_
#define GRID3D_H_

#include "../Structures/HostDeviceVector.h"

#include <string>

typedef HostDeviceVector vector;

class Grid3D {
public:
	Grid3D(std::size_t _sizeX, std::size_t _sizeY, std::size_t _sizeZ, float _S);
	~Grid3D() {};

	void readEpsilon(const std::string& fileName);

	int sizeX, sizeY, sizeZ;
	float S;
	vector Hx, Hy, Hz, Ex, Ey, Ez, epsilon;
	int time;
};
#endif /* GRID3D_H_ */
