#include<bits/stdc++.h>
using namespace std;

int max_iteration =100000;
double tolerance= 1e-9;
double f(const vector<double>& a, double x) {
    double value = 0;
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        value += a[i] * pow(x, n - i - 1);
    }
    return value;
}
void secant(vector<double>&mat)
{   
    int n=mat.size();
    double a=mat[0];
    double b=mat[1];
    double root_max=-(b/a);
    double x1,x2,x3;

    set<double> roots;
    for(int i =0; i<10000 ;i++)
    {
        int iterations=1;
        x1=root_max-i;
        x2=root_max-i-100;
        
        do{
            x3=x2-((f(mat,x2)*(x2-x1))/(f(mat,x2)-f(mat,x1)));
            x1=x2;
            x2=x3;
            iterations++;
        }while(iterations<max_iteration && abs(f(mat,x3))>tolerance);
        
        
        if(iterations<max_iteration){
        double r=round(x3);
        
        if(roots.find(r)==roots.end())
        {
            roots.insert(r);
        }
        }
        if(roots.size()==n)
        {
            break;
        }
        
    }
    cout<<"The roots "<<endl;
    for(auto it:roots)
    {
        cout<<it<<" ";
    }
    
    
    
}





int main()
{
    int maxPow;
    cout << "Enter maximum power of the polynomial: ";
    cin >> maxPow;

    cout << "Enter " << maxPow + 1 << " coefficients: ";
    vector<double> mat(maxPow + 1);
    for (int i = 0; i <= maxPow; ++i) {
        cin >> mat[i];
    }
    
    secant(mat);
    
    
}





