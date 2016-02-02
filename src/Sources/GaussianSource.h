/*
 * GaussianSorce.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef GAUSSIANSORCE_H_
#define GAUSSIANSORCE_H_
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <iostream>

#include "Source.h"

/*
 * Функтор для обновления данных о поле в случае
 * гармонического источника.
 */

struct GaussianUpdater {
	GaussianUpdater(float _amp, float _freq, float _deltaFreq) : amp(_amp), freq(_freq), deltaFreq(_deltaFreq) {};

	float amp, freq, deltaFreq;
	d_ptr field;

	__device__
	void operator() (const int time);
};

/*
 * Класс реализующий фуекционал гармонического источника.
 * Необходимо разобрать с возможностью реализации использования этого класса
 * через интерфейс Source
 */

class GaussianSource: public Source {
public:
	GaussianSource(float _amp, float _freq, float _deltaFreq, int _positionX, int _positionY) : amp(_amp),
																			freq(_freq), deltaFreq(_deltaFreq),
																			positionX(_positionX),
																			positionY(_positionY),
																			updater(amp, freq, deltaFreq) {
		std::cout << "Harmonic source added: \n";
		std::cout << "\t amplitude : " << updater.amp << std::endl;
		std::cout << "\t frequency : " << updater.freq << std::endl;
		std::cout << "\t centered in : x=" << positionX << "px, y=" << positionY << "px" << std::endl;

	};
	~GaussianSource() {};

	void updateField(d_ptr _field, const int time);

	int getPositionX() { return positionX; }
	int getPositionY() { return positionY; }

	float amp, freq, deltaFreq;
	int positionX, positionY;
private:
	GaussianUpdater updater;
};

#endif /* GAUSSIANSORCE_H_ */
