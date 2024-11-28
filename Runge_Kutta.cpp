#include<bits/stdc++.h>

using namespace std;

// Function to evaluate the ODE at a given point
double func(double x, double y, const vector<double>& coefficients) {
    double result = 0.0;
    int max_power = coefficients.size() - 1;
    for (int i = 0; i <= max_power; ++i) {
        result += coefficients[i] * pow(x,i);
    }
    return result;
}

// Runge-Kutta 4th Order Method implementation
void rungeKutta4(double x0, double y0, double x_end, double h, const vector<double>& coefficients) {
    int n = static_cast<int>((x_end - x0) / h);
    double x = x0;
    double y = y0;

    cout << fixed << setprecision(6);
    cout << "x\t\ty\n";
    cout << x << "\t" << y << "\n";

    for (int i = 0; i < n; ++i) {
        double k1 = h * func(x, y, coefficients);
        double k2 = h * func(x + h / 2.0, y + k1 / 2.0, coefficients);
        double k3 = h * func(x + h / 2.0, y + k2 / 2.0, coefficients);
        double k4 = h * func(x + h, y + k3, coefficients);

        y = y + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
        x = x + h;

        cout << x << "\t" << y << "\n";
    }
}

int main() {
    int max_power;
    cout << "Enter the maximum power of the function (e.g., 2 for quadratic): ";
    cin >> max_power;

    vector<double> coefficients(max_power + 1);
    cout << "Provide coefficients for terms up to x^" << max_power << ":\n";
    for (int i = 0; i <= max_power; ++i) {
        cout << "Coefficient for x^" << i << ": ";
        cin >> coefficients[i];
    }

    double x0, y0, x_end, h;
    cout << "Enter initial x value (x0): ";
    cin >> x0;
    cout << "Enter initial y value (y0): ";
    cin >> y0;
    cout << "Enter the x value to solve until (x_end): ";
    cin >> x_end;
    cout << "Enter step size (h): ";
    cin >> h;

    cout << "\nResults using Runge-Kutta 4th Order Method:\n";
    rungeKutta4(x0, y0, x_end, h, coefficients);

    return 0;
}
