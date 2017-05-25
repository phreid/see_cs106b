// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
using namespace std;

enum Space {Empty, Cell};

void readInputToGrid(Grid<Space> &grid) {
    string path;
    string line;
    ifstream instream;
    int numRows;
    int numCols;

    path = getLine("Please enter your filepath: ");

    while (! openFile(instream, path)) {
        path = getLine("Error. Please enter your filepath: ");
    }

    getLine(instream, line);
    numRows = stringToInteger(line);
    getLine(instream, line);
    numCols = stringToInteger(line);
    grid.resize(numRows, numCols);

    for (int r = 0; r < numRows; r++) {
        getLine(instream, line);
        for (int c = 0; c < numCols; c++) {
            if (line[c] == '-') grid.set(r, c, Empty);
            else grid.set(r, c, Cell);
        }
    }
}

string gridToString(Grid<Space> &grid) {
    string output;

    for (int r = 0; r < grid.numRows(); r++) {
        for (int c = 0; c < grid.numCols(); c++) {
            if (grid.get(r, c) == Empty) output += '-';
            else output += 'X';
        }
        output += '\n';
    }

    return output;
}

int countNeighbors(Grid<Space> &grid, int r, int c, bool useWrapping) {
    int numNeighbors = 0;

    Vector<int> offsets;
    offsets.add(0);
    offsets.add(1);
    offsets.add(-1);

    for (int i = 0; i < offsets.size(); i++) {
        for (int j = 0; j < offsets.size(); j++) {
            int x = offsets.get(i);
            int y = offsets.get(j);

            if (! ((x == 0) & (y == 0))) {
                if (grid.inBounds(r - x, c - y)) {
                    if (grid.get(r - x, c - y) == Cell) numNeighbors++;
                }
            }
        }
    }

    return numNeighbors;
}

void updateGrid(Grid<Space> &grid, bool useWrapping = false) {
    Grid<Space> tempGrid;
    tempGrid.deepCopy(grid);

    for (int r = 0; r < grid.numRows(); r++) {
        for (int c = 0; c < grid.numCols(); c++) {
            int numNeighbors = countNeighbors(grid, r, c, useWrapping);

            if (numNeighbors <= 1) tempGrid.set(r, c, Empty);
            if (numNeighbors == 3) tempGrid.set(r, c, Cell);
            if (numNeighbors >= 4) tempGrid.set(r, c, Empty);
        }
    }

    grid = tempGrid;
}

void animate(Grid<Space> &grid, int pauseTime, int numFrames) {
    string s = gridToString(grid);
    cout << s;
    clearConsole();
}

int main() {
    // TODO: Finish the program!
    Grid<Space> grid;

    readInputToGrid(grid);

    animate(grid, 50, 10);

    return 0;
}
