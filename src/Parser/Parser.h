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
#include "../Routines/HxOutputRoutineTM.h"
#include "../Routines/HyOutputRoutineTM.h"
#include "../Sources/HarmonicSource.h"
#include "../Sources/RickerSource.h"
#include "../BoundaryCond/ABCTM.h"
#include "../BoundaryCond/TFSFCondTM.h"
#include "../BoundaryCond/TFSFCondTE.h"
#include "../BoundaryCond/PeriodicCondTM.h"
#include "../BoundaryCond/PeriodicCondTE.h"
#include "../Grids/GridTE.h"
#include "../Routines/HzOutputRoutineTE.h"
#include "../Routines/ExOutputRoutineTE.h"
#include "../Routines/EyOutputRoutineTE.h"
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
	std::vector<HxOutputRoutineTM*> HxOut;
	std::vector<HyOutputRoutineTM*> HyOut;
	std::vector<HzOutputRoutineTE*> HzOut;
	std::vector<ExOutputRoutineTE*> ExOut;
	std::vector<EyOutputRoutineTE*> EyOut;
	std::vector<ABCTM*> ABCTMs;
	std::vector<ABCTE*> ABCTEs;
	std::vector<PeriodicCondTM*> periodicsTM;
	std::vector<PeriodicCondTE*> periodicsTE;
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
	void readSigmaTM();
	void createGridTE();
	inline void addSourceTE();
	inline void addBoundaryCondTE();
	inline void addRoutineTE();
	void readEpsilonTE();


};

#endif /* PARSER_H_ */
