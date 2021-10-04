#ifndef __MAZE
#define __MAZE
#include <vector>

class Maze
{
public:
    // Create cube matrix of specified size
    Maze(unsigned size);

private:
	// Set nodes as occupied
    void generateMaze();
    void occupySphere(float radius, float x, float y, float z);

	unsigned _size;
	std::vector<bool> _nodes;
};
#endif
