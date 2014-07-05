/*
 * LifeModel.h
 *
 */

#ifndef LIFEMODEL_H_
#define LIFEMODEL_H_

#include "Life.h"
#include "Generation.h"
#include <string>
#include <vector>


using namespace std;

class LifeModel {
public:
	LifeModel(string filename, int top, int left);
	virtual ~LifeModel();

	int generationNum();
	void gotoGen(int g);
	void forward();
	void back();
	void beginning();
	void end();
	Generation* getCurrentGeneration();

	void debug(int g);

private:
	vector<Generation *> generations;
	int genNum;

	void cacheGenerations(int numGenerations);
	int countNeighbours(bool gen[NUM_ROWS][NUM_COLS], int row, int col);
};

#endif /* LIFEMODEL_H_ */

