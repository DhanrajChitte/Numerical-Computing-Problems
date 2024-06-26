#include <iostream>
#include <cmath>
#include "LU.hpp"

using namespace std;

int main()
{
    int r = 3;
    int c = 4;

    LU m1;

    // Read matrices from files
    m1.ReadFiles();

    // Print the original combined matrix
    cout << "Original matrix:" << endl;
    m1.PrintMatrix();

    // Perform LU decomposition
    vector<LU> decomposition = m1.lowerUpperDecomposition();

    // The first element in the vector is the U matrix
    LU U = decomposition[0];
    // The second element in the vector is the L matrix
    LU L = decomposition[1];

    // Print L matrix
    cout << "L matrix:" << endl;
    L.PrintMatrix();

    // Print U matrix
    cout << "U matrix:" << endl;
    U.PrintMatrix();

    return 0;
}
