/*
 * LifeModel.cpp
 *
 * The model for the Life program.
 *
 */

#include "LifeModel.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

/**
 * Read the initial generation from a file in the patterns/ directory.
 * Place that shape with the upper left corner at (left, top) on the map.
 * Generate the remaining NUM_GENERATIONS generations.
 */
LifeModel::LifeModel(string filename, int top, int left) {
	this->genNum = 0;
	this->generations.push_back(new Generation(filename, top, left));
	for(int i=1; i<NUM_GENERATIONS; i++) {
		Generation* next = this->generations.back()->nextGeneration();
		this->generations.push_back(next);
	}
}

/**
 * Destructor
 */
LifeModel::~LifeModel() {
}

/**
 * Get the current generation.
 */
int LifeModel::generationNum() {
	return this->genNum;
}

/**
 * Go to a specific generation.
 */
void LifeModel::gotoGen(int g) {
	this->genNum = min(NUM_GENERATIONS-1, max(0, g));
}

/**
 * Move the simulation forward by one generation.
 */
void LifeModel::forward() {
	this->genNum = min(NUM_GENERATIONS-1, this->genNum + 1);
}

/**
 * Move the simulation backwards by one generation.
 */
void LifeModel::back() {
	this->genNum = max(0, this->genNum - 1);
}

/**
 * Move the simulation to the first generation.
 */
void LifeModel::beginning() {
	this->genNum = 0;
}

/**
 * Move the simulation to the last generation.
 */
void LifeModel::end() {
	this->genNum = NUM_GENERATIONS - 1;
}

/**
 * Get the current generation.
 */
Generation* LifeModel::getCurrentGeneration() {
	return this->generations[this->genNum];
}

/**
 * Print out one generation of the simulation.
 */
void LifeModel::debug(int genNum) {
	this->generations[genNum]->debug();
}



