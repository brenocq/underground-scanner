#ifndef __GRAPHICS
#define __GRAPHICS
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>// Glfw para criar janela
#include "glad/glad.h"// Glad para usar funções do OpenGL
#include "maze.hpp"
#include "graphics/shader.hpp"
#include "graphics/userInterface.hpp"
#include "camera.hpp"

class Graphics
{
public:
    Graphics(Maze& maze);
    ~Graphics();

    void run();

private:
    void initGlfw();
    void initOpenGL();
    void createVAOs();

    void render();

    Maze& _maze;

    // Window
    unsigned _width;
    unsigned _height;
    GLFWwindow* _window;
    bool _moveWithMouse;

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
    Camera _camera;
    Shader* _maze_shader;
    UserInterface* _ui;
    unsigned _pointVAO;
    unsigned _lineVAO;
    unsigned _cubeVAO;

    std::vector<Point> _points;
    std::vector<Line> _lines;
};

#endif
