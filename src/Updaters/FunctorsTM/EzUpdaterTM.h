/*
 * EzUpdaterTM.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef EZUPDATERTM_H_
#define EZUPDATERTM_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class EzUpdaterTM {
public:
	__host__ __device__
	EzUpdaterTM(d_ptr _Ez, d_ptr _Hx, d_ptr _Hy, d_ptr _epsilon, d_ptr _sigma, d_ptr _excluded, int _sizeX, int _sizeY, float _S ) : Ez(_Ez), Hx(_Hx), Hy(_Hy),
			epsilon(_epsilon), sigma(_sigma), excluded(_excluded), sizeX(_sizeX), sizeY(_sizeY), S(_S) {};

	__host__ __device__
	EzUpdaterTM(): sizeX(0), sizeY(0), S(0) {}

	void setParams(d_ptr _Ez, d_ptr _Hx, d_ptr _Hy, d_ptr _epsilon, d_ptr _sigma, d_ptr _excluded, int _sizeX, int _sizeY, float _S ) {
		Ez=_Ez;
		Hx=_Hx;
		Hy=_Hy;
		epsilon=_epsilon;
		sigma = _sigma;
		excluded = _excluded;
		sizeX=_sizeX;
		sizeY=_sizeY;
		S=_S;
	}

	__host__ __device__
	~EzUpdaterTM() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Ez, Hx, Hy, epsilon, sigma, excluded;
	int sizeX, sizeY;
	float S;
};

#endif /* EZUPDATERTM_H_ */
