#ifndef __USER_INTERFACE
#define __USER_INTERFACE
#include "maze.hpp"
#include "camera.hpp"

class UserInterface
{
public:
    UserInterface(Maze& maze, Camera& camera);
    void init();
    void render();

private:
    void mazeGeneration();
    void searchControl();
    void statistics();
    
    Maze& _maze;
    Camera& _camera;
};

#endif
