#include <bits/stdc++.h>
using namespace std;

// inicia tipo estrutura para pares de inteiros - representação para as arestas
typedef pair<int, int> pairs;
typedef pair<int, pairs> edge;

// estrutura grafo
struct graph {
    int V, E;
    int *vertexWeight, *vertexRank;
    bool *sum_check;
    vector<pair<int, pairs>> edges;
    vector<pair<int, edge>> edges_by_vWeight;

    graph(int V, int E);

    void addVweight(int v, int vw);
    void addEdge(int u, int v, int w);
    void kruskalMST();
    void sortByWeight();
    void sortByVweight()
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

void graph::sortByWeight(){
    int i, j;

    for (i = 0; i < vector.size()-1; i++){
        for (j = 0; j < vector.size()-i-1; j++){
            if (vector.at(j).first > vector.at(j+1).first){
                pair<int, edge> aux;

                aux.first = vector.at(j).first;
                aux.second.first = vector.at(j).second.first;
                aux.second.second.first = vector.at(j).second.second.first;
                aux.second.second.second = vector.at(j).second.second.second;

                vector.at(j).first = vector.at(i).first;
                vector.at(j).second.first = vector.at(i).second.first;
                vector.at(j).second.second.first = vector.at(i).second.second.first;
                vector.at(j).second.second.second = vector.at(i).second.second.second;

                vector.at(i).first = aux.first;
                vector.at(i).second.first = aux.second.first;
                vector.at(i).second.second.first = aux.second.second.first;
                vector.at(i).second.second.second = aux.second.second.second;
            } /*else if (vector.at(j).first == vector.at(j+1).first && vector.at(j).second.first > vector.at(j+1).second.first){
                pair<int, edge> aux;

                aux.first = vector.at(j).first;
                aux.second.first = vector.at(j).second.first;
                aux.second.second.first = vector.at(j).second.second.first;
                aux.second.second.second = vector.at(j).second.second.second;

                vector.at(j).first = vector.at(i).first;
                vector.at(j).second.first = vector.at(i).second.first;
                vector.at(j).second.second.first = vector.at(i).second.second.first;
                vector.at(j).second.second.second = vector.at(i).second.second.second;

                vector.at(i).first = aux.first;
                vector.at(i).second.first = aux.second.first;
                vector.at(i).second.second.first = aux.second.second.first;
                vector.at(i).second.second.second = aux.second.second.second;
            }
            */
        }
    }
}

void graph::sort_by_vWeight(){
    int i, j;

    for (i = 0; i < vector.size(); i++){
        for (j = 0; j < vector.size()-1; j++){
            if (vector.at(j).first == vector.at(j+1).first){
                if(vector.at(j).second.first < vector.at(j+1).second.first){
                    pair<int, edge> aux;

                    aux.second.first = vector.at(j).second.first;
                    aux.second.second.first = vector.at(j).second.second.first;
                    aux.second.second.second = vector.at(j).second.second.second;

                    vector.at(j).second.first = vector.at(i).second.first;
                    vector.at(j).second.second.first = vector.at(i).second.second.first;
                    vector.at(j).second.second.second = vector.at(i).second.second.second;

                    vector.at(i).second.first = aux.second.first;
                    vector.at(i).second.second.first = aux.second.second.first;
                    vector.at(i).second.second.second = aux.second.second.second;
                }
            }
        }
    }
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
    disjointSets ds(V);
    vector<pair<int, pairs>> route;
    vector<pair<int, pairs>>::iterator it;
    vector<pair<int, edge>>::iterator it2;

    sort(edges.begin(), edges.end());

    for (it = edges.begin(); it != edges.end(); it++){
        int svw = vertexWeight[it->second.first]+vertexWeight[it->second.second];
        int w = it->first;
        int u = it->second.first;
        int v = it->second.second;

        edges_by_vWeight.push_back({w, {svw, {u, v}}});
    }

    sort_by_weight(edges_by_vWeight);
    sort_by_vWeight(edges_by_vWeight);

    for (it = edges.begin(); it != edges.end(); it++){
        int svw = vertexWeight[it->second.first]+vertexWeight[it->second.second];
        int w = it->first;
        int u = it->second.first;
        int v = it->second.second;
        cout << "{" << w << ", {" << svw << ", {" << u << ", " << v << "}}}" << endl;
    }

    for (it2 = edges_by_vWeight.begin(); it2 != edges_by_vWeight.end(); it2++){
        int u = it2->second.second.first;
        int v = it2->second.second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v){
            route.push_back({it2->first, {u, v}});
            mst_weight += it2->first;

            vertexRank[u]++;
            vertexRank[v]++;

            mst_attractiveness += vertexWeight[u];
            sum_check[u] = true;

            mst_attractiveness += vertexWeight[v];
            sum_check[v] = true;

            ds.merge(set_u, set_v);
        }
    }
    /*
    sort(edges.begin(), edges.end());
    for (it = edges.begin(); it != edges.end(); it++){
        int u = it->second.first;
        int v = it->second.second;
        cout << "u: " << u << " v: " << v << endl;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v){
            route.push_back({it->first, {u, v}});
            mst_weight += it->first;

            vertexRank[u]++;
            vertexRank[v]++;

            mst_attractiveness += vertexWeight[u];
            sum_check[u] = true;

            mst_attractiveness += vertexWeight[v];
            sum_check[v] = true;

            cout << "set u: " << set_u << " set v: " << set_v << endl;
            ds.merge(set_u, set_v);
        }
    }
    */
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
