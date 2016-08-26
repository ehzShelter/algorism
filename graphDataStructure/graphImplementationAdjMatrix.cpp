#include <iostream>
#include <new>
#include <queue>
#include <stack>
#include <limits>

enum visit {
    UNDISCOVERED,
    DISCOVERED,
    PROCESSED
};

enum noInfo {
    NOPARENT = -1,
    NOLevelInfo = -1,
    NOTIME = -1,
    INFINITY = -1
};

class Graph {
private:
    bool** adjMatrix;
    int vertexCount;

    // below attributes for bfs
    int* state;
    int* parent;
    int* level;

    // dfs attributes for dfs
    int time;
    int* startTime;
    int* endTime;

public:
    // constructor and destructor
    Graph(int);
    ~Graph();

    // getter and setter
    int getVertexCount();
    int setVertexCount();

    // add edges in both directed and undirected Graph
    void addEdgeUndirected(int, int);
    void addEdgeDirected(int, int);

    // remove edges in both directed and undirected Graph
    void removeEdgeUndirected(int, int);
    void removeEdgeDirected(int, int);

    bool isEdge(int, int);

    // displaying Graph
    void display();
    void initializeState();

    void showStateInfo();
    void showParentInfo();
    // specific to BFS
    void showLevelInfo();

    // Specific to DFS
    void showStartEndTime();

    // DFS algorithm
    // Stack Based ALgorithm
    // using Stack
    // visitDFS(explore the Graph recursively Adjacent to that node)
    // DFS(explore the Whole Graph like Maze)
    void visitDFS(int);
    void DFS();

    void showPath(int, int);
    // BFS
    void BFS(int);
};

void Graph::BFS(int s)
{
    std::cout << " BFS: " << std::endl;
    initializeState();

    state[s] = DISCOVERED;

    std::queue<int> Q;
    Q.push(s);

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        std::cout << v << " ";

        for (int i = 0; i < this->vertexCount; i++) {
            if (isEdge(v, i) && state[i] == UNDISCOVERED)
            {
                state[i] = DISCOVERED;
                Q.push(i);
            }
        }
        state[v] = PROCESSED;
    }
}

void Graph::showPath(int from, int target)
{
    if (from == target) {
        return;
    } else if (this->parent[target] == -1) {
        std::cout << "No paths " << std::endl;
    } else {
        this->showPath(from, this->parent[target]);
        std::cout << this->parent[target] << " ";
    }
}

void Graph::showStartEndTime()
{
    for (int i = 0; i < this->vertexCount; i++) {
        std::cout << "Node : " << i << " --- "
                  << "startTime " << this->startTime[i] << "\t"
                  << "endTime " << this->endTime[i]
                  << std::endl;
    }
}

Graph::Graph(int vertexCount)
{
    this->vertexCount = vertexCount;

    // must needed for DFS
    this->time = 0;
    this->state = new int[vertexCount];
    this->parent = new int[vertexCount];

    // for BFS
    this->level = new int[vertexCount];

    // for DFS
    this->startTime = new int[vertexCount];
    this->endTime = new int[vertexCount];
    // pointer to bool which is allocated in heap
    // pointer to pointer
    adjMatrix = new bool*[vertexCount];

    for (int i = 0; i < this->vertexCount; i++) {
        adjMatrix[i] = new bool[vertexCount];
        for (int j = 0; j < vertexCount; j++) {
            adjMatrix[i][j] = false;
        }
    }
}

void Graph::visitDFS(int startNode)
{
    std::cout << startNode << "\t";
    this->state[startNode] = DISCOVERED;
    this->time = this->time + 1;

    this->startTime[startNode] = this->time;

    // GO as long as it can from its adjVertex

    for (int i = 0; i < this->vertexCount; i++) {
        if (this->isEdge(startNode, i) && this->state[i] == UNDISCOVERED) {
            this->parent[i] = startNode;
            // recursively find all node
            visitDFS(i);
        }
    }

    this->state[startNode] = PROCESSED;
    this->time = this->time + 1;
    this->endTime[startNode] = this->time;
}

void Graph::DFS()
{
    std::cout << "star DFS..\n";

    initializeState();

    for (int i = 0; i < this->vertexCount; i++) {
        if (this->state[i] == UNDISCOVERED) {
            visitDFS(i);
        }
    }

    std::cout << std::endl;
}

// destructor
// free allocated memory
Graph::~Graph()
{
    delete (this->state);
    delete (this->parent);
    delete (this->level);
    delete (this->startTime);
    delete (this->endTime);

    for (int i = 0; i < vertexCount; i++) {
        delete[] adjMatrix[i];
    }

    delete[] adjMatrix;
}

void Graph::initializeState()
{
    for (int i = 0; i < this->vertexCount; i++) {
        this->state[i] = UNDISCOVERED;
        this->parent[i] = NOPARENT;
        this->level[i] = NOLevelInfo;
        this->startTime[i] = -1;
        this->endTime[i] = -1;
    }
}

void Graph::showLevelInfo()
{
    std::cout << "Graph Level Info...\n";
    for (int i = 0; i < this->vertexCount; i++) {
        std::cout << "Node " << i << "\tNode Level: " << this->level[i] << "\n";
    }
}
void Graph::showParentInfo()
{
    std::cout << "Graph Parent Info...\n";
    for (int i = 0; i < this->vertexCount; i++) {
        std::cout << "Node " << i << "\tits Parent pointer: " << this->parent[i] << "\n";
    }
}
void Graph::showStateInfo()
{
    std::cout << "Graph State Info...\n";
    for (int i = 0; i < this->vertexCount; i++) {
        std::cout << "Node " << i << "\tNode State: " << this->state[i] << "\n";
    }
}
int Graph::getVertexCount()
{
    return this->vertexCount;
}
void Graph::addEdgeUndirected(int i, int j)
{
    if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount) {
        adjMatrix[i][j] = true;
        adjMatrix[j][i] = true;
    }
}
void Graph::addEdgeDirected(int i, int j)
{
    if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount) {
        adjMatrix[i][j] = true;
    }
}
void Graph::removeEdgeUndirected(int i, int j)
{
    if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount) {
        adjMatrix[i][j] = false;
        adjMatrix[j][i] = false;
    }
}
void Graph::removeEdgeDirected(int i, int j)
{
    if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount) {
        adjMatrix[i][j] = false;
    }
}
bool Graph::isEdge(int i, int j)
{
    if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount)
        // this is actually return true
        return adjMatrix[i][j];
    else {
        std::cout << "Invalid vertex number.\n";
        return false;
    }
}
void Graph::display()
{
    int u, v; // vertex
    std::cout << "\t   ";
    for (u = 0; u < vertexCount; u++) {
        std::cout << u << " ";
    }
    for (u = 0; u < vertexCount; u++) {
        std::cout << "\nadj[" << (char)(u + 48) << "] -> ";
        for (v = 0; v < vertexCount; ++v) {
            std::cout << " " << adjMatrix[u][v];
        }
    }
    std::cout << "\n\n";
}

int main(void)
{
    Graph g(6);
    g.initializeState();

    g.addEdgeDirected(0, 1);
    g.addEdgeDirected(0, 3);
    g.addEdgeDirected(1, 2);
    g.addEdgeDirected(2, 3);
    g.addEdgeDirected(3, 1);
    g.addEdgeDirected(4, 2);
    g.addEdgeDirected(4, 5);
    g.addEdgeDirected(5, 5);

    // displaying the adjMatrix
    g.display();

    g.DFS();
    g.showStartEndTime();
    g.showParentInfo();
    g.showPath(1, 3);
    g.BFS(1);
}
