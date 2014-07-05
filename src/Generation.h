#ifndef GENERATION_H_
#define GENERATION_H_

#include "Life.h"
#include <string>

using namespace std;

class Generation {
public:
	Generation(string filename, int top, int left);
	Generation(int genNum);
	virtual ~Generation();

	Generation* nextGeneration();

	void debug();

	// Need to add appropriate access to the map for the UI to display.
	bool islive(int row,int col);
	void changeLife(int r, int c);
	void saveTOFile();

private:
	int genNum;
	bool map[NUM_ROWS][NUM_COLS];

	int countNeighbours(int row, int col);
};


#endif /* GENERATION_H_ */


