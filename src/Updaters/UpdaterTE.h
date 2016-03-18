/*
 * UpdaterTE.h
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef UPDATERTE_H_
#define UPDATERTE_H_

#include "Updater.h"
#include "../Routines/Routine.h"
#include "../Grids/GridTE.h"
#include "../BoundaryCond/BoundaryCond.h"
#include "../BoundaryCond/TFSFCondTE.h"
#include "../Sources/Source.h"
#include "FunctorsTE/ExUpdaterTE.h"
#include "FunctorsTE/EyUpdaterTE.h"
#include "FunctorsTE/HzUpdaterTE.h"

#include <vector>

class UpdaterTE: public Updater {
public:
	UpdaterTE() : grid(NULL), tfsfCond(NULL) {};
	~UpdaterTE() {};
	// Добавляет дополнительные вычиления
	void addRoutine(Routine* routine);
	// Добавляет сетку для которой проводится обновление
	void addGrid(GridTE* _grid);
	// Добавляет граничные условия
	void addBoundaryCond(BoundaryCond* boundaryCond);
	// Добавляет источник
	void addSource(Source* source);
	// Добавляет TFSF граничные условия
	void addTFSF(TFSFCondTE* _tfsfCond);
	// Запускает моделирование на num шагов
	void run(int num);
protected:
	// Обновляет все поля DONE
	void updateFields();
	// Проводит все дополнительные вычисления DONE
	void updateRoutines();
	// Применяет граничные условия DONE
	void updateBoundaryCond();
	// Обновляет E DONE
	void updateE();
	// Обновляет H DONE
	void updateH();
	// Считает источники DONE
	void updateSources();
	// Применяет граничные условия TFSF
	void updateTFSF();

private:
	// Вектор дополнительных вычислений
	std::vector<Routine*> routines;
	// Сетка для которой проводится обновление
	GridTE* grid;
	// Граничные условия
	std::vector<BoundaryCond*> boundaryConds;
	// Граничные услови TFSF
	TFSFCondTE* tfsfCond;
	// Вектор источников
	std::vector<Source*> sources;
	// Функторы для обновления полей
	ExUpdaterTE ExUpdater;
	EyUpdaterTE EyUpdater;
	HzUpdaterTE HzUpdater;
};

#endif /* UPDATERTE_H_ */
