#include "wall.h"
#include "maze.h"
/********************************************************************/
/*                                                                  */
/*  A1 Part 3: runMaze                                              */
/*                                                                  */
/*  Author1 Name: Wonkeun No                                        */
/*      - class/function list/main author or main checker           */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/********************************************************************/

#include <iostream>
bool moveInMaze(Maze& theMaze, int path[], int startCell, int endCell, int numOfPaths);

//runMaze function takes Maze object, integer array, and starting and ending cell as an integer. 
//It finds a way from starting cell to ending cell and adds cells in the path to integer array. 
//Function returns an integer which is the number of cells in the path. 
//If path is not found, it returns zero.    
int runMaze(Maze& theMaze, int path[], int startCell, int endCell){    
    
    bool pathFound = moveInMaze(theMaze, path, startCell, endCell, 0);
    
    int numOfCellsInPath = 0;
    if (pathFound){
        while(path[numOfCellsInPath] != endCell){
            numOfCellsInPath++;
        } 
        ++numOfCellsInPath;
    } else {
        path = {};
    }
    
    return numOfCellsInPath;
}

//moveInMaze function takes Maze object, integer array, starting and ending cell as an integer, and the number of cells in the current path.
//Function marks the current cell as visited, and adds it to the integer array to store the path. 
//It tries to move in every direction. 
//It calls itself recursively with new postion if next cell can be visited. 
//Once starting and ending cells are equal, the function returns true. 
//Otherwise it returns false. 
bool moveInMaze(Maze& theMaze, int path[], int startCell, int endCell, int numOfPath){
    int rightDirection, bottomDirection, leftDirection, topDirection;
    bool exitFound = false;
    
    theMaze.mark(startCell);
    path[numOfPath] = startCell;
    numOfPath++;
    
    if (startCell == endCell){
        exitFound = true;
    }
    
    if (!exitFound){
        rightDirection = startCell +1;
        
        if ((rightDirection / theMaze.numCols()) <= theMaze.numCols() && theMaze.canGo(startCell, rightDirection) && !theMaze.isMarked(rightDirection)){
            exitFound = moveInMaze(theMaze, path, rightDirection, endCell, numOfPath);
        }
    }
        
    if (!exitFound){
        bottomDirection = startCell + theMaze.numCols();
        
        if ((bottomDirection/theMaze.numCols()) <= theMaze.numRows() && theMaze.canGo(startCell, bottomDirection) && !theMaze.isMarked(bottomDirection)){
            exitFound = moveInMaze(theMaze, path, bottomDirection, endCell, numOfPath);
        }
    }
        
    if (!exitFound){
        leftDirection = startCell -1;
        
        if (leftDirection >= 0 && theMaze.getRow(startCell) == theMaze.getRow(leftDirection) && theMaze.canGo(startCell, leftDirection) && !theMaze.isMarked(leftDirection)){
            exitFound = moveInMaze(theMaze, path, leftDirection, endCell, numOfPath);
        }
    }
        
    if (!exitFound){
        topDirection = startCell - theMaze.numCols();
        
        if (topDirection >= 0 && theMaze.canGo(startCell, topDirection) && !theMaze.isMarked(topDirection) ){
            exitFound = moveInMaze(theMaze, path, topDirection, endCell, numOfPath);
        }
    }
        
    return exitFound;
}
