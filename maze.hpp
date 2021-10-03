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

string nodeToString(Node node)
{
    string str;
    str = "(" + to_string(node.val[0]) + ", " + to_string(node.val[1]) + ", " + to_string(node.val[2]) + ")";
    return str;
}

struct Edge
{
    Node n1;
    Node n2;
};

class GraphNode
{
public:
    Node value;
    int set;

    GraphNode(Node val, int group)
    {
        value = val;
        set = group;
    }
};

class DisjointSet
{
public:
    map<string, GraphNode> nodeMapping;

    DisjointSet(vector<Node> nodes)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            GraphNode node = GraphNode(nodes[i], i);
            nodeMapping.insert(pair<string, GraphNode>(nodeToString(node.value), node));
        }
    };

    void joinSets(Node node1, Node node2)
    {
        string str1 = nodeToString(node1);
        string str2 = nodeToString(node2);
        if (nodeMapping.at(str1).set != nodeMapping.at(str2).set)
        {
            nodeMapping.at(str1).set = nodeMapping.at(str2).set;
        }
    };
};

class Maze
{
private:
    int graphSize;
    vector<Node> nodes;
    vector<Edge> edges;
    vector<Node> getNeighbours(Node node);

public:
    // Construtor da classe que gera o conjunto de nós
    Maze(int size);
    // Função que gera proceduralmente o labirinto 3D
    void generateMaze();
};

#endif