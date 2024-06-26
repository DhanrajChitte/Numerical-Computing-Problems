#include <bits/stdc++.h>
using namespace std;
class FixedPoint
{
public:
    double X0 = 0;
    // cout << "enter the x0 value: " << Fx.X0 << endl;
    double prev;
    double root;
    double Tol = 0.00001;

    double RootFinding();
    double Function(double);
};