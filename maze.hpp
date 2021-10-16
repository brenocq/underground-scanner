#ifndef __MAZE
#define __MAZE

#include <vector>
#include <queue>
#include <stdint.h>

#define MAZE_FREE 0x00
#define MAZE_OCCUPIED 0x01
#define MAZE_VISITED 0x02
#define MAZE_FRONTIER 0x04
#define MAZE_CURRENT 0x08

class Maze
{
public:

    struct Pos
    {
        int x, y, z;
        float a_star_h; // Euclidian distance to target
        float a_star_g; // Distance walked from start
    };

    enum class Search {
        BFS = 0,
        ASTAR
    };

    Maze(unsigned size_);

    //---------- Generation ----------//
    void resize(unsigned newSize);
    void generateMaze();

    //---------- Search ----------//
    void initSearch();
    void iterSearch();

    //---------- Getters and setters ----------//
    Search getSearch() const { return _search; }
    void setSearch(Search search);
    bool setTarget(int x, int y, int z);
    bool setStart(int x, int y, int z);
    Pos getStart() const { return _start; }
    Pos getTarget() const { return _target; }
    uint8_t getNode(int x, int y, int z);
    void setNode(int x, int y, int z, uint8_t value);
    unsigned getIteration() const { return _iteration; }
    unsigned getNumVisited() const { return _numVisited; }
    unsigned getNumFrontier() const { return _numFrontier; }

    unsigned size;
private:
    void initBFS();
    void iterBFS();
    void initAstar();
    void iterAstar();

    // Set nodes as occupied
    void occupySphere(float radius, float x, float y, float z);
    void clearMazeSearch();
    void tryInsertBFS(int x, int y, int z);
    void tryInsertAStar(Pos last, Pos a);
    bool checkFound(Pos p);
    void updateNumFrontierVisible();

    Search _search;// Current type of search
    bool _found;// If found the target (stop iterations)
    std::vector<uint8_t> _nodes;// All world nodes
    Pos _start, _target, _cur_search;

    // Statistics
    unsigned _iteration;
    unsigned _numVisited;
    unsigned _numFrontier;

    //----- BFS auxiliars -----//
    std::queue<Pos> _bfs_queue;

    //----- A* auxiliars -----//
    struct AStarHeuristic
    {
    	bool operator()(const Pos& a, const Pos& b)
        {
            // Reverse the comparision so the pqueue returns
            // the lowest value.
            return (a.a_star_g + a.a_star_h) > (b.a_star_g + b.a_star_h);
        }
    };
    int _a_star_dist_from_start;
    std::priority_queue<Pos, std::vector<Pos>, AStarHeuristic> _a_star_queue;
};
#endif

