#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include<bits/stdc++.h>
using namespace std;
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


// Function to perform linear curve fitting (y = a + bx)
void linearCurveFitting(const vector<double>& x, const vector<double>& y, double x_val) {
    int n = x.size();
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    vector<vector<double>> A = {{n, sum_x}, {sum_x, sum_x2}};
    vector<double> B = {sum_y, sum_xy};
    vector<double> solution= gaussJordanElimination(A,B);
    double a=solution[0];
    double b=solution[1];    
   
   // double b = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
     //double a = (sum_y - b * sum_x) / n;

    cout << "Linear fit: y = " << a << " + " << b << "x" << endl;
    double y_val = a + b * x_val;
    cout << "For x = " << x_val << ", y = " << y_val << endl;
}

// Function to perform quadratic curve fitting (y = a + bx + cx^2)
void quadraticCurveFitting(const vector<double>& x, const vector<double>& y, double x_val) {
    int n = x.size();
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
    vector<vector<double>> A = 
    {
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
    double y_val = a + b * x_val + c * x_val * x_val;
    cout << "For x = " << x_val << ", y = " << y_val << endl;

}

// Function to perform exponential curve fitting (y = ab^x)
void exponentialCurveFitting(const vector<double>& x, const vector<double>& y, double x_val) {
    int n = x.size();
    double sum_x = 0, sum_logy = 0, sum_xlogy = 0, sum_x2 = 0;

    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_logy += log(y[i]);
        sum_xlogy += x[i] * log(y[i]);
        sum_x2 += x[i] * x[i];
    }

    vector<vector<double>>A={{n,sum_x},{sum_x,sum_x2}};
    vector<double>B={sum_logy,sum_xlogy};
    vector<double>solution=gaussJordanElimination(A,B);
    double a=solution[0];
    double b=solution[1];
    //double b =((n * sum_xlogy - sum_x * sum_logy) / (n * sum_x2 - sum_x * sum_x));
    //double a = exp((sum_logy - b * sum_x) / n);
     b=exp(b);
     a=exp(a);
    cout << "Exponential fit: y = " << a << " * " << b << "^x" << endl;
    double y_val = a * pow(b, x_val);
    cout << "For x = " << x_val << ", y = " << y_val << endl;
}

// Function to perform power curve fitting (y = ax^b)
void powerCurveFitting(const vector<double>& x, const vector<double>& y, double x_val) {
    int n = x.size();
    double sum_logx = 0, sum_logy = 0, sum_logxlogy = 0, sum_logx2 = 0;

    for (int i = 0; i < n; i++) {
        sum_logx += log(x[i]);
        sum_logy += log(y[i]);
        sum_logxlogy += log(x[i]) * log(y[i]);
        sum_logx2 += log(x[i]) * log(x[i]);
    }

    vector<vector<double>> A={{n,sum_logx},{sum_logx,sum_logx2}};
    vector<double> B={sum_logy,sum_logxlogy};
    vector<double>solution= gaussJordanElimination(A,B);
    double a=solution[0];
    double b=solution[1];
     a=exp(a);

   // double b = ((n * sum_logxlogy - sum_logx * sum_logy) / (n * sum_logx2 - sum_logx * sum_logx));
    //double a = exp((sum_logy - b * sum_logx) / n);

    cout << "Power fit: y = " << a << " * x^" << b << endl;
    double y_val = a * pow(x_val, b);
    cout << "For x = " << x_val << ", y = " << y_val << endl;
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

    int choice;
    cout << "Choose the type of curve fitting:\n";
    cout << "1. Linear (y = a + bx)\n";
    cout << "2. Quadratic (y = a + bx + cx^2)\n";
    cout << "3. Exponential (y = ab^x)\n";
    cout << "4. Power (y = ax^b)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    double x_val;
    cout << "Enter the value of x to evaluate the fitted curve: ";
    cin >> x_val;

    switch (choice) {
        case 1:
            linearCurveFitting(x, y, x_val);
            break;
        case 2:
            quadraticCurveFitting(x, y, x_val);
            break;
        case 3:
            exponentialCurveFitting(x, y, x_val);
            break;
        case 4:
            powerCurveFitting(x, y, x_val);
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }

    return 0;
}