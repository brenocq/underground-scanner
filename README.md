# underground-scanner

Underground Scanner is a visualization program for search algorithms. (Developed as an assignment for SCC)

The main concept is that a drone needs to navigate from a starting point to a target point in an underground mine. Will it be able do to it? How can we achieve that?

To do so, given that the drone is provided with a map of the mine, the drone will run search algorithms to find a path to the target point.

The currently implemented search algorithms are A* and BFS to find the minimum distance between two points on 3d grid.

## Screenshots and demos

TODO

## Installation

### Ubuntu
```
sudo apt-get update
sudo apt-get install mesa-utils libglfw3-dev libglm-dev
```
### Arch
```
sudo pacman -Sy glfw-x11 glm
```

## Running
```
cd underground-scanner
make run
```
