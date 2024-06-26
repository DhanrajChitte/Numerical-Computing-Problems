#include <iostream>
#include <cmath>
#include "GE.hpp"
#include <fstream>
using namespace std;

string fileName_L = "M3.txt";
string fileName_R = "M1.txt";

// Default constructor implementation
GE::GE()
{
    // Initialize rows and cols if needed
    rows = 0;
    cols = 0;
    mat = nullptr; // Ensure mat is initialized to nullptr
}

// Constructor implementation
GE::GE(int r, int c) : rows(r), cols(c)
{
    // Dynamically Allocate the memory for the array
    mat = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new double[cols];
    }
}

// Destructor implementation
GE::~GE()
{
    // Deallocate memory for the matrix
    for (int i = 0; i < rows; i++)
    {
        delete[] mat[i];
    }
    delete[] mat;
}

void GE::ReadFiles()
{
    ifstream fin;
    fin.open("M3.txt");

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
    fin.open("M1.txt");

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

void GE::UT()
{
    for (int i = 0; i < rows; i++)
    {
        double pivot = mat[i][i];
        if (pivot != 0) // Prevent division by zero
        {
            for (int j = 0; j < cols; j++)
            {
                mat[i][j] = mat[i][j] / pivot;
            }

            for (int k = i + 1; k < rows; k++)
            {
                double temp1 = mat[k][i];
                for (int j = 0; j < cols; j++)
                {
                    mat[k][j] = mat[k][j] - (temp1 * mat[i][j]);
                }
            }
        }
    }
    cout << "Matrix after converting the upper triangular" << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << mat[i][j] << "         ";
        }
        cout << endl;
    }
}

void GE::BackSubstitution()
{
    double ans[cols - 2];
    // int ans[2] / [rows - 1] = mat[rows - 1][cols - 1];
    double lhs = 0.0;
    ans[cols - 2] = mat[rows - 1][cols - 1]; // value of the last variable stored

    for (int r = rows - 2; r >= 0; r--) // starting from the second last row
    {
        for (int c = r + 1; c < cols - 1; c++) // starting from the element just after the pivot position
        {
            lhs += mat[r][c] * ans[c];
        }

        ans[r] = (mat[r][cols - 1] - lhs) / mat[r][r];
        lhs = 0;
    }

    cout << "Solution:" << endl;
    for (int i = 0; i < cols - 1; i++)
    {
        cout << "x" << i + 1 << " = " << ans[i] << endl;
    }
}
