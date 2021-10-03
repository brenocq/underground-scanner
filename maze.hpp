#ifndef __MAZE
#define __MAZE

#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Node
{
    vector<int> val;
};
// --------------------------------------
struct Edge
{
    Node n1;
    Node n2;
};
// --------------------------------------
string nodeToString(Node node);
// --------------------------------------
class GraphNode
{
public:
    Node value;
    int set;
    GraphNode(Node val, int group);
};
// --------------------------------------
class DisjointSet
{
public:
    map<string, GraphNode> nodeMapping;

    DisjointSet(vector<Node> nodes);

    void joinSets(Node node1, Node node2);
};
// --------------------------------------
class Maze
{
private:
    int graphSize;
    vector<Node> nodes;
    vector<Node> getNeighbours(Node node);

public:
    // Arestas do labirinto gerado
    vector<Edge> edges;
    // Construtor da classe que gera o conjunto de nós
    Maze(int size);
    // Função que gera proceduralmente o labirinto 3D
    void generateMaze();
};
// --------------------------------------
#endif