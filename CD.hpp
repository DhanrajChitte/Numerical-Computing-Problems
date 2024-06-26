#ifndef CD_HPP
#define CD_HPP

#include <iostream>
#include <vector>
using namespace std;

class CD
{
public:
    int rows;
    int cols;
    double **mat;

    CD();
    CD(int r, int c);
    CD(const CD &other);            // Copy constructor
    CD &operator=(const CD &other); // Copy assignment operator
    ~CD();

    void ReadFiles();
    bool isSymmetric();
    double getLii(int, double **);
    double getLij(int, int, double **);
    vector<vector<double>> transpose();
    vector<CD> choleskyDecomposition();

    void PrintMatrix();
};

#endif