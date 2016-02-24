/*
 * HxUpdater3D.h
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef HXUPDATER3D_H_
#define HXUPDATER3D_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class HxUpdater3D {
public:
	__host__ __device__
	HxUpdater3D(d_ptr _Hx, d_ptr _Ey, d_ptr _Ez, d_ptr _epsilon, int _sizeX, int _sizeY, int _sizeZ, float _S )
														: Hx(_Hx), Ey(_Ey), Ez(_Ez),
														  epsilon(_epsilon), sizeX(_sizeX),
														  sizeY(_sizeY), sizeZ(_sizeZ), S(_S) {};

	__host__ __device__
	HxUpdater3D(): sizeX(0), sizeY(0), sizeZ(0), S(0) {}

	void setParams(d_ptr _Hx, d_ptr _Ey, d_ptr _Ez, d_ptr _epsilon, int _sizeX, int _sizeY, int _sizeZ, float _S ) {
		Hx=_Hx;
		Ey=_Ey;
		Ez=_Ez;
		epsilon=_epsilon;
		sizeX=_sizeX;
		sizeY=_sizeY;
		sizeZ=_sizeZ;
		S=_S;
	}

	__host__ __device__
	~HxUpdater3D() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Hx, Ey, Ez, epsilon;
	int sizeX, sizeY, sizeZ;
	float S;
};


#endif /* HXUPDATER3D_H_ */
