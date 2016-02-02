/*
 * ABCTE.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "ABCTE.h"

#include <iostream>

ABCTE::ABCTE(GridTE* _grid) : EyLeft((_grid->sizeY-1)*6, 0),
						  EyRight((_grid->sizeY-1)*6, 0),
						  ExTop((_grid->sizeX-1)*6, 0),
						  ExBottom((_grid->sizeX-1)*6, 0),
						  coeff0(0),
						  coeff1(0),
						  coeff2(0),
						  grid(_grid),
						  coeffDevice(3, 0)
{
	float temp1 = grid->S;
	float temp2 = 1.0 / temp1 + 2.0 + temp1;
	coeff0 = -(1.0 / temp1 - 2.0 + temp1) / temp2;
	coeff1 = -2.0 * (temp1 - 1.0 / temp1) / temp2;
	coeff2 = 4.0 * (temp1 + 1.0 / temp1)  / temp2;
	int sizeX = grid->sizeX;
	int sizeY = grid->sizeY;
	std::vector<float> coeffHost(3, 0);
	coeffHost[0] = coeff0;
	coeffHost[1] = coeff1;
	coeffHost[2] = coeff2;
	coeffDevice = coeffHost;
	leftUpdater.setParams(grid->Ey.getDevicePtr(),
							EyLeft.getDevicePtr(),
							coeffDevice.data(),
							sizeX, sizeY);
	rightUpdater.setParams(grid->Ey.getDevicePtr(),
							  EyRight.getDevicePtr(),
							  coeffDevice.data(),
							  sizeX, sizeY);
	topUpdater.setParams(grid->Ex.getDevicePtr(),
							  ExTop.getDevicePtr(),
							  coeffDevice.data(),
							  sizeX, sizeY);
	bottomUpdater.setParams(grid->Ex.getDevicePtr(),
							  ExBottom.getDevicePtr(),
							  coeffDevice.data(),
							  sizeX, sizeY);
	std::cout << "Absorption boundary conditions initialized \n";
}
