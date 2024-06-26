#include <bits/stdc++.h>
#include "NR.hpp"
using namespace std;

double f(double X)
{
    return (X * X - 4 * X + 2);
}
double fdash(double X)
{
    return (2 * X - 4);
}

double NewtonRaphson::Newton_Raphson()
{
    do
    {
        prev = X0;
        X0 = X0 - f(X0) / fdash(X0);
    } while (fabs(X0 - prev) > Tol);

    root = X0;
    cout << "roots of given equation: " << root;
    return root;
}