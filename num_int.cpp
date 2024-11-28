#include <bits/stdc++.h>
using namespace std;


double func(double x) {
    return 1/(1+pow(x, 2));  
}

double trapezoidalRule(double a, double b, int n, double h) {
    double result = func(a) + func(b);  
    for (int i = 0; i <=b; i=i+h) {
        if(i==0 || i==n)continue;
        result += 2 * func(i);
    }
    result *= (h / 2.0);
    return result;
}


double simpsonOneThirdRule(double a, double b, int n, double h) {
    if (n % 2 != 0) {
        cout << "Error: n should be a multiple of 2 for Simpson's 1/3 Rule." << endl;
        return -1;
    }

    double result = func(a) + func(b);  
    for (int i = 0; i <=b; i=i+h) {
        if(i==0 || i==n)continue;
        result += (i % 2 == 0 ? 2 : 4) * func(i);
    }
    result *= (h / 3);
    return result;
}



double simpsonThreeEighthRule(double a, double b, int n, double h) {
    if (n % 3 != 0) {
        cout << "Error: n should be a multiple of 3 for Simpson's 3/8 Rule." << endl;
        return -1;
    }

    double result = func(a) + func(b);  
     for (int i = 0; i <=b; i=i+h) {
        if(i==0 || i==n)continue;
        result += (i % 3 == 0 ? 2 : 3) * func(i);
    }
    result *= (3 * h / 8);
    return result;
}






int main() {
    double a, b, h;
    int n;

    cout<< "Enter the lower limit a: ";
    cin>> a;
    cout<< "Enter the upper limit b: ";
    cin>> b;
    cout<< "Enter the number of divisions n: ";
    cin>> n;

    h = (b - a) / n;
    cout << "Step size h: " << h << endl;
    
    

    
    //TRAPEOIDAL
    double result1 = trapezoidalRule(a, b, n, h);
    cout << "Result of Trapezoidal Rule: " << result1 << endl;
    
    
    
    //1/3 SIMPSONS RULE
       double result2 = simpsonOneThirdRule(a, b, n, h);
    if (result2 != -1) {
        cout << "Result of Simpson's 1/3 Rule: " << result2 << endl;
    }

    

   //3/8 SIMPSONS RULE
 double result3 = simpsonThreeEighthRule(a, b, n, h);
    if (result3 != -1) {
        cout << "Result of Simpson's 3/8 Rule: " << result3 << endl;
    }


    return 0;
}
