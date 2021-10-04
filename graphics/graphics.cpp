#include "graphics/graphics.hpp"
#include "camera.hpp"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Graphics::Graphics(Maze& maze):
    _maze(maze), _width(900), _height(900)
{
    initGlfw();
    initOpenGL();

    _shader = new Shader("graphics/shaders/shader.vert", "graphics/shaders/shader.frag");
    _maze_shader = new Shader("graphics/shaders/maze_shader.vert", "graphics/shaders/shader.frag");

    _lines.push_back({{0,0,0}, {1,1,1}});
    _lines.push_back({{1,1,1}, {1,1,0}});
    _points.push_back({0,0,0});
    _points.push_back({1,1,1});

    createVAOs();
    _ui.init();
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
        _ui.render();

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
	Graphics *gptr = (Graphics*) glfwGetWindowUserPointer(window);

        if(key == 'N' && action != GLFW_RELEASE)
        {
            std::cout << "N pressed\n";
        }

	if(key == 'W' && action != GLFW_RELEASE)
        {
	    gptr->_camera.rotateDirection(0.1f, true);
        }

        if(key == 'S' && action != GLFW_RELEASE)
        {
	    gptr->_camera.rotateDirection(-0.1f, true);
        }

        if(key == 'A' && action != GLFW_RELEASE)
        {
	    gptr->_camera.rotateDirection(0.1f, false);
        }

        if(key == 'D' && action != GLFW_RELEASE)
        {
	    gptr->_camera.rotateDirection(-0.1f, false);
        }

        if(key == 'Q' && action != GLFW_RELEASE)
        {
	    gptr->_camera.zoom(0.1f);
        }

        if(key == 'E' && action != GLFW_RELEASE)
        {
	    gptr->_camera.zoom(-0.1f);
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	//----- Create cube VAO -----//
    float cubeVertexData[] = {
	    -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
	};

	glGenVertexArrays(1, &_cubeVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(_cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexData), cubeVertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind objects
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 
}

void Graphics::render()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shader->bind();

    // Draw lines
    glBindVertexArray(_lineVAO);
    glDrawArrays(GL_LINES, 0, _lines.size()*2);

    // Draw points
    glBindVertexArray(_pointVAO);
    glDrawArrays(GL_POINTS, 0, _points.size());

    _maze_shader->bind();

    // Rendering labyrinth
    for (uint32_t z = 0 ; z < _maze._size; z++)
    for (uint32_t y = 0 ; y < _maze._size; y++)
    for (uint32_t x = 0 ; x < _maze._size; x++)
    {
	uint8_t a_node = _maze.getNode(x, y, z);

	glm::vec4 color = glm::vec4(0.0, 0.0, 0.0, 0.0);

        // Set color uniform based on vertex info

	if (a_node & MAZE_OCCUPIED) 
	    color = glm::vec4(1.0, 0.0, 0.0, 1.0);

	_maze_shader->setUniformV4("color", color);
        
	// Set model matrix
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3((float)x, (float)y, (float)z));

	glm::mat4 view_projection = _camera.getViewProjectionMatrix();

	_maze_shader->setUniformM4("model", model);
	_maze_shader->setUniformM4("viewProjection", view_projection);

    	// Draw points
	glBindVertexArray(_cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
    }
}

