#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pairs;

//structure for graph
struct graph {
    int V, E;
    int *vertexWeight, *vertexRank;
    bool *sum_check;
    vector<pair<int, pairs>> edges;

    graph(int V, int E);

    void addVweight(int v, int vw);
    void addEdge(int u, int v, int w);
    void kruskalMST();
};

graph::graph(int V, int E){
    this->V = V;
    this->E = E;

    vertexWeight = new int[V];
    vertexRank = new int[V];
    sum_check = new bool[V];

    for (int i = 0; i < V; i++){
        vertexRank[i] = 0;
    }

    for (int i = 0; i < V; i++){
        sum_check[i] = false;
    }
  }

void graph::addVweight(int v, int vw){
    vertexWeight[v] = vw;
}

void graph::addEdge(int u, int v, int w){
    edges.push_back({w, {u, v}});
}

struct disjointSets {
    int *parent, *rank;
    int n;

    disjointSets(int n);

    int find(int u);
    void merge(int x, int y);
};

disjointSets::disjointSets(int n){
    this->n = n;
    parent = new int[n+1];
    rank = new int[n+1];

    for (int i = 0; i <= n; i++){
        rank[i] = 0;
        parent[i] = i;
    }
}

int disjointSets::find(int u){
    if (u != parent[u])
        parent[u] = find(parent[u]);
    return parent[u];
}

void disjointSets::merge(int x, int y){
    x = find(x), y = find(y);

    if (rank[x] > rank[y])
        parent[y] = x;
    else
        parent[x] = y;

    if (rank[x] == rank[y])
        rank[y]++;
}

void graph::kruskalMST(){
    int mst_weight = 0, mst_attractiveness = 0;

    sort(edges.begin(), edges.end());
    disjointSets ds(V);

    vector<pair<int, pairs>> route;
    vector<pair<int, pairs>>::iterator it;
    for (it = edges.begin(); it != edges.end(); it++){
        int u = it->second.first;
        int v = it->second.second;
        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v){
            route.push_back({it->first, {u, v}});
            mst_weight += it->first;

            vertexRank[u]++;
            vertexRank[v]++;

            //if (!sum_check[u]){
                mst_attractiveness += vertexWeight[u];
                sum_check[u] = true;
            //}

            //if (!sum_check[v]){
                mst_attractiveness += vertexWeight[v];
                sum_check[v] = true;
            //}

            ds.merge(set_u, set_v);
        }
    }

    cout << mst_weight << " " << mst_attractiveness << endl;

    for (int i = 0; i < V; i++){
        if (sum_check[i]){
            cout << vertexRank[i] << " ";
        }
    } cout << endl;

    for (it = route.begin(); it != route.end(); it++){
        cout << it->second.first << " " << it->second.second << " " << it->first << endl;
    }

   return;
}
