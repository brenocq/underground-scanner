#ifndef __USER_INTERFACE
#define __USER_INTERFACE
#include "maze.hpp"

class UserInterface
{
public:
    UserInterface(Maze& maze);
    void init();
    void render();

private:
    void mazeGeneration();
    void searchControl();
    
    int startX = 0, startY = 0, startZ = 0;
    int goalX = 6, goalY = 6, goalZ = 6;
    Maze& _maze;
};

#endif
