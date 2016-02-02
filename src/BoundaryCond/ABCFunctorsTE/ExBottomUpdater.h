/*
 * ExBottomUpdater.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef EXBOTTOMUPDATER_H_
#define EXBOTTOMUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class ExBottomUpdater {
public:
	__host__ __device__
	ExBottomUpdater(d_ptr _Ex, d_ptr _ExBottom, d_ptr _coeff,
					std::size_t _sizeX, std::size_t _sizeY) : Ex(_Ex), ExBottom(_ExBottom),
															coeff(_coeff), sizeX(_sizeX),
															sizeY(_sizeY) {};
	__host__ __device__
	ExBottomUpdater() : sizeX(0), sizeY(0) {};

	__host__ __device__
	~ExBottomUpdater() {};
	__device__
	void operator() (const int indx);

	void setParams(d_ptr _Ex, d_ptr _ExBottom, d_ptr _coeff,
					int _sizeX, int _sizeY)
	{
		Ex = _Ex;
		ExBottom = _ExBottom;
		coeff = _coeff;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}
private:
	d_ptr Ex, ExBottom;
	d_ptr coeff;
	int sizeX, sizeY;
};
#endif /* EXBOTTOMUPDATER_H_ */
