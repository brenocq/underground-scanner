#include <iostream>
#include <vector>
#include <stdlib.h>
#include "maze.hpp"

using namespace std;

string nodeToString(Node node)
{
    string str;
    str = "(" + to_string(node.val[0]) + ", " + to_string(node.val[1]) + ", " + to_string(node.val[2]) + ")";
    return str;
}

GraphNode::GraphNode(Node val, int group)
{
    value = val;
    set = group;
}

DisjointSet::DisjointSet(vector<Node> nodes)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        GraphNode node = GraphNode(nodes[i], i);
        nodeMapping.insert(pair<string, GraphNode>(nodeToString(node.value), node));
    }
}

void DisjointSet::joinSets(Node node1, Node node2)
{
    string str1 = nodeToString(node1);
    string str2 = nodeToString(node2);
    if (nodeMapping.at(str1).set != nodeMapping.at(str2).set)
    {
        nodeMapping.at(str1).set = nodeMapping.at(str2).set;
    }
};

Maze::Maze(int size)
{

    graphSize = size;

    // Gera os nós do grafo
    for (int i = 0; i < graphSize; i++)
    {
        for (int j = 0; j < graphSize; j++)
        {
            for (int k = 0; k < graphSize; k++)
            {
                Node aux;
                aux.val = {i, j, k};
                nodes.push_back(aux);
            }
        }
    }
    generateMaze();
}

void Maze::generateMaze()
{
    //Gera todas as arestas do grafo
    vector<Edge> allEdges;
    for (int i = 0; i < nodes.size(); i++)
    {
        vector<Node> neighbours = getNeighbours(nodes[i]);
        for (int j = 0; j < neighbours.size(); j++)
        {
            Edge edge;
            edge.n1 = nodes[i];
            edge.n2 = neighbours[j];
            allEdges.push_back(edge);
        }
    }
    DisjointSet ds = DisjointSet(nodes);
    while (edges.size() < (nodes.size() - 1))
    {
        Edge edge;
        int randIndex = rand() % (allEdges.size());
        edge = allEdges[randIndex];
        allEdges.erase(allEdges.begin() + randIndex);
        if (ds.nodeMapping.at(nodeToString(edge.n1)).set != ds.nodeMapping.at(nodeToString(edge.n2)).set)
        {
            ds.joinSets(edge.n1, edge.n2);
            edges.push_back(edge);
        }
    }
}

vector<Node> Maze::getNeighbours(Node node)
{
    vector<Node> neighbours;
    vector<vector<int>> pos = {{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};
    for (int i = 0; i < pos.size(); i++)
    {
        if (node.val[0] + pos[i][0] >= 0 && node.val[0] + pos[i][0] < graphSize && node.val[1] + pos[i][1] >= 0 && node.val[1] + pos[i][1] < graphSize && node.val[2] + pos[i][2] >= 0 and node.val[2] + pos[i][2] < graphSize)
        {
            Node aux;
            for (int j = 0; j < 3; j++)
            {
                aux.val.push_back(node.val[j] + pos[i][j]);
            }
            neighbours.push_back(aux);
        }
    }
    return neighbours;
}

// Debug
int main()
{
    Maze maze = Maze(7);
    printf("%ld\n", maze.edges.size());
}