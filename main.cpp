#include "maze.hpp"
#include "graphics/graphics.hpp"

int main()
{
    Maze maze(10);
	Graphics gfx(maze);
	gfx.run();

	return 0;
}
