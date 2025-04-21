#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> graph = {
    {1, 3},          // Node 0
    {0, 2, 3, 4},    // Node 1
    {1, 4, 5},       // Node 2
    {0, 1, 4, 6},    // Node 3
    {1, 2, 3, 5, 6}, // Node 4
    {2, 4, 6},       // Node 5
    {3, 4, 5}        // Node 6
};

void depthFirstSearch(int curr, int destination, vector<int> &visited) {
    cout << curr << " ";
    if (curr == destination) {
        cout << "\nReached Destination (DFS)" << endl;
        return;
    }
    visited[curr] = 1;
    for (int next : graph[curr]) {
        if (!visited[next]) {
            depthFirstSearch(next, destination, visited);
            return; // remove this if you want full path instead of first found
        }
    }
}

void breadthFirstSearch(int start, int target, vector<int> &visited) {
    queue<int> q;
    cout << start << " ";
    visited[start] = 1;
    q.push(start);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int next : graph[node]) {
            if (!visited[next]) {
                cout << next << " ";
                visited[next] = 1;
                if (next == target) {
                    cout << "\nReached Destination (BFS)" << endl;
                    return;
                }
                q.push(next);
            }
        }
    }
}

int main() {
    int source, target;
    cout << "Enter source node (0-6): ";
    cin >> source;
    cout << "Enter destination node (0-6): ";
    cin >> target;

    if (source < 0 || source >= 7 || target < 0 || target >= 7) {
        cout << "Invalid input. Please enter values between 0 and 6." << endl;
        return 0;
    }

    vector<int> visitedDFS(7, 0);
    vector<int> visitedBFS(7, 0);

    cout << "DFS Path: ";
    depthFirstSearch(source, target, visitedDFS);
    cout << "\nBFS Path: ";
    breadthFirstSearch(source, target, visitedBFS);

    return 0;
}
