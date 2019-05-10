/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include "../testslib.h"
#include "../SparseMatrixMock.h"


void _constructorFail1(void)
{
	SparseMatrix<int>(0);
}


void testConstructorFail1(void)
{
	cout << "constructor fail #1..." << flush;
	assertException("InvalidDimensionsException", _constructorFail1);
	cout << " OK" << endl;
}


void _constructorFail2(void)
{
	SparseMatrix<int>(0, 1);
}


void testConstructorFail2(void)
{
	cout << "constructor fail #2..." << flush;
	assertException("InvalidDimensionsException", _constructorFail2);
	cout << " OK" << endl;
}


void _constructorFail3(void)
{
	SparseMatrix<int>(1, 0);
}


void testConstructorFail3(void)
{
	cout << "constructor fail #3..." << flush;
	assertException("InvalidDimensionsException", _constructorFail3);
	cout << " OK" << endl;
}


void _constructorFail4(void)
{
	SparseMatrix<int>(0, 0);
}


void testConstructorFail4(void)
{
	cout << "constructor fail #4..." << flush;
	assertException("InvalidDimensionsException", _constructorFail4);
	cout << " OK" << endl;
}
