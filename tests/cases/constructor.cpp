/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include "../inc/testslib.h"
#include "../inc/SparseMatrixMock.h"


void _constructorFail1(void)
{
	SparseMatrix::SparseMatrix<int>(0);
}


void testConstructorFail1(void)
{
	std::cout << "constructor fail #1..." << std::flush;
	assertException("InvalidDimensionsException", _constructorFail1);
	std::cout << " OK" << std::endl;
}


void _constructorFail2(void)
{
	SparseMatrix::SparseMatrix<int>(0, 1);
}


void testConstructorFail2(void)
{
	std::cout << "constructor fail #2..." << std::flush;
	assertException("InvalidDimensionsException", _constructorFail2);
	std::cout << " OK" << std::endl;
}


void _constructorFail3(void)
{
	SparseMatrix::SparseMatrix<int>(1, 0);
}


void testConstructorFail3(void)
{
	std::cout << "constructor fail #3..." << std::flush;
	assertException("InvalidDimensionsException", _constructorFail3);
	std::cout << " OK" << std::endl;
}


void _constructorFail4(void)
{
	SparseMatrix::SparseMatrix<int>(0, 0);
}


void testConstructorFail4(void)
{
	std::cout << "constructor fail #4..." << std::flush;
	assertException("InvalidDimensionsException", _constructorFail4);
	std::cout << " OK" << std::endl;
}
