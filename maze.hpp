#ifndef __MAZE
#define __MAZE

#include <iostream>
#include <list>
using namespace std;

struct Node {
    int x;
    int y;
    int z;
};

class Maze {
    private:
        int graphSize;
        list<Node> nodes;

    
    public:   
        // Construtor da classe, que gera proceduralmente o labirinto 3D
        Maze(int size);
};

#endif