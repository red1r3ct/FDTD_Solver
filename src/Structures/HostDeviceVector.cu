/*
 * HostDeviceVector.cpp
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#include "HostDeviceVector.h"

#include <thrust/fill.h>
#include <thrust/copy.h>
#include <iostream>

HostDeviceVector::HostDeviceVector() {}

HostDeviceVector::~HostDeviceVector() {}

HostDeviceVector::HostDeviceVector(std::size_t size, float placeholder) {
	deviceVector.resize(size);
	thrust::fill(deviceVector.begin(), deviceVector.end(), placeholder);
	hostVector.resize(size);
	thrust::fill(hostVector.begin(), hostVector.end(), placeholder);
}

void HostDeviceVector::resize(std::size_t size, float placeholder) {
	deviceVector.resize(size);
	thrust::fill(deviceVector.begin(), deviceVector.end(), placeholder);
	hostVector.resize(size);
	thrust::fill(hostVector.begin(), hostVector.end(), placeholder);
}

void HostDeviceVector::fill(float placeholder) {
	thrust::fill(deviceVector.begin(), deviceVector.end(), placeholder);
	thrust::fill(hostVector.begin(), hostVector.end(), placeholder);
}

void HostDeviceVector::GPUtoCPU() {
	thrust::copy(deviceVector.begin(), deviceVector.end(), hostVector.begin());
}

void HostDeviceVector::CPUtoGPU() {
	thrust::copy(hostVector.begin(), hostVector.end(), deviceVector.begin());
}

thrust::device_ptr<float> HostDeviceVector::getDevicePtr() {
	return deviceVector.data();
}

float* HostDeviceVector::getHostPtr() {
	return &hostVector[0];
}

std::size_t HostDeviceVector::getSize() const {
	return hostVector.size();
}

float& HostDeviceVector::operator [] (std::size_t index) {
	return hostVector[index];
}
