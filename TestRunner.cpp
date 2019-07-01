/*! \mainpage Linear Algebra Library (LaLib) and TestRunner Application
*
* \section intro_sec Introduction
*
* Welcome to Michael's solution for Brain Corporation. Here you will find the shared library as requested. Additionally,
* there is a test application to demonstrate usage of the library and automated test to prove correctness. How is this achieved?
* There is a third package, generator, that takes advantage of https://www.numpy.org/, the fundamental package 
* for scientific computing with Python. This standalone application will generate know matricies and expected results.
* The TestRunner application will consume one of these test case files and run the results of LaLib against it in an automated fashion.
* The results are printed at the end of the test execution.
*
* \section install_sec Build
*
* Run makeall\n
* This simple shell script will compile the shared library into LaLib.so as well as compile and link the TestRunner 
* application to drive the library.
*
* g++ -fPIC LaLib.cpp -shared -o LaLib.so\n
* g++ -o TestRunner TestRunner.cpp LaLib.so
*
* \section exe_sec Execution
*
* Run ./TestRunner -h to view application help 
*
* This test application will load the linear algebra shared library and execute with the following options.\n\n
* Options:\n
*  -t              Transponse\n
*  -m              Multiply\n
*  -tf <filename>  Execute transpose simulations from given file\n
*  -mf <filename>  Execute multiply simulations from given file\n\n

\subsection trans_subc Transpose

@code
$ ./TestRunner -t
Transpose given matrix.
Enter rows and columns of matrix: 3 1

Enter elements of matrix:
Enter element [1][1]: 3
Enter element [2][1]: 8
Enter element [3][1]: 24

Transpose:
 3 8 24
@endcode

\subsection multiply_subc Multiply

@code
$ ./TestRunner -m
Multiply given matrices using the dot product.
Enter rows and columns for first matrix: 2 2
Enter rows and columns for second matrix: 2 2

Enter elements of first matrix:
Enter element [1][1]: 1
Enter element [1][2]: 2
Enter element [2][1]: 3
Enter element [2][2]: 4

Enter elements of second matrix:
Enter element [1][1]: 5
Enter element [1][2]: 6
Enter element [2][1]: 7
Enter element [2][2]: 8

Product:
 19 22
 43 50
@endcode

* \section correctness_sec Prove Correctness
*
* To prove correctness, execute the generator application to produce known results. Then run TestRunner application to
* pull in the random matricies, call LaLib to calculcate a result, and then compare the calculated result against the
* numpy verified result from generator output.
* Note: The assignment indicates to utilize only the C++ standard library to implement the shared library. This is honored indeed.
* However, in order to prove correctness, we must utilize a verifiable and known quantity, and there is no better choice than a package
* such as numpy, especially considering the simplicity and ease of coding that python solution.
*
* \subsection gen_subc Generator
*
* Run the generator to generate known transpose operations as follows:
@code
* ./generator.py -t 1000 -10 10 1 100 > test/many-transpose.test
@endcode
* This will generate 1000 test cases and save in given file. From here, correctness is verfied by executing the TestRunner as follows.
* In this example we run transpose operations:
@code
$ ./TestRunner -tf test/many-transpose.test
Transpose simulations from: test/many-transpose.test
Success. All 1000 transpose test cases match expected result.
@endcode
* If there is a failure, it will be reported as follows.
* In this example we run multiply operations on a generated file, but we open it first and manually edit the file to change one of the expected elements:
@code
./TestRunner -mf test/m6-expectedFail.test
Multiply simulations from: test/m6-expectedFail.test

Failed on multiply test case 9987

matrixA:
14 7 18 8 7 20 6 12 20 20 20 20 3 19 11 5 5 5 5 0 8 10 5
2 19 3 0 4 14 18 3 6 17 11 11 11 13 10 7 13 6 9 7 1 20 3
19 8 0 13 13 4 14 12 3 3 14 15 17 18 20 14 12 3 1 0 8 7 10
18 15 20 14 17 16 5 7 12 4 17 19 17 19 0 2 9 19 4 13 1 10 15
1 5 7 1 0 14 20 6 4 6 11 4 3 8 4 16 2 12 0 1 5 17 10
15 20 19 20 1 8 1 0 14 3 10 9 12 19 3 6 4 14 2 18 12 19 2
2 14 20 18 6 4 3 9 18 0 16 7 16 10 1 4 16 16 17 7 5 17 13
19 3 6 1 1 18 12 3 10 9 15 9 13 10 6 18 5 5 11 5 17 11 20
13 16 6 10 11 7 16 12 19 17 17 5 11 17 15 4 18 10 10 9 11 11 18
14 3 15 20 4 20 16 4 16 10 13 4 9 19 1 17 3 17 13 18 18 16 19

matrixB:
9 7 1 14 10 6 10 0 11 14 5 9
1 0 12 0 1 12 1 6 6 10 8 3
4 12 0 3 2 14 14 14 0 5 12 8
0 0 14 12 2 12 12 9 6 5 10 0
12 7 4 12 6 12 12 11 9 11 6 2
14 9 12 4 6 5 0 8 2 11 13 4
7 2 4 8 3 13 3 10 4 1 7 1
0 3 9 6 11 6 13 8 8 13 8 0
0 1 6 14 14 7 0 12 12 7 5 1
11 14 6 2 9 12 3 14 13 12 10 2
3 12 8 6 1 10 3 9 6 5 3 13
4 4 14 7 5 7 11 8 4 14 0 6
13 8 0 10 5 2 6 4 4 2 0 5
13 0 3 5 5 7 9 3 10 2 1 14
0 13 14 9 7 6 1 6 4 0 0 7
14 0 3 11 6 6 12 14 14 12 14 9
4 9 11 8 5 3 11 9 3 14 3 12
10 10 7 7 9 6 13 9 5 3 2 8
5 3 8 12 5 0 2 13 1 1 6 5
1 10 6 9 3 3 2 10 0 14 3 13
8 8 6 12 6 2 8 11 4 10 7 1
7 5 8 0 14 3 3 3 12 9 12 4
0 11 12 7 10 3 4 11 2 14 13 13

productExpected:
1556 1657 1834 1755 1641 1911 1597 2152 1690 2049 1607 1472
1405 1302 1594 1256 1276 1467 1037 1716 1339 1614 1310 1260
1471 1343 1680 1904 1395 1583 1674 1705 1543 1804 1232 1474
1724 1780 1906 2015 1632 1998 2000 2215 1573 2289 1639 1879
1148 970 1107 982 1050 1134 955 1396 1053 1202 1256 974
1361 1336 1578 1666 1363 1646 1574 1809 1435 1820 1457 1505
1206 1437 1765 1788 1470 1593 1663 216 1319 1764 1538 1520
1620 1530 1530 1833 1532 1340 1338 1956 1432 1947 1613 1541
1573 1858 2112 2164 1853 1968 1684 2427 1799 2267 1723 1769
1917 1792 1952 2302 1854 1905 1868 2606 1757 2294 2118 1859

productCalculated:
1556 1657 1834 1755 1641 1911 1597 2152 1690 2049 1607 1472
1405 1302 1594 1256 1276 1467 1037 1716 1339 1614 1310 1260
1471 1343 1680 1904 1395 1583 1674 1705 1543 1804 1232 1474
1724 1780 1906 2015 1632 1998 2000 2215 1573 2289 1639 1879
1148 970 1107 982 1050 1134 955 1396 1053 1202 1256 974
1361 1336 1578 1666 1363 1646 1574 1809 1435 1820 1457 1505
1206 1437 1765 1788 1470 1593 1663 2126 1319 1764 1538 1520
1620 1530 1530 1833 1532 1340 1338 1956 1432 1947 1613 1541
1573 1858 2112 2164 1853 1968 1684 2427 1799 2267 1723 1769
1917 1792 1952 2302 1854 1905 1868 2606 1757 2294 2118 1859
@endcode
*
* \section trouble_sec Troubleshooting
*
*	-# cygwin can find the *.so library in current directory, but WSL and other environments may not.\n
*		Set the LD_LIBRARY_PATH as follows:\n
*		export LD_LIBRARY_PATH=.
*	-# The Python generator requires numpy; install it as faollows:\n
*		pip install numpy
*	-# Turn on logging in the LaLib by defining LOGGING:\n
*		#define LOGGING
*	-# Useful online matrix calculator:\n
*		https://matrix.reshish.com/multCalculation.php
*	-# Numpy reference:\n
*		https://docs.scipy.org/doc/numpy/reference/index.html
*
* \section roadmap_sec Road Map
*	-# LaLib implements the linear algebra operations as functions. It may become useful one day to wrap these in a C++ class.
*	-# The mf and tf options from TestRunner will execute all the test cases in a given directory
*
* 
*/

