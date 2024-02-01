#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int calculateCutSize(const vector<int>& partition, const vector<vector<int>>& adjacencyMatrix) {
    int cutSize = 0;
    int numNodes = partition.size();

    for (int i = 0; i < numNodes - 1; ++i) {
        for (int j = i + 1; j < numNodes; ++j) {
            if (partition[i] != partition[j]) {
                cutSize += adjacencyMatrix[i][j];
            }
        }
    }

    return cutSize;
}

void kernighanLin(vector<int>& partition, vector<vector<int>>& adjacencyMatrix) {
    int numNodes = partition.size();
    int initialCutSize = calculateCutSize(partition, adjacencyMatrix);

    for (int iter = 0; iter < numNodes / 2; ++iter) {
        vector<int> gain(numNodes, 0);

        for (int i = 0; i < numNodes; ++i) {
            if (partition[i] == 0) {
                for (int j = 0; j < numNodes; ++j) {
                    if (partition[j] == 1) {
                        gain[i] += adjacencyMatrix[i][j];
                    }
                }
            } else {
                for (int j = 0; j < numNodes; ++j) {
                    if (partition[j] == 0) {
                        gain[i] += adjacencyMatrix[i][j];
                    }
                }
            }
        }

        int maxGainNode = distance(gain.begin(), max_element(gain.begin(), gain.end()));
        partition[maxGainNode] = 1 - partition[maxGainNode];
        gain[maxGainNode] = 0;

        int newCutSize = calculateCutSize(partition, adjacencyMatrix);

        cout << "Iteration " << iter + 1 << ": Cut Size = " << newCutSize << endl;

        if (newCutSize >= initialCutSize) {
            cout << "No improvement. Reverting to the initial partition." << endl;
            partition = {0, 0, 1, 1, 1, 1, 0, 0}; // Reset to the initial partition
        } else {
            initialCutSize = newCutSize;
        }
    }

    cout << "\nKernighan-Lin partitioning result:" << endl;
    for (int i = 0; i < numNodes; ++i) {
        cout << "Node " << i << ": Partition " << partition[i] << endl;
    }
}

int main() {
    vector<vector<int>> adjacencyMatrix = {
            {0, 1, 1, 0, 0, 0, 0, 0},
            {1, 0, 1, 1, 0, 0, 0, 0},
            {1, 1, 0, 1, 0, 0, 0, 0},
            {0, 1, 1, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 1, 1, 0},
            {0, 0, 0, 0, 1, 0, 1, 1},
            {0, 0, 0, 0, 1, 1, 0, 1},
            {0, 0, 0, 0, 0, 1, 1, 0}
    };

    vector<int> partition = {0, 0, 1, 1, 1, 1,0,0};

    kernighanLin(partition, adjacencyMatrix);

    return 0;
}