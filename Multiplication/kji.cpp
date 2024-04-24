#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

int generateRandomNumber() {
    return rand() % 10;
}

void initializeMatrix(vector<vector<int>>& matrix, int n) {
    matrix.resize(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = generateRandomNumber();
        }
    }
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> matrixProduct(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for (int k = 0; k < n; ++k) {
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

int main() {
    ofstream outFile("kji.csv");
    srand(time(nullptr));

    int N = 6002;

    for (int n = 1; n <= N; n=n+50) {
        vector<vector<int>> A, B;
        initializeMatrix(A, n);
        initializeMatrix(B, n);

        const int numTrials = 1;
        double totalTime = 0.0;

        for (int i = 0; i < numTrials; ++i) {
            auto start = high_resolution_clock::now();

            vector<vector<int>> product = matrixProduct(A, B);

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            totalTime += duration.count();
        }

        double averageTime = totalTime / numTrials;
        outFile << n << "," << averageTime/1000000 << endl;
        cout << "For n = " << n << ", kji : " << averageTime/1000000 << " seconds" << endl;
    }

    return 0;
}
