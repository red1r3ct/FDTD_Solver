/*
 * GridTM.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef GRIDTM_H_
#define GRIDTM_H_

#include "../Structures/HostDeviceVector.h"

#include <string>

typedef HostDeviceVector vector;

/*
 * Класс контейнер. Содержит данные о полях в виде HostDeviceVector
 * и данные о размерах сетки а также времени моделирования
 */
class GridTM {
public:
	GridTM(std::size_t _sizeX, std::size_t _sizeY, float _S);
	~GridTM() {};

	void readEpsilon(const std::string& fileName);

	void readSigma(const std::string& fileName);

	void readExcluded(const std::string& fileName);

	// Геометрические размеры
	std::size_t sizeX, sizeY;
	float S;
	// Компоненты поля
	vector Hx, Hy, Ez, epsilon, sigma, excluded;
	// Время
	std::size_t time;
};

#endif /* GRIDTM_H_ */
