/*
 * Updater1DTE.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef UPDATER1DTE_H_
#define UPDATER1DTE_H_

#include "../Sources/Source.h"
#include "../Grids/Grid1DTE.h"
#include "Functors1DTE/UpdaterEy1D.h"
#include "Functors1DTE/UpdaterHz1D.h"
#include "Updater.h"

class Updater1DTE: public Updater {
public:
	Updater1DTE();
	~Updater1DTE() {};

	void addSource(Source* _source);

	void addGrid(Grid1DTE* _grid);

protected:
	// Обновляет все поля
	void updateFields();
	void updateEy();
	void updateHz();
	// Проводит все дополнительные вычисления
	void updateRoutines() {};
	// Применяет граничные условия
	void updateBoundaryCond() {};
	// Считает источники
	void updateSources();
private:
	Grid1DTE* grid;
	Source* source;

	UpdaterEy1D updaterEy;
	UpdaterHz1D updaterHz;
};

#endif /* UPDATER1DTE_H_ */
