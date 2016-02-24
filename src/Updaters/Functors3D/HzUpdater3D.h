/*
 * HzUpdater3D.h
 *
 *  Created on: 06 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef HZUPDATER3D_H_
#define HZUPDATER3D_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class HzUpdater3D {
public:
	__host__ __device__
	HzUpdater3D(d_ptr _Hz, d_ptr _Ex, d_ptr _Ey, d_ptr _epsilon, int _sizeX, int _sizeY, int _sizeZ, float _S )
														: Hz(_Hz), Ex(_Ex), Ey(_Ey),
														  epsilon(_epsilon), sizeX(_sizeX),
														  sizeY(_sizeY), sizeZ(_sizeZ), S(_S) {};

	__host__ __device__
	HzUpdater3D(): sizeX(0), sizeY(0), sizeZ(0), S(0) {}

	void setParams(d_ptr _Hz, d_ptr _Ex, d_ptr _Ey, d_ptr _epsilon, int _sizeX, int _sizeY, int _sizeZ, float _S ) {
		Hz=_Hz;
		Ex=_Ex;
		Ey=_Ey;
		epsilon=_epsilon;
		sizeX=_sizeX;
		sizeY=_sizeY;
		sizeZ=_sizeZ;
		S=_S;
	}

	__host__ __device__
	~HzUpdater3D() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Hz, Ex, Ey, epsilon;
	int sizeX, sizeY, sizeZ;
	float S;
};

#endif /* HZUPDATER3D_H_ */
