/*
 * HostDeviceVector.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef HOSTDEVICEVECTOR_H_
#define HOSTDEVICEVECTOR_H_

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

/*
 * Основной контейнер для данных. Позволяет синхронизировать данные
 * между GPU b CPU. Позволяет получать прямые указатели на данные.
 */

class HostDeviceVector {
public:
	HostDeviceVector();
	HostDeviceVector(std::size_t size, float placeHolder);
	~HostDeviceVector();

	// Синхронизирует данные с GPU на CPU
	void GPUtoCPU();
	// Синхронизирует данные с CPU на GPU
	void CPUtoGPU();
	// Преобразует в тип указателя на вектор GPU
	thrust::device_ptr<float> getDevicePtr();
	// Преобразует в тип указвтеля на вектор CPU
	float* getHostPtr();
	// Возвращает размер вектора на CPU
	std::size_t getSize() const;
	// Перегрузка [ ] для доступа к CPU вектору
	float& operator[] (std::size_t index);

private:
	thrust::device_vector<float> deviceVector;
	thrust::host_vector<float> hostVector;
};

#endif /* HOSTDEVICEVECTOR_H_ */
