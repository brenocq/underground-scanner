#include "maze.hpp"
#include <math.h>

Maze::Maze(unsigned size):
    _size(size)
{
    _nodes.resize(_size*_size*_size);

    // Set some nodes as occupied
    generateMaze();
}

void Maze::generateMaze()
{
    for(unsigned i = 0; i < _size*_size; i++)
        _nodes[i] = true;

    occupySphere(3, 2, 2, 2);
    occupySphere(2, _size-2, _size-2, _size-2);
}

void Maze::occupySphere(float radius, float x, float y, float z)
{
    // Draw sphere
    float r = radius;// Radius
    float sX = x;// Position x
    float sY = y;// Position y
    float sZ = z;// Position z
    unsigned i = 0;
    for(unsigned z = 0; z < _size; z++)
        for(unsigned y = 0; y < _size; y++)
            for(unsigned x = 0; x < _size; x++)
            {
                float dx = x-sX;
                float dy = y-sY;
                float dz = z-sZ;
                float dist = sqrt(dx*dx + dy*dy + dz*dz);
                if(dist < r)
                    _nodes[i] = true;
                i++;
            }
}
