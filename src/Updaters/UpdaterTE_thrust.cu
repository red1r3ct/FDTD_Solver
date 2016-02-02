#include "UpdaterTE.h"

#include "thrust/for_each.h"
#include <thrust/iterator/counting_iterator.h>
#include <cmath>
#include <iostream>


__host__
void UpdaterTE::updateE() {
	thrust::counting_iterator<int> start(0);
	thrust::counting_iterator<int> end(grid->sizeY*(grid->sizeX));
	thrust::for_each(start , end , ExUpdater);
	thrust::for_each(start , end , EyUpdater);
}
__host__
void UpdaterTE::updateH() {
	thrust::counting_iterator<int> start(0);
	thrust::counting_iterator<int> end((grid->sizeY)*(grid->sizeX));
	thrust::for_each(start, end, HzUpdater);
}
