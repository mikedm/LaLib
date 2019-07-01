/*!
 *  \file      LaLib.h
 *  \package   LaLib
 *  \details   Include this header file with your application to make use of LaLib shared library.
 *  \author    Michael Meloney
 *  \version   1.1
 *  \date      June 26, 2019
 *  \brief     Header File of LaLib, a linear algebra shared library for client with awful case of not-invented-here syndrome. All matrix operation results are passed in by reference. Modern compilers will utilize return value optimization (RVO) so we could alternatively design the interface to return the result vector without a performance impact. Pass all matricies by reference because if passed by value then a copy of the object must be made.
 */

#ifndef LALIB_H
#define LALIB_H

#include <vector>
using namespace std;

/**
 * @brief For the given matrix, print each element in standard row/column format
 *
 * @param matrix The input matrix to print.
 * @param includeSize Optional parameter (default false) to include the size of the matrix (number of rows/columns)
 */
void matrixPrint(
	vector<vector<int>> &matrix,
	bool includeSize = false);

/**
* @brief For the given matrix, transpose the elements and set the result in trans
*
* @param matrix Input matrix to transpose
* @param trans Result transpose matrix
* @returns -1 if failed to calculate transpose operation, 0 for success
*/
int matrixTranspose(
	vector<vector<int>> &matrix, 
	vector<vector<int>> &trans);

/**
* @brief Multiply the given matricies and set the result in product
*
* @param matrixA Input matrix to multiply
* @param matrixB Input matrix to multiply
* @param product Result product matrix
* @returns -1 if failed to calculate product operation, 0 for success
*/
int matrixMultiply(
	vector<vector<int>> &matrixA,
	vector<vector<int>> &matrixB,
	vector<vector<int>> &product);

#endif