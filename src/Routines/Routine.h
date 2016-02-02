/*
 * Routine.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef ROUTINE_H_
#define ROUTINE_H_

#include "../Grids/GridTM.h"

/*
 * Базовый класс для дополнительных вычислений.
 * Гарантирует что метод compute() вызывается на
 * каждой иттерации
 */

class Routine {
public:
	Routine() {};
	virtual ~Routine() {};

	virtual void compute(int time) = 0;
};

#endif /* ROUTINE_H_ */
