/*
 * HzUpdater.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef HZUPDATER_H_
#define HZUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class HzUpdater {
public:
	__host__ __device__
	HzUpdater(d_ptr _Hz, d_ptr _Ey1D, int _sizeX,
			  int _sizeY, float _S, int _firstX, int _lastX) :
											Hz(_Hz), Ey1D(_Ey1D),
											sizeX(_sizeX), sizeY(_sizeY),
											S(_S), firstX(_firstX),
											lastX(_lastX) {};

	__host__ __device__
	HzUpdater(): sizeX(0), sizeY(0), S(0), firstX(0), lastX(0) {}

	void setParams(d_ptr _Hz, d_ptr _Ey1D, int _sizeX,
			int _sizeY, float _S , int _firstX, int _lastX) {
		Hz=_Hz;
		Ey1D=_Ey1D;
		sizeX=_sizeX;
		sizeY=_sizeY;
		S=_S;
		firstX = _firstX;
		lastX = _lastX;
	}

	__host__ __device__
	~HzUpdater() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Hz, Ey1D;
	int sizeX, sizeY, firstX, lastX;
	float S;
};

#endif /* HZUPDATER_H_ */