/*!
*  \file      TestRunner.cpp
*  \author    Michael Meloney
*  \version   1.1
*  \date      June 26, 2019
*  \brief     Sample application and automated test framework to execute a single operation or run many operations from file
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "LaLib.h"

using namespace std;

/**
* @brief Read all matrix elements from the user; query the user for size, and each element
*
* @param matrix Output matrix vector that is the result of reading from file
*/
void getMatrixFromUser(
	vector<vector<int>> &matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			cout << "Enter element [" << i + 1 << "][" << j + 1 << "]: ";
			cin >> matrix[i][j];
		}
	}
}

/**
* @brief Read all matrix elements from the given stream
*
* @param stream Input stream to read
* @param matrix Output matrix vector that is the result of reading from file
*/
void getMatrixFromStream(
	ifstream &stream,
	vector<vector<int>> &matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			stream >> matrix[i][j];
		}
	}
}

/**
* @brief Check for eof, skip whitespace
*
* @param file File stream to check for end of file
* @returns TRUE if end of file, otherwise FALSE
*/
bool isEof(ifstream &file)
{
	char c = file.peek();
	while (c == '\n'
		|| c == '\r'
		|| c == ' ')
	{
		file.get();
		c = file.peek();
	}

	return file.eof();
}

/**
* @brief Ask the user for matrix size of two matricies, and matrix elements, then calculate product, finally output the result.
*
* @returns 0 for success, otherwise -1
*/
int doMatrixMultiply()
{
	int r1, c1, r2, c2;

	cout << "Multiply given matrices using the dot product."
		<< endl
		<< "Enter rows and columns for first matrix: ";
	cin >> r1 >> c1;
	cout << "Enter rows and columns for second matrix: ";
	cin >> r2 >> c2;

	if (r1 < 1 || c1 < 1 || r2 < 1 || c2 < 1)
	{
		cout << "Invalid input." << endl;
		return -1;
	}

	if (c1 != r2)
	{
		cout << "Column of first matrix not equal to row of second." << endl;
		return -1;
	}

	vector<vector<int>> matrixA(r1, vector<int>(c1, 0));
	vector<vector<int>> matrixB(r2, vector<int>(c2, 0));

	// The result will have the same number of rows as the 1st matrix, 
	// and the same number of columns as the 2nd matrix.
	vector<vector<int>> product(r1, vector<int>(c2, 0));

	cout << endl << "Enter elements of first matrix:" << endl;
	getMatrixFromUser(matrixA);

	cout << endl << "Enter elements of second matrix:" << endl;
	getMatrixFromUser(matrixB);

	matrixMultiply(matrixA, matrixB, product);

	cout << endl << "Product:" << endl;
	matrixPrint(product);
	cout << endl;
}

