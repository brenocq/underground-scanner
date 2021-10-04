#include "graphics/graphics.hpp"
#include <iostream>

Graphics::Graphics(const Maze& maze):
	_maze(maze), _width(500), _height(500)
{
	initGlfw();
	initOpenGL();

	_shader = new Shader("graphics/shaders/shader.vert", "graphics/shaders/shader.frag");
	_shader->bind();

	_lines.push_back({{0,0,0}, {1,1,1}});
	_lines.push_back({{1,1,1}, {1,1,0}});
	_points.push_back({0,0,0});
	_points.push_back({1,1,1});

	createVAOs();
}

Graphics::~Graphics()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void Graphics::run()
{
	while(!glfwWindowShouldClose(_window))
	{
		render();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void Graphics::initGlfw()
{
	//----- Initialize window and window callbacks -----//
	if(!glfwInit())
	{
		std::cout << "[Graphics] Failed to initialize glfw!" << std::endl;
		exit(0);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Create window
	_window = glfwCreateWindow(_width, _height, "Maze IA", nullptr, nullptr);
	if(!_window)
	{
		std::cout << "[Graphics] Failed to initialize window!" << std::endl;
		glfwTerminate();
		exit(0);
	}

	glfwSetWindowUserPointer(_window, this);
	glfwMakeContextCurrent(_window);

	//---------- Callbacks ----------//
	glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(key == 'N' && action == GLFW_PRESS)
		{
			std::cout << "N pressed\n";
		}
	});
}

void Graphics::initOpenGL()
{
	//----- Initialize OpenGL -----//
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "[Graphics] Failed to initialize glad!" << std::endl;
		exit(0);
	}

	glViewport(0, 0, _width, _height);
	glLineWidth(2.0f);
	glPointSize(10.0f);
}

void Graphics::createVAOs()
{
	unsigned VBO;
	//----- Create line VAO -----//
 	glGenVertexArrays(1, &_lineVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(_lineVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Line)*_lines.size(), _lines.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//----- Create point VAO -----//
 	glGenVertexArrays(1, &_pointVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(_pointVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Point)*_points.size(), _points.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind objects
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 
}

void Graphics::render()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw lines
	glBindVertexArray(_lineVAO);
	glDrawArrays(GL_LINES, 0, _lines.size()*2);

	// Draw points
	glBindVertexArray(_pointVAO);
	glDrawArrays(GL_POINTS, 0, _points.size());
}
