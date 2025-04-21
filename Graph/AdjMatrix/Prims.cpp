#include <iostream>
using namespace std;

#define V 7
#define INF 99999  // Represents no connection

class Graph {
private:
    int adjMatrix[V][V];

public:
    void inputGraph() {
        cout << "Enter the adjacency matrix (" << V << "x" << V << "):\n";
        cout << "(Use 0 for no direct edge between vertices)\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cin >> adjMatrix[i][j];
                if (adjMatrix[i][j] == 0 && i != j)
                    adjMatrix[i][j] = INF;
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

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != INF && !mstSet[v] && adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                }
            }
        }

        cout << "\nEdge \tWeight\n";
        int totalWeight = 0;
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << "\t" << adjMatrix[i][parent[i]] << "\n";
            totalWeight += adjMatrix[i][parent[i]];
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
