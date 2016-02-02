/*
 * EyUpdater.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef EYUPDATER_H_
#define EYUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class EyUpdater {
public:
	__host__ __device__
	EyUpdater(d_ptr _Ey, d_ptr _Hz1D, int _sizeX,
			  int _sizeY, float _S, int _firstX, int _lastX) :
											Ey(_Ey), Hz1D(_Hz1D),
											sizeX(_sizeX), sizeY(_sizeY),
											S(_S), firstX(_firstX),
											lastX(_lastX) {};

	__host__ __device__
	EyUpdater(): sizeX(0), sizeY(0), S(0), firstX(0), lastX(0) {}

	void setParams(d_ptr _Ey, d_ptr _Hz1D, int _sizeX,
			int _sizeY, float _S , int _firstX, int _lastX) {
		Ey=_Ey;
		Hz1D=_Hz1D;
		sizeX=_sizeX;
		sizeY=_sizeY;
		S=_S;
		firstX = _firstX;
		lastX = _lastX;
	}

	__host__ __device__
	~EyUpdater() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Ey, Hz1D;
	int sizeX, sizeY, firstX, lastX;
	float S;
};
#endif /* EYUPDATER_H_ */
