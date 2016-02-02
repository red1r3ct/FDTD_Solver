/*
 * HarmonicSource.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef HARMONICSOURCE_H_
#define HARMONICSOURCE_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <iostream>

#include "Source.h"

/*
 * Функтор для обновления данных о поле в случае
 * гармонического источника.
 */

struct HarmonicUpdater {
	HarmonicUpdater(float _amp, float _freq) : amp(_amp), freq(_freq) {};

	float amp, freq;
	d_ptr field;

	__device__
	void operator() (const int time);
};

/*
 * Класс реализующий фуекционал гармонического источника.
 * Необходимо разобрать с возможностью реализации использования этого класса
 * через интерфейс Source
 */

class HarmonicSource: public Source {
public:
	HarmonicSource(float _amp, float _freq, int _positionX, int _positionY) : amp(_amp), freq(_freq),
																			positionX(_positionX),
																			positionY(_positionY),
																			updater(amp, freq) {
		std::cout << "Harmonic source added: \n";
		std::cout << "\t amplitude : " << updater.amp << std::endl;
		std::cout << "\t frequency : " << updater.freq << std::endl;
		std::cout << "\t centered in : x=" << positionX << "px, y=" << positionY << "px" << std::endl;

	};
	~HarmonicSource() {};

	void updateField(d_ptr _field, const int time);

	int getPositionX() { return positionX; }
	int getPositionY() { return positionY; }

	float amp, freq;
	int positionX, positionY;
private:
	HarmonicUpdater updater;
};

#endif /* HARMONICSOURCE_H_ */
