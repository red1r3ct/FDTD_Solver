#include "ABCTM.h"

#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/system/cuda/execution_policy.h>
#include <iostream>


void ABCTM::apply() {
	thrust::counting_iterator<int> startY(0);
	thrust::counting_iterator<int> endY(grid->sizeY);
	thrust::counting_iterator<int> startX(0);
	thrust::counting_iterator<int> endX(grid->sizeX);
	thrust::for_each(startY, endY, leftUpdater);
	thrust::for_each(startY, endY, rightUpdater);
	thrust::for_each(startX, endX, bottomUpdater);
	thrust::for_each(startX, endX, topUpdater);
}
