#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix
{
public:
    int rows;
    int cols;
    int index;
    double **mat;

    Matrix();
    Matrix(int r, int c);
    ~Matrix(); // Destructor Declaration

    void ReadFiles();
    bool isDiagonallyDominant();
    bool makeDiagonallyDominant();
    int getDDRowAt(int r);
    void SwapRows(int r1, int r2);
    void GaussJacobi();
    int norm(int r);
};

#endif
