/*
 * Updater1D.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef UPDATER1D_H_
#define UPDATER1D_H_

#include "../Sources/Source.h"
#include "../Grids/Grid1DTM.h"
#include "Functors1D/UpdaterHy1D.h"
#include "Functors1D/UpdaterEz1D.h"
#include "Updater.h"

class Updater1DTM: public Updater {
public:
	Updater1DTM();
	~Updater1DTM() {};

	void addSource(Source* _source);

	void addGrid(Grid1DTM* _grid);

protected:
	// Обновляет все поля
	void updateFields();
	void updateEz();
	void updateHy();
	// Проводит все дополнительные вычисления
	void updateRoutines() {};
	// Применяет граничные условия
	void updateBoundaryCond() {};
	// Считает источники
	void updateSources();
private:
	Grid1DTM* grid;
	Source* source;

	UpdaterHy1D updaterHy;
	UpdaterEz1D updaterEz;
};

#endif /* UPDATER1D_H_ */
