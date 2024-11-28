#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
double f(double x, double y) {
    return sin(x); // The derivative function
}

void rungeKutta(double x0, double y0, double h, double xEnd) {
    vector<double> x_values;
    vector<double> y_values;

    double x = x0;
    double y = y0;

    while (x <= xEnd) {
        x_values.push_back(x);
        y_values.push_back(y);
        
        // Calculate the Runge-Kutta coefficients
        double k1 = h * f(x, y);
        double k2 = h * f(x + h / 2, y + k1 / 2);
        double k3 = h * f(x + h / 2, y + k2 / 2);
        double k4 = h * f(x + h, y + k3);
        
        // Update the next value of y
        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        x += h;
    }

    // Print the results
    cout << "x\t\t y\n";
    for (size_t i = 0; i < x_values.size(); ++i) {
        std::cout << x_values[i] << "\t " << y_values[i] << "\n";
    }
}

int main() {
    double x0 = 0.0;   // Initial x
    double y0 = 0.0;   // Initial y (y(0) = 0)
    double h = 0.1;    // Step size
    double xEnd = 4 * M_PI; // End of the interval

    rungeKutta(x0, y0, h, xEnd);

    return 0;
}
