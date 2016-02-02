/*
 * ABC.cpp
 *
 *  Created on: 19 янв. 2016 г.
 *      Author: aleksandr
 */

#include "ABCTM.h"

#include <iostream>

ABCTM::ABCTM(GridTM* _grid) : EzLeft(_grid->sizeY*6, 0),
						  EzRight(_grid->sizeY*6, 0),
						  EzTop(_grid->sizeX*6, 0),
						  EzBottom(_grid->sizeX*6, 0),
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
	coeff2 = 4.0 * (temp1 + 1.0 / temp1) / temp2;
	int sizeX = grid->sizeX;
	int sizeY = grid->sizeY;
	std::vector<float> coeffHost(3, 0);
	coeffHost[0] = coeff0;
	coeffHost[1] = coeff1;
	coeffHost[2] = coeff2;
	coeffDevice = coeffHost;
	leftUpdater.setParams(grid->Ez.getDevicePtr(),
							EzLeft.getDevicePtr(),
							coeffDevice.data(),
							sizeX, sizeY);
	rightUpdater.setParams(grid->Ez.getDevicePtr(),
							  EzRight.getDevicePtr(),
							  coeffDevice.data(),
							  sizeX, sizeY);
	topUpdater.setParams(grid->Ez.getDevicePtr(),
							  EzTop.getDevicePtr(),
							  coeffDevice.data(),
							  sizeX, sizeY);
	bottomUpdater.setParams(grid->Ez.getDevicePtr(),
							  EzBottom.getDevicePtr(),
							  coeffDevice.data(),
							  sizeX, sizeY);
	std::cout << "Absorption boundary conditions initialized \n";
}
