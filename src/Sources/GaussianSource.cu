/*
 * GaussianSorce.cpp
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#include "GaussianSource.h"

void GaussianSource::updateField(d_ptr _field, const int time) {
	updater.field = _field;
	thrust::counting_iterator<int> start(time);
	thrust::counting_iterator<int> end(time+1);
	thrust::for_each(start , end , updater);
}

__device__
void GaussianUpdater::operator()(const int time) {
	//float Pi = 3.1415926535;
	//field[0] =
}
