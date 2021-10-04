FILES_IMGUI_ = imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_widgets.cpp imgui_tables.cpp imgui_impl_glfw.cpp imgui_impl_opengl3.cpp
FILES_IMGUI =$(patsubst %, extern/imgui/%, ${FILES_IMGUI_})
FILES_GFX = graphics/graphics.cpp graphics/shader.cpp graphics/camera.cpp graphics/userInterface.cpp

run:
	g++ main.cpp maze.cpp ${FILES_GFX} extern/glad/glad.c ${FILES_IMGUI} -lglfw -lGL -lX11 -lXrandr -lXi -ldl -I. -I./extern/ -g -Wall -o maze
	./maze
