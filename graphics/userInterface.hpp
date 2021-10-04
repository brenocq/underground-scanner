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

    Maze& _maze;
};

#endif
