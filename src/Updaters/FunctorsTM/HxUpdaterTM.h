/*
 * HxUpdaterTM.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef HXUPDATERTM_H_
#define HXUPDATERTM_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class HxUpdaterTM {
public:
	__host__
	HxUpdaterTM(d_ptr _Ez, d_ptr _Hx, d_ptr _Hy, d_ptr _epsilon, int _sizeX, int _sizeY, float _S ) : Ez(_Ez), Hx(_Hx), Hy(_Hy),
			epsilon(_epsilon), sizeX(_sizeX), sizeY(_sizeY), S(_S) {};
	__host__
	~HxUpdaterTM() {};

	__host__
	HxUpdaterTM(): sizeX(0), sizeY(0), S(0) {}

	void setParams(d_ptr _Ez, d_ptr _Hx, d_ptr _Hy, d_ptr _epsilon, int _sizeX, int _sizeY, float _S ) {
		Ez=_Ez;
		Hx=_Hx;
		Hy=_Hy;
		epsilon=_epsilon;
		sizeX=_sizeX;
		sizeY=_sizeY;
		S=_S;
	}

	__host__ __device__
	void operator() (const int indx);

	d_ptr Ez, Hx, Hy, epsilon;
	int sizeX, sizeY;
	float S;
};

#endif /* HXUPDATERTM_H_ */
