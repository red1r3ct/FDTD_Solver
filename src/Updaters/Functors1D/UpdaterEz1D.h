/*
 * UpdaterEz1D.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef UPDATEREZ1D_H_
#define UPDATEREZ1D_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class UpdaterEz1D {
public:
	__host__ __device__
	UpdaterEz1D(d_ptr _Ez, d_ptr _Hy, d_ptr _Ceze, d_ptr _Cezh, int _size) : Ez(_Ez), Hy(_Hy),
																			 Ceze(_Ceze), Cezh(_Cezh),
																			 size(_size) {};
	__host__ __device__
	UpdaterEz1D() : size(0) {};

	__host__ __device__
	void setParams(d_ptr _Ez, d_ptr _Hy, d_ptr _Ceze, d_ptr _Cezh, int _size) {
		Ez = _Ez;
		Hy = _Hy;
		Ceze = _Ceze;
		Cezh = _Cezh;
		size = _size;
	}
	__device__
	void operator() (const int indx);

	d_ptr Ez, Hy, Ceze, Cezh;
	int size;
};

#endif /* UPDATEREZ1D_H_ */
