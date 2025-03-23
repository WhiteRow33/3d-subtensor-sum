#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

const double epsilon = 1e-6;

vector<vector<double>> readInputs(ifstream& input);
void printSum(vector<vector<double>>& inputNumbers);
vector<vector<vector<double>>> calculateAllSum(const vector<vector<vector<double>>>& tensor, int row, int col, int depth);
double getSubTensorSum(const vector<vector<vector<double>>>& allSum, int startX, int startY, int startZ, int endX, int endY, int endZ);
int countSubTensorsWithTargetSum(const vector<vector<vector<double>>>& allSum, double targetSum, int row, int col, int depth);

int main() {
    string filename = "sample_1.txt";
    ifstream input(filename);

    if (input.fail()) {
        cout << "Could not open the file: " << filename << endl;
        return 0;
    }

    vector<vector<double>> inputNumbers;
    inputNumbers = readInputs(input);
    printSum(inputNumbers);
    input.close();

    return 0;
}

vector<vector<double>> readInputs(ifstream& input) {
    string line;
    vector<vector<double>> inputNumbers;
    while (getline(input, line)) {
        vector<double> row;
        istringstream iss(line);
        double number;
        while (iss >> number) {
            row.push_back(number);
        }
        inputNumbers.push_back(row);
    }
    return inputNumbers;
}

void printSum(vector<vector<double>>& inputNumbers) {
    double targetSum = inputNumbers[1][0];

    int row = inputNumbers[0][0], col = inputNumbers[0][1], depth = inputNumbers[0][2];
    vector<vector<vector<double>>> inputTensor(row, vector<vector<double>>(col, vector<double>(depth)));

    for (int i = 3; i < inputNumbers.size(); i++) {
        inputTensor[inputNumbers[i][0]][inputNumbers[i][1]][inputNumbers[i][2]] = inputNumbers[i][3];
    }

    vector<vector<vector<double>>> allSum = calculateAllSum(inputTensor, row, col, depth);
    int count = countSubTensorsWithTargetSum(allSum, targetSum, row, col, depth);

    cout << count << endl;
}

vector<vector<vector<double>>> calculateAllSum(const vector<vector<vector<double>>>& tensor, int row, int col, int depth) {
    vector<vector<vector<double>>> allSum(row, vector<vector<double>>(col, vector<double>(depth)));

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            for (int k = 0; k < depth; ++k) {
                double currentValue = tensor[i][j][k];

                double preRow = 0, preCol = 0, preDepth = 0, overlap1 = 0, overlap2 = 0, overlap3 = 0, overlap4 = 0;

                if (i > 0) preRow = allSum[i - 1][j][k];
                if (j > 0) preCol = allSum[i][j - 1][k];
                if (k > 0) preDepth = allSum[i][j][k - 1];
                if (i > 0 && j > 0) overlap1 = allSum[i - 1][j - 1][k];
                if (i > 0 && k > 0) overlap2 = allSum[i - 1][j][k - 1];
                if (j > 0 && k > 0) overlap3 = allSum[i][j - 1][k - 1];
                if (i > 0 && j > 0 && k > 0) overlap4 = allSum[i - 1][j - 1][k - 1];

                allSum[i][j][k] = currentValue + preRow + preCol + preDepth - overlap1 - overlap2 - overlap3 + overlap4;
            }
        }
    }
    return allSum;
}

double getSubTensorSum(const vector<vector<vector<double>>>& allSum, int startX, int startY, int startZ, int endX, int endY, int endZ) {
    double total = allSum[endX][endY][endZ];

    if (startX > 0) total -= allSum[startX - 1][endY][endZ];
    if (startY > 0) total -= allSum[endX][startY - 1][endZ];
    if (startZ > 0) total -= allSum[endX][endY][startZ - 1];

    if (startX > 0 && startY > 0) total += allSum[startX - 1][startY - 1][endZ];
    if (startX > 0 && startZ > 0) total += allSum[startX - 1][endY][startZ - 1];
    if (startY > 0 && startZ > 0) total += allSum[endX][startY - 1][startZ - 1];

    if (startX > 0 && startY > 0 && startZ > 0) total -= allSum[startX - 1][startY - 1][startZ - 1];

    return total;
}

int countSubTensorsWithTargetSum(const vector<vector<vector<double>>>& allSum, double targetSum, int row, int col, int depth) {
    int count = 0;

    for (int startX = 0; startX < row; ++startX) {
        for (int startY = 0; startY < col; ++startY) {
            for (int startZ = 0; startZ < depth; ++startZ) {
                for (int endX = startX; endX < row; ++endX) {
                    for (int endY = startY; endY < col; ++endY) {
                        for (int endZ = startZ; endZ < depth; ++endZ) {
                            double sum = getSubTensorSum(allSum, startX, startY, startZ, endX, endY, endZ);
                            if (fabs(targetSum - sum) < epsilon) {
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }

    return count;
}