/**
* @brief Ask the user for matrix size, and matrix elements, then calculate transpose, finally output the result.
*
* @returns 0 for success, otherwise -1
*/
int doMaxtrixTranspose()
{
	int r, c;

	cout << "Transpose given matrix."
		<< endl
		<< "Enter rows and columns of matrix: ";
	cin >> r >> c;

	if (r < 1 || c < 1)
	{
		cout << "Invalid input." << endl;
		return -1;
	}

	vector<vector<int>> matrix(r, vector<int>(c, 0));
	vector<vector<int>> trans(c, vector<int>(r, 0));

	cout << endl << "Enter elements of matrix:" << endl;
	getMatrixFromUser(matrix);

	matrixTranspose(matrix, trans);
	
	cout << endl << "Transpose:" << endl;
	matrixPrint(trans);
	cout << endl;
}

/**
* @brief Read matricies from file and calculate transpose. Then compare against the expected transpose in the input file.
*
* @param filename Filename of input file to read; see generator to discover how to create these files
* @returns 0 for success, otherwise -1
*/
int doMatrixTransposeSimulation(char *filename)
{
	cout << "Transpose simulations from: " << filename << endl;
	ifstream file(filename);

	int count = 0;
	while (file && !isEof(file))
	{
		int r, c;

		file >> r >> c;
		vector<vector<int>> matrix(r, vector<int>(c, 0));
		vector<vector<int>> transExpected(c, vector<int>(r, 0));
		vector<vector<int>> transCalculated(c, vector<int>(r, 0));

		getMatrixFromStream(file, matrix);
		getMatrixFromStream(file, transExpected);

		matrixTranspose(matrix, transCalculated);
		++count;

		bool isEqual = transExpected == transCalculated;

		if (!isEqual)
		{
			cout << endl << "Failed on transpose test case " << count << endl;
			cout << endl << "matrix:" << endl;
			matrixPrint(matrix);
			cout << endl << "transExpected:" << endl;
			matrixPrint(transExpected);
			cout << endl << "transCalculated:" << endl;
			matrixPrint(transCalculated);

			return -1;
		}
	}

	cout << "Success. All " << count << " transpose test cases match expected result." << endl;
	return 0;
}

