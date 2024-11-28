#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Gauss-Jordan Elimination function to solve Ax = B
vector<double> gaussJordanElimination(vector<vector<double>> A, vector<double> B) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        // Find the pivot row
        int pivotRow = i;
        for (int j = i + 1; j < n; ++j) {
            if (abs(A[j][i]) > abs(A[pivotRow][i])) {
                pivotRow = j;
            }
        }
        // Swap rows if necessary
        if (i != pivotRow) {
            swap(A[i], A[pivotRow]);
            swap(B[i], B[pivotRow]);
        }
        // Normalize the pivot row
        double pivot = A[i][i];
        for (int j = 0; j < n; ++j) {
            A[i][j] /= pivot;
        }
        B[i] /= pivot;

        // Eliminate elements above and below the pivot
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                double factor = A[j][i];
                for (int k = 0; k < n; ++k) {
                    A[j][k] -= factor * A[i][k];
                }
                B[j] -= factor * B[i];
            }
        }
    }

    return B; // Solution vector
}

int main() {
    int n;
    cout << "Enter the number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter the x and y values:\n";
    for (int i = 0; i < n; ++i) {
        cout << "x[" << i << "]: ";
        cin >> x[i];
        cout << "y[" << i << "]: ";
        cin >> y[i];
    }

    // Initialize sums for the normal equations
    double sum_x2 = 0, sum_x = 0, sum_1 = n; // n is the count of points
    double sum_x3 = 0, sum_x4 = 0;
    double sum_y = 0, sum_xy = 0, sum_x2y = 0;

    for (int i = 0; i < n; ++i) {
        double xi = x[i];
        double yi = y[i];
        sum_x2 += xi * xi;
        sum_x += xi;
        sum_y += yi;
        sum_xy += xi * yi;
        sum_x2y += xi * xi * yi;
        sum_x3 += xi * xi * xi;
        sum_x4 += xi * xi * xi * xi;
    }

    // Construct the matrices for Ax = B
    vector<vector<double>> A = {
        {sum_1, sum_x, sum_x2},
        {sum_x, sum_x2, sum_x3},
        {sum_x2, sum_x3, sum_x4}
    };
    vector<double> B = {sum_y, sum_xy, sum_x2y};

    // Solve for coefficients
    vector<double> coefficients = gaussJordanElimination(A, B);

    double a = coefficients[0]; // Constant term
    double b = coefficients[1]; // Linear term
    double c = coefficients[2]; // Quadratic term

    // Output the results
    cout << fixed << setprecision(6);
    cout << "\nThe quadratic equation is:\n";
    cout << "y = " << a << " + " << b << "x + " << c << "x^2" << endl;

    return 0;
}
