#include <iostream>
#include <vector>

#define MAX_ITER 20

using namespace std;

void jacobi(vector<vector<double>> &a, vector<double> &b, vector<double>& x)
{
    int order = x.size();
    vector<double> updated_x(order, 0);

    for (int iter = 0; iter < MAX_ITER; iter++)
    {
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
        }

        cout << "Iteration " << iter + 1 << ":" << endl;

        // Updating solution vector after each iteration
        for (int i = 0; i < order; i++)
        {
            x[i] = updated_x[i];
            cout << "x" << i << " = " << x[i] << endl;
        }

        cout << endl;
    }
}

void gaussSeidel(vector<vector<double>> &a, vector<double> &b, vector<double>& x)
{
    int order = x.size();

    for (int iter = 0; iter < MAX_ITER; iter++)
    {
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
            x[i] = updated_x;
        }

        cout << "Iteration " << iter + 1 << ":" << endl;
        for (int i = 0; i < order; i++)
        {
            cout << "x" << i << " = " << x[i] << endl;
        }
        cout << endl;
    }
}

int main()
{
    int order;
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

    cout << "\tJacobi Method:" << endl;
    jacobi(a, b, x);

    fill(x.begin(), x.end(), 0);
    cout << "\n\tGauss-Seidel Method:" << endl;
    gaussSeidel(a, b, x);

    return 0;
}