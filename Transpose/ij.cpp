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

void transposeInPlace(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}

vector<vector<int>> transposeWithAdditionalArray(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> transposed(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

int main() {
    srand(time(nullptr));
    ofstream outFile("inPlace(ij).csv");
    ofstream outFile1("array(ij).csv");
    const int maxSize = 100002;

    for (int n = 1; n <= maxSize; n = n+50) {
        vector<vector<int>> matrix;
        initializeMatrix(matrix, n);

        const int numTrials = 3;
        double totalTime1 = 0.0;
        double totalTime2 = 0.0;

        for (int i = 0; i < numTrials; ++i) {

            auto start = high_resolution_clock::now();

            transposeInPlace(matrix);

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            double ans = duration.count() / 1000;
            totalTime1+= ans;
            




            start = high_resolution_clock::now();

            vector<vector<int>> transposed = transposeWithAdditionalArray(matrix);

            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            double ans1 = duration.count() / 1000;
            totalTime2+= ans1;
            
        }
        outFile << n << "," << totalTime1/numTrials << endl;
        cout << n << "," << totalTime1/numTrials << endl;

        outFile1 << n << "," << totalTime2/numTrials << endl;
        cout << n << "," << totalTime2/numTrials << endl;
    }

    

    return 0;
}
