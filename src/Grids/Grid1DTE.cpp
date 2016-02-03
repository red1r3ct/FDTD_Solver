/*
 * Grid1DTE.cpp
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#include "Grid1DTE.h"

#include <cmath>

Grid1DTE::Grid1DTE(std::size_t _size, float _S, std::size_t _nLoss, float _maxLoss) : size(_size),
											time(0), nLoss(_nLoss), S(_S), Hz(_size-1, 0), Ey(_size, 0),
											Chzh(_size-1, 0), Chze(_size-1, 0), Ceye(_size, 0),
											Ceyh(_size,0), maxLoss(_maxLoss)
{
	float imp0 = 377.0;
	for(int i = 0; i < size - 1; i++) {
		if (i < size - 1 - nLoss) {
			Ceye[i] = 1.0;
			Ceyh[i] = S*imp0;
			Chzh[i] = 1.0;
			Chze[i] = S/imp0;
		} else {
			float depthInLayer = depthInLayer + 0.5;
			float lossFactor = maxLoss* pow((float)(depthInLayer) / (float)(nLoss), 2);
			Ceye[i] = (1.0 - lossFactor) / (1.0 + lossFactor);
			Ceyh[i] = S * imp0 / (1.0 + lossFactor);
			depthInLayer += 0.5;
			lossFactor = maxLoss * pow((float)(depthInLayer) / (float)(nLoss), 2);
			Chzh[i] = (1.0 - lossFactor) / (1.0 + lossFactor);
			Chze[i] = S / imp0 / (1.0 + lossFactor);
		}
	}
	Ceye.CPUtoGPU();
	Ceyh.CPUtoGPU();
	Chzh.CPUtoGPU();
	Chze.CPUtoGPU();
}
