#ifndef __MAZE
#define __MAZE

#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Node
{
    vector<int> val = {};
};

struct Edge
{
    Node n1;
    Node n2;
};

class Maze
{
private:
    int graphSize;
    vector<Node> nodes;
    vector<Edge> edges;
    DisjointSet ds;
    vector<Node> getNeighbours(Node node);

public:
    // Construtor da classe que gera o conjunto de nós
    Maze(int size);
    // Função que gera proceduralmente o labirinto 3D
    void generateMaze();
};

class DisjointSet
{
public:
    map<Node, GraphNode> nodeMapping = {};
    DisjointSet(vector<Node> nodes);
    void joinSets(Node node1, Node node2);
};

class GraphNode
{
public:
    Node value;
    int set;
    GraphNode(Node value, int group);
};

#endif