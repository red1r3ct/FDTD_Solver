/*
 * GridTE.cpp
 *
 *  Created on: 28 янв. 2016 г.
 *      Author: aleksandr
 */

#include "GridTE.h"

#include <iostream>
#include <fstream>
#include <vector>

#define epsilonHost(M, N) epsilon[(M) * (sizeY) + (N)]

GridTE::GridTE(std::size_t _sizeX, std::size_t _sizeY, float _S) :  sizeX(_sizeX), sizeY(_sizeY),
														  Hz((sizeX-1)*(sizeY-1), 0),
														  Ex((sizeX-1)*sizeY, 0), Ey(sizeX*(sizeY-1) ,0),
														  epsilon(sizeX*sizeY, 1), time(0), S(_S) {
	std::cout << "GridTE was initiated: \n";
	std::cout << "\t sizeX = " << (int)(sizeX) << "px \n";
	std::cout << "\t sizeY = " << (int)(sizeY) << "px \n";
}

void GridTE::readEpsilon(const std::string& fileName) {
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
		std::cout << " ! Error reading file with epsilon ! \n";
		return;
	}
	while(!file.eof()) {
		int xCoord(0);
		int yCoord(0);
		file >> xCoord;
		file >> yCoord;
		float epsilonValue;
		file >> epsilonValue;
		if (xCoord >= 0 && xCoord < sizeX && yCoord >= 0 && yCoord < sizeY) {
			epsilonHost(xCoord, yCoord) = epsilonValue;
		}
	}
	epsilon.CPUtoGPU();
	file.close();
}
