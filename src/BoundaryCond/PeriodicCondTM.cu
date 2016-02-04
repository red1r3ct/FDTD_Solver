/*
 * PeriodicCond.cpp
 *
 *  Created on: 04 февр. 2016 г.
 *      Author: aleksandr
 */

#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>
#include <iostream>

#include "PeriodicCondTM.h"

PeriodicCondTM::PeriodicCondTM(GridTM* _grid) : EzLeft(_grid->sizeY*6, 0),
						  EzRight(_grid->sizeY*6, 0),
						  HxTemp(_grid->sizeX, 0),
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
	topBottomUpdater.setParams(grid->Ez.getDevicePtr(),
								grid->Hx.getDevicePtr(),
								grid->Hy.getDevicePtr(),
								HxTemp.getDevicePtr(),
								grid->epsilon.getDevicePtr(),
								grid->sigma.getDevicePtr(),
								grid->sizeX,
								grid->sizeY,
								grid->S);
	std::cout << "Periodic boundary conditions (top and bottom) initialized \n";
	std::cout << "Absorption boundary conditions (left and right) initialized \n";
}
__host__
void PeriodicCondTM::apply() {
	thrust::counting_iterator<int> startY(0);
	thrust::counting_iterator<int> endY(grid->sizeY);
	thrust::counting_iterator<int> startX(2);
	thrust::counting_iterator<int> endX(grid->sizeX-2);
	thrust::for_each(startY, endY, leftUpdater);
	thrust::for_each(startY, endY, rightUpdater);
	thrust::for_each(startX, endX, topBottomUpdater);
}

