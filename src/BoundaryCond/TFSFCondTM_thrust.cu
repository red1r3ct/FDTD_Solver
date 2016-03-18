#include "TFSFCondTM.h"

#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>
#include <iostream>


void TFSFCondTM::updateEz() {
	thrust::counting_iterator<int> start(firstY);
	thrust::counting_iterator<int> end(lastY+1);
	thrust::for_each(start , end , EzUpdater);
}

void TFSFCondTM::updateHx() {
	thrust::counting_iterator<int> start(firstX);
	thrust::counting_iterator<int> end(lastX+1);
	thrust::for_each(start , end , HxUpdater);
}

void TFSFCondTM::updateHy() {
	thrust::counting_iterator<int> start(firstY);
	thrust::counting_iterator<int> end(lastY+1);
	thrust::for_each(start , end , HyUpdater);
}
