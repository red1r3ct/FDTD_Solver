/*
 * Updater3D.h
 *
 *  Created on: 05 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef UPDATER3D_H_
#define UPDATER3D_H_

#include "Updater.h"
#include "../Routines/Routine.h"
#include "../Grids/Grid3D.h"
#include "../BoundaryCond/BoundaryCond.h"
#include "../Sources/Source.h"

#include "Functors3D/ExUpdater3D.h"
#include "Functors3D/EyUpdater3D.h"
#include "Functors3D/EzUpdater3D.h"
#include "Functors3D/HxUpdater3D.h"
#include "Functors3D/HyUpdater3D.h"
#include "Functors3D/HzUpdater3D.h"

#include <vector>

/*
 * Класс для обновления данных трехмерной решетки.
 * в .cu файле реализованны функции вызовающие GPU ядра.
 */

class Updater3D: public Updater {
public:
	Updater3D() : grid(nullptr) {};
	~Updater3D() {}
	// Добавляет дополнительные вычиления
	void addRoutine(Routine* routine);
	// Добавляет сетку для которой проводится обновление
	void addGrid(Grid3D* _grid);
	// Добавляет граничные условия
	void addBoundaryCond(BoundaryCond* boundaryCond);
	// Добавляет источник
	void addSource(Source* source);
	// Запускает моделирование на num шагов
	void run(int num);
protected:
	// Обновляет все поля TODO
	void updateFields();
	// Проводит все дополнительные вычисления TODO
	void updateRoutines();
	// Применяет граничные условия TODO
	void updateBoundaryCond();
	// Обновляет E TODO
	void updateE();
	// Обновляет H TODO
	void updateH();
	// Считает источники TODO
	void updateSources();

private:
	// Вектор дополнительных вычислений
	std::vector<Routine*> routines;
	// Сетка для которой проводится обновление
	Grid3D* grid;
	// Граничные условия
	std::vector<BoundaryCond*> boundaryConds;
	// Вектор источников
	std::vector<Source*> sources;
	// Функторы для обновления полей

};

#endif /* UPDATER3D_H_ */
