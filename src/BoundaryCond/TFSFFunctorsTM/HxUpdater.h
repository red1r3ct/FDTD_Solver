/*
 * HxUpdater.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef HXUPDATER_H_
#define HXUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class HxUpdater {
public:
	__host__ __device__
	HxUpdater(d_ptr _Hx, d_ptr _Ez1D, int _sizeX,
			  int _sizeY, float _S, int _firstY, int _lastY) :
											Hx(_Hx), Ez1D(_Ez1D),
											sizeX(_sizeX), sizeY(_sizeY),
											S(_S), firstY(_firstY),
											lastY(_lastY) {};

	__host__ __device__
	HxUpdater(): sizeX(0), sizeY(0), S(0), firstY(0), lastY(0) {}

	void setParams(d_ptr _Hx, d_ptr _Ez1D, int _sizeX,
			int _sizeY, float _S , int _firstY, int _lastY) {
		Hx=_Hx;
		Ez1D=_Ez1D;
		sizeX=_sizeX;
		sizeY=_sizeY;
		S=_S;
		firstY = _firstY;
		lastY = _lastY;
	}

	__host__ __device__
	~HxUpdater() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Hx, Ez1D;
	int sizeX, sizeY, firstY, lastY;
	float S;
};

#endif /* HXUPDATER_H_ */
