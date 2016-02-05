/*
 * Grid3D.cpp
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#include "Grid3D.h"

#include <iostream>
#include <fstream>
#include <vector>

#define epsilonHost(M, N, P) epsilon[( (M) * (sizeY) + (N) ) * sizeY + (P)]

Grid3D::Grid3D(std::size_t _sizeX, std::size_t _sizeY, std::size_t _sizeZ, float _S) :
									sizeX(_sizeX), sizeY(_sizeY), sizeZ(_sizeZ),
									Hx(sizeX*(sizeY-1)*(sizeY-1), 0), Hy((sizeX-1)*sizeY*(sizeZ-1), 0),
									Hz((sizeX-1)*(sizeY-1)*sizeZ, 0), Ex((sizeX-1)*sizeY*sizeZ, 0),
									Ey(sizeX*(sizeY-1)*sizeZ ,0), Ez(sizeX*sizeY*(sizeZ-1), 0),
									epsilon(sizeX*sizeY*sizeZ, 1), time(0), S(_S) {
	std::cout << "Grid3D was initiated: \n";
	std::cout << "\t sizeX = " << (int)(sizeX) << "px \n";
	std::cout << "\t sizeY = " << (int)(sizeY) << "px \n";
	std::cout << "\t sizeZ = " << (int)(sizeZ) << "px \n";
}

void Grid3D::readEpsilon(const std::string& fileName) {
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
		std::cout << " ! Error reading file with epsilon ! \n";
		return;
	}
	while(!file.eof()) {
		int xCoord(0);
		int yCoord(0);
		int zCoord(0);
		file >> xCoord;
		file >> yCoord;
		file >> zCoord;
		float epsilonValue;
		file >> epsilonValue;
		if (xCoord >= 0 && xCoord < sizeX && yCoord >= 0 && yCoord < sizeY && zCoord >= 0 && zCoord < sizeZ) {
			epsilonHost(xCoord, yCoord, zCoord) = epsilonValue;
		}
	}
	epsilon.CPUtoGPU();
	file.close();
}
