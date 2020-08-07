/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include "../inc/testslib.h"
#include "../inc/SparseMatrixMock.h"


void _subtractionFail1(void)
{
	SparseMatrix::SparseMatrix<int> a(3, 4), b(3, 5);
	a.subtract(b);
}


void testSubtractionFail1(void)
{
	std::cout << "subtract() fail #1..." << std::flush;
	assertException("InvalidDimensionsException", _subtractionFail1);
	std::cout << " OK" << std::endl;
}


void _subtractionFail2(void)
{
	SparseMatrix::SparseMatrix<int> a(3, 4), b(4, 4);
	a.subtract(b);
}


void testSubtractionFail2(void)
{
	std::cout << "subtract() fail #2..." << std::flush;
	assertException("InvalidDimensionsException", _subtractionFail2);
	std::cout << " OK" << std::endl;
}


void _subtractionFail3(void)
{
	SparseMatrix::SparseMatrix<int> a(3, 4), b(4, 5);
	a.subtract(b);
}


void testSubtractionFail3(void)
{
	std::cout << "subtract() fail #3..." << std::flush;
	assertException("InvalidDimensionsException", _subtractionFail3);
	std::cout << " OK" << std::endl;
}


void testSubtraction(void)
{
	for (int N = 0; N < 5e3; N++) {
		std::cout << "\rmatrices subtraction... #" << N + 1 << std::flush;

		// generate random matrices
		int rows = rand() % 16 + 1;
		int cols = rand() % 16 + 1;

		std::vector<std::vector<int> > classicMatrixA = generateRandomMatrix<int>(rows, cols);
		SparseMatrixMock<int> sparseMatrixA = SparseMatrixMock<int>::fromVectors(classicMatrixA);

		std::vector<std::vector<int> > classicMatrixB = generateRandomMatrix<int>(rows, cols);
		SparseMatrixMock<int> sparseMatrixB = SparseMatrixMock<int>::fromVectors(classicMatrixB);

		// calculate result manually
		std::vector<std::vector<int> > manualResult = subtractMatrices(classicMatrixA, classicMatrixB);

		// method
		assertEquals<SparseMatrix::SparseMatrix<int>, std::vector<std::vector<int> > >(
			sparseMatrixA.subtract(sparseMatrixB),
			manualResult,
			"Incorrect matrices subtract"
		);

		// operator
		assertEquals<SparseMatrix::SparseMatrix<int>, std::vector<std::vector<int> > >(
			sparseMatrixA - sparseMatrixB,
			manualResult,
			"Incorrect matrices subtract (operator -)"
		);
	}

	std::cout << " OK" << std::endl;
}
