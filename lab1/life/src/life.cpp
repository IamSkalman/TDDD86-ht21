#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>
#include <string>
#include <algorithm>


using namespace std;
Grid<char> createFirstGrid(const string& textfile);
void printGrid(const Grid<char>& grid);
void tick(Grid<char>& grid);

int main() {
    /*
     * Prints the introduction and asks for which textfile the simulation shall be based on.
     * Then it asks for an inputCommand which decides if the program shall simulate one tick,
     * infinite amounts of ticks or quit.
     */

    string textfile;
    Grid<char> grid;
    Grid<char> tempGrid;
    string inputCommand;

    cout << "Welcome to the TDDD86 Game of Life,\n"
                 "a simulation of the lifecycle of a bacteria colony.\n"
                 "Cells (X) live and die by the following rules:\n"
                 "- A cell with 1 or fewer neighbours dies.\n"
                 "- Locations with 2 neighbours remain stable.\n"
                 "- Locations with 3 neighbours will create life.\n"
                 "- A cell with 4 or more neighbours dies."
              << endl;
    cout << "Grid input file name?" << endl;
    cin >> textfile;

    grid = createFirstGrid(textfile);
    printGrid(grid);

    while (inputCommand != "q"){
        cout << "a)nimate, t)ick, q)uit?" << endl;
        cin >> inputCommand;
        if (inputCommand == "t"){
            clearConsole();
            tick(grid);
            printGrid(grid);
        }
        else if (inputCommand == "a"){
            while(true){
                clearConsole();
                tick(grid);
                printGrid(grid);
                pause(100);
            }
        }
        else if(inputCommand == "q"){
            cout << "Have a nice Life!" << endl;
        }
        else{
            clearConsole();
            printGrid(grid);
        }
    }
    return 0;
}

int getAmountOfNeighbours(int rowIndex, int columnIndex, const Grid<char>& grid){
    /*
     * Returns int amount of neighbours around a single cell in the grid.
     * Param rowIndex is the cells row coordinate in the grid.
     * Param columnIndex is the cells column coordinate in the grid.
     * Param grid is the reference to the grid.
     */
    int neighbourCounter = 0;
    for(int k = rowIndex-1; k < rowIndex+2; k++){
        for(int l = columnIndex-1; l < columnIndex+2; l++){
            if(grid.inBounds(k,l)){
                if(grid.get(k,l) == 'X' && !(rowIndex == k && columnIndex == l)){
                    neighbourCounter++;
                }
            }
        }
    }
    return neighbourCounter;
}

void tick(Grid<char>& grid){
    /*
     * Returns nothing (void), changes the grid one generation forward by updating the grid
     * Param grid is a reference to the grid.
     */
    int neighbourCounter;
    Grid<char> tempGrid = grid;

    for(int i = 0; i < tempGrid.numRows(); i++){
        for (int j = 0; j < tempGrid.numCols(); j++){
            neighbourCounter = getAmountOfNeighbours(i,j,tempGrid);
            if(neighbourCounter <= 1 || neighbourCounter >= 4){
                grid.set(i,j,'-');
            }
            else if(neighbourCounter == 3){
                grid.set(i,j,'X');
            }
            else{
                grid.set(i,j, tempGrid.get(i,j));
            }
        }
    }
}

void printGrid(const Grid<char>& grid){
    /*
     * Returns nothing (void), prints the grid one row at the time.
     * Param grid is a reference to the current grid.
     */
    string row;
    char cell;
    for(int i = 0; i < grid.numRows(); i++){
        row = "";
        for (int j = 0; j < grid.numCols(); j++){
            cell = grid.get(i,j);
            row += cell;
        }
        cout << row << endl;
    }
}

Grid<char> createFirstGrid(const string& textfile) {
    /*
     * Returns a Grid<char> from a given textfile.
     * Param textfile is a constant string reference to the chosen textfile.
     */
    ifstream input;
    input.open(textfile);
    string line;
    int lineCounter = 0;
    int rows;
    int column;
    Grid<char> grid;

    while (getline(input, line)){
        if (line[0] != '#'){
            if(lineCounter == 0){
                rows = stoi(line);
            }
            else if (lineCounter == 1) {
                column = stoi(line);
                grid = Grid<char>(rows, column);

            }
            else if (line[0] == '-' || line[0] == 'X'){
                for (int i = 0; i < column; i++){
                    grid[lineCounter-2][i] = line[i];
                }
            }
        }
        lineCounter++;
    }
    input.close();

    return grid;
}
