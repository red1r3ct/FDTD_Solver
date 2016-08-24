/*
 * IntensityOutputRoutine.cpp
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#include "IntensityOutputRoutineTM.h"

#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>



void IntensityOutputRoutineTM::collectDataGPU() {
	thrust::counting_iterator<int> start(0);
	thrust::counting_iterator<int> end(intensityGPU.getSize());
	thrust::for_each(start , end , updaterIntensity);
}