/**
* @brief Read matricies from file and calculate product. Then compare against the expected product in the input file.
*
* @param filename Filename of input file to read; see generator to discover how to create these files
* @returns 0 for success, otherwise -1
*/
int doMatrixMultiplySimulation(char *filename)
{
	cout << "Multiply simulations from: " << filename << endl;
	ifstream file(filename);

	int count = 0;
	while (file && !isEof(file))
	{
		int r1, c1, r2, c2;

		file >> r1 >> c1;
		vector<vector<int>> matrixA(r1, vector<int>(c1, 0));
		getMatrixFromStream(file, matrixA);

		file >> r2 >> c2;
		vector<vector<int>> matrixB(r2, vector<int>(c2, 0));
		vector<vector<int>> productExpected(r1, vector<int>(c2, 0));
		vector<vector<int>> productCalculated(r1, vector<int>(c2, 0));

		getMatrixFromStream(file, matrixB);
		getMatrixFromStream(file, productExpected);

		matrixMultiply(matrixA, matrixB, productCalculated);
		++count;

		bool isEqual = productExpected == productCalculated;
		
		if (!isEqual)
		{
			cout << endl << "Failed on multiply test case " << count << endl;
			cout << endl << "matrixA:" << endl;
			matrixPrint(matrixA);
			cout << endl << "matrixB:" << endl;
			matrixPrint(matrixB);
			cout << endl << "productExpected:" << endl;
			matrixPrint(productExpected);
			cout << endl << "productCalculated:" << endl;
			matrixPrint(productCalculated);

			return -1;
		}
	}

	cout << "Success. All " << count << " multiply test cases match expected result." << endl;
	return 0;
}

/**
* @brief Get the value of the command option.
*
* @param begin Pointer to beginning of string
* @param end Pointer to end of string
* @param option Option to search for
* @returns Return the string value of the given command option, or NULL if not found
*/
char* getCmdOption(
	char **begin,
	char **end,
	const string &option)
{
	char **itr = find(begin, end, option);
	if (itr != end && ++itr != end)
	{
		return *itr;
	}
	return 0;
}

/**
* @brief Check if a given option exists.
*
* @param begin Pointer to beginning of string
* @param end Pointer to end of string
* @param option Option to search for
* @returns true if option exists, otherwise false
*/
bool cmdOptionExists(
	char **begin,
	char **end,
	const string &option)
{
	return find(begin, end, option) != end;
}

/**
* @brief Main application entry point to take commandline arguments and execute correct options.
*
* @param argc Count of arguments
* @param argv Commandline values
*/
int main(
	int argc, 
	char *argv[])
{
	if (cmdOptionExists(argv, argv + argc, "-h"))
	{
		cout
			<< "Hello Brain!" << endl
			<< "This test application will drive Michael Meloney's linear algebra shared library" << endl
			<< "Options:" << endl
			<< "   -t              Transponse" << endl
			<< "   -m              Multiply" << endl
			<< "   -tf <filename>  Execute transpose simulations from given file" << endl
			<< "   -mf <filename>  Execute multiply simulations from given file" << endl
			<< endl;
		return 0;
	}

	if (cmdOptionExists(argv, argv + argc, "-t"))
	{
		doMaxtrixTranspose();
	}

	if (cmdOptionExists(argv, argv + argc, "-m"))
	{
		doMatrixMultiply();
	}

	char *tf = getCmdOption(argv, argv + argc, "-tf");
	if (NULL != tf)
	{
		doMatrixTransposeSimulation(tf);
	}

	char *mf = getCmdOption(argv, argv + argc, "-mf");
	if (NULL != mf)
	{
		doMatrixMultiplySimulation(mf);
	}

	return 0;
}