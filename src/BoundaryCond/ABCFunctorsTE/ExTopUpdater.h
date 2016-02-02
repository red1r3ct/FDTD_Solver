/*
 * ExTopUpdater.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef EXTOPUPDATER_H_
#define EXTOPUPDATER_H_
#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class ExTopUpdater {
public:
	__host__ __device__
	ExTopUpdater(d_ptr _Ex, d_ptr _ExTop, d_ptr _coeff,
					std::size_t _sizeX, std::size_t _sizeY) : Ex(_Ex), ExTop(_ExTop),
															coeff(_coeff), sizeX(_sizeX),
															sizeY(_sizeY) {};
	__host__ __device__
	ExTopUpdater() : sizeX(0), sizeY(0) {};

	__host__ __device__
	~ExTopUpdater() {};
	__device__
	void operator() (const int indx);

	void setParams(d_ptr _Ex, d_ptr _ExTop, d_ptr _coeff,
					int _sizeX, int _sizeY)
	{
		Ex = _Ex;
		ExTop = _ExTop;
		coeff = _coeff;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}

private:
	d_ptr Ex, ExTop;
	d_ptr coeff;
	int sizeX, sizeY;
};
#endif /* EXTOPUPDATER_H_ */
