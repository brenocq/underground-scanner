#include "graphics/userInterface.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// ImGui backends
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>
// Time for search animation
#include <ctime>

UserInterface::UserInterface(Maze& maze):
    _maze(maze)
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
    // Start render
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Render
    {
        static bool open = true;
        //ImGui::ShowDemoWindow(&open);
        if(firstTime)
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(300, 300));
        }
        ImGui::Begin("Control", &open);
        {
            ImGui::Text("To control the camera:");
            ImGui::BulletText("While pressing the mouse wheel");
            ImGui::BulletText("Rotate the camera using the mouse");
            ImGui::BulletText("Move the camera using AWSD");
            ImGui::Separator();
            mazeGeneration();
            ImGui::Separator();
            searchControl();
        }
        ImGui::End();
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
    Maze::Pos target = _maze.getStart();
    int targetX = target.x;
    int targetY = target.y;
    int targetZ = target.z;
    targetChanged |= ImGui::DragInt("X##TargetX", &targetX, 0.5f, 0, mazeSize-1, "%d");
    targetChanged |= ImGui::DragInt("Y##TargetY", &targetY, 0.5f, 0, mazeSize-1, "%d");
    targetChanged |= ImGui::DragInt("Z##TargetZ", &targetZ, 0.5f, 0, mazeSize-1, "%d");

    if(ImGui::Button("Regenerate"))
        _maze.generateMaze();

    // Check if need to update start/goal positions
    if(startChanged || targetChanged)
    {
        _maze.setStart(startX, startY, startZ);
        _maze.setTarget(targetX, targetY, targetZ);
        _maze.initSearch();
    }

    // Resize and regenerate maze
    if(sizeChanged)
        _maze.resize(mazeSize);
}

void UserInterface::searchControl()
{
    static bool play = false;
    ImGui::Text("Search control");

    // Select search combo box
    const char* typesOfSearch[] = { "BFS (Blind search)", "A* (Guided search)" };
    static int selected = 0;
    ImGui::Combo("Type", &selected, typesOfSearch, IM_ARRAYSIZE(typesOfSearch));

    // Buttons
    if(ImGui::Button("Reset"))
        _maze.initSearch();
    
    ImGui::SameLine();
    if(ImGui::Button("Play"))
        play = true;

    ImGui::SameLine();
    if(ImGui::Button("Stop"))
        play = false;

    ImGui::SameLine();
    if(ImGui::Button("Next"))
	    _maze.iterSearch();

    if(play)
    {
        // Execute graphics update every X seconds
        static clock_t lastTime = std::clock();
        const clock_t currTime = std::clock();
        float timeDiff = float(currTime-lastTime)/CLOCKS_PER_SEC;
        if(timeDiff > 0.1f)
        {
	        _maze.iterSearch();
            lastTime = currTime;
        }
    }
}