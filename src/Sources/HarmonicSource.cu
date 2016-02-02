/*
 * HarmonicSource.cpp
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#include <cuda.h>
#include <cuda_runtime_api.h>
#include <iostream>
#include <thrust/device_ptr.h>
#include "thrust/for_each.h"
#include <thrust/iterator/counting_iterator.h>

#include "HarmonicSource.h"

void HarmonicSource::updateField(d_ptr _field, const int time) {
	updater.field = _field;
	thrust::counting_iterator<int> start(time);
	thrust::counting_iterator<int> end(time+1);
	thrust::for_each(start , end , updater);
}

__device__
void HarmonicUpdater::operator()(const int time) {
	field[0] = amp*sinf(freq*(float)(time));
}
