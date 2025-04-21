#include <iostream>
#include <vector>
using namespace std;

#define V 7
#define INF 99999  // Manually defining a large number as infinity

class Graph {
private:
    vector<pair<int, int>> adjList[V];  // Adjacency list: pair(vertex, weight)

public:
    void inputGraph() {
        cout << "Enter the adjacency list (" << V << " vertices):\n";
        cout << "(Enter pairs of the form 'vertex weight', use -1 for no edge)\n";
        for (int i = 0; i < V; i++) {
            cout << "Enter edges for vertex " << i << " (end with -1):\n";
            int vertex, weight;
            while (true) {
                cin >> vertex;
                if (vertex == -1) break;
                cin >> weight;
                adjList[i].push_back(make_pair(vertex, weight));
                adjList[vertex].push_back(make_pair(i, weight)); // For undirected graph
            }
        }
    }

    int minKey(int key[], bool mstSet[]) {
        int min = INF, minIndex = -1;
        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

    void primMST() {
        int parent[V];  // Stores MST
        int key[V];     // Minimum weight edge
        bool mstSet[V]; // Track included vertices

        for (int i = 0; i < V; i++) {
            key[i] = INF;
            mstSet[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < V - 1; count++) {
            int u = minKey(key, mstSet);
            mstSet[u] = true;

            // Update key and parent values for adjacent vertices of u
            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!mstSet[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
            }
        }

        cout << "\nEdge \tWeight\n";
        int totalWeight = 0;
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << "\t" << key[i] << "\n";
            totalWeight += key[i];
        }
        cout << "Total Weight of MST: " << totalWeight << endl;
    }
};

int main() {
    Graph g;
    int choice;

    do {
        cout << "\n====== MENU ======\n";
        cout << "1. Input Graph\n";
        cout << "2. Apply Prim's Algorithm\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.inputGraph();
                break;
            case 2:
                g.primMST();
                break;
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
