#include <iostream>  
#include <vector>  
#include <cmath>  
#include <iomanip>  
#include <fstream>  
  
using namespace std;  
  
const int numStrategies = 100;  
  
// Function to create payoff matrices for each player  
void createPayoffMatrices(vector<vector<double>>& payoffMatrixA, vector<vector<double>>& payoffMatrixB) {  
    for (int i = 0; i < numStrategies; ++i) {  
        for (int j = 0; j < numStrategies; ++j) {  
            double x = i, y = j;  
            double target = (x + y) / 8.0; // quarter of the arithmetic mean  
            double distanceA = abs(x - target);  
            double distanceB = abs(y - target);  
  
            // Define payoffs  
            if (distanceA < distanceB) {  
                payoffMatrixA[i][j] = 1.0;  
                payoffMatrixB[i][j] = -1.0;  
            } else if (distanceB < distanceA) {  
                payoffMatrixA[i][j] = -1.0;  
                payoffMatrixB[i][j] = 1.0;  
            } else {  
                payoffMatrixA[i][j] = 0.5;  
                payoffMatrixB[i][j] = 0.5;  
            }  
        }  
    }  
}  
  
// Function to find Nash equilibria  
vector<pair<int, int>> findNashEquilibria(const vector<vector<double>>& payoffMatrixA, const vector<vector<double>>& payoffMatrixB) {  
    vector<pair<int, int>> equilibria;  
  
    // Iterate over all possible strategy pairs (i, j)  
    for (int i = 0; i < numStrategies; ++i) {  
        for (int j = 0; j < numStrategies; ++j) {  
            bool isNashForA = true, isNashForB = true;  
  
            // Check for player A: strategy i must be the best response to strategy j of player B  
            for (int iAlt = 0; iAlt < numStrategies; ++iAlt) {  
                if (payoffMatrixA[iAlt][j] > payoffMatrixA[i][j]) {  
                    isNashForA = false;  
                    break;  
                }  
            }  
  
            // Check for player B: strategy j must be the best response to strategy i of player A  
            for (int jAlt = 0; jAlt < numStrategies; ++jAlt) {  
                if (payoffMatrixB[i][jAlt] > payoffMatrixB[i][j]) {  
                    isNashForB = false;  
                    break;  
                }  
            }  
  
            // If neither player wants to change strategy, add the pair (i, j) to Nash equilibria  
            if (isNashForA && isNashForB) {  
                equilibria.emplace_back(i, j);  
            }  
        }  
    }  
  
    return equilibria;  
}  
  
// Function to print a matrix  
void printMatrix(const vector<vector<double>>& matrix) {  
    for (const auto& row : matrix) {  
        for (double value : row) {  
            cout << setw(5) << value << " ";  
        }  
        cout << endl;  
    }  
}  
  
int main() {  
    // Initialize payoff matrices for each player  
    vector<vector<double>> payoffMatrixA(numStrategies, vector<double>(numStrategies, 0.0));  
    vector<vector<double>> payoffMatrixB(numStrategies, vector<double>(numStrategies, 0.0));  
  
    // Create payoff matrices  
    createPayoffMatrices(payoffMatrixA, payoffMatrixB);  
  
    // Print payoff matrices  
    cout << "Payoff Matrix for Player A:" << endl;  
    printMatrix(payoffMatrixA);  
  
    cout << "\\nPayoff Matrix for Player B:" << endl;  
    printMatrix(payoffMatrixB);  
  
    // Find Nash equilibria  
    vector<pair<int, int>> equilibria = findNashEquilibria(payoffMatrixA, payoffMatrixB);  
  
    // Print found Nash equilibria  
    cout << "\\nFound Nash Equilibria:" << endl;  
    for (const auto& eq : equilibria) {  
        cout << "Strategy A: " << eq.first << ", Strategy B: " << eq.second << endl;  
    }  
  
    return 0;  
}
