#include <iostream>
#include <set>
#include <vector>
#include <map>

#define MAX 1000

using namespace std;

int minKey(int keys[], bool mstSet[], int n) {
    int min = INT_MAX, min_index;

    for(int i = 0; i < n; i++) {
        if(keys[i] < min && mstSet[i] == false) {
            min = keys[i];
            min_index = i;
        }
    }

    return min_index;
}

void printMST(int parent[], int graph[][MAX], int n) {

    cout << "The Minimum Spanning Tree for the given graph is ...\n";
    for(int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << "  -->  " << graph[i][parent[i]] << endl;
    }
}

void primMST(int n, int graph[][MAX]) {
    int parent[n]; // array to store constructed mst
    bool mstSet[n]; // keeps track of which vertices are not included in mst yet
    int keys[n]; // shortest path from the vertices in mst

    for(int i = 0; i < n; i++) 
        keys[i] = INT_MAX, mstSet[i] = false;
    keys[0] = 0;
    parent[0] = -1;

    for(int i = 0; i < n-1; i++){
        
        int u = minKey(keys, mstSet, n);
        mstSet[u] = true;

        for(int j = 0; j < n; j++) {
            if(graph[u][j] && mstSet[j] == false && keys[j] > graph[u][j])
                keys[j] = graph[u][j], parent[j] = u;
        }
    }
    printMST(parent, graph, n);
}

int main() {

    int n;
    cout << "Enter the number of vertices in the graph :";
    cin >> n;
    int e;
    cout << "Enter the number of edges in the graph :";
    cin >> e;
    int a[n+1][MAX]; // adjacency matrix of the graph
    //initializing the graph matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j)
                a[i][j] = 0; // cost to travel from a vertex to itself is zero
            else
                a[i][j] = INT_MAX; // assume infinite cost to travel to other vertices
        }
    }
    // taking input
    for(int i = 0; i < e; i++) {
        int v1, v2, w;
        cout << "Edge " << i << " :";
        cin >> v1 >> v2;
        cout << "Weight :" ;
        cin >> w;
        a[v1][v2] = a[v2][v1] = w;
    }
    primMST(n, a);
}