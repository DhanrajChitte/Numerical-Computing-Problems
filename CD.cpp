#include <iostream>
#include <cmath>
#include "CD.hpp"
#include <fstream>
using namespace std;

string fileName_L = "M3.txt";
string fileName_R = "M1.txt";

// Default constructor implementation
CD::CD() : rows(0), cols(0), mat(nullptr) {}
/* CD::CD()
{
    // Initialize rows and cols if needed
    rows = 0;
    cols = 0;
    mat = nullptr; // Ensure mat is initialized to nullptr
}*/

// Constructor implementation
CD::CD(int r, int c) : rows(r), cols(c)
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
CD::~CD()
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
CD::CD(const CD &other) : rows(other.rows), cols(other.cols)
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
CD &CD::operator=(const CD &other)
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

void CD::ReadFiles()
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

void CD::PrintMatrix()
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

bool CD::isSymmetric()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols - 1; j++)
        {
            if (i > j)
            {
                if (mat[i][j] != mat[j][i])
                    return false;
            }
        }
    }
    return true;
}

vector<vector<double>> CD::transpose()
{
    vector<vector<double>> M(cols, vector<double>(rows)); // Adjusted dimensions for transpose
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            M[j][i] = mat[i][j]; // Correctly transposing the matrix
        }
    }
    return M;
}

double CD::getLii(int i, double **L)
{
    double sum = 0.0;
    for (int k = 0; k < i; k++)
    {
        sum += pow(L[i][k], 2);
    }
    return sqrt(mat[i][i] - sum);
}

double CD::getLij(int i, int j, double **L)
{
    double sum = 0.0;
    for (int k = 0; k < j; k++)
    {
        sum += L[i][k] * L[j][k];
    }
    return (mat[i][j] - sum) / L[j][j];
}

vector<CD> CD::choleskyDecomposition()
{
    vector<CD> Result;
    CD L1(this->rows, this->cols);
    CD L2(this->rows, this->cols);
    double **L = L1.mat;

    if (!this->isSymmetric())
    {
        cerr << "Matrix is not symmetric. We can't factorize via Cholesky Method!" << endl;
        exit(1);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j <= i; j++) // Only process the lower triangular part
        {
            if (i == j)
            {
                L[i][i] = getLii(i, L); // Diagonal elements
                if (L[i][i] <= 0)
                {
                    cerr << "Matrix is not positive definite." << endl;
                    exit(1);
                }
            }
            else
            {
                L[i][j] = getLij(i, j, L); // Lower triangular non-diagonal elements
            }
        }
    }

    vector<vector<double>> T = L1.transpose(); // Transpose the lower triangular matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            L2.mat[i][j] = T[i][j]; // Assign transposed values to L2
        }
    }

    Result.push_back(L1);
    Result.push_back(L2);
    return Result;
}
