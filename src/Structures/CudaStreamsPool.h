/*
 * CudaStreamsPool.h
 *
 *  Created on: 24 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef CUDASTREAMSPOOL_H_
#define CUDASTREAMSPOOL_H_

#include <thrust/system/cuda/execution_policy.h>
#include <vector>
#include <map>

// Пул потоков Cuda нужен для запуска ядер в нескольких потоках.
// Возвращает по требованию поток
// Если свободных потоков в пуле нет, то создает новый
// Класс является Singleton!!! http://cpp-reference.ru/patterns/creational-patterns/singleton/

class CudaStreamsPool {
private:
	CudaStreamsPool();
	CudaStreamsPool(const CudaStreamsPool&);
	CudaStreamsPool& operator= (CudaStreamsPool&);

	static CudaStreamsPool * instance;
	std::vector<cudaStream_t> freeStreams;
	std::vector<cudaStream_t> inUseStreams;

public:
	~CudaStreamsPool();

	static CudaStreamsPool* getInstance() {
		if( instance == nullptr ) {
			instance = new CudaStreamsPool;
		}
		return instance;
	}
	// Возвращает поток
	cudaStream_t* getStream();
	// Синхронизирует все потоки
	void syncAll();
	//Освобождает все потоки
	void releaseAll();
};

#endif /* CUDASTREAMSPOOL_H_ */
