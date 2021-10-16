#include "maze.hpp"
#include <math.h>
#include <queue>
#include <stdio.h>
#include <iostream>
#include <vector>

Maze::Maze(unsigned size_):
    size(size_), _search(Search::BFS), _start({0,0,0}), _target({size_-1,size_-1,size_-1}),
    _iteration(0), _numVisited(0), _numFrontier(0)
{
    resize(size);
    initSearch();
}

bool Maze::setTarget(int x, int y, int z)
{
    if (_nodes[x + y * size + z * (size * size)] & MAZE_OCCUPIED) return true;
    _target = {x, y, z};
    return false;
}

bool Maze::setStart(int x, int y, int z)
{
    if (_nodes[x + y * size + z * (size * size)] & MAZE_OCCUPIED) return true;
    _start = {x, y, z};
    return false;
}

void Maze::setSearch(Search search)
{ 
    _search = search;
    initSearch();
}

uint8_t Maze::getNode(int x, int y, int z)
{
    return _nodes[x + y * size + z * (size * size)];
}

void Maze::setNode(int x, int y, int z, uint8_t value)
{
    _nodes[x + y * size + z * (size * size)] = value;
}

//------------------------------------------------//
//----------------- MAZE GENERATION --------------//
//------------------------------------------------//
void Maze::resize(unsigned newSize)
{
    if(_start.x >= newSize)
        _start.x = newSize;
    if(_start.y >= newSize)
        _start.y = newSize;
    if(_start.z >= newSize)
        _start.z = newSize;

    if(_target.x >= newSize)
        _target.x = newSize;
    if(_target.y >= newSize)
        _target.y = newSize;
    if(_target.z >= newSize)
        _target.z = newSize;

    size = newSize;
    _nodes.resize(size*size*size);
    // Set some nodes as occupied
    generateMaze();
}

void Maze::generateMaze()
{
    for(unsigned i = 0; i < _nodes.size(); i++)
        _nodes[i] = MAZE_FREE;

    for(unsigned i = 0; i < size*size; i++)
        _nodes[i] = MAZE_OCCUPIED;

    for(unsigned i = 0; i < size; i++)
        occupySphere(rand()%size/3, rand()%size, rand()%size, rand()%size);

    // Reset search
    initSearch();
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
                    _nodes[i] |= MAZE_OCCUPIED;
                i++;
            }
}

void Maze::clearMazeSearch()
{
    for(unsigned i = 0; i < size*size*size; i++)
        _nodes[i] &= MAZE_OCCUPIED;
}

//------------------------------------------------//
//-------------------- SEARCH --------------------//
//------------------------------------------------//
void Maze::initSearch()
{
    switch (_search)
    {
        case Search::BFS:
            initBFS();
            break;
        case Search::ASTAR:
            initAstar();
            break;
        default:
            std::cout << "[Maze] Unknown search when trying to initialize" << std::endl;
    }
    _iteration = 0;
}

void Maze::iterSearch()
{
    if (_found) return;
    switch (_search)
    {
        case Search::BFS:
            iterBFS();
            break;
        case Search::ASTAR:
            iterAstar();
            break;
        default:
            std::cout << "[Maze] Unknown search when trying to iterate search" << std::endl;
    }
    _iteration++;
    updateNumFrontierVisible();
}

bool Maze::checkFound(Pos p)
{
    // If target, finish
    if (p.x == _target.x &&
        p.y == _target.y &&
        p.z == _target.z)
        _found = true;
}

//-------------------- BFS --------------------//
void Maze::initBFS()
{
    _found = false;
    _cur_search = _start;
    _bfs_queue = std::queue<Pos>();

    clearMazeSearch();
    setNode(_start.x, _start.y, _start.z, MAZE_CURRENT);
    _bfs_queue.push(_cur_search);
}

