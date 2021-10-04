#ifndef __GRAPHICS
#define __GRAPHICS
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>// Glfw para criar janela
#include "glad/glad.h"// Glad para usar funções do OpenGL
#include "maze.hpp"
#include "graphics/shader.hpp"

class Graphics
{
public:
	Graphics(const Maze& maze);
	~Graphics();

	void run();

private:
	void initGlfw();
	void initOpenGL();
	void createVAOs();

	void render();

	const Maze& _maze;

	// Window
	unsigned _width;
	unsigned _height;
	GLFWwindow* _window;

	struct Point
	{
		float x;
		float y;
		float z;
	};

	struct Line
	{
		Point p0;
		Point p1;
	};

	// OpenGL
	Shader* _shader;
	unsigned _pointVAO;
	unsigned _lineVAO;
	std::vector<Point> _points;
	std::vector<Line> _lines;
};

#endif
