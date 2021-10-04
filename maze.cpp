#include "maze.hpp"
#include <math.h>

Maze::Maze(unsigned size_):
    size(size_)
{
    resize(size);
}

void Maze::resize(unsigned newSize)
{
    size = newSize;
    _nodes.resize(size*size*size);
    // Set some nodes as occupied
    generateMaze();
}

void Maze::generateMaze()
{
    for(unsigned i = 0; i < _nodes.size(); i++)
        _nodes[i] = MAZE_NONE;

    for(unsigned i = 0; i < size*size; i++)
        _nodes[i] = MAZE_OCCUPIED;

    for(unsigned i = 0; i < size; i++)
        occupySphere(rand()%size/3, rand()%size, rand()%size, rand()%size);
}

uint8_t Maze::getNode(int x, int y, int z)
{
    return _nodes[x + y * size + z * (size * size)];
}

void Maze::occupySphere(float radius, float x, float y, float z)
{
    // Draw sphere
    float r = radius; // Radius
    float sX = x;     // Position x
    float sY = y;     // Position y
    float sZ = z;     // Position z
    unsigned i = 0;
    for(unsigned z = 0; z < size; z++)
        for(unsigned y = 0; y < size; y++)
            for(unsigned x = 0; x < size; x++)
            {
                float dx = x-sX;
                float dy = y-sY;
                float dz = z-sZ;
                float dist = sqrt(dx*dx + dy*dy + dz*dz);
                if(dist < r)
                    _nodes[i] = MAZE_OCCUPIED;
                i++;
            }
}

