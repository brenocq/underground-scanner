run:
	g++ main.cpp maze.cpp graphics/graphics.cpp graphics/shader.cpp glad/glad.c -lglfw -lGL -lX11 -lXrandr -lXi -ldl -I. -g -Wall -o maze
	./maze
