#include <iostream>
#include <cmath>
#include "GS.hpp"

using namespace std;

int main()
{
    int r = 3;
    int c = 4;
    // int r1 = 0;
    // int r2 = 1;
    // int index = 0;

    Matrix m1;
    Matrix m2(r, c);
    m1.ReadFiles();
    m1.makeDiagonallyDominant();
    m1.GaussSeidel();

    return 0;
}