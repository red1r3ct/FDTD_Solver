/*
 * UpdaterEy1D.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef UPDATEREY1D_H_
#define UPDATEREY1D_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class UpdaterEy1D {
public:
	__host__ __device__
	UpdaterEy1D(d_ptr _Ey, d_ptr _Hz, d_ptr _Ceye, d_ptr _Ceyh, int _size) : Ey(_Ey), Hz(_Hz),
																			 Ceye(_Ceye), Ceyh(_Ceyh),
																			 size(_size) {};
	__host__ __device__
	UpdaterEy1D() : size(0) {};

	__host__ __device__
	void setParams(d_ptr _Ey, d_ptr _Hz, d_ptr _Ceye, d_ptr _Ceyh, int _size) {
		Ey = _Ey;
		Hz = _Hz;
		Ceye = _Ceye;
		Ceyh = _Ceyh;
		size = _size;
	}
	__device__
	void operator() (const int indx);

	d_ptr Ey, Hz, Ceye, Ceyh;
	int size;
};
#endif /* UPDATEREY1D_H_ */
