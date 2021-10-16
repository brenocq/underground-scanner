#include "maze.hpp"
#include "graphics/graphics.hpp"

int main()
{
    srand(40);
    Maze maze(30);
	Graphics gfx(maze);
	gfx.run();

	return 0;
}
