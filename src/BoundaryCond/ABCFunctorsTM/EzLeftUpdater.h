/*
 * EzLeftUpdater.h
 *
 *  Created on: 23 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef EZLEFTUPDATER_H_
#define EZLEFTUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class EzLeftUpdater {
public:
	__host__ __device__
	EzLeftUpdater(d_ptr _Ez, d_ptr _EzLeft, d_ptr _coeff,
					std::size_t _sizeX, std::size_t _sizeY) : Ez(_Ez), EzLeft(_EzLeft),
															coeff(_coeff), sizeX(_sizeX),
															sizeY(_sizeY) {};
	__host__ __device__
	EzLeftUpdater(): sizeX(0), sizeY(0) {};

	__host__ __device__
	~EzLeftUpdater() {};
	__device__
	void operator() (const int indx);

	void setParams(d_ptr _Ez, d_ptr _EzLeft, d_ptr _coeff,
					int _sizeX, int _sizeY)
	{
		Ez = _Ez;
		EzLeft = _EzLeft;
		coeff = _coeff;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}

private:
	d_ptr Ez, EzLeft;
	d_ptr coeff;
	int sizeX, sizeY;
};
#endif /* EZLEFTUPDATER_H_ */
