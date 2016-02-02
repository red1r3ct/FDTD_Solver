/*
 * EyLeftUpdater.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef EYLEFTUPDATER_H_
#define EYLEFTUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class EyLeftUpdater {
public:
	__host__ __device__
	EyLeftUpdater(d_ptr _Ey, d_ptr _EyLeft, d_ptr _coeff,
					std::size_t _sizeX, std::size_t _sizeY) : Ey(_Ey), EyLeft(_EyLeft),
															coeff(_coeff), sizeX(_sizeX),
															sizeY(_sizeY) {};
	__host__ __device__
	EyLeftUpdater(): sizeX(0), sizeY(0) {};

	__host__ __device__
	~EyLeftUpdater() {};
	__device__
	void operator() (const int indx);

	void setParams(d_ptr _Ey, d_ptr _EyLeft, d_ptr _coeff,
					int _sizeX, int _sizeY)
	{
		Ey = _Ey;
		EyLeft = _EyLeft;
		coeff = _coeff;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}

private:
	d_ptr Ey, EyLeft;
	d_ptr coeff;
	int sizeX, sizeY;
};

#endif /* EYLEFTUPDATER_H_ */
