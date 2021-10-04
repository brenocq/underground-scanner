#include "maze.hpp"
#include "graphics/graphics.hpp"

int main()
{
    Maze maze(7);
	Graphics gfx(maze);
	gfx.run();

	return 0;
}
