#ifndef __MAZE
#define __MAZE
#include <vector>

struct Node
{
	float x;
	float y;
	float z;
};

struct Edge
{
    Node* n1;
    Node* n2;
};

class Maze
{
public:
    // Construtor da classe que gera o conjunto de nós
    Maze(int size);

private:
    // Função que gera proceduralmente o labirinto 3D
    void generateMaze();

	int graphSize;
	std::vector<Node> nodes;
    std::vector<Edge> edges;
    //DisjointSet ds;
	//std::vector<Node> getNeighbours(Node node);
	
};

//class DisjointSet
//{
//public:
//    map<Node, GraphNode> nodeMapping = {};
//    DisjointSet(vector<Node> nodes);
//    void joinSets(Node node1, Node node2);
//};

//class GraphNode
//{
//public:
//    Node value;
//    int set;
//    GraphNode(Node value, int group);
//};

#endif
