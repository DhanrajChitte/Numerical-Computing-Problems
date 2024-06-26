#include <iostream>
#include <cmath>
#include "GE.hpp"

using namespace std;

int main()
{
    int r = 3;
    int c = 4;

    GE m1;
    GE m2(r, c);
    m1.ReadFiles();
    m1.UT();
    m1.BackSubstitution();

    return 0;
}
