#include <iostream>
#include <list>
#include "maze.hpp"

using namespace std;

Maze::Maze(int size){

    graphSize = size;

    // Gera os nós do grafo
    for(int i = 0; i < graphSize; i++) {
        for(int j = 0; j < graphSize; j++) {
            for (int k = 0; k < graphSize; k++){
                Node aux;
                aux.x = i; aux.y = j; aux.z = k;

                nodes.push_back(aux);
            }
        }
    }
}

// Debug
int main(){
    Maze(7);
}