/*
 * Parser.cpp
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#include "Parser.h"

#include <cmath>
#include <iostream>

Parser::Parser(): gridTM(nullptr), gridTE(nullptr), tfsfTM(nullptr), tfsfTE(nullptr), num(0) {

}

Parser::~Parser() {
	if (gridTM != nullptr) {
		delete gridTM;
	}
	if (gridTE != nullptr) {
		delete gridTE;
	}
	for (auto source: hSources){
		delete source;
	}
	for (auto source: rSources){
		delete source;
	}
	for (auto ezout: EzOut){
		delete ezout;
	}
	for (auto hzout: HzOut){
		delete hzout;
	}
	for (auto exout: ExOut){
		delete exout;
	}
	for (auto eyout: EyOut){
		delete eyout;
	}
	for (auto hxout: HxOut){
		delete hxout;
	}
	for (auto hyout: HyOut){
		delete hyout;
	}
	for (auto abc: ABCTMs){
		delete abc;
	}
	for (auto abc: ABCTEs){
		delete abc;
	}
	if (tfsfTM != nullptr) {
		delete tfsfTM;
	}
	if (tfsfTE != nullptr) {
		delete tfsfTE;
	}
}

void Parser::runFile(std::string fileName) {
	fileStream.open(fileName);
	if (!fileStream.is_open()) {
		return;
	}
	std::string simulationType;
	fileStream >> simulationType; // Skip prefix
	fileStream >> simulationType; // Read type
	if (simulationType == "TE") {
		runTE();
	}
	if (simulationType == "TM") {
		runTM();
	}
	fileStream.close();
}

void Parser::runTM() {
	std::string command = "";
	while (fileStream >> command) {
		if (command == "GridTM:") {
			createGridTM();
		}
		if (command == "Epsilon:") {
			readEpsilonTM();
		}
		if (command == "Sigma:") {
			readSigmaTM();
		}
		if (command == "Source:") {
			addSourceTM();
		}
		if (command == "BoundaryCond:") {
			addBoundaryCondTM();
		}
		if (command == "Output:") {
			addRoutineTM();
		}
		if (command == "Run:") {
			fileStream >> num;
		}
	}
	for (auto source: hSources){
		updaterTM.addSource(source);
	}
	for (auto ezout: EzOut){
		updaterTM.addRoutine(ezout);
	}
	for (auto hxout: HxOut){
		updaterTM.addRoutine(hxout);
	}
	for (auto hyout: HyOut){
		updaterTM.addRoutine(hyout);
	}
	for (auto abc: ABCTMs){
		updaterTM.addBoundaryCond(abc);
	}
	if (tfsfTM != nullptr) {
		updaterTM.addTFSF(tfsfTM);
	}
	updaterTM.run(num);
}

void Parser::runTE() {
	std::string command = "";
	while (fileStream >> command) {
		if (command == "GridTE:") {
			createGridTE();
		}
		if (command == "Epsilon:") {
			readEpsilonTE();
		}
		if (command == "Source:") {
			addSourceTE();
		}
		if (command == "BoundaryCond:") {
			addBoundaryCondTE();
		}
		if (command == "Output:") {
			addRoutineTE();
		}
		if (command == "Run:") {
			fileStream >> num;
		}
	}
	for (auto source: hSources){
		updaterTE.addSource(source);
	}
	for (auto hzout: HzOut){
		updaterTE.addRoutine(hzout);
	}
	for (auto exout: ExOut){
		updaterTE.addRoutine(exout);
	}
	for (auto eyout: EyOut){
		updaterTE.addRoutine(eyout);
	}
	for (auto abc: ABCTEs){
		updaterTE.addBoundaryCond(abc);
	}
	if (tfsfTE != nullptr) {
		updaterTE.addTFSF(tfsfTE);
	}
	updaterTE.run(num);
}

void Parser::readEpsilonTM() {
	std::string epsilonFileName = "";
	fileStream >> epsilonFileName;
	gridTM->readEpsilon(epsilonFileName);
}

void Parser::readSigmaTM() {
	std::string sigmaFileName = "";
	fileStream >> sigmaFileName;
	gridTM->readSigma(sigmaFileName);
}

void Parser::readEpsilonTE() {
	std::string epsilonFileName = "";
	fileStream >> epsilonFileName;
	gridTE->readEpsilon(epsilonFileName);
}

void Parser::createGridTM() {
	int sizeX(0), sizeY(0);
	fileStream >> sizeX;
	fileStream >> sizeY;
	gridTM = new GridTM(sizeX, sizeY, 1/sqrt(2));
	updaterTM.addGrid(gridTM);
}

void Parser::createGridTE() {
	int sizeX(0), sizeY(0);
	fileStream >> sizeX;
	fileStream >> sizeY;
	gridTE = new GridTE(sizeX, sizeY, 1/sqrt(2));
	updaterTE.addGrid(gridTE);
}

inline void Parser::addSourceTM() {
	std::string sourceType;
	fileStream >> sourceType;
	if (sourceType == "Harmonic") {
		float amp = 0;
		fileStream >> amp;
		float freq = 0;
		fileStream >> freq;
		freq = 4.44063/freq;
		int posX(0), posY(0);
		fileStream >> posX >> posY;
		HarmonicSource* hSource = new HarmonicSource(amp, freq, posX, posY);
		hSources.push_back(hSource);
	}
	if (sourceType == "Ricker") {
		float amp = 0;
		fileStream >> amp;
		float freq = 0;
		fileStream >> freq;
		freq = 4.44063/freq;
		int M = 0;
		fileStream >> M;
		int posX(0), posY(0);
		fileStream >> posX >> posY;
		RickerSource* rSource = new RickerSource(amp, freq, M, posX, posY);
		rSources.push_back(rSource);
	}
}

inline void Parser::addSourceTE() {
	std::string sourceType;
	fileStream >> sourceType;
	if (sourceType == "Harmonic") {
		float amp = 0;
		fileStream >> amp;
		float freq = 0;
		fileStream >> freq;
		freq = 4.44063/freq;
		int posX(0), posY(0);
		fileStream >> posX >> posY;
		HarmonicSource* hSource = new HarmonicSource(amp, freq, posX, posY);
		hSources.push_back(hSource);
	}
	if (sourceType == "Ricker") {
		float amp = 0;
		fileStream >> amp;
		float freq = 0;
		fileStream >> freq;
		freq = 4.44063/freq;
		int M = 0;
		fileStream >> M;
		int posX(0), posY(0);
		fileStream >> posX >> posY;
		RickerSource* rSource = new RickerSource(amp, freq, M, posX, posY);
		rSources.push_back(rSource);
	}
}

inline void Parser::addBoundaryCondTM() {
	std::string condType;
	fileStream >> condType;
	if (condType == "ABC") {
		ABCTM* abc = new ABCTM(gridTM);
		ABCTMs.push_back(abc);
	}
	if (condType == "TFSF") {
		int firstX, lastX, firstY, lastY;
		fileStream >> firstX >> lastX >> firstY >> lastY;
		tfsfTM = new TFSFCondTM(gridTM, firstX, lastX, firstY, lastY);
		std::string sourceType;
		fileStream >> sourceType;
		if (sourceType == "Harmonic") {
				float amp = 0;
				fileStream >> amp;
				float freq = 0;
				fileStream >> freq;
				freq = 4.44063/freq;
				hTFSFSource = new HarmonicSource(amp, freq, 0, 0);
				tfsfTM->addSource(hTFSFSource);
		}
		if (sourceType == "Ricker") {
			float amp = 0;
			fileStream >> amp;
			float freq = 0;
			fileStream >> freq;
			freq = 4.44063/freq;
			int M = 0;
			fileStream >> M;
			rTFSFSource = new RickerSource(amp, freq, M, 0, 0);
			tfsfTM->addSource(rTFSFSource);
		}
	}
}

inline void Parser::addBoundaryCondTE() {
	std::string condType;
	fileStream >> condType;
	if (condType == "ABC") {
		ABCTE* abc = new ABCTE(gridTE);
		ABCTEs.push_back(abc);
	}
	if (condType == "TFSF") {
		int firstX, lastX, firstY, lastY;
		fileStream >> firstX >> lastX >> firstY >> lastY;
		tfsfTE = new TFSFCondTE(gridTE, firstX, lastX, firstY, lastY);
		std::string sourceType;
		fileStream >> sourceType;
		if (sourceType == "Harmonic") {
				float amp = 0;
				fileStream >> amp;
				float freq = 0;
				fileStream >> freq;
				freq = 4.44063/freq;
				hTFSFSource = new HarmonicSource(amp, freq, 0, 0);
				tfsfTE->addSource(hTFSFSource);
		}
		if (sourceType == "Ricker") {
				float amp = 0;
				fileStream >> amp;
				float freq = 0;
				fileStream >> freq;
				freq = 4.44063/freq;
				int M = 0;
				fileStream >> M;
				rTFSFSource = new RickerSource(amp, freq, M, 0, 0);
				tfsfTE->addSource(rTFSFSource);
			}
	}
}

inline void Parser::addRoutineTM() {
	std::string routineType;
	fileStream >> routineType;
	if (routineType == "Ez") {
		std::string fileName;
		int firstX, lastX, stepX, firstY, lastY, stepY, startTime, endTime, period;
		fileStream >> fileName >> firstX >> lastX >> stepX >> firstY >> lastY >> stepY >> startTime >> endTime >> period;
		EzOutputRoutineTM* routine = new EzOutputRoutineTM(fileName, gridTM, firstX, lastX,
															stepX, firstY, lastY, stepY,
															startTime, endTime,
															period);
		EzOut.push_back(routine);
	}
	if (routineType == "Hx") {
		std::string fileName;
		int firstX, lastX, stepX, firstY, lastY, stepY, startTime, endTime, period;
		fileStream >> fileName >> firstX >> lastX >> stepX >> firstY >> lastY >> stepY >> startTime >> endTime >> period;
		HxOutputRoutineTM* routine = new HxOutputRoutineTM(fileName, gridTM, firstX, lastX,
															stepX, firstY, lastY, stepY,
															startTime, endTime,
															period);
		HxOut.push_back(routine);
	}
	if (routineType == "Hy") {
		std::string fileName;
		int firstX, lastX, stepX, firstY, lastY, stepY, startTime, endTime, period;
		fileStream >> fileName >> firstX >> lastX >> stepX >> firstY >> lastY >> stepY >> startTime >> endTime >> period;
		HyOutputRoutineTM* routine = new HyOutputRoutineTM(fileName, gridTM, firstX, lastX,
															stepX, firstY, lastY, stepY,
															startTime, endTime,
															period);
		HyOut.push_back(routine);
	}
}

inline void Parser::addRoutineTE() {
	std::string routineType;
	fileStream >> routineType;
	if (routineType == "Hz") {
		std::string fileName;
		int firstX, lastX, stepX, firstY, lastY, stepY, startTime, endTime, period;
		fileStream >> fileName >> firstX >> lastX >> stepX >> firstY >> lastY >> stepY >> startTime >> endTime >> period;
		HzOutputRoutineTE* routine = new HzOutputRoutineTE(fileName, gridTE, firstX, lastX,
															stepX, firstY, lastY, stepY,
															startTime, endTime,
															period);
		HzOut.push_back(routine);
	}
	if (routineType == "Ex") {
		std::string fileName;
		int firstX, lastX, stepX, firstY, lastY, stepY, startTime, endTime, period;
		fileStream >> fileName >> firstX >> lastX >> stepX >> firstY >> lastY >> stepY >> startTime >> endTime >> period;
		ExOutputRoutineTE* routine = new ExOutputRoutineTE(fileName, gridTE, firstX, lastX,
															stepX, firstY, lastY, stepY,
															startTime, endTime,
															period);
		ExOut.push_back(routine);
	}
	if (routineType == "Ey") {
		std::string fileName;
		int firstX, lastX, stepX, firstY, lastY, stepY, startTime, endTime, period;
		fileStream >> fileName >> firstX >> lastX >> stepX >> firstY >> lastY >> stepY >> startTime >> endTime >> period;
		EyOutputRoutineTE* routine = new EyOutputRoutineTE(fileName, gridTE, firstX, lastX,
															stepX, firstY, lastY, stepY,
															startTime, endTime,
															period);
		EyOut.push_back(routine);
	}
}

