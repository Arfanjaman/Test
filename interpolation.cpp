#include <iostream>
#include <vector>
#include <iomanip>
#include<bits/stdc++.h>
using namespace std;

// Function to generate the forward difference table
void generateForwardDifferenceTable(vector<double>& x, vector<double>& y, vector<vector<double>>& diffTable) {
    int n = x.size();
    for (int i = 0; i < n; i++) {
        diffTable[i][0] = y[i];
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            diffTable[i][j] = diffTable[i + 1][j - 1] - diffTable[i][j - 1];
        }
    }
}

// Function to generate the backward difference table
void generateBackwardDifferenceTable(vector<double>& x, vector<double>& y, vector<vector<double>>& diffTable) {
    int n = x.size();
    for (int i = 0; i < n; i++) {
        diffTable[i][0] = y[i];
    }
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            diffTable[i][j] = diffTable[i][j - 1] - diffTable[i - 1][j - 1];
        }
    }
}

// Function to print the difference table
void printDifferenceTable(vector<vector<double>>& diffTable, int n) {
    cout << "Difference Table:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            cout << setw(10) << diffTable[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to perform Newton Forward Interpolation
double newtonForwardInterpolation(vector<double>& x, vector<vector<double>>& diffTable, double value) {
    double result = diffTable[0][0];
    double h = x[1] - x[0];
    double u = (value - x[0]) / h;
    double u_term = 1;
    int n = x.size();

    for (int i = 1; i < n; i++) {
        u_term *= (u - (i - 1));
        result += (u_term * diffTable[0][i]) / tgamma(i + 1);
    }

    return result;
}

// Function to perform Newton Backward Interpolation
double newtonBackwardInterpolation(vector<double>& x, vector<vector<double>>& diffTable, double value) {
    int n = x.size();
    double result = diffTable[n - 1][0];
    double h = x[1] - x[0];
    double u = (value - x[n - 1]) / h;
    double u_term = 1;

    for (int i = 1; i < n; i++) {
        u_term *= (u + (i - 1));
        result += (u_term * diffTable[n - i-1][i]) / tgamma(i + 1); // used when we generate a single table
        //result += (u_term * diffTable[n - 1][i]) / tgamma(i + 1); is used if we generate a separate backward table
    }

    return result;
}

int main() {
    int n;
    cout << "Enter the number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter the data points (x and y):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    vector<vector<double>> forwardDiffTable(n, vector<double>(n, 0));
    //vector<vector<double>> backwardDiffTable(n, vector<double>(n, 0));

    generateForwardDifferenceTable(x, y, forwardDiffTable);
    //generateBackwardDifferenceTable(x, y, backwardDiffTable);

    cout << "Forward Difference Table:" << endl;
    printDifferenceTable(forwardDiffTable, n);

    //cout << "Backward Difference Table:" << endl;
    //printDifferenceTable(backwardDiffTable, n);

    double value;
    cout << "Enter the value to interpolate: ";
    cin >> value;

    double forwardResult = newtonForwardInterpolation(x, forwardDiffTable, value);
    double backwardResult = newtonBackwardInterpolation(x, forwardDiffTable, value); //change it to backwardtable if needed.

    cout << "Interpolated value using Newton Forward Interpolation: " << forwardResult << endl;
    cout << "Interpolated value using Newton Backward Interpolation: " << backwardResult << endl;

    return 0;
}