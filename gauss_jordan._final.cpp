#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to print a matrix
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

// Function to perform Gauss-Jordan Elimination
void gaussJordanElimination(vector<vector<double>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        // Find the pivot row
        int pivotRow = i;
        for (int j = i + 1; j < n; ++j) {
            if (abs(matrix[j][i]) > abs(matrix[pivotRow][i])) {
                pivotRow = j;
            }
        }
        // Swap rows if necessary
        if (i != pivotRow) {
            swap(matrix[i], matrix[pivotRow]);
        }
        // Normalize the pivot row
        double pivot = matrix[i][i];
        for (int j = 0; j < n + 1; ++j) {
            matrix[i][j] /= pivot;
        }
        // Eliminate elements above and below the pivot
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                double factor = matrix[j][i];
                for (int k = 0; k < n + 1; ++k) {
                    matrix[j][k] -= factor * matrix[i][k];
                }
            }
        }
    }
}

// Function to calculate the inverse of a matrix using Gauss-Jordan Elimination
bool gaussJordanInverse(vector<vector<double>>& A) {
    int n = A.size();
    vector<vector<double>> I(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i) {
        I[i][i] = 1;
    }



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
            swap(I[i], I[pivotRow]);
        }
        // Check if the pivot element is zero
        if (A[i][i] == 0) {
            return false; // Matrix is not invertible
        }


    for (int i = 0; i < n; ++i) {
        double diag = A[i][i];
       // if (diag == 0) return false;
        for (int j = 0; j < n; ++j) {
            A[i][j] /= diag;
            I[i][j] /= diag;
        }
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double factor = A[j][i];
                for (int k = 0; k < n; ++k) {
                    A[j][k] -= factor * A[i][k];
                    I[j][k] -= factor * I[i][k];
                }
            }
        }
    }
}
    A = I;
    return true;

}
// Function to convert to Row Echelon Form
void rowEchelonForm(vector<vector<double>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        double lead = matrix[i][i];
        for (int j = i; j < n + 1; ++j) {
            matrix[i][j] /= lead;
        }
        for (int j = i + 1; j < n; ++j) {
            double factor = matrix[j][i];
            for (int k = i; k < n + 1; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of equations: ";
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> matrix(n, vector<double>(n + 1));
    cout << "Enter the coefficients of the equations:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            cin >> matrix[i][j];
            if (j < n) A[i][j] = matrix[i][j];
        }
    }

    cout << "The input matrix is:\n";
    printMatrix(matrix);

   gaussJordanElimination(matrix);
    cout << "The matrix after Gauss-Jordan Elimination is:\n";
    printMatrix(matrix);

    if (gaussJordanInverse(A)) {
        cout << "The inverse matrix is:\n";
        printMatrix(A);
    } else {
        cout << "Inverse does not exist\n";
    }

    rowEchelonForm(matrix);
    cout << "The matrix in Row Echelon Form is:\n";
    printMatrix(matrix);

    return 0;
}
