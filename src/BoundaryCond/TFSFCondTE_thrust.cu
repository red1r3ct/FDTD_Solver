#include "TFSFCondTE.h"

#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>
#include <iostream>


void TFSFCondTE::updateHz() {
	thrust::counting_iterator<int> start(firstY);
	thrust::counting_iterator<int> end(lastY);
	thrust::for_each(start , end , HzUpdater);
}

void TFSFCondTE::updateEx() {
	thrust::counting_iterator<int> start(firstX);
	thrust::counting_iterator<int> end(lastX);
	thrust::for_each(start , end , ExUpdater);
}

void TFSFCondTE::updateEy() {
	thrust::counting_iterator<int> start(firstY);
	thrust::counting_iterator<int> end(lastY);
	thrust::for_each(start , end , EyUpdater);
}
