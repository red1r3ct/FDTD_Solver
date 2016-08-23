/*
 * IntensityOutputRoutine.cpp
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#include "IntensityOutputRoutineTM.h"

#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>


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



void IntensityOutputRoutineTM::collectDataGPU() {
	thrust::counting_iterator<int> start(0);
	thrust::counting_iterator<int> end(grid->size-1);
	thrust::for_each(start , end , updaterHy);
	#define Ez(M, N) grid->Ez[(M) * (grid->sizeY) + (N)]
	for(int m = 0; m < sizeX; m++ ) {
		for(int n = 0; n < sizeY; n++ ){
			intensity(m, n) += Ez(firstX + m*resolutionX, firstY + n*resolutionX)*Ez(firstX + m*resolutionX, firstY + n*resolutionX);
		}
	}
}
