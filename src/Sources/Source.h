/*
 * Source.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef SOURCE_H_
#define SOURCE_H_

#include <thrust/device_ptr.h>

typedef thrust::device_ptr<float> d_ptr;

/*
 * Базовый класс для источников. Гарантируется вызов на
 * каждой иттерации метода updateField
 */

class Source {
public:
	Source() {};
	virtual ~Source() {};
	virtual void updateField(d_ptr _field, const int time) = 0;

	virtual int getPositionX() = 0;
	virtual int getPositionY() = 0;
};

#endif /* SOURCE_H_ */
