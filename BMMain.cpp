#include <iostream>
#include <cmath>
using namespace std;
#include "BM.hpp"

int main(void)
{
    BisectionMethod obj(pow(10, -10)); // check agin with lower precisions
    obj.find_interval();
    obj.bisection();
    // obj.get_interval(-2.0,-0.1);
    obj.get_interval(0, 1);
    obj.bisection();
    // obj.get_interval(-1.0,1.0);
    // obj.bisection();
    return 0;
}