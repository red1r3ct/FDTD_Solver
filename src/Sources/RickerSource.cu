#include "RickerSource.h"

#include <iostream>
#include <thrust/device_ptr.h>
#include "thrust/for_each.h"
#include <thrust/iterator/counting_iterator.h>
#include "math_constants.h"
#include "math.h"

#include "RickerSource.h"

#define Pi CUDART_PI_F

void RickerSource::updateField(d_ptr _field, const int time) {
	updater.field = _field;
	thrust::counting_iterator<int> start(time);
	thrust::counting_iterator<int> end(time+1);
	thrust::for_each(start , end , updater);
}

__device__
void RickerUpdater::operator()(const int time) {
	float temp = powf(Pi*(freq*time-M),2);
	field[0] = amp*(1-2*temp)*expf(-1.0f*temp);
}
