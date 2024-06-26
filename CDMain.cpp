#include <iostream>
#include <cmath>
#include "CD.hpp"

using namespace std;

int main()
{
    int r = 3;
    int c = 4;

    CD m1;
    CD m2(r, c);

    m1.ReadFiles();
    m1.PrintMatrix();

    if (m1.isSymmetric())
    {
        cout << "The matrix is symmetric." << endl;
    }
    else
    {
        cout << "The matrix is not symmetric." << endl;
        return 1;
    }

    vector<CD> decomposed = m1.choleskyDecomposition();

    cout << "L Matrix:" << endl;
    decomposed[0].PrintMatrix();

    cout << "L^T Matrix:" << endl;
    decomposed[1].PrintMatrix();

    return 0;
}
