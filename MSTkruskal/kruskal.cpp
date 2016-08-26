#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace GraphStructure {

struct Vertex {
    char name;
    Vertex* previous;
    int color;

    Vertex(char Vname)
        : name(Vname)
    {
    }
};

struct Edge {
    Vertex firstVertex;
    Vertex secondVertex;
    // minimum weighted spanning forest
    int weight;
    Edge(Vertex V1, Vertex V2, int w)
        : firstVertex(V1)
        , secondVertex(V2)
        , weight(w)
    {
    }
};

struct Graph {
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
};

// GraphStructure
}

namespace DisjointSet {
// pseudocode directly from cormen
// I want to keep all thing public
// here I am not thinking about software security
struct DisjointSetForest {
    // store the reference of parents
    std::unordered_map<char, char> parent;
    // used for better performance
    // flatening the forest
    std::unordered_map<char, int> rank;

    void makeSet(char x)
    {
        parent[x] = x;
        rank[x] = 0;
    }

    // path compression
    char findSet(char x)
    {
        if (x != parent[x]) {
            parent[x] = findSet(parent[x]);
        }

        return parent[x];
    }

    void link(char x, char y)
    {
        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else {
            parent[x] = y;

            if (rank[x] == rank[y]) {
                rank[y]++;
            }
        }
    }

    // union by rank
    void doUnion(char x, char y)
    {
        link(findSet(x), findSet(y));
    }
};
// DisjointSet namespace end
}

namespace MST {

void Kruskal(GraphStructure::Graph& G)
{
    std::vector<GraphStructure::Edge> A;

    DisjointSet::DisjointSetForest forest;

    // make single vertex disjoint
    for (auto it : G.vertices) {
        forest.makeSet(it.name);
    }

    // sort the edge accoring to weight
    std::sort(G.edges.begin(), G.edges.end(),
        [](auto x, auto y) { return x.weight < y.weight; });

    for (GraphStructure::Edge e : G.edges) {
        char first = forest.findSet(e.firstVertex.name);
        char second = forest.findSet(e.secondVertex.name);

        // vertex are in different tree
        if (first != second) {
            A.push_back(e);
            forest.doUnion(first, second);
        }
    }

    for (GraphStructure::Edge e : A) {
        std::cout << e.firstVertex.name << " --- " << e.secondVertex.name
                  << " " << e.weight << std::endl;
    }
}
}

int main(void)
{
    GraphStructure::Graph G;

    GraphStructure::Vertex v1('A');
    GraphStructure::Vertex v2('B');
    GraphStructure::Vertex v3('C');
    GraphStructure::Vertex v4('D');
    GraphStructure::Vertex v5('E');
    GraphStructure::Vertex v6('F');

    std::vector<GraphStructure::Vertex> allVertex{
        v1, v2, v3, v4, v4, v5
    };

    for (auto v : allVertex) {
        G.vertices.push_back(v);
    }

    // std::cout << G.vertices.size() << std::endl;

    G.edges.push_back(GraphStructure::Edge(v1, v2, 4));
    G.edges.push_back(GraphStructure::Edge(v1, v6, 2));
    G.edges.push_back(GraphStructure::Edge(v6, v2, 5));
    G.edges.push_back(GraphStructure::Edge(v3, v2, 6));
    G.edges.push_back(GraphStructure::Edge(v3, v6, 1));
    G.edges.push_back(GraphStructure::Edge(v6, v5, 4));
    G.edges.push_back(GraphStructure::Edge(v4, v5, 2));
    G.edges.push_back(GraphStructure::Edge(v4, v3, 3));

    MST::Kruskal(G);
}
