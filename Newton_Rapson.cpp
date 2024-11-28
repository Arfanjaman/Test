#include<bits/stdc++.h>
using namespace std;

double tolerance= 1e-9;
double f(const vector<double>& a, double x) {
    double value = 0;
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        value += a[i] * pow(x, n - i - 1);
    }
    return value;
}

double df(const vector<double>& a, double x) {
    double value = 0;
    int n = a.size();
    for (int i = 0; i < n - 1; ++i) { 
        value += a[i] * (n - i - 1) * pow(x, n - i - 2);
    }
    return value;
}



void nr(vector<double>&mat)
{   
    
    set<double> roots;
    int n=mat.size();
    double a=mat[0];
    double b=mat[1];
    double root_max=-(b/a);
     int iterations=1;
    while(roots.size()<n){
    
        double x0,x1;
        x0=root_max;
        root_max--;
    

       iterations++;
       if(iterations>100000){
        cout<<"Roots not found"<<endl;
        break;
       }
        
        
        while(abs(f(mat,x0))>tolerance)
        {
            x1=x0-(f(mat,x0)/df(mat,x0));
            x0=x1;
            
        }
        
        double r=round(x0);
        
        if(roots.find(r)==roots.end())
        {
            roots.insert(r);
        }
        
        if(roots.size()==5)// does not work and runs indefinitely when i use n instead of 5
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
    
    nr(mat);
    
    
}





