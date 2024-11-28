#include <iostream>
#include <vector>
#include <cmath> // For std::abs

using namespace std;

void jacobi(vector<vector<double>> &a, vector<double> &b, vector<double> &x, double tolerance)
{
    int order = x.size();
    vector<double> updated_x(order, 0);

    for (int iter = 0; iter < 1000; iter++) // Large iteration cap to avoid infinite loop
    {
        double max_diff = 0.0;

        for (int i = 0; i < order; i++)
        {
            double sum = 0;
            for (int j = 0; j < order; j++)
            {
                if (j != i)
                {
                    sum += a[i][j] * x[j];
                }
            }
            updated_x[i] = (b[i] - sum) / a[i][i];
            max_diff = max(max_diff, abs(updated_x[i] - x[i]));
        }

        cout << "Iteration " << iter + 1 << ":" << endl;

        // Updating solution vector and printing results
        for (int i = 0; i < order; i++)
        {
            x[i] = updated_x[i];
            cout << "x" << i << " = " << x[i] << endl;
        }
        cout << endl;

        // Check for convergence
        if (max_diff < tolerance)
        {
            cout << "Converged after " << iter + 1 << " iterations." << endl;
            break;
        }
    }
}

void gaussSeidel(vector<vector<double>> &a, vector<double> &b, vector<double> &x, double tolerance)
{
    int order = x.size();

    for (int iter = 0; iter < 1000; iter++) // Large iteration cap to avoid infinite loop
    {
        double max_diff = 0.0;

        for (int i = 0; i < order; i++)
        {
            double sum = 0;
            for (int j = 0; j < order; j++)
            {
                if (j != i)
                {
                    sum += a[i][j] * x[j];
                }
            }
            double updated_x = (b[i] - sum) / a[i][i];
            max_diff = max(max_diff, abs(updated_x - x[i]));
            x[i] = updated_x;
        }

        cout << "Iteration " << iter + 1 << ":" << endl;
        for (int i = 0; i < order; i++)
        {
            cout << "x" << i << " = " << x[i] << endl;
        }
        cout << endl;

        // Check for convergence
        if (max_diff < tolerance)
        {
            cout << "Converged after " << iter + 1 << " iterations." << endl;
            break;
        }
    }
}

int main()
{
    int order;
    double tolerance;

    cout << "Enter the order of the coefficient matrix: ";
    cin >> order;

    vector<vector<double>> a(order, vector<double>(order));
    vector<double> b(order);
    vector<double> x(order, 0);

    cout << "Enter the coefficient matrix:" << endl;
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            cin >> a[i][j];
        }
    }

    cout << "Enter the constants vector:" << endl;
    for (int i = 0; i < order; i++)
    {
        cin >> b[i];
    }

    cout << "Enter the tolerance for convergence: ";
    cin >> tolerance;

    cout << "\tJacobi Method:" << endl;
    jacobi(a, b, x, tolerance);

    fill(x.begin(), x.end(), 0); // Reset the solution vector
    cout << "\n\tGauss-Seidel Method:" << endl;
    gaussSeidel(a, b, x, tolerance);

    return 0;
}
