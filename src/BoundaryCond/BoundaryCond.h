/*
 * BoundaryCond.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef BOUNDARYCOND_H_
#define BOUNDARYCOND_H_

/*
 * Базовый класс для граничных условий.
 */

class BoundaryCond {
public:
	BoundaryCond() {};
	virtual ~BoundaryCond() {};

	virtual void apply() = 0;

};

#endif /* BOUNDARYCOND_H_ */
