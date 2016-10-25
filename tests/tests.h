/**
 * This file is part of the SparseMatrix library
 *
 * Copyright (c) 2014-2016 Petr Kessler (http://kesspess.1991.cz)
 *
 * @license  MIT
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#ifndef __TESTS_H__

	#define	__TESTS_H__

	#include "testslib.h"
	#include "SparseMatrixMock.h"
	#include "../src/SparseMatrix/SparseMatrix.h"


	void constructorFail1(void)
	{
		SparseMatrix<int>(0);
	}


	void constructorFail2(void)
	{
		SparseMatrix<int>(0, 1);
	}


	void constructorFail3(void)
	{
		SparseMatrix<int>(1, 0);
	}


	void constructorFail4(void)
	{
		SparseMatrix<int>(0, 0);
	}


	void getFail(void)
	{
		SparseMatrix<int> m(1, 1);
		m.get(2, 1);
	}


	void setFail(void)
	{
		SparseMatrix<int> m(3, 4);
		m.set(-1, 4, 0);
	}


	void multiplicationFail1(void)
	{
		SparseMatrix<int> m(3, 4);
		vector<int> x(3, 1);
		m.multiply(x);
	}


	void multiplicationFail2(void)
	{
		SparseMatrix<int> a(3, 4), b(5, 6);
		a.multiply(b);
	}


	void additionFail1(void)
	{
		SparseMatrix<int> a(3, 4), b(3, 5);
		a.add(b);
	}


	void additionFail2(void)
	{
		SparseMatrix<int> a(3, 4), b(4, 4);
		a.add(b);
	}


	void additionFail3(void)
	{
		SparseMatrix<int> a(3, 4), b(4, 5);
		a.add(b);
	}


	void testGettersAndSetters(void)
	{
		ostringstream oss;

		int idx = 1;
		SparseMatrix<int> m(3);
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				oss.str("");
				oss << "insertion test #" << idx++;
				assertEquals<int>(oss.str().c_str(), 0, m.get(i, j));
			}
		}

		m.set(-4, 1, 3);
		assertEquals<int>("insertion test #10", -4, m.get(1, 3));
	}


	void testInternalStorage(void)
	{
		/*
			Matrix
			[ 1  0 4 5 ]
			[ 2 -1 0 0 ]
			[ 0  0 3 2 ]

			should be stored as
			values:  [ 1, 4, 5, 2, -1, 3, 2 ]
			columns: [ 1, 3, 4, 1, 2, 3, 4 ]
			rows:    [ 1, 4, 6, 8 ]
		*/

		SparseMatrixMock<int> m(3, 4);
		m.set(1, 1, 1)
			.set(4, 1, 3)
			.set(5, 1, 4)
			.set(2, 2, 1)
			.set(-1, 2, 2)
			.set(3, 3, 3)
			.set(2, 3, 4);

		vector<int> values;
		values.push_back(1);
		values.push_back(4);
		values.push_back(5);
		values.push_back(2);
		values.push_back(-1);
		values.push_back(3);
		values.push_back(2);

		vector<int> columnPointers;
		columnPointers.push_back(1);
		columnPointers.push_back(3);
		columnPointers.push_back(4);
		columnPointers.push_back(1);
		columnPointers.push_back(2);
		columnPointers.push_back(3);
		columnPointers.push_back(4);

		vector<int> rowPointers;
		rowPointers.push_back(1);
		rowPointers.push_back(4);
		rowPointers.push_back(6);
		rowPointers.push_back(8);

		assertEquals<vector<int> >("internal values storage", values, *(m.getValues()));
		assertEquals<vector<int> >("internal column pointers storage", columnPointers, *(m.getColumnPointers()));
		assertEquals<vector<int> >("internal row pointers storage", rowPointers, *(m.getRowPointers()));
	}


	void testVectorMultiplication1(void)
	{
		// [ 0 0 1 ]   [ 2 ]   [  3 ]
		// [ 2 0 3 ] × [ 0 ] = [ 13 ]
		// [ 0 4 7 ]   [ 3 ]   [ 21 ]

		SparseMatrix<int> m(3);
		m.set(1, 1, 3)
			.set(2, 2, 1)
			.set(3, 2, 3)
			.set(4, 3, 2)
			.set(7, 3, 3);

		vector<int> x;
		x.push_back(2);
		x.push_back(0);
		x.push_back(3);

		vector<int> result;
		result.push_back(3);
		result.push_back(13);
		result.push_back(21);

		assertEquals<vector<int> >("vector multiplication #1", m.multiply(x), result);
	}


	void testVectorMultiplication2(void)
	{
		// [ 0 0 0 ]   [ 1 ]   [ 0 ]
		// [ 0 0 0 ] × [ 1 ] = [ 0 ]
		// [ 0 0 0 ]   [ 1 ]   [ 0 ]

		SparseMatrix<int> m(3);
		vector<int> x(3, 1);
		vector<int> result(3, 0);

		assertEquals<vector<int> >("vector multiplication #2", m.multiply(x), result);
	}


	void testVectorMultiplication3(void)
	{
		// [ 1 2 3 ]   [ 0 ]   [ 0 ]
		// [ 4 5 6 ] × [ 0 ] = [ 0 ]
		// [ 7 8 9 ]   [ 0 ]   [ 0 ]

		SparseMatrix<int> m(3);
		m.set(1, 1, 1)
			.set(2, 1, 2)
			.set(3, 1, 3)
			.set(4, 2, 1)
			.set(5, 2, 2)
			.set(6, 2, 3)
			.set(7, 3, 1)
			.set(8, 3, 2)
			.set(9, 3, 3);

		vector<int> x(3, 0);
		vector<int> result(3, 0);

		assertEquals<vector<int> >("vector multiplication #3", m.multiply(x), result);
	}


	void testAddition1(void)
	{
		// [ 0 0 0 ]   [ 1 2 3 ]   [ 1 2 3 ]
		// [ 0 0 0 ] + [ 4 5 6 ] = [ 4 5 6 ]
		// [ 0 0 0 ]   [ 7 8 9 ]   [ 7 8 9 ]

		SparseMatrix<int> a(3);
		SparseMatrix<int> b(3);
		b.set(1, 1, 1)
			.set(2, 1, 2)
			.set(3, 1, 3)
			.set(4, 2, 1)
			.set(5, 2, 2)
			.set(6, 2, 3)
			.set(7, 3, 1)
			.set(8, 3, 2)
			.set(9, 3, 3);

		assertEquals<SparseMatrix<int> >("addition #1", a.add(b), b);
	}


	void testAddition2(void)
	{
		// [ -1 -2 -3 ]   [ 1 2 3 ]   [ 0 0 0 ]
		// [ -4 -5 -6 ] + [ 4 5 6 ] = [ 0 0 0 ]
		// [ -7 -8 -9 ]   [ 7 8 9 ]   [ 0 0 0 ]

		SparseMatrix<int> a(3);
		a.set(-1, 1, 1)
			.set(-2, 1, 2)
			.set(-3, 1, 3)
			.set(-4, 2, 1)
			.set(-5, 2, 2)
			.set(-6, 2, 3)
			.set(-7, 3, 1)
			.set(-8, 3, 2)
			.set(-9, 3, 3);

		SparseMatrix<int> b(3);
		b.set(1, 1, 1)
			.set(2, 1, 2)
			.set(3, 1, 3)
			.set(4, 2, 1)
			.set(5, 2, 2)
			.set(6, 2, 3)
			.set(7, 3, 1)
			.set(8, 3, 2)
			.set(9, 3, 3);

		assertEquals<SparseMatrix<int> >("addition #2", a.add(b), SparseMatrix<int>(3));
	}


	void testAddition3(void)
	{
		// [ 1 0 1 ]   [ 0 1 0 ]   [ 1 1 1 ]
		// [ 0 1 0 ] + [ 1 0 1 ] = [ 1 1 1 ]
		// [ 1 0 1 ]   [ 0 1 0 ]   [ 1 1 1 ]

		SparseMatrix<int> a(3);
		a.set(1, 1, 1)
			.set(1, 1, 3)
			.set(1, 2, 2)
			.set(1, 3, 1)
			.set(1, 3, 3);

		SparseMatrix<int> b(3);
		b.set(1, 1, 2)
			.set(1, 2, 1)
			.set(1, 2, 3)
			.set(1, 3, 2);

		SparseMatrix<int> result(3);
		result.set(1, 1, 1)
			.set(1, 1, 2)
			.set(1, 1, 3)
			.set(1, 2, 1)
			.set(1, 2, 2)
			.set(1, 2, 3)
			.set(1, 3, 1)
			.set(1, 3, 2)
			.set(1, 3, 3);

		assertEquals<SparseMatrix<int> >("addition #3", a.add(b), result);
	}


	void testMultiplication1(void)
	{
		// [ 1 2 3 ]   [ 1 1 1 ]   [  3  6  3 ]
		// [ 4 5 6 ] × [ 1 1 1 ] = [  9 15  9 ]
		// [ 7 8 9 ]   [ 0 1 0 ]   [ 15 24 15 ]

		SparseMatrix<int> a(3);
		a.set(1, 1, 1)
			.set(2, 1, 2)
			.set(3, 1, 3)
			.set(4, 2, 1)
			.set(5, 2, 2)
			.set(6, 2, 3)
			.set(7, 3, 1)
			.set(8, 3, 2)
			.set(9, 3, 3);

		SparseMatrix<int> b(3);
		b.set(1, 1, 1)
			.set(1, 1, 2)
			.set(1, 1, 3)
			.set(1, 2, 1)
			.set(1, 2, 2)
			.set(1, 2, 3)
			.set(1, 3, 2);

		SparseMatrix<int> result(3);
		result.set(3, 1, 1)
			.set(6, 1, 2)
			.set(3, 1, 3)
			.set(9, 2, 1)
			.set(15, 2, 2)
			.set(9, 2, 3)
			.set(15, 3, 1)
			.set(24, 3, 2)
			.set(15, 3, 3);

		assertEquals<SparseMatrix<int> >("multiplication #1", a.multiply(b), result);
	}


	void testMultiplication2(void)
	{
		// [ 1 0 1 ]   [ 0 0 0 ]   [ 0 0 0 ]
		// [ 0 0 1 ] × [ 0 0 0 ] = [ 0 0 0 ]
		// [ 2 2 0 ]   [ 0 0 0 ]   [ 0 0 0 ]

		SparseMatrix<int> a(3);
		a.set(1, 1, 1)
			.set(1, 1, 3)
			.set(1, 2, 3)
			.set(2, 3, 1)
			.set(2, 3, 2);

		SparseMatrix<int> b(3);
		SparseMatrix<int> result(3);

		assertEquals<SparseMatrix<int> >("multiplication #2", a.multiply(b), result);
	}


	void testMultiplication3(void)
	{
		// [ 1 0 0 ]   [ 1 2 3 ]   [ 1 2 3 ]
		// [ 0 1 0 ] × [ 4 5 6 ] = [ 4 5 6 ]
		// [ 0 0 1 ]   [ 7 8 9 ]   [ 7 8 9 ]

		SparseMatrix<int> a(3);
		a.set(1, 1, 1)
			.set(1, 2, 2)
			.set(1, 3, 3);

		SparseMatrix<int> b(3);
		b.set(1, 1, 1)
			.set(2, 1, 2)
			.set(3, 1, 3)
			.set(4, 2, 1)
			.set(5, 2, 2)
			.set(6, 2, 3)
			.set(7, 3, 1)
			.set(8, 3, 2)
			.set(9, 3, 3);

		assertEquals<SparseMatrix<int> >("multiplication #3.1", a.multiply(b), b);
		assertEquals<SparseMatrix<int> >("multiplication #3.2", b.multiply(a), b);
	}

#endif
