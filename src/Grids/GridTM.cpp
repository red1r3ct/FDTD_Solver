/*
 * GridTM.cpp
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#include "GridTM.h"

#include <iostream>
#include <fstream>
#include <vector>

#define epsilonHost(M, N) epsilon[(M) * (sizeY) + (N)]
#define excludedHost(M, N) excluded[(M) * (sizeY) + (N)]
#define sigmaHost(M, N) sigma[(M) * (sizeY) + (N)]

GridTM::GridTM(std::size_t _sizeX, std::size_t _sizeY, float _S) :  sizeX(_sizeX), sizeY(_sizeY), Hx(sizeX*(sizeY-1), 0),
														  Hy((sizeX-1)*sizeY, 0), Ez(sizeX*sizeY ,0),
														  epsilon(sizeX*sizeY, 1), sigma(sizeX*sizeY, 0),
														  time(0), S(_S), excluded(sizeX*sizeY, 0) {
	std::cout << "GridTM was initiated: \n";
	std::cout << "\t sizeX = " << (int)(sizeX) << "px \n";
	std::cout << "\t sizeY = " << (int)(sizeY) << "px \n";
}

void GridTM::readEpsilon(const std::string& fileName) {
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

void GridTM::readExcluded(const std::string& fileName) {
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
		std::cout << " ! Error reading file with excluded ! \n";
		return;
	}
	while(!file.eof()) {
		int xCoord(0);
		int yCoord(0);
		file >> xCoord;
		file >> yCoord;
		float excludedValue;
		file >> excludedValue;
		if (xCoord >= 0 && xCoord < sizeX && yCoord >= 0 && yCoord < sizeY) {
			excludedHost(xCoord, yCoord) = excludedValue;
		}
	}
	excluded.CPUtoGPU();
	file.close();
}

void GridTM::readSigma(const std::string& fileName) {
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
		std::cout << " ! Error reading file with sigma ! \n";
		return;
	}
	while(!file.eof()) {
		int xCoord(0);
		int yCoord(0);
		file >> xCoord;
		file >> yCoord;
		float sigmaValue;
		file >> sigmaValue;
		if (xCoord >= 0 && xCoord < sizeX && yCoord >= 0 && yCoord < sizeY) {
			sigmaHost(xCoord, yCoord) = sigmaValue;
		}
	}
	sigma.CPUtoGPU();
	file.close();
}
