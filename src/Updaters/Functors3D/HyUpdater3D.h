/*
 * HyUpdater3D.h
 *
 *  Created on: 06 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef HYUPDATER3D_H_
#define HYUPDATER3D_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class HyUpdater3D {
public:
	__host__ __device__
	HyUpdater3D(d_ptr _Hy, d_ptr _Ex, d_ptr _Ez, d_ptr _epsilon, int _sizeX, int _sizeY, int _sizeZ, float _S )
														: Hy(_Hy), Ex(_Ex), Ez(_Ez),
														  epsilon(_epsilon), sizeX(_sizeX),
														  sizeY(_sizeY), sizeZ(_sizeZ), S(_S) {};

	__host__ __device__
	HyUpdater3D(): sizeX(0), sizeY(0), sizeZ(0), S(0) {}

	void setParams(d_ptr _Hy, d_ptr _Ex, d_ptr _Ez, d_ptr _epsilon, int _sizeX, int _sizeY, int _sizeZ, float _S ) {
		Hy=_Hy;
		Ex=_Ex;
		Ez=_Ez;
		epsilon=_epsilon;
		sizeX=_sizeX;
		sizeY=_sizeY;
		sizeZ=_sizeZ;
		S=_S;
	}

	__host__ __device__
	~HyUpdater3D() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Hy, Ex, Ez, epsilon;
	int sizeX, sizeY, sizeZ;
	float S;
};

#endif /* HYUPDATER3D_H_ */
