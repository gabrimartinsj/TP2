#include <bits/stdc++.h>
#include "graph1.h"
using namespace std;

int main(){
   int N, T;

   cin >> N >> T;
   cin.ignore();

   string input;
   graph graph(N, T);

   getline(cin, input);
   istringstream stream(input);

   int value, i = 0;
   while (stream >> value){
       graph.addVweight(i, value);
       i++;
   }

   for (int i = 0; i < T; i++){
       int p_i, p_j, cost;
       string input;

       getline(cin, input);
       istringstream stream(input);

       stream >> p_i;
       stream >> p_j;
       stream >> cost;

       graph.addEdge(p_i, p_j, cost);
   }

   graph.kruskalMST();

   return 0;
}
