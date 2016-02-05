#include "PeriodicCondTE.h"

#include <iostream>

PeriodicCondTE::PeriodicCondTE(GridTE* _grid) : EyLeft((_grid->sizeY-1)*6, 0),
						  EyRight((_grid->sizeY-1)*6, 0),
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
	topBottomUpdater.setParams(grid->Ex.getDevicePtr(),
								grid->Ey.getDevicePtr(),
								grid->Hz.getDevicePtr(),
								grid->epsilon.getDevicePtr(),
								grid->sizeX,
								grid->sizeY,
								grid->S);
	std::cout << "Periodic boundary conditions ( top and bottom ) initialized \n";
	std::cout << "Absorption boundary conditions ( left right ) initialized \n";
}

void PeriodicCondTE::apply() {
	thrust::counting_iterator<int> startY(0);
	thrust::counting_iterator<int> endY(grid->sizeY-1);
	thrust::counting_iterator<int> startX(2);
	thrust::counting_iterator<int> endX(grid->sizeX-3);
	thrust::for_each(startY, endY, leftUpdater);
	thrust::for_each(startY, endY, rightUpdater);
	thrust::for_each(startX, endX, topBottomUpdater);
}
