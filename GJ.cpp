#include <iostream>
#include <cmath>
#include <fstream>
#include "GJ.hpp"

using namespace std;

const double tol = 0.0001;

string fileName_L = "M3.txt";
string fileName_R = "M1.txt";

// Default constructor implementation
Matrix::Matrix()
{
    // Initialize rows and cols if needed
    rows = 0;
    cols = 0;
    mat = nullptr; // Ensure mat is initialized to nullptr
}

// Constructor implementation
Matrix::Matrix(int r, int c) : rows(r), cols(c)
{
    // Dynamically Allocate the memory for the array
    mat = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new double[cols];
    }
}

// Destructor implementation
Matrix::~Matrix()
{
    // Deallocate memory for the matrix
    for (int i = 0; i < rows; i++)
    {
        delete[] mat[i];
    }
    delete[] mat;
}

void Matrix::ReadFiles()
{
    ifstream fin;
    fin.open(fileName_L);

    fin >> rows >> cols;

    // Dynamically Allocate the memory for the array
    mat = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new double[cols];
    }

    cout << "\n Rows::" << rows << "\t cols::" << cols << endl;

    // Read the matrix from the first file
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < (cols - 1); j++)
        {
            fin >> mat[i][j];
        }
    }

    // Print the matrix Elements
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << mat[i][j] << "   ";
        }
        cout << endl;
    }

    fin.close();

    // open second file
    fin.open(fileName_R);

    // Read the matrix elements from second file
    for (int i = 0; i < rows; i++)
    {
        fin >> mat[i][cols - 1];
    }

    cout << "The Final Matrix is after combine elements of both the files" << endl;

    // Print the combine matrix
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

int Matrix::getDDRowAt(int r)
{
    for (int i = r + 1; i < rows; i++)
    {
        double sum = 0.0;
        for (int c = 0; c < cols - 1; c++)
        {
            if (r != c)
            {
                sum += fabs(mat[i][c]);
            }
        }
        if (fabs(mat[i][r]) >= sum)
        {
            return i;
        }
    }
    cout << "No Diagonally Dominant row found after Row " << r << endl;
    return -1;
}

void Matrix::SwapRows(int r1, int r2)
{
    for (int i = 0; i < cols; i++)
    {
        double tmp;
        tmp = mat[r1][i];
        mat[r1][i] = mat[r2][i];
        mat[r2][i] = tmp;
    }
}

bool Matrix::isDiagonallyDominant()
{
    for (int r = 0; r < rows; r++)
    {
        double sum = 0;
        for (int c = 0; c < cols - 1; c++)
        {
            if (r != c)
            {
                sum += fabs(mat[r][c]);
            }
        }
        if (fabs(mat[r][r]) < sum)
        {
            return false;
        }
    }
    return true;
}

bool Matrix::makeDiagonallyDominant()
{
    if (isDiagonallyDominant())
    {
        cout << "Matrix is already diagonally dominant" << endl;
        return true; // No need to proceed further
    }

    int r;
    for (r = 0; r < rows; r++)
    {
        double sum = 0;
        for (int c = 0; c < cols - 1; c++)
        {
            if (r != c)
            {
                sum += fabs(mat[r][c]);
            }
        }
        if (sum > fabs(mat[r][r]))
        {
            cout << "Row " << r + 1 << " can be made diagonally dominant." << endl;
            int index = getDDRowAt(r);
            if (index != -1)
            {
                SwapRows(r, index);
                cout << "Swapped rows " << r + 1 << " and " << index + 1 << endl;
            }
            else
            {
                cout << "Not Possible to Make Diagonally Dominant" << endl;
                return false;
            }
        }
    }

    cout << "Diagonally Dominant Matrix:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << mat[i][j] << "   ";
        }
        cout << endl;
    }

    return true;
}

void Matrix::GaussJacobi()
{
    double *ans = new double[cols - 1];
    double *prev = new double[cols - 1];

    for (int i = 0; i < cols - 1; i++)
    {
        ans[i] = 0;
        prev[i] = 0;
    }

    while (true)
    {
        bool done = true;

        for (int r = 0; r < rows; r++)
        {
            double sum = 0.0;

            for (int c = 0; c < cols - 1; c++)
            {
                if (r != c)
                {
                    sum += mat[r][c] * prev[c];
                }
            }

            ans[r] = (mat[r][cols - 1] - sum) / mat[r][r];

            if (fabs(ans[r] - prev[r]) > tol)
            {
                done = false;
            }
        }

        for (int i = 0; i < cols - 1; i++)
        {
            prev[i] = ans[i];
        }

        if (done)
        {
            break;
        }
    }

    cout << "Solution:" << endl;
    for (int i = 0; i < cols - 1; i++)
    {
        cout << "x" << i + 1 << " = " << ans[i] << endl;
    }

    delete[] ans;
    delete[] prev;
}
