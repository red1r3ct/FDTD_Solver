/*
 * Updater.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef UPDATER_H_
#define UPDATER_H_

/*
 * Базовый класс для обновления полей. Содержит методо iterate()
 * который совершает одну иттерацию алгоритма. От данного класса
 * должны быть унаследованны все апдейтеры. Для однообразности кода
 * необходимо реализовать соответствующие методы.
 */

class Updater {
public:
	Updater() {};
	virtual ~Updater() {};
	// Функция проводит одну иттерацию
	void iterate();
protected:
	// Обновляет все поля
	virtual void updateFields() = 0;
	// Проводит все дополнительные вычисления
	virtual void updateRoutines() = 0;
	// Применяет граничные условия
	virtual void updateBoundaryCond() = 0;
	// Считает источники
	virtual void updateSources() = 0;

};

#endif /* UPDATER_H_ */
