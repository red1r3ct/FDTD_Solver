/*
 * Grid1D.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#include "Grid1DTM.h"

#include <cmath>

Grid1DTM::Grid1DTM(std::size_t _size, float _S, std::size_t _nLoss, float _maxLoss) : size(_size),
											time(0), nLoss(_nLoss), S(_S), Hy(_size-1, 0), Ez(_size, 0),
											Chyh(_size, 0), Chye(_size, 0), Ceze(_size, 0),
											Cezh(_size,0), maxLoss(_maxLoss)
{
	float imp0 = 377.0;
	for(int i = 0; i < size - 1; i++) {
		if (i < size - 1 - nLoss) {
			Ceze[i] = 1.0;
			Cezh[i] = S*imp0;
			Chyh[i] = 1.0;
			Chye[i] = S/imp0;
		} else {
			float depthInLayer = i - (size - 1 - nLoss) + 0.5;
			float lossFactor = maxLoss* pow((float)(depthInLayer) / (float)(nLoss), 2);
			Ceze[i] = (1.0 - lossFactor) / (1.0 + lossFactor);
			Cezh[i] = S * imp0 / (1.0 + lossFactor);
			depthInLayer += 0.5;
			lossFactor = maxLoss * pow((float)(depthInLayer) / (float)(nLoss), 2);
			Chyh[i] = (1.0 - lossFactor) / (1.0 + lossFactor);
			Chye[i] = S / imp0 / (1.0 + lossFactor);
		}
	}
	Ceze.CPUtoGPU();
	Cezh.CPUtoGPU();
	Chyh.CPUtoGPU();
	Chye.CPUtoGPU();
}
