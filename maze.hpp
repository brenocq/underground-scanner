#ifndef __MAZE
#define __MAZE
#include <vector>
#include <stdint.h>

#define MAZE_OCCUPIED 0x01
#define MAZE_SEARCH 0x02

class Maze
{
public:
    // Create cube matrix of specified size
    Maze(unsigned size);

    uint8_t getNode(int x, int y, int z);

    unsigned _size;
private:
    // Set nodes as occupied
    void generateMaze();
    void occupySphere(float radius, float x, float y, float z);

    std::vector<uint8_t> _nodes;
};
#endif
