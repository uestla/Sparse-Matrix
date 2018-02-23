/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include "../inc/testslib.h"
#include "../inc/SparseMatrixMock.h"


void _getFail(void)
{
	SparseMatrix<int> m(1, 1);
	m.get(1, 0);
}


void testGetFail(void)
{
	cout << "get() fail..." << flush;
	assertException("InvalidCoordinatesException", _getFail);
	cout << " OK" << endl;
}


void _setFail(void)
{
	SparseMatrix<int> m(3, 4);
	m.set(-1, 3, -1);
}


void testSetFail(void)
{
	cout << "set() fail..." << flush;
	assertException("InvalidCoordinatesException", _setFail);
	cout << " OK" << endl;
}


void testGettersAndSetters(void)
{
	cout << "getters/setters..." << flush;

	SparseMatrix<int> m(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			assertEquals<int>(0, m.get(i, j));
		}
	}

	m.set(-4, 0, 2);
	assertEquals<int>(-4, m.get(0, 2));

	cout << " OK" << endl;
}