void Maze::iterBFS()
{
    if(_bfs_queue.size() == 0)
        return;

    Pos next_node = _bfs_queue.front();
    _bfs_queue.pop();

    int x = next_node.x;
    int y = next_node.y;
    int z = next_node.z;

    // Clear last current
    setNode(_cur_search.x,_cur_search.y,_cur_search.z, MAZE_VISITED);
    // Set new current
    setNode(x,y,z, MAZE_CURRENT|MAZE_VISITED);
    _cur_search = {x,y,z};

    // Fill queue with adjacent nodes
    for (int i = x-1 ; i <= x+1 ; ++i)
        for (int j = y-1 ; j <= y+1 ; ++j)
            for (int k = z-1 ; k <= z+1 ; ++k)
                tryInsertBFS(i, j, k);

    checkFound(next_node);
}

// TODO: change to Pos maybe
void Maze::tryInsertBFS(int x, int y, int z)
{
    // Check bounds
    if (x >= 0 && x < size &&
        y >= 0 && y < size &&
        z >= 0 && z < size)
    {
        if (!(getNode(x,y,z) & (MAZE_VISITED | MAZE_OCCUPIED)))
        {
            setNode(x,y,z, MAZE_FRONTIER|MAZE_VISITED);
            _bfs_queue.push({x, y, z});
        }
    }
}

//-------------------- A* --------------------//
void Maze::initAstar()
{
    _found = false;
    _cur_search = _start;
    _a_star_queue = std::priority_queue<Pos, std::vector<Pos>, AStarHeuristic>();

    clearMazeSearch();
    setNode(_start.x, _start.y, _start.z, MAZE_CURRENT);
    _a_star_queue.push(_cur_search);
}

void Maze::iterAstar()
{
    // Take from pqueue (check if empty and so on)
    if(_a_star_queue.size() == 0)
        return;

    Pos next_node = _a_star_queue.top();

    _a_star_queue.pop();

    int x = next_node.x;
    int y = next_node.y;
    int z = next_node.z;

    // Clear last current
    setNode(_cur_search.x, _cur_search.y, _cur_search.z, MAZE_VISITED);
    
    // Set new current
    setNode(x,y,z, MAZE_CURRENT|MAZE_VISITED);
    _cur_search = {x,y,z};

    // insert nearby elements in the pqueue
    for (int i = x-1 ; i <= x+1 ; ++i)
        for (int j = y-1 ; j <= y+1 ; ++j)
            for (int k = z-1 ; k <= z+1 ; ++k)
                tryInsertAStar(next_node, {i, j, k, 0, next_node.a_star_g });
    checkFound(next_node);

    // check if we are in the target
}

void Maze::tryInsertAStar(Pos last, Pos a)
{
    int x = a.x, y = a.y, z = a.z;

	// Check bounds
	if (x >= 0 && x < size &&
    	    y >= 0 && y < size &&
    	    z >= 0 && z < size &&
	    !(getNode(x,y,z) & (MAZE_VISITED | MAZE_OCCUPIED)))
	{
        // Calculate distance to target
	    float dx = x - _target.x;
	    float dy = y - _target.y;
	    float dz = z - _target.z;
        float distTarget = dx*dx + dy*dy + dz*dz;

        // Calculate distance between nodes
        dx = x - last.x;
        dy = y - last.y;
        dz = z - last.z;
        float distLast = dx*dx + dy*dy + dz*dz;

	    // G is the current G + 1
	    // H is the manhattan distance
	    _a_star_queue.push({x, y, z, distTarget, a.a_star_g + distLast});
	    setNode(x,y,z, MAZE_FRONTIER | MAZE_VISITED);
	}
}

void Maze::updateNumFrontierVisible()
{
    _numVisited = 0;
    _numFrontier = 0;
    for(uint8_t node : _nodes)
    {
       if(node & MAZE_FRONTIER) 
           _numFrontier++;
       else if(node & MAZE_VISITED) 
           _numVisited++;
    }
}
