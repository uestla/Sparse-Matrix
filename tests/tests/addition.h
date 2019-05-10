/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include "../testslib.h"
#include "../SparseMatrixMock.h"


void _additionFail1(void)
{
	SparseMatrix<int> a(3, 4), b(3, 5);
	a.add(b);
}


void testAdditionFail1(void)
{
	cout << "add() fail #1..." << flush;
	assertException("InvalidDimensionsException", _additionFail1);
	cout << " OK" << endl;
}


void _additionFail2(void)
{
	SparseMatrix<int> a(3, 4), b(4, 4);
	a.add(b);
}


void testAdditionFail2(void)
{
	cout << "add() fail #2..." << flush;
	assertException("InvalidDimensionsException", _additionFail2);
	cout << " OK" << endl;
}


void _additionFail3(void)
{
	SparseMatrix<int> a(3, 4), b(4, 5);
	a.add(b);
}


void testAdditionFail3(void)
{
	cout << "add() fail #3..." << flush;
	assertException("InvalidDimensionsException", _additionFail3);
	cout << " OK" << endl;
}


void testAddition(void)
{
	for (int N = 0; N < 5e3; N++) {
		cout << "\rmatrices addition... #" << N + 1 << flush;

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
				manualResult[i][j] += classicMatrixA[i][j] + classicMatrixB[i][j];
			}
		}

		// method
		assertEquals<SparseMatrix<int>, vector<vector<int> > >(
			sparseMatrixA.add(sparseMatrixB),
			manualResult,
			"Incorrect matrices addition"
		);

		// operator
		assertEquals<SparseMatrix<int>, vector<vector<int> > >(
			sparseMatrixA + sparseMatrixB,
			manualResult,
			"Incorrect matrices addition (operator +)"
		);
	}

	cout << " OK" << endl;
}
