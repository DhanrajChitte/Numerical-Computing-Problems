#include <iostream>
// #ifndef MATRIX_HPP
// #define MATRIX_HPP

class GE
{
public:
    int rows;
    int cols;
    int index;
    double **mat;

    GE();
    GE(int r, int c);
    ~GE(); // Destructor Declaration

    void ReadFiles();
    void UT();
    void BackSubstitution();
};

// #endif // MATRIX_HPP
