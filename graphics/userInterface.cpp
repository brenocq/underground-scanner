#include "graphics/userInterface.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// ImGui backends
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>

UserInterface::UserInterface()
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
            ImGui::SetNextWindowSize(ImVec2(300, 900));
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
    static int mazeSize = 7;
    ImGui::Text("Maze generation");
    ImGui::Spacing();
    bool sizeChanged = ImGui::DragInt("Size", &mazeSize, 0.5f, 2, 100, "%d");
    ImGui::Text("Start position");
    static int startX = 0, startY = 0, startZ = 0;
    ImGui::DragInt("X##StartX", &startX, 0.5f, 0, mazeSize-1, "%d");
    ImGui::DragInt("Y##StartY", &startY, 0.5f, 0, mazeSize-1, "%d");
    ImGui::DragInt("Z##StartZ", &startZ, 0.5f, 0, mazeSize-1, "%d");
    ImGui::Text("Goal position");
    static int goalX = mazeSize-1, goalY = mazeSize-1, goalZ = mazeSize-1;
    ImGui::DragInt("X##GoalX", &goalX, 0.5f, 0, mazeSize-1, "%d");
    ImGui::DragInt("Y##GoalY", &goalY, 0.5f, 0, mazeSize-1, "%d");
    ImGui::DragInt("Z##GoalZ", &goalZ, 0.5f, 0, mazeSize-1, "%d");
    ImGui::Button("Generate");

    // Check if need to update start/goal positions
    if(sizeChanged)
    {
        if(startX >= mazeSize)
            startX = mazeSize-1;
        if(startY >= mazeSize)
            startY = mazeSize-1;
        if(startZ >= mazeSize)
            startZ = mazeSize-1;

        if(goalX >= mazeSize)
            goalX = mazeSize-1;
        if(goalY >= mazeSize)
            goalY = mazeSize-1;
        if(goalZ >= mazeSize)
            goalZ = mazeSize-1;
    }
}

void UserInterface::searchControl()
{
    ImGui::Text("Search control");

    // Select search combo box
    const char* typesOfSearch[] = { "Unguided search", "A* (Guided search)" };
    int selected = 0;
    ImGui::Combo("Type", &selected, typesOfSearch, IM_ARRAYSIZE(typesOfSearch));

    // Buttons
    ImGui::Button("Reset");
    ImGui::SameLine();
    ImGui::Button("Advance");
}
