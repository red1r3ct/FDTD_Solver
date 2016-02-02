/*
 * HyUpdater.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef HYUPDATER_H_
#define HYUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class HyUpdater {
public:
	__host__ __device__
	HyUpdater(d_ptr _Hy, d_ptr _Ez1D, int _sizeX,
			  int _sizeY, float _S, int _firstX, int _lastX) :
											Hy(_Hy), Ez1D(_Ez1D),
											sizeX(_sizeX), sizeY(_sizeY),
											S(_S), firstX(_firstX),
											lastX(_lastX) {};

	__host__ __device__
	HyUpdater(): sizeX(0), sizeY(0), S(0), firstX(0), lastX(0) {}

	void setParams(d_ptr _Hy, d_ptr _Ez1D, int _sizeX,
			int _sizeY, float _S , int _firstX, int _lastX) {
		Hy=_Hy;
		Ez1D=_Ez1D;
		sizeX=_sizeX;
		sizeY=_sizeY;
		S=_S;
		firstX = _firstX;
		lastX = _lastX;
	}

	__host__ __device__
	~HyUpdater() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Hy, Ez1D;
	int sizeX, sizeY, firstX, lastX;
	float S;
};

#endif /* HYUPDATER_H_ */
