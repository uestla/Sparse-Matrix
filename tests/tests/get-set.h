/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include "../testslib.h"
#include "../SparseMatrixMock.h"


void _getFail(void)
{
	SparseMatrix<int> m(1, 1);
	m.get(2, 1);
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
	m.set(-1, 4, 0);
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
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			assertEquals<int>(0, m.get(i, j));
		}
	}

	m.set(-4, 1, 3);
	assertEquals<int>(-4, m.get(1, 3));

	cout << " OK" << endl;
}
