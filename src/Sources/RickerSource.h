/*
 * RickerSource.h
 *
 *  Created on: 02 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef RICKERSOURCE_H_
#define RICKERSOURCE_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <iostream>

#include "Source.h"

/*
 * Функтор для обновления данных о поле в случае
 * источника в формк вейвлета Рикера.
 */

struct RickerUpdater {
	RickerUpdater(float _amp, float _freq, int _M) : amp(_amp), freq(_freq), M(_M) {};

	float amp, freq;
	int M;
	d_ptr field;

	__device__
	void operator() (const int time);
};

/*
 * Класс реализующий фуекционал гармонического источника.
 * Необходимо разобрать с возможностью реализации использования этого класса
 * через интерфейс Source
 */

class RickerSource: public Source {
public:
	RickerSource(float _amp, float _freq, int _M, int _positionX, int _positionY) : amp(_amp), freq(_freq), M(_M),
																			positionX(_positionX),
																			positionY(_positionY),
																			updater(amp, freq, M) {
		std::cout << "Ricker wavelet source added: \n";
		std::cout << "\t amplitude : " << updater.amp << std::endl;
		std::cout << "\t peak frequency : " << updater.freq << std::endl;
		std::cout << "\t delay multiple : " << updater.M << std::endl;
		std::cout << "\t centered in : x=" << positionX << "px, y=" << positionY << "px" << std::endl;

	};
	~RickerSource() {};

	void updateField(d_ptr _field, const int time);

	int getPositionX() { return positionX; }
	int getPositionY() { return positionY; }

	float amp, freq, M;
	int positionX, positionY;
private:
	RickerUpdater updater;
};
#endif /* RICKERSOURCE_H_ */
