#ifndef CD_HPP
#define CD_HPP

#include <iostream>
#include <vector>
using namespace std;

class LU
{
public:
    int rows;
    int cols;
    double **mat;

    LU();
    LU(int r, int c);
    LU(const LU &other);            // Copy constructor
    LU &operator=(const LU &other); // Copy assignment operator
    ~LU();

    void ReadFiles();
    void PrintMatrix();
    double computeL(double **, double **, double **, int, int);
    double computeU(double **, double **, double **, int, int);
    vector<LU> lowerUpperDecomposition();
};

#endif