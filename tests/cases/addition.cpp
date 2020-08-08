/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include "../inc/testslib.h"
#include "../inc/SparseMatrixMock.h"


void _additionFail1(void)
{
	SparseMatrix::SparseMatrix<int> a(3, 4), b(3, 5);
	a.add(b);
}


void testAdditionFail1(void)
{
	std::cout << "add() fail #1..." << std::flush;
	assertException("InvalidDimensionsException", _additionFail1);
	std::cout << " OK" << std::endl;
}


void _additionFail2(void)
{
	SparseMatrix::SparseMatrix<int> a(3, 4), b(4, 4);
	a.add(b);
}


void testAdditionFail2(void)
{
	std::cout << "add() fail #2..." << std::flush;
	assertException("InvalidDimensionsException", _additionFail2);
	std::cout << " OK" << std::endl;
}


void _additionFail3(void)
{
	SparseMatrix::SparseMatrix<int> a(3, 4), b(4, 5);
	a.add(b);
}


void testAdditionFail3(void)
{
	std::cout << "add() fail #3..." << std::flush;
	assertException("InvalidDimensionsException", _additionFail3);
	std::cout << " OK" << std::endl;
}


void testAddition(void)
{
	for (int N = 0; N < 5e3; N++) {
		std::cout << "\rmatrices addition... #" << N + 1 << std::flush;

		// generate random matrices
		int rows = rand() % 16 + 1;
		int cols = rand() % 16 + 1;

		std::vector<std::vector<int> > classicMatrixA = generateRandomMatrix<int>(rows, cols);
		SparseMatrixMock<int> sparseMatrixA = SparseMatrixMock<int>::fromVectors(classicMatrixA);

		std::vector<std::vector<int> > classicMatrixB = generateRandomMatrix<int>(rows, cols);
		SparseMatrixMock<int> sparseMatrixB = SparseMatrixMock<int>::fromVectors(classicMatrixB);

		// calculate result manually
		std::vector<std::vector<int> > manualResult = addMatrices(classicMatrixA, classicMatrixB);

		// method
		assertEquals<SparseMatrix::SparseMatrix<int>, std::vector<std::vector<int> > >(
			sparseMatrixA.add(sparseMatrixB),
			manualResult,
			"Incorrect matrices addition"
		);

		// operator
		assertEquals<SparseMatrix::SparseMatrix<int>, std::vector<std::vector<int> > >(
			sparseMatrixA + sparseMatrixB,
			manualResult,
			"Incorrect matrices addition (operator +)"
		);
	}

	std::cout << " OK" << std::endl;
}
