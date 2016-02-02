/*
 * Parser.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <fstream>

#include "../Grids/GridTM.h"
#include "../Updaters/UpdaterTM.h"
#include "../Updaters/UpdaterTE.h"
#include "../Routines/IntensityOutputRoutineTM.h"
#include "../Routines/EzOutputRoutineTM.h"
#include "../Sources/HarmonicSource.h"
#include "../Sources/RickerSource.h"
#include "../BoundaryCond/ABCTM.h"
#include "../BoundaryCond/TFSFCondTM.h"
#include "../BoundaryCond/TFSFCondTE.h"
#include "../Grids/GridTE.h"
#include "../Routines/HzOutputRoutineTE.h"
#include "../BoundaryCond/ABCTE.h"

/*
 * Должен по структуре входного файла запускать соответствующее
 * моделирование.
 */

class Parser {
public:
	Parser();
	~Parser();

	void runFile(std::string fileName);

private:
	std::ifstream fileStream;
	GridTM* gridTM;
	UpdaterTE updaterTE;
	GridTE* gridTE;
	UpdaterTM  updaterTM;
	std::vector<HarmonicSource*> hSources;
	std::vector<RickerSource*> rSources;
	std::vector<EzOutputRoutineTM*> EzOut;
	std::vector<HzOutputRoutineTM*> HzOut;
	std::vector<ABCTM*> ABCTMs;
	std::vector<ABCTE*> ABCTEs;
	TFSFCondTM* tfsfTM;
	TFSFCondTE* tfsfTE;
	HarmonicSource* hTFSFSource;
	RickerSource* rTFSFSource;
	int num;

	void runTE();
	void runTM();

	void createGridTM();
	inline void addSourceTM();
	inline void addBoundaryCondTM();
	inline void addRoutineTM();
	void readEpsilonTM();
	void createGridTE();
	inline void addSourceTE();
	inline void addBoundaryCondTE();
	inline void addRoutineTE();
	void readEpsilonTE();


};

#endif /* PARSER_H_ */
