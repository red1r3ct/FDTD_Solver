/*
 * EzTopUpdater.h
 *
 *  Created on: 23 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef EZTOPUPDATER_H_
#define EZTOPUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class EzTopUpdater {
public:
	__host__ __device__
	EzTopUpdater(d_ptr _Ez, d_ptr _EzTop, d_ptr _coeff,
					std::size_t _sizeX, std::size_t _sizeY) : Ez(_Ez), EzTop(_EzTop),
															coeff(_coeff), sizeX(_sizeX),
															sizeY(_sizeY) {};
	__host__ __device__
	EzTopUpdater(): sizeX(0), sizeY(0) {};

	__host__ __device__
	~EzTopUpdater() {};
	__device__
	void operator() (const int indx);

	void setParams(d_ptr _Ez, d_ptr _EzTop, d_ptr _coeff,
					int _sizeX, int _sizeY)
	{
		Ez = _Ez;
		EzTop = _EzTop;
		coeff = _coeff;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}

private:
	d_ptr Ez, EzTop;
	d_ptr coeff;
	int sizeX, sizeY;
};

#endif /* EZTOPUPDATER_H_ */
