/*
 * UpdaterHy1D.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef UPDATERHY1D_H_
#define UPDATERHY1D_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class UpdaterHy1D {
public:
	__host__ __device__
	UpdaterHy1D(d_ptr _Ez, d_ptr _Hy, d_ptr _Chyh, d_ptr _Chye, int _size) : Ez(_Ez), Hy(_Hy),
																			 Chyh(_Chyh), Chye(_Chye),
																			 size(_size) {};
	__host__ __device__
	UpdaterHy1D() : size(0) {};

	__host__ __device__
	void setParams(d_ptr _Ez, d_ptr _Hy, d_ptr _Chyh, d_ptr _Chye, int _size) {
		Ez = _Ez;
		Hy = _Hy;
		Chyh = _Chyh;
		Chye = _Chye;
		size = _size;
	}
	__device__
	void operator() (const int indx);

	d_ptr Ez, Hy, Chyh, Chye;
	int size;
};
#endif /* UPDATERHY1D_H_ */
