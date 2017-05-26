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

void printGrid(Grid<Space> &grid) {
    string output;

    for (int r = 0; r < grid.numRows(); r++) {
        for (int c = 0; c < grid.numCols(); c++) {
            if (grid.get(r, c) == Empty) output += '-';
            else output += 'X';
        }
        output += '\n';
    }

    cout << output;
}

int countNeighbors(Grid<Space> &grid, int r, int c, bool useWrapping) {
    int numNeighbors = 0;

    Vector<int> offsets;
    offsets.add(0);
    offsets.add(1);
    offsets.add(-1);

    for (int i = 0; i < offsets.size(); i++) {
        for (int j = 0; j < offsets.size(); j++) {
            int offX = offsets.get(i);
            int offY = offsets.get(j);
            int x = r - offX;
            int y = c - offY;

            if (! ((offX == 0) & (offY == 0))) {
                if (useWrapping) {
                    int x_wrap = (x + grid.numRows()) % grid.numRows();
                    int y_wrap = (y + grid.numCols()) % grid.numCols();
                    if (grid.get(x_wrap, y_wrap) == Cell) numNeighbors++;
                } else {
                    if (grid.inBounds(x, y)) {
                        if (grid.get(x, y) == Cell) numNeighbors++;
                    }
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

void tick(Grid<Space> &grid) {
    updateGrid(grid);
    printGrid(grid);
}

void animate(Grid<Space> &grid, int pauseTime, int numFrames) {
    string s;
    int curFrame = 0;

    while (curFrame < numFrames) {
        tick(grid);
        pause(pauseTime);
        curFrame++;
    }
}

int main() {
    // TODO: Finish the program!
    Grid<Space> grid;

    readInputToGrid(grid);
    printGrid(grid);

    while (true) {
        string s = getLine("a)nimate, t)ick, q)uit? ");

        if (s == "t") {
            tick(grid);
        } else if (s == "q") {
            cout << "Have a nice Life!";
            break;
        } else if (s == "a") {
            animate(grid, 50, 10);
        } else {
            cout << "Invalid choice; please try again." << endl;
        }
    }

    return 0;
}
