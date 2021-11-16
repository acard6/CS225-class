/* Your code here! */
#pragma once
#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <vector> 
#include <stack>
#include <queue>

using namespace cs225;
using namespace std;

class SquareMaze
{
public:
    /* data */
    // default constructor.  creates empty maze
    SquareMaze();
    
    // makes a new SquareMaze of the given width and height
    void makeMaze(int width, int height);

    /** This uses your representation of the maze to determine whether 
    * it is possible to travel in the given direction from the square at 
    * coordinates (x,y).
    */
    bool canTravel(int x, int y, int dir) const;
    
    // sets whether or not the specified wall exists
    void setWall(int x, int y, int dir, bool exists);
    
    // solves the SquareMaze
    vector<int> solveMaze();
    
    // draws the maze without a soln
    PNG* drawMaze() const;
    
    // This function calls drawMaze, then solveMaze; it modifies the 
    // PNG from drawMaze to show the solution vector and the exit.
    PNG* drawMazeWithSolution();

    ~SquareMaze();

private:
    int height_;
    int width_;
    vector<pair<bool,bool>>* walls;
    DisjointSets* dset;
};
