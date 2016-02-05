/*
 * TopBottomUpdaterTE.h
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef TOPBOTTOMUPDATERTE_H_
#define TOPBOTTOMUPDATERTE_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class TopBottomUpdaterTE {
public:
	__host__ __device__
	TopBottomUpdaterTE(d_ptr _Ex, d_ptr _Ey, d_ptr _Hz, d_ptr _epsilon,
					std::size_t _sizeX, std::size_t _sizeY, float _S) : Ex(_Ex), Ey(_Ey),
															Hz(_Hz), epsilon(_epsilon),
															sizeX(_sizeX), sizeY(_sizeY),
															S(_S) {};
	__host__ __device__
	TopBottomUpdaterTE(): sizeX(0), sizeY(0), S(0) {};

	__host__ __device__
	~TopBottomUpdaterTE() {};
	__device__
	void operator() (const int indx);

	void setParams(d_ptr _Ex, d_ptr _Ey, d_ptr _Hz, d_ptr _epsilon,
					std::size_t _sizeX, std::size_t _sizeY, float _S)
	{
		Ex = _Ex;
		Ey = _Ey;
		Hz = _Hz;
		epsilon = _epsilon;
		S = _S;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}
private:
	d_ptr Ex, Ey, Hz, epsilon;
	int sizeX, sizeY;
	float S;
};
#endif /* TOPBOTTOMUPDATERTE_H_ */
