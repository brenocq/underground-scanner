#include "maze.hpp"
#include <math.h>
#include <stdio.h>
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

void Maze::setTarget(int x, int y, int z)
{
    _target = {x, y, z};
}

void Maze::setStart(int x, int y, int z)
{
    _start = {x, y, z};
}

void Maze::initBFS()
{
    found = false;
    _bfs_search = _start;
    _bfs_queue.push(_bfs_search);
}

void Maze::beginIterBFS()
{
    if (found) return;

    Pos next_node = _bfs_queue.front();

    int x = next_node.x;
    int y = next_node.y;
    int z = next_node.z;

    printf("searching %d %d %d", x, y, z);

    _nodes[x + y * size + z * (size * size)] = MAZE_SEARCH;

    // Fill queue with adjacent nodes
    for (int i = x-1 ; i <= x+1 ; ++i)
    for (int j = y-1 ; j <= y+1 ; ++j)
    for (int k = z-1 ; i <= z+1 ; ++k)
    {
	tryInsertBFS(i, j, k);
    }
}

void Maze::tryInsertBFS(int x, int y, int z)
{
    // Check bounds
    if (x >= 0 && x < size &&
	y >= 0 && y < size &&
        z >= 0 && z < size)

    if (!(getNode(x,y,z) & (MAZE_VISITED | MAZE_OCCUPIED)))
    {
	_bfs_queue.push({x, y, z});
	printf("Inserted %d %d %d", x, y, z);
    }
}

void Maze::endIterBFS()
{
    Pos next_node = _bfs_queue.front();
    _bfs_queue.pop();

    int x = next_node.x;
    int y = next_node.y;
    int z = next_node.z;

    _nodes[x + y * size + z * (size * size)] = MAZE_VISITED;

    // If target, return
    if (x == _target.x &&
	y == _target.y &&
	z == _target.z)
	found = true;
}

void Maze::initAstar()
{

}

void Maze::iterAstar()
{

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

