/*!
*  \file      LaLib.cpp
*  \details   Implementation of LaLib shared library
*  \author    Michael Meloney
*  \version   1.1
*  \date      June 26, 2019
*  \brief     Implement multiply and transpose operations for LaLib
*/

#include <exception>
#include <iostream>
#include "LaLib.h"

/*
For debugging, it may be useful to enable logging; set this #define and recompile.
*/

// #define LOGGING

// See header file for function comments

// Matric operation implementation from:
// https://www.programiz.com/cpp-programming/examples/matrix-multiplication
// https://www.programiz.com/cpp-programming/examples/matrix-transpose


void matrixPrint(
	vector<vector<int>> &matrix,
	bool includeSize)
{
	// Get num rows and columns by querying the size of the matrix
	int r = matrix.size();
	int c = matrix[0].size();

	// Print the size if asked to do so
	if (includeSize)
	{
		cout << r << " " << c << endl;
	}

	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			cout << " " << matrix[i][j];
			if (j == c - 1)
			{
				cout << endl;
			}
		}
	}
}

int matrixTranspose(
	vector<vector<int>> &matrix,
	vector<vector<int>> &trans)
{
#ifdef LOGGING
	cout << endl << "Input Matrix: " << endl;
	matrixPrint(matrix);
#endif

	int r = matrix.size();
	int c = matrix[0].size();

	// Transpose matrix and store result in trans.
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			trans[j][i] = matrix[i][j];
		}
	}

#ifdef LOGGING
	cout << endl << "Transpose of Matrix: " << endl;
	matrixPrint(trans);
#endif

	return 0;
}

int matrixMultiply(
	vector<vector<int>> &matrixA,
	vector<vector<int>> &matrixB,
	vector<vector<int>> &product)
{
#ifdef LOGGING
	cout << endl << "Input MatrixA: " << endl;
	matrixPrint(matrixA);

	cout << endl << "Input MatrixB: " << endl;
	matrixPrint(matrixB);
#endif

	int r1 = matrixA.size();
	int c1 = matrixA[0].size();

	int r2 = matrixB.size();
	int c2 = matrixB[0].size();

	// Multiply matrixA by matrixB and store in product.
	// The algorithm is known as the dot product.
	for (int i = 0; i < r1; ++i)
	{
		for (int j = 0; j < c2; ++j)
		{
			product[i][j] = 0;
			for (int k = 0; k < c1; ++k)
			{
				product[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}

#ifdef LOGGING
	cout << endl << "Product: " << endl;
	matrixPrint(product);
#endif
	
	return 0;
}