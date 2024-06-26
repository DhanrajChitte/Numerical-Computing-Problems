#include "FP.hpp"

double FixedPoint::Function(double x)
{
    return ((x * x + 2) / 4);
}

double FixedPoint::RootFinding()
{
    do
    {
        prev = X0;
        X0 = Function(X0);
    } while (fabs(X0 - prev) > Tol);

    root = X0;
    cout << "roots of given equation: " << root;
    return root;
}