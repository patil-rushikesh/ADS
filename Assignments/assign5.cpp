#include <iostream>
#include <climits>
using namespace std;

int minDistance(int dist[], bool sptSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

void printSolution(int dist[], int V, int src) {
    cout << "\nShortest distances from node " << src << ":\n";
    cout << "Node\tDistance\n";
    for (int i = 0; i < V; i++)
        cout << i << "\t" << dist[i] << endl;
}

void dijkstra(int graph[100][100], int V, int src) {
    int dist[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] != 9999 && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist, V, src);
}

int main() {
    int V, graph[100][100];
    cout << "Enter number of nodes: ";
    cin >> V;

    if (V > 100 || V <= 0) {
        cout << "Error: Number of nodes must be between 1 and 100.\n";
        return 1;
    }

    cout << "Enter the graph as adjacency matrix (-1 for no edge):\n";

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = 9999;  
            }
        }
    }

    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            cout << "Enter cost if there is an edge from " << i << " to " << j << " (-1 for no edge): ";
            int cost;
            cin >> cost;
            if (cost == -1) {
                graph[i][j] = 9999;
            } else {
                graph[i][j] = cost;
            }
            graph[j][i] = graph[i][j];  
        }
    }

    int src;
    cout << "Enter source node (0 to " << V - 1 << "): ";
    cin >> src;

    if (src < 0 || src >= V) {
        cout << "Invalid source node!\n";
        return 1;
    }

    dijkstra(graph, V, src);

    return 0;
}

