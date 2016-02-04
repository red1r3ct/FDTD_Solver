/*
 * TopBottomUpdater.h
 *
 *  Created on: 04 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef TOPBOTTOMUPDATER_H_
#define TOPBOTTOMUPDATER_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class TopBottomUpdater {
public:
	__host__ __device__
	TopBottomUpdater(d_ptr _Ez, d_ptr _Hx, d_ptr _Hy, d_ptr _HxTemp, d_ptr _epsilon, d_ptr _sigma,
					std::size_t _sizeX, std::size_t _sizeY, float _S) : Ez(_Ez), Hx(_Hx), Hy(_Hy),
															HxTemp(_HxTemp), epsilon(_epsilon),
															sigma(_sigma), sizeX(_sizeX), sizeY(_sizeY),
															S(_S) {};
	__host__ __device__
	TopBottomUpdater(): sizeX(0), sizeY(0), S(0) {};

	__host__ __device__
	~TopBottomUpdater() {};
	__device__
	void operator() (const int indx);

	void setParams(d_ptr _Ez, d_ptr _Hx, d_ptr _Hy, d_ptr _HxTemp, d_ptr _epsilon, d_ptr _sigma,
					std::size_t _sizeX, std::size_t _sizeY, float _S)
	{
		Ez = _Ez;
		Hx = _Hx;
		Hy = _Hy;
		HxTemp = _HxTemp;
		epsilon = _epsilon;
		sigma = _sigma;
		S = _S;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}
private:
	d_ptr Ez, Hx, Hy, epsilon, sigma, HxTemp;
	int sizeX, sizeY;
	float S;
};

#endif /* TOPBOTTOMUPDATER_H_ */
