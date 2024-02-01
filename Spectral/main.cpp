#include <iostream>
#include <vector>
#include "eigen-3.4.0/Eigen/Eigenvalues"

using namespace Eigen;

void spectralPartitioning(const MatrixXd& adjacencyMatrix, int numPartitions) {
    MatrixXd degreeMatrix = adjacencyMatrix.rowwise().sum().asDiagonal();
    MatrixXd laplacianMatrix = degreeMatrix - adjacencyMatrix;

    SelfAdjointEigenSolver<MatrixXd> eigensolver(laplacianMatrix);
    MatrixXd eigenvectors = eigensolver.eigenvectors();

    VectorXd secondSmallestEigenvector = eigenvectors.col(1);

    std::vector<int> partition(adjacencyMatrix.rows(), 0);
    for (int i = 0; i < secondSmallestEigenvector.size(); ++i) {
        partition[i] = (secondSmallestEigenvector(i) > 0) ? 1 : 0;
    }

    std::cout << "Partition Assignment:\n";
    for (int i = 0; i < partition.size(); ++i) {
        std::cout << "Vertex " << i << ": Partition " << partition[i] << "\n";
    }
}

int main() {
    MatrixXd adjacencyMatrix(8, 8);
    adjacencyMatrix << 0, 1, 1, 0, 0, 0, 0, 0,
            1, 0, 1, 1, 0, 0, 0, 0,
            1, 1, 0, 1, 0, 0, 0, 0,
            0, 1, 1, 0, 1, 0, 0, 0,
            0, 0, 0, 1, 0, 1, 1, 0,
            0, 0, 0, 0, 1, 0, 1, 1,
            0, 0, 0, 0, 1, 1, 0, 1,
            0, 0, 0, 0, 0, 1, 1, 0;

    int numPartitions = 2;

    spectralPartitioning(adjacencyMatrix, numPartitions);

    return 0;
}
