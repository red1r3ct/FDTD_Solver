/*
 * UpdaterHz1D.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef UPDATERHZ1D_H_
#define UPDATERHZ1D_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class UpdaterHz1D {
public:
	__host__ __device__
	UpdaterHz1D(d_ptr _Ey, d_ptr _Hz, d_ptr _Chzh, d_ptr _Chze, int _size) : Ey(_Ey), Hz(_Hz),
																			 Chzh(_Chzh), Chze(_Chze),
																			 size(_size) {};
	__host__ __device__
	UpdaterHz1D() : size(0) {};

	__host__ __device__
	void setParams(d_ptr _Ey, d_ptr _Hz, d_ptr _Chzh, d_ptr _Chze, int _size) {
		Ey = _Ey;
		Hz = _Hz;
		Chzh = _Chzh;
		Chze = _Chze;
		size = _size;
	}
	__device__
	void operator() (const int indx);

	d_ptr Ey, Hz, Chzh, Chze;
	int size;
};
#endif /* UPDATERHZ1D_H_ */
