/*
 * EyRightUpdater.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef EYRIGHTUPDATER_H_
#define EYRIGHTUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class EyRightUpdater {
public:
	__host__ __device__
	EyRightUpdater(d_ptr _Ey, d_ptr _EyRight, d_ptr _coeff,
					std::size_t _sizeX, std::size_t _sizeY) : Ey(_Ey), EyRight(_EyRight),
															coeff(_coeff), sizeX(_sizeX),
															sizeY(_sizeY) {};
	__host__ __device__
	EyRightUpdater(): sizeX(0), sizeY(0) {};

	__host__ __device__
	~EyRightUpdater() {};
	__device__
	void operator() (const int indx);

	void setParams(d_ptr _Ey, d_ptr _EyRight, d_ptr _coeff,
					int _sizeX, int _sizeY)
	{
		Ey = _Ey;
		EyRight = _EyRight;
		coeff = _coeff;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}

private:
	d_ptr Ey, EyRight;
	d_ptr coeff;
	int sizeX, sizeY;
};
#endif /* EYRIGHTUPDATER_H_ */
