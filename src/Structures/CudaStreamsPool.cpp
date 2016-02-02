/*
 * CudaStreamsPool.cpp
 *
 *  Created on: 24 янв. 2016 г.
 *      Author: aleksandr
 */

#include "CudaStreamsPool.h"

CudaStreamsPool *CudaStreamsPool::instance = nullptr;

CudaStreamsPool::CudaStreamsPool() {}

cudaStream_t* CudaStreamsPool::getStream() {
	if (freeStreams.size() == 0) {
		cudaStream_t newStream;
		cudaStreamCreate(&newStream);
		freeStreams.push_back(newStream);
	}
	cudaStream_t cudaStream = freeStreams.back();
	freeStreams.pop_back();
	inUseStreams.push_back(cudaStream);
	return &(inUseStreams.back());
}

CudaStreamsPool::~CudaStreamsPool() {
	for(auto stream: inUseStreams) {
		cudaStreamDestroy(stream);
	}
	for(auto stream: freeStreams) {
		cudaStreamDestroy(stream);
	}
}

void CudaStreamsPool::syncAll() {
	for(auto stream: inUseStreams) {
		cudaStreamSynchronize(stream);
	}
	releaseAll();
}

void CudaStreamsPool::releaseAll() {
	for(int i = 0; i < inUseStreams.size(); i++) {
		cudaStream_t stream = inUseStreams[i];
		freeStreams.push_back(stream);
	}
	inUseStreams.clear();
}
