#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

const int sz = 10;
bool walls[sz * sz][2] = {0}; // 0 for a wall, 1 for no wall (left -> top)
bool visited[sz * sz] = {0};
int path[sz * sz] = {0}; // Store the solution path

// Directions (North, East, South, West)
const int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// Maze cell struct for Dijkstra's priority queue
struct Cell {
    int index, dist;
    bool operator<(const Cell& other) const {
        return dist > other.dist; // Min-heap based on distance
    }
};

// Helper function to print the maze
void printMaze() {
    for (int i = 0; i < sz; i++) {
        // Print top walls
        for (int j = 0; j < sz; j++) {
            if (walls[i * sz + j][1]) cout << "+   "; // No top wall
            else cout << "+---"; // Top wall
        }
        cout << "+\n";
        // Print left walls
        for (int j = 0; j < sz; j++) {
            if (walls[i * sz + j][0]) cout << "    "; // No left wall
            else cout << "|   "; // Left wall
        }
        cout << "|\n";
    }
    // Print bottom wall
    for (int j = 0; j < sz; j++) {
        cout << "+---";
    }
    cout << "+\n";
}

// Random DFS to generate the maze
int nextCell(int pos) {
    vector<int> options;
    if (pos >= sz) { if (!visited[pos - sz]) options.push_back(-sz); }
    if ((pos + 1) % sz != 0) { if (!visited[pos + 1]) options.push_back(1); }
    if (pos < sz * (sz - 1)) { if (!visited[pos + sz]) options.push_back(sz); }
    if (pos % sz != 0) { if (!visited[pos - 1]) options.push_back(-1); }
    
    if (options.empty()) return 0;
    return options[rand() % options.size()];
}

void connect(int pos1, int pos2) {
    if (pos2 > pos1) {
        if (pos2 == pos1 + 1) walls[pos2][0] = 1; // Remove right wall
        else walls[pos2][1] = 1; // Remove bottom wall
    } else {
        if (pos1 == pos2 + 1) walls[pos1][0] = 1; // Remove left wall
        else walls[pos1][1] = 1; // Remove top wall
    }
}

void randomDFS(int pos) {
    visited[pos] = true;
    int next = pos + nextCell(pos);
    while (next != pos) {
        connect(pos, next);
        randomDFS(next);
        next = pos + nextCell(pos);
    }
}

// Dijkstra's Algorithm to solve the maze
void dijkstraSolve(int start, int goal) {
    priority_queue<Cell> pq;
    vector<int> dist(sz * sz, INT_MAX);
    vector<int> prev(sz * sz, -1);
    vector<bool> visited(sz * sz, false);
    
    dist[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        int curr = pq.top().index;
        pq.pop();

        if (curr == goal) break;
        if (visited[curr]) continue;

        visited[curr] = true;

        // Explore neighbors (North, East, South, West)
        for (int i = 0; i < 4; i++) {
            int nx = curr / sz + directions[i][0];
            int ny = curr % sz + directions[i][1];
            int neighbor = nx * sz + ny;
            
            if (nx >= 0 && nx < sz && ny >= 0 && ny < sz) {
                bool canMove = false;
                if (i == 0 && walls[curr][1]) canMove = true;  // North
                if (i == 1 && walls[curr + 1][0]) canMove = true;  // East
                if (i == 2 && walls[neighbor][1]) canMove = true;  // South
                if (i == 3 && walls[curr][0]) canMove = true;  // West

                if (canMove && dist[neighbor] > dist[curr] + 1) {
                    dist[neighbor] = dist[curr] + 1;
                    prev[neighbor] = curr;
                    pq.push({neighbor, dist[neighbor]});
                }
            }
        }
    }

    // Backtrack to get the path
    int curr = goal;
    while (curr != -1) {
        path[curr] = 1;
        curr = prev[curr];
    }
}

// Function to print the maze with the solution path
void printSolvedMaze() {
    for (int i = 0; i < sz; i++) {
        // Print top walls
        for (int j = 0; j < sz; j++) {
            if (walls[i * sz + j][1]) cout << "+   ";
            else cout << "+---";
        }
        cout << "+\n";
        // Print left walls and solution path
        for (int j = 0; j < sz; j++) {
            if (walls[i * sz + j][0]) cout << " ";
            else cout << "|";

            if (path[i * sz + j]) cout << " * "; // Solution path
            else cout << "   "; // Empty space
        }
        cout << "|\n";
    }
    // Print bottom wall
    for (int j = 0; j < sz; j++) {
        cout << "+---";
    }
    cout << "+\n";
}

int main() {
    srand(time(0));

    // Generate a random maze using DFS
    randomDFS(0);

    // Print the generated maze
    cout << "Generated Maze:\n";
    printMaze();

    // Solve the maze using Dijkstra's algorithm
    dijkstraSolve(0, sz * sz - 1);

    // Print the maze with the solution path
    cout << "\nSolved Maze:\n";
    printSolvedMaze();

    return 0;
}
