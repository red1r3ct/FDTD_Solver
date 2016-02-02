/*
 * EzBottomUpdater.h
 *
 *  Created on: 23 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef EZBOTTOMUPDATER_H_
#define EZBOTTOMUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class EzBottomUpdater {
public:
	__host__ __device__
	EzBottomUpdater(d_ptr _Ez, d_ptr _EzBottom, d_ptr _coeff,
					std::size_t _sizeX, std::size_t _sizeY) : Ez(_Ez), EzBottom(_EzBottom),
															coeff(_coeff), sizeX(_sizeX),
															sizeY(_sizeY) {};
	__host__ __device__
	EzBottomUpdater(): sizeX(0), sizeY(0) {};

	__host__ __device__
	~EzBottomUpdater() {};
	__device__
	void operator() (const int indx);

	void setParams(d_ptr _Ez, d_ptr _EzBottom, d_ptr _coeff,
					int _sizeX, int _sizeY)
	{
		Ez = _Ez;
		EzBottom = _EzBottom;
		coeff = _coeff;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}
private:
	d_ptr Ez, EzBottom;
	d_ptr coeff;
	int sizeX, sizeY;
};

#endif /* EZBOTTOMUPDATER_H_ */
