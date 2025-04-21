#include <iostream>
#include <climits>
using namespace std;

int minKey(int key[], bool mstSet[], int V) {  
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if(mstSet[v] == false && key[v] < min){
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[][100], int V) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++) {  
        cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << endl;
    }
}

void primMST(int graph[][100], int V, int startNode) {
    int parent[V];
    int key[V];
    bool mstSet[V];

    for(int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[startNode] = 0 ;
    parent[startNode] = -1;

    for(int count = 0 ; count < V-1 ; count++) {
        int u = minKey(key, mstSet, V);  
        mstSet[u] = true;

        for(int v = 0 ; v < V ; v++) {
            if(graph[u][v] > 0 && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    printMST(parent, graph, V);
}

int main(){
    int ch, V, startNode;
    cout << "Enter no. of nodes: ";
    cin >> V;

    int graph[100][100];

    cout << "Enter the graph as adjacency matrix(zero if none):" << endl;
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            if(i == j){
                graph[i][j] = 0;
            }
            else{
                cout << "Enter the cost if there is an edge from " << i << " to " << j << ": ";
                cin >> graph[i][j];
                graph[j][i] = graph[i][j];  
            }
        }
    }

    do{
        cout << "Enter the starting node (0 to "<<V-1<<"): ";
        cin >> startNode;

        primMST(graph, V, startNode);
        cout << "Do you want to change the starting node? (0/1): ";
        cin >> ch;
    }
    while(ch == 1);
    return 0;
}
