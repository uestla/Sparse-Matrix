/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include "../testslib.h"
#include "../SparseMatrixMock.h"


void _subtractionFail1(void)
{
	SparseMatrix<int> a(3, 4), b(3, 5);
	a.subtract(b);
}


void testSubtractionFail1(void)
{
	cout << "subtract() fail #1..." << flush;
	assertException("InvalidDimensionsException", _subtractionFail1);
	cout << " OK" << endl;
}


void _subtractionFail2(void)
{
	SparseMatrix<int> a(3, 4), b(4, 4);
	a.subtract(b);
}


void testSubtractionFail2(void)
{
	cout << "subtract() fail #2..." << flush;
	assertException("InvalidDimensionsException", _subtractionFail2);
	cout << " OK" << endl;
}


void _subtractionFail3(void)
{
	SparseMatrix<int> a(3, 4), b(4, 5);
	a.subtract(b);
}


void testSubtractionFail3(void)
{
	cout << "subtract() fail #3..." << flush;
	assertException("InvalidDimensionsException", _subtractionFail3);
	cout << " OK" << endl;
}


void testSubtraction(void)
{
	for (int N = 0; N < 5e3; N++) {
		cout << "\rmatrices subtraction... #" << N + 1 << flush;

		// generate random matrices
		int rows = rand() % 16 + 1;
		int cols = rand() % 16 + 1;

		vector<vector<int> > classicMatrixA = generateRandomMatrix<int>(rows, cols);
		SparseMatrixMock<int> sparseMatrixA = SparseMatrixMock<int>::fromVectors(classicMatrixA);

		vector<vector<int> > classicMatrixB = generateRandomMatrix<int>(rows, cols);
		SparseMatrixMock<int> sparseMatrixB = SparseMatrixMock<int>::fromVectors(classicMatrixB);

		// calculate result manually
		vector<vector<int> > manualResult(rows, vector<int>(cols, 0));

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				manualResult[i][j] += classicMatrixA[i][j] - classicMatrixB[i][j];
			}
		}

		// method
		assertEquals<SparseMatrix<int>, vector<vector<int> > >(
			sparseMatrixA.subtract(sparseMatrixB),
			manualResult,
			"Incorrect matrices subtract"
		);

		// operator
		assertEquals<SparseMatrix<int>, vector<vector<int> > >(
			sparseMatrixA - sparseMatrixB,
			manualResult,
			"Incorrect matrices subtract (operator -)"
		);
	}

	cout << " OK" << endl;
}
