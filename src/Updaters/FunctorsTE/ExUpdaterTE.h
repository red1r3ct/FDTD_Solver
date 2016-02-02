/*
 * ExUpdaterTE.h
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef EXUPDATERTE_H_
#define EXUPDATERTE_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class ExUpdaterTE {
public:
	__host__ __device__
	ExUpdaterTE(d_ptr _Ex, d_ptr _Hz, d_ptr _epsilon, int _sizeX, int _sizeY, float _S ) : Ex(_Ex), Hz(_Hz),
			epsilon(_epsilon), sizeX(_sizeX), sizeY(_sizeY), S(_S) {};

	__host__ __device__
	ExUpdaterTE(): sizeX(0), sizeY(0), S(0) {}

	void setParams(d_ptr _Ex, d_ptr _Hz, d_ptr _epsilon, int _sizeX, int _sizeY, float _S ) {
		Ex=_Ex;
		Hz=_Hz;
		epsilon=_epsilon;
		sizeX=_sizeX;
		sizeY=_sizeY;
		S=_S;
	}

	__host__ __device__
	~ExUpdaterTE() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Ex, Hz, epsilon;
	int sizeX, sizeY;
	float S;
};

#endif /* EXUPDATERTE_H_ */
