#include "Updater3D.h"

#include "thrust/for_each.h"
#include <thrust/iterator/counting_iterator.h>
#include <cmath>
#include <iostream>


__host__
void Updater3D::updateE() {
	thrust::counting_iterator<int> startEx(0);
	thrust::counting_iterator<int> endEx((sizeX-1)*(sizeY-1)*(sizeZ-1));
	thrust::counting_iterator<int> startEy(0);
	thrust::counting_iterator<int> endEy((sizeX-1)*(sizeY-1)*(sizeZ-1));
	thrust::counting_iterator<int> startEz(0);
	thrust::counting_iterator<int> endEz((sizeX-1)*(sizeY-1)*(sizeZ-1));

	thrust::for_each(startEx, endEx, ExUpdater);
	thrust::for_each(startEy, endEy, EyUpdater);
	thrust::for_each(startEz, endEz, EzUpdater);
}
__host__
void Updater3D::updateH() {
	thrust::counting_iterator<int> startHx(0);
	thrust::counting_iterator<int> endHx((sizeX)*(sizeY-1)*(sizeZ-1));
	thrust::counting_iterator<int> startHy(0);
	thrust::counting_iterator<int> endHy((sizeX-1)*(sizeY)*(sizeZ-1));
	thrust::counting_iterator<int> startHz(0);
	thrust::counting_iterator<int> endHz((sizeX-1)*(sizeY-1)*(sizeZ));

	thrust::for_each(startHx, endHx, HxUpdater);
	thrust::for_each(startHy, endHy, HyUpdater);
	thrust::for_each(startHz, endHz, HzUpdater);
}
