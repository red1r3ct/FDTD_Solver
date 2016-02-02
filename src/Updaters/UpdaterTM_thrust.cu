#include "UpdaterTM.h"

#include "thrust/for_each.h"
#include <thrust/iterator/counting_iterator.h>
#include <cmath>
#include <iostream>


__host__
void UpdaterTM::updateE() {
	thrust::counting_iterator<int> start(0);
	thrust::counting_iterator<int> end(grid->sizeY*(grid->sizeX) - 1);
	thrust::for_each(start , end , EzUpdater);
}
__host__
void UpdaterTM::updateH() {
	thrust::counting_iterator<int> startHxHy(0);
	thrust::counting_iterator<int> endHxHy(grid->sizeY*grid->sizeX - 1);
	thrust::for_each(startHxHy , endHxHy , HxHyUpdater);
}
