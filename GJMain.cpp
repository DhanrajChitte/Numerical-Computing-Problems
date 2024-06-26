#include <iostream>
#include "GJ.hpp"

using namespace std;

int main()
{
    int r = 3;
    int c = 4;

    Matrix m1;
    Matrix m2(r, c);
    m1.ReadFiles();
    m1.makeDiagonallyDominant();
    m1.GaussJacobi();

    return 0;
}
