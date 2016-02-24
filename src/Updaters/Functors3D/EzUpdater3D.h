/*
 * EzUpdater3D.h
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef EZUPDATER3D_H_
#define EZUPDATER3D_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class EzUpdater3D {
public:
	__host__ __device__
	EzUpdater3D(d_ptr _Ez, d_ptr _Hx, d_ptr _Hy, d_ptr _epsilon, int _sizeX, int _sizeY, int _sizeZ, float _S )
														: Ez(_Ez), Hx(_Hx), Hy(_Hy),
														  epsilon(_epsilon), sizeX(_sizeX),
														  sizeY(_sizeY), sizeZ(_sizeZ), S(_S) {};

	__host__ __device__
	EzUpdater3D(): sizeX(0), sizeY(0), sizeZ(0), S(0) {}

	void setParams(d_ptr _Ez, d_ptr _Hx, d_ptr _Hy, d_ptr _epsilon, int _sizeX, int _sizeY, int _sizeZ, float _S) {
		Ez=_Ez;
		Hx=_Hx;
		Hy=_Hy;
		epsilon=_epsilon;
		sizeX=_sizeX;
		sizeY=_sizeY;
		sizeZ=_sizeZ;
		S=_S;
	}

	__host__ __device__
	~EzUpdater3D() {};

	__host__ __device__
	void operator() (const int indx);

	d_ptr Ez, Hx, Hy, epsilon;
	int sizeX, sizeY, sizeZ;
	float S;
};

#endif /* EZUPDATER3D_H_ */
