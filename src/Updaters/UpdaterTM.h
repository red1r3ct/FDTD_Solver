/*
 * UpdaterTM.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef UPDATERTM_H_
#define UPDATERTM_H_

#include "Updater.h"
#include "../Routines/Routine.h"
#include "../Grids/GridTM.h"
#include "../BoundaryCond/BoundaryCond.h"
#include "../BoundaryCond/TFSFCondTM.h"
#include "../Sources/Source.h"
#include "FunctorsTM/EzUpdaterTM.h"
#include "FunctorsTM/HxHyUpdaterTM.h"
#include "FunctorsTM/HxUpdaterTM.h"
#include "FunctorsTM/HyUpdaterTM.h"

#include <vector>

/*
 * Класс для обновления данных в случае TM поляризации.
 * в .cu файле реализованны функции вызовающие GPU ядра.
 */

class UpdaterTM: public Updater {
public:
	UpdaterTM() : grid(NULL), tfsfCond(NULL) {};
	~UpdaterTM() {	}
	// Добавляет дополнительные вычиления
	void addRoutine(Routine* routine);
	// Добавляет сетку для которой проводится обновление
	void addGrid(GridTM* _grid);
	// Добавляет граничные условия
	void addBoundaryCond(BoundaryCond* boundaryCond);
	// Добавляет источник
	void addSource(Source* source);
	// Добавляет TFSF граничные условия
	void addTFSF(TFSFCondTM* _tfsfCond);
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
	GridTM* grid;
	// Граничные условия
	std::vector<BoundaryCond*> boundaryConds;
	// Граничные услови TFSF
	TFSFCondTM* tfsfCond;
	// Вектор источников
	std::vector<Source*> sources;
	// Функторы для обновления полей
	EzUpdaterTM EzUpdater;
	HxHyUpdaterTM HxHyUpdater;
};

#endif /* UPDATERTM_H_ */
