#include<bits/stdc++.h>
using namespace std;

const double EPSILON = 1e-30; // Tolerance for convergence
const int MAX_ITERATIONS = 100000; // Maximum number of iterations

// Function coefficients
double a, b, c, d;

double f(const vector<double>& a, double x) {
    double value = 0;
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        value += a[i] * pow(x, n - i - 1);
    }
    return value;
}


// False Position method to find a root in the interval [a, b]
double falsePosition(vector<double>& a,double left, double right) {
    double c;
    int iterations = 0;

    // Check if the interval contains a root
    if (f(a,left) * f(a,right) > 0) {
        cout << "No root in the interval [" << left << ", " << right << "]." << endl;
        return NAN; // Return NaN if no root is found
    }

    // False Position Algorithm
    while (abs(right - left) > EPSILON && iterations < MAX_ITERATIONS) {
        c = (left * f(a,right) - right * f(a,left)) / (f(a,right) - f(a,left));

        if (f(a,c) == 0) {
            return c; // Found exact root
        } else if (f(a,left) * f(a,c) < 0) {
            right = c; // Root lies in [left, c]
        } else {
            left = c; // Root lies in [c, right]
        }

        iterations++;
    }

    if (iterations == MAX_ITERATIONS) {
        cout << "Maximum number of iterations reached." << endl;
    }

    return c; // Return the best approximation
}

// Find multiple roots in the interval [a, b]
void findMultipleRoots(vector<double>&a,double start, double end) {
    set<double> roots;
    double intervalSize = 0.001; // Size of the interval to search for roots

    for (double i = start; i <= end; i += intervalSize) {
        double left = i;
        double right = i + intervalSize;

        // Check if the interval [left, right] contains a root
        if (f(a,left) * f(a,right) < 0) {
            double root = falsePosition(a,left, right);

            if (!isnan(root)) {
                roots.insert(root); // Store unique roots
            }
        }
    }

    // Print the roots
    cout << "Roots: ";
    for (double root : roots) {
        cout << root << " ";
    }
    cout << endl;
}

int main() {
   int maxPow;
    cout << "Enter maximum power of the polynomial: ";
    cin >> maxPow;

    cout << "Enter " << maxPow + 1 << " coefficients: ";
    vector<double> a(maxPow + 1);
    for (int i = 0; i <= maxPow; ++i) {
        cin >> a[i];
    }

    // Input range to search for roots
    double rangeStart, rangeEnd;
    cout << "Enter the range [start, end] to search for roots:" << endl;
    cout << "Start: ";
    cin >> rangeStart;
    cout << "End: ";
    cin >> rangeEnd;

    // Find and display roots
    findMultipleRoots(a,rangeStart, rangeEnd);

    return 0;
}
