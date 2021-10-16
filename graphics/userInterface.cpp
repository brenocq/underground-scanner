#include "graphics/userInterface.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
// ImGui backends
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>
// Time for search animation
#include <ctime>

UserInterface::UserInterface(Maze& maze, Camera& camera):
    _maze(maze), _camera(camera)
{

}

void UserInterface::init()
{
    ImGui::CreateContext();

    GLFWwindow* window = glfwGetCurrentContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void UserInterface::render()
{
    static bool firstTime = true;
    static bool automaticCameraRotation = false;
    bool autoCamStateChanged = false;// If automaticCameraRotation was selected/deselected
    // Start render
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Render
    {
        //ImGui::ShowDemoWindow(&open);
        if(firstTime)
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(300, 510));
        }
        ImGui::Begin("Control");
        {
            ImGui::Text("To control the camera:");
            ImGui::BulletText("While pressing the mouse wheel, \nmove the mouse");
            ImGui::BulletText("Zoom in/out using the scroll");
            autoCamStateChanged = ImGui::Checkbox("Automatic rotation", &automaticCameraRotation);
            ImGui::Separator();
            mazeGeneration();
            ImGui::Separator();
            searchControl();
        }
        ImGui::End();

        if(firstTime)
        {
            ImGui::SetNextWindowPos(ImVec2(700, 0));
            ImGui::SetNextWindowSize(ImVec2(200, 200));
        }
        ImGui::Begin("Statistics");
        {
            statistics();
        }
        ImGui::End();

        if(automaticCameraRotation)
        {
            // Move camera
            static clock_t lastTime = std::clock();
            if(autoCamStateChanged) lastTime = std::clock();
            const clock_t currTime = std::clock();
            float timeDiff = float(currTime-lastTime)/CLOCKS_PER_SEC;
            _camera.rotateDirection(timeDiff, false);
            lastTime = currTime;
        }
    }
    // End render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    firstTime = false;
}

void UserInterface::mazeGeneration()
{
    int mazeSize = (int)_maze.size;
    ImGui::Text("Maze generation");
    ImGui::Spacing();
    bool sizeChanged = ImGui::DragInt("Size", &mazeSize, 0.5f, 2, 100, "%d");

    ImGui::Text("Start position");
    bool startChanged = false;
    Maze::Pos start = _maze.getStart();
    int startX = start.x;
    int startY = start.y;
    int startZ = start.z;
    startChanged |= ImGui::DragInt("X##StartX", &startX, 0.5f, 0, mazeSize-1, "%d");
    startChanged |= ImGui::DragInt("Y##StartY", &startY, 0.5f, 0, mazeSize-1, "%d");
    startChanged |= ImGui::DragInt("Z##StartZ", &startZ, 0.5f, 0, mazeSize-1, "%d");

    ImGui::Text("Target position");
    bool targetChanged = false;
    Maze::Pos target = _maze.getTarget();
    int targetX = target.x;
    int targetY = target.y;
    int targetZ = target.z;
    targetChanged |= ImGui::DragInt("X##TargetX", &targetX, 0.5f, 0, mazeSize-1, "%d");
    targetChanged |= ImGui::DragInt("Y##TargetY", &targetY, 0.5f, 0, mazeSize-1, "%d");
    targetChanged |= ImGui::DragInt("Z##TargetZ", &targetZ, 0.5f, 0, mazeSize-1, "%d");

    if(ImGui::Button("Regenerate"))
        _maze.generateMaze();

    static bool rc;
    // Check if need to update start/goal positions
    if(startChanged || targetChanged)
    {
        rc |= _maze.setStart(startX, startY, startZ);
        rc |= _maze.setTarget(targetX, targetY, targetZ);

        _maze.initSearch();
    }

    if (rc)
    {
        static bool err_msg;
        ImGui::Begin("Error", &err_msg);
        ImGui::Text("Could not set Start/Target positions. Probably occupied.");
        if (ImGui::Button("OK!")) rc = false;
        ImGui::End();
    }

    // Resize and regenerate maze
    if(sizeChanged)
    {
        int diff = _maze.size - mazeSize;
        _camera.zoom(diff*2);
        _maze.resize(mazeSize);
    }
}

void UserInterface::searchControl()
{
    static bool play = false;
    static float delay = 0.1f;
    ImGui::Text("Search control");

    // Select search combo box
    const char* typesOfSearch[] = { "BFS (Blind search)", "A* (Guided search)" };
    static int selected = 0;

    if (ImGui::Combo("Type", &selected, typesOfSearch, IM_ARRAYSIZE(typesOfSearch)))
    {
        switch (selected)
        {
	    case 0: _maze.setSearch(Maze::Search::BFS); break;
	    case 1: _maze.setSearch(Maze::Search::ASTAR); break;
        }
    }

    // Buttons
    ImGui::Text("Manual control");
    if(ImGui::Button("Reset"))
        _maze.initSearch();
    ImGui::SameLine();
    if(ImGui::Button("Next"))
	    _maze.iterSearch();
    
    ImGui::Text("Automatic control");
    ImGui::SliderFloat("Delay (sec)", &delay, 0.0001f, 0.2f, "%.4f");
    if(ImGui::Button("Play"))
        play = true;
    ImGui::SameLine();
    if(ImGui::Button("Pause"))
        play = false;

    if(play)
    {
        // Execute graphics update every X seconds
        static clock_t lastTime = std::clock();
        const clock_t currTime = std::clock();
        float timeDiff = float(currTime-lastTime)/CLOCKS_PER_SEC;
        if(timeDiff > delay)
        {
	        _maze.iterSearch();
            lastTime = currTime;
        }
    }
}

void UserInterface::statistics()
{
    ImGui::Text("Iterations: %d", _maze.getIteration());
    ImGui::Text("Visited nodes: %d", _maze.getNumVisited());
    ImGui::Text("Frontier nodes: %d", _maze.getNumFrontier());
}
