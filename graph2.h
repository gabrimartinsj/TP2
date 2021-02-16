#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Data structure to store a graph edge
struct Edge {
    int src, dest, weight;
};

// A class to represent a disjoint set
class DisjointSet
{
    unordered_map<int, int> parent;
public:
    // perform MakeSet operation
    void makeSet(int N)
    {
        // create `N` disjoint sets (one for each vertex)
        for (int i = 0; i < N; i++) {
            parent[i] = i;
        }
    }

    // Find the root of the set in which element `k` belongs
    int Find(int k)
    {
        // if `k` is root
        if (parent[k] == k) {
            return k;
        }

        // recur for the parent until we find the root
        return Find(parent[k]);
    }

    // Perform Union of two subsets
    void Union(int a, int b)
    {
        // find the root of the sets in which elements
        // `x` and `y` belongs
        int x = Find(a);
        int y = Find(b);

        parent[x] = y;
    }
};

// Function to construct MST using Kruskal’s algorithm
vector<Edge> KruskalAlgo(vector<Edge> edges, int N)
{
    // stores the edges present in MST
    vector<Edge> MST;

    // initialize `DisjointSet` class
    DisjointSet ds;

    // create a singleton set for each element of the universe
    ds.makeSet(N);

    // MST contains exactly `V-1` edges
    while (MST.size() != N - 1)
    {
        // consider the next edge with minimum weight from the graph
        Edge next_edge = edges.back();
        edges.pop_back();

        // find the root of the sets to which two endpoints
        // vertices of the next edge belongs
        int x = ds.Find(next_edge.src);
        int y = ds.Find(next_edge.dest);

        // if both endpoints have different parents, they belong to
        // different connected components and can be included in MST
        if (x != y)
        {
            MST.push_back(next_edge);
            ds.Union(x, y);
        }
    }
    return MST;
}

// Comparison object to be used to order the edges
struct compare
{
    inline bool operator() (Edge const &a, Edge const &b)
    {
        return (a.weight > b.weight);
    }
};

int main()
{
    // vector of graph edges as per the above diagram.
    vector<Edge> edges =
    {
        // `(u, v, w)` triplet represent undirected edge from
        // vertex `u` to vertex `v` having weight `w`
        { 0, 1, 25000 }, { 0, 2, 25000 }, { 0, 3, 25000 }, { 1, 2, 25000 },
        { 1, 3, 25000 }, { 2, 3, 25000 }
    };

    // sort edges by increasing weight
    sort(edges.begin(), edges.end(), compare());

    // total number of nodes in the graph
    int N = 4;

    // construct graph
    vector<Edge> e = KruskalAlgo(edges, N);

    for (Edge &edge: e)
        cout << "(" << edge.src << ", " << edge.dest << ", "
            << edge.weight << ")" << endl;

    return 0;
}
