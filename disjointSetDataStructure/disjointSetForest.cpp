#include <iostream>
#include <unordered_map>

// pseudocode directly from cormen
struct DisjointSetForest {
    // store the reference of parents
    std::unordered_map<char, char> parent;
    // used for better performance
    // flatening the tree
    std::unordered_map<char, int> rank;

public:
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
    void unionSets(char x, char y)
    {
        link(findSet(x), findSet(y));
    }
};

void testDisJointSet(DisjointSetForest& DS)
{
    DS.makeSet('a');
    DS.makeSet('b');
    DS.makeSet('c');
    DS.makeSet('d');
    DS.makeSet('e');
    DS.makeSet('f');

    DS.unionSets('a', 'b');
    DS.unionSets('e', 'f');


    std::cout << DS.findSet('a') << std::endl;

    DS.unionSets('a', 'e');

    std::cout << DS.findSet('a') << std::endl;
}

int main(void)
{
    DisjointSetForest DS;
    testDisJointSet(DS);
}
