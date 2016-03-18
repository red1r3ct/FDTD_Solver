#include "Updater1DTM.h"

#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>
#include <iostream>


void Updater1DTM::updateEz() {
	thrust::counting_iterator<int> start(1);
	thrust::counting_iterator<int> end(grid->size-1);
	thrust::for_each(start , end , updaterEz);
}

void Updater1DTM::updateHy() {
	thrust::counting_iterator<int> start(0);
	thrust::counting_iterator<int> end(grid->size-1);
	thrust::for_each(start , end , updaterHy);
}
