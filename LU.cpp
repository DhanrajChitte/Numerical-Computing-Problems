#include <iostream>
#include <cmath>
#include "LU.hpp"
#include <fstream>
using namespace std;

string fileName_L = "M3.txt";
string fileName_R = "M1.txt";

// Default constructor implementation
LU::LU() : rows(0), cols(0), mat(nullptr) {}
/* CD::CD()
{
    // Initialize rows and cols if needed
    rows = 0;
    cols = 0;
    mat = nullptr; // Ensure mat is initialized to nullptr
}*/

// Constructor implementation
LU::LU(int r, int c) : rows(r), cols(c)
{
    // Dynamically Allocate the memory for the array
    mat = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new double[cols]();
    }
}

// Destructor implementation
// Destructor implementation
LU::~LU()
{
    if (mat)
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] mat[i];
        }
        delete[] mat;
        mat = nullptr; // Avoid dangling pointer
    }
}

// Copy constructor
LU::LU(const LU &other) : rows(other.rows), cols(other.cols)
{
    if (other.mat)
    {
        mat = new double *[rows];
        for (int i = 0; i < rows; i++)
        {
            mat[i] = new double[cols];
            for (int j = 0; j < cols; j++)
            {
                mat[i][j] = other.mat[i][j];
            }
        }
    }
    else
    {
        mat = nullptr;
    }
}

// Copy assignment operator
LU &LU::operator=(const LU &other)
{
    if (this == &other)
        return *this;

    // Deallocate current memory
    for (int i = 0; i < rows; i++)
    {
        delete[] mat[i];
    }
    delete[] mat;

    // Allocate new memory and copy elements
    rows = other.rows;
    cols = other.cols;
    if (other.mat)
    {
        mat = new double *[rows];
        for (int i = 0; i < rows; i++)
        {
            mat[i] = new double[cols];
            for (int j = 0; j < cols; j++)
            {
                mat[i][j] = other.mat[i][j];
            }
        }
    }
    else
    {
        mat = nullptr;
    }

    return *this;
}

void LU::ReadFiles()
{
    ifstream fin;

    // Deallocate previous memory if any
    if (mat)
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] mat[i];
        }
        delete[] mat;
        mat = nullptr;
    }

    fin.open(fileName_L);
    if (!fin)
    {
        cerr << "Error opening file: " << fileName_L << endl;
        exit(1);
    }

    fin >> rows >> cols;

    // Allocate memory for the matrix
    mat = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new double[cols]();
    }

    cout << "\nRows::" << rows << "\tcols::" << cols << endl;

    // Read the matrix from the first file
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < (cols - 1); j++)
        {
            if (!(fin >> mat[i][j]))
            {
                cerr << "Error reading matrix element from " << fileName_L << endl;
                exit(1);
            }
        }
    }

    fin.close();

    // Open the second file
    fin.open(fileName_R);
    if (!fin)
    {
        cerr << "Error opening file: " << fileName_R << endl;
        exit(1);
    }

    // Read the matrix elements from the second file
    for (int i = 0; i < rows; i++)
    {
        if (!(fin >> mat[i][cols - 1]))
        {
            cerr << "Error reading matrix element from " << fileName_R << endl;
            exit(1);
        }
    }

    cout << "The Final Matrix is after combining elements of both the files" << endl;

    // Print the combined matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << mat[i][j] << "   ";
        }
        cout << endl;
    }

    fin.close();
}

void LU::PrintMatrix()
{
    // int r = this->rows, c = this->cols;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "\n";
}

vector<LU> LU::lowerUpperDecomposition()
{
    vector<LU> D;
    LU M1(this->rows, this->cols); // L matrix
    LU M2(this->rows, this->cols); // U matrix
    double **L = M1.mat;
    double **U = M2.mat;

    // Initialize L matrix to identity
    for (int i = 0; i < rows; i++)
    {
        L[i][i] = 1; // Change from U to L
    }

    // Crout's method
    for (int r = 0; r < rows; r++)
    {
        for (int c = r; c < cols - 1; c++) // U matrix calculation
        {
            U[r][c] = computeU(mat, U, L, r, c); // Adjusted indices and function call
        }
        for (int c = r + 1; c < rows; c++) // L matrix calculation
        {
            L[c][r] = computeL(mat, L, U, c, r); // Adjusted indices and function call
        }
    }

    D.push_back(M1);
    D.push_back(M2);
    return D;
}

double LU::computeL(double **mat, double **L, double **U, int row, int col)
{
    double ans = mat[row][col];
    for (int k = 0; k < col; k++)
    {
        ans -= L[row][k] * U[k][col];
    }
    return ans / U[col][col]; // Added division by U[col][col]
}

double LU::computeU(double **mat, double **U, double **L, int row, int col)
{
    double ans = mat[row][col];
    for (int k = 0; k < row; k++)
    {
        ans -= L[row][k] * U[k][col];
    }
    return ans; // Removed division by L[row][row]
}
