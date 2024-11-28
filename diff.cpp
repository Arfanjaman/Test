#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

// Function to calculate the product for ds(x, n)
double ds(double x, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        double mul = 1.0;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                mul *= (x - j);
            }
        }
        sum += mul;
    }
    return sum;
}
double ds2(double x, int n) {
     double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        double mul = 1.0;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                mul *= (x + j);
            }
        }
        sum += mul;
    }
    return sum;
}




// Forward difference method
void forward(const vector<double>& x, const vector<double>& y, double x_val) {
    int n = x.size();
    double h = x[1] - x[0];
    double s = (x_val - x[0]) / h;

    // Create the forward difference table
    vector<vector<double>> mat(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        mat[i][0] = y[i];
    }

    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < n - j; ++i) {
            mat[i][j] = mat[i + 1][j - 1] - mat[i][j - 1];
        }
    }

    // Compute the derivative using forward differences
    double res = 0.0;
    for (int i = 1; i < n; ++i) {
        double delta = mat[0][i];
        res += delta * ds(s, i) / tgamma(i + 1); // tgamma(i+1) is equivalent to factorial(i)
    }

    res /= h;

    // Print the result
    cout << fixed << setprecision(6);
    cout << "The derivative at x = " << x_val << " using forward interpolation is " << res << endl;
}

// Backward difference method
void backward(const vector<double>& x, const vector<double>& y, double x_val) {
    int n = x.size();
    double h = x[1] - x[0];
    double s = (x_val - x[n - 1]) / h;

    // Create the backward difference table
    vector<vector<double>> mat(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        mat[i][0] = y[i];
    }

    for (int j = 1; j < n; ++j) {
        for (int i = n - 1; i >= j; --i) {
            mat[i][j] = mat[i][j - 1] - mat[i - 1][j - 1];
        }
    }

    // Compute the derivative using backward differences
    double res = 0.0;
    for (int i = 1; i < n; ++i) {
        double delta = mat[n - 1][i];
        res += delta * ds2(s, i) / tgamma(i + 1); // tgamma(i+1) is equivalent to factorial(i)
    }

    res /= h;

    // Print the result
    cout << fixed << setprecision(6);
    cout << "The derivative at x = " << x_val << " using backward interpolation is " << res << endl;
}

int main() {
    int n;
    cout << "Enter the number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter the x values:\n";
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }

    cout << "Enter the y values:\n";
    for (int i = 0; i < n; ++i) {
        cin >> y[i];
    }

    double x_val;
    cout << "Enter the value of x at which to calculate the derivative: ";
    cin >> x_val;

    // Determine whether to use forward or backward interpolation
    double mid = x[n / 2];
    if (x_val <= mid) {
        forward(x, y, x_val);
    } else {
        backward(x, y, x_val);
    }

    return 0;
}
//x= 1.5 2.0 2.5 3.0 3.5 
//y= 3.375 7.0 13.625 23 38.875
