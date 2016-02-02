/*
 * Updater.cpp
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#include "Updater.h"
#include <iostream>

void Updater::iterate() {
	updateFields();
	updateBoundaryCond();
	updateSources();
	updateRoutines();
}
