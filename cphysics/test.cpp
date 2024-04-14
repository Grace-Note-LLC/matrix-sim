#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y, z;
};

void printEdges(int size, int start) {
    vector<Point> edges;
    for (int x = start; x < size - start; x++) {
        for (int y = start; y < size - start; y++) {
            for (int z = start; z < size - start; z++) {
                if (x == start || x == size - start - 1 ||
                    y == start || y == size - start - 1 ||
                    z == start || z == size - start - 1) {
                    edges.push_back({x, y, z});
                }
            }
        }
    }

    // Printing edges
    cout << "Edges at level " << start << ":" << endl;
    for (const auto& edge : edges) {
        cout << "(" << edge.x << ", " << edge.y << ", " << edge.z << ") ";
    }
    cout << endl << endl;
}

int main() {
    int cubeSize = 4;  // Define the cube size (n x n x n)
    
    // Print edges for the outer cube
    printEdges(cubeSize, 0);

    // Print edges for the next inner cube, which starts at 1 and ends at n-2
    if (cubeSize > 2) {  // Ensure there is space for an inner cube
        printEdges(cubeSize, 1);
    }

    return 0;
}
