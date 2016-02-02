/*
 * ExUpdater.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef EXUPDATER_H_
#define EXUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class ExUpdater {
public:
	__host__ __device__
	ExUpdater(d_ptr _Ex, d_ptr _Hz1D, int _sizeX,
			  int _sizeY, float _S, int _firstY, int _lastY) :
											Ex(_Ex), Hz1D(_Hz1D),
											sizeX(_sizeX), sizeY(_sizeY),
											S(_S), firstY(_firstY),
											lastY(_lastY) {};

	__host__ __device__
	ExUpdater(): sizeX(0), sizeY(0), S(0), firstY(0), lastY(0) {}

	void setParams(d_ptr _Ex, d_ptr _Hz1D, int _sizeX,
			int _sizeY, float _S , int _firstY, int _lastY) {
		Ex=_Ex;
		Hz1D=_Hz1D;
		sizeX=_sizeX;
		sizeY=_sizeY;
		S=_S;
		firstY = _firstY;
		lastY = _lastY;
	}

	__host__ __device__
	~ExUpdater() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Ex, Hz1D;
	int sizeX, sizeY, firstY, lastY;
	float S;
};

#endif /* EXUPDATER_H_ */
