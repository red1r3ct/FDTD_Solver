/*
 * EyUpdaterTE.h
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef EYUPDATERTE_H_
#define EYUPDATERTE_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class EyUpdaterTE {
public:
	__host__ __device__
	EyUpdaterTE(d_ptr _Ey, d_ptr _Hz, d_ptr _epsilon, int _sizeX, int _sizeY, float _S ) : Ey(_Ey), Hz(_Hz),
			epsilon(_epsilon), sizeX(_sizeX), sizeY(_sizeY), S(_S) {};

	__host__ __device__
	EyUpdaterTE(): sizeX(0), sizeY(0), S(0) {}

	void setParams(d_ptr _Ey, d_ptr _Hz, d_ptr _epsilon, int _sizeX, int _sizeY, float _S ) {
		Ey=_Ey;
		Hz=_Hz;
		epsilon=_epsilon;
		sizeX=_sizeX;
		sizeY=_sizeY;
		S=_S;
	}

	__host__ __device__
	~EyUpdaterTE() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Ey, Hz, epsilon;
	int sizeX, sizeY;
	float S;
};
#endif /* EYUPDATERTE_H_ */
