/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include "../testslib.h"
#include "../SparseMatrixMock.h"


void _multiplicationFail1(void)
{
	SparseMatrix<int> m(3, 4);
	vector<int> x(3, 1);
	m.multiply(x);
}


void testMultiplicationFail1(void)
{
	cout << "multiply() fail #1..." << flush;
	assertException("InvalidDimensionsException", _multiplicationFail1);
	cout << " OK" << endl;
}


void _multiplicationFail2(void)
{
	SparseMatrix<int> a(3, 4), b(5, 6);
	a.multiply(b);
}


void testMultiplicationFail2(void)
{
	cout << "multiply() fail #2..." << flush;
	assertException("InvalidDimensionsException", _multiplicationFail2);
	cout << " OK" << endl;
}


void testVectorMultiplication(void)
{
	for (int N = 0; N < 5e3; N++) {
		cout << "\rvector multiplication... #" << N + 1 << flush;

		// generate random vector and matrix
		int rows = rand() % 16 + 1;
		int cols = rand() % 16 + 1;

		vector<int> vec = generateRandomVector<int>(cols);

		vector<vector<int> > classicMatrix = generateRandomMatrix<int>(rows, cols);
		SparseMatrixMock<int> sparseMatrix = SparseMatrixMock<int>::fromVectors(classicMatrix);

		// calculate result manually
		vector<int> manualResult(rows, 0);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				manualResult[i] += classicMatrix[i][j] * vec[j];
			}
		}

		// method
		assertEquals<vector<int> >(manualResult, sparseMatrix.multiply(vec), "Incorrect vector multiplication");

		// operator
		assertEquals<vector<int> >(manualResult, sparseMatrix * vec, "Incorrect vector multiplication (operator *)");
	}

	cout << " OK" << endl;
}


void testMatricesMultiplication(void)
{
	for (int N = 0; N < 5e3; N++) {
		cout << "\rmatrices multiplication... #" << N + 1 << flush;

		// generate random matrices
		int rowsA = rand() % 16 + 1;
		int colsArowsB = rand() % 16 + 1;
		int colsB = rand() % 16 + 1;

		vector<vector<int> > classicMatrixA = generateRandomMatrix<int>(rowsA, colsArowsB);
		SparseMatrixMock<int> sparseMatrixA = SparseMatrixMock<int>::fromVectors(classicMatrixA);

		vector<vector<int> > classicMatrixB = generateRandomMatrix<int>(colsArowsB, colsB);
		SparseMatrixMock<int> sparseMatrixB = SparseMatrixMock<int>::fromVectors(classicMatrixB);

		// calculate result manually
		vector<vector<int> > manualResult(rowsA, vector<int>(colsB, 0));

		for (int i = 0; i < rowsA; i++) {
			for (int j = 0; j < colsB; j++) {
				manualResult[i][j] = 0;

				for (int k = 0; k < colsArowsB; k++) { // rows in B
					manualResult[i][j] += classicMatrixA[i][k] * classicMatrixB[k][j];
				}
			}
		}

		// method
		assertEquals<SparseMatrix<int>, vector<vector<int> > >(
			sparseMatrixA.multiply(sparseMatrixB),
			manualResult,
			"Incorrect matrices multiplication"
		);

		// operator
		assertEquals<SparseMatrix<int>, vector<vector<int> > >(
			sparseMatrixA * sparseMatrixB,
			manualResult,
			"Incorrect matrices multiplication (operator *)"
		);
	}

	cout << " OK" << endl;
}
