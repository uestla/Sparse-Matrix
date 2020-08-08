/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include "../inc/testslib.h"
#include "../inc/SparseMatrixMock.h"


void _multiplicationFail1(void)
{
	SparseMatrix::SparseMatrix<int> m(3, 4);
	std::vector<int> x(3, 1);
	m.multiply(x);
}


void testMultiplicationFail1(void)
{
	std::cout << "multiply() fail #1..." << std::flush;
	assertException("InvalidDimensionsException", _multiplicationFail1);
	std::cout << " OK" << std::endl;
}


void _multiplicationFail2(void)
{
	SparseMatrix::SparseMatrix<int> a(3, 4), b(5, 6);
	a.multiply(b);
}


void testMultiplicationFail2(void)
{
	std::cout << "multiply() fail #2..." << std::flush;
	assertException("InvalidDimensionsException", _multiplicationFail2);
	std::cout << " OK" << std::endl;
}


void testVectorMultiplication(void)
{
	for (int N = 0; N < 5e3; N++) {
		std::cout << "\rvector multiplication... #" << N + 1 << std::flush;

		// generate random vector and matrix
		int rows = rand() % 16 + 1;
		int cols = rand() % 16 + 1;

		std::vector<int> vec = generateRandomVector<int>(cols);

		std::vector<std::vector<int> > classicMatrix = generateRandomMatrix<int>(rows, cols);
		SparseMatrixMock<int> sparseMatrix = SparseMatrixMock<int>::fromVectors(classicMatrix);

		// calculate result manually
		std::vector<int> manualResult = multiplyMatrixByVector(classicMatrix, vec);

		// method
		assertEquals<std::vector<int> >(manualResult, sparseMatrix.multiply(vec), "Incorrect vector multiplication");

		// operator
		assertEquals<std::vector<int> >(manualResult, sparseMatrix * vec, "Incorrect vector multiplication (operator *)");
	}

	std::cout << " OK" << std::endl;
}


void testMatricesMultiplication(void)
{
	for (int N = 0; N < 5e3; N++) {
		std::cout << "\rmatrices multiplication... #" << N + 1 << std::flush;

		// generate random matrices
		int rowsA = rand() % 16 + 1;
		int colsArowsB = rand() % 16 + 1;
		int colsB = rand() % 16 + 1;

		std::vector<std::vector<int> > classicMatrixA = generateRandomMatrix<int>(rowsA, colsArowsB);
		SparseMatrixMock<int> sparseMatrixA = SparseMatrixMock<int>::fromVectors(classicMatrixA);

		std::vector<std::vector<int> > classicMatrixB = generateRandomMatrix<int>(colsArowsB, colsB);
		SparseMatrixMock<int> sparseMatrixB = SparseMatrixMock<int>::fromVectors(classicMatrixB);

		// calculate result manually
		std::vector<std::vector<int> > manualResult = multiplyMatrices(classicMatrixA, classicMatrixB);

		// method
		assertEquals<SparseMatrix::SparseMatrix<int>, std::vector<std::vector<int> > >(
			sparseMatrixA.multiply(sparseMatrixB),
			manualResult,
			"Incorrect matrices multiplication"
		);

		// operator
		assertEquals<SparseMatrix::SparseMatrix<int>, std::vector<std::vector<int> > >(
			sparseMatrixA * sparseMatrixB,
			manualResult,
			"Incorrect matrices multiplication (operator *)"
		);
	}

	std::cout << " OK" << std::endl;
}
