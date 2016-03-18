#include "Updater1DTE.h"
#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>
#include <iostream>


void Updater1DTE::updateEy() {
	thrust::counting_iterator<int> start(0);
	thrust::counting_iterator<int> end(grid->size-1);
	thrust::for_each(start , end , updaterEy);
}

void Updater1DTE::updateHz() {
	thrust::counting_iterator<int> start(0);
	thrust::counting_iterator<int> end(grid->size-1);
	thrust::for_each(start , end , updaterHz);
}
