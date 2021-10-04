#ifndef __MAZE
#define __MAZE

#include <vector>
#include <queue>
#include <stdint.h>

#define MAZE_NONE 0x00
#define MAZE_OCCUPIED 0x01
#define MAZE_SEARCH 0x02
#define MAZE_VISITED 0x04

class Maze
{
public:
    // Create cube matrix of specified size
    Maze(unsigned size_);

    void setTarget(int x, int y, int z);
    void setStart(int x, int y, int z);

    void initBFS();
    void beginIterBFS();
    void endIterBFS();

    void initAstar();
    void iterAstar();

    uint8_t getNode(int x, int y, int z);
    void resize(unsigned newSize);
    void generateMaze();
    unsigned size;

    struct Pos
    {
	int x, y, z;
    };

private:
    // Set nodes as occupied
    void occupySphere(float radius, float x, float y, float z);

    void tryInsertBFS(int x, int y, int z);

    bool found;
    std::vector<uint8_t> _nodes;
    std::queue<Pos> _bfs_queue;
    Pos _start, _target, _bfs_search;
};
#endif

