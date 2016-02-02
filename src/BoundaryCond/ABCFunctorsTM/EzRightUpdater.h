/*
 * EzRightUpdater.h
 *
 *  Created on: 23 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef EZRIGHTUPDATER_H_
#define EZRIGHTUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class EzRightUpdater {
public:
	__host__ __device__
	EzRightUpdater(d_ptr _Ez, d_ptr _EzRight, d_ptr _coeff,
					std::size_t _sizeX, std::size_t _sizeY) : Ez(_Ez), EzRight(_EzRight),
															coeff(_coeff), sizeX(_sizeX),
															sizeY(_sizeY) {};
	__host__ __device__
	EzRightUpdater(): sizeX(0), sizeY(0) {};

	__host__ __device__
	~EzRightUpdater() {};
	__device__
	void operator() (const int indx);

	void setParams(d_ptr _Ez, d_ptr _EzRight, d_ptr _coeff,
					int _sizeX, int _sizeY)
	{
		Ez = _Ez;
		EzRight = _EzRight;
		coeff = _coeff;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}

private:
	d_ptr Ez, EzRight;
	d_ptr coeff;
	int sizeX, sizeY;
};
#endif /* EZRIGHTUPDATER_H_ */
