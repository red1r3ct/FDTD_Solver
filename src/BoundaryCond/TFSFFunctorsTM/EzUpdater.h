/*
 * EzUpdater.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef EZUPDATER_H_
#define EZUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class EzUpdater {
public:
	__host__ __device__
	EzUpdater(d_ptr _Ez, d_ptr _Hy1D, int _sizeX, int _sizeY, float _S, int _firstX, int _lastX) : Ez(_Ez), Hy1D(_Hy1D),
			sizeX(_sizeX), sizeY(_sizeY), S(_S), firstX(_firstX), lastX(_lastX) {};

	__host__ __device__
	EzUpdater(): sizeX(0), sizeY(0), S(0), firstX(0), lastX(0) {}

	void setParams(d_ptr _Ez, d_ptr _Hy1D, int _sizeX, int _sizeY, float _S , int _firstX, int _lastX) {
		Ez=_Ez;
		Hy1D=_Hy1D;
		Hy1D=_Hy1D;
		sizeX=_sizeX;
		sizeY=_sizeY;
		S=_S;
		firstX = _firstX;
		lastX = _lastX;
	}

	__host__ __device__
	~EzUpdater() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Ez, Hy1D;
	int sizeX, sizeY, firstX, lastX;
	float S;
};

#endif /* EZUPDATER_H_ */
