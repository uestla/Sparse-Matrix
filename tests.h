#ifndef __TESTS_H__

	#define	__TESTS_H__

	#include "testslib.h"
	#include "SparseMatrix.h"



	void constructorFail1(void)
	{
		SparseMatrix(0);
	}



	void constructorFail2(void)
	{
		SparseMatrix(-5);
	}



	void constructorFail3(void)
	{
		SparseMatrix(-4, 3);
	}



	void constructorFail4(void)
	{
		SparseMatrix(3, -1);
	}



	void constructorFail5(void)
	{
		SparseMatrix(-10, -7);
	}



	void getFail(void)
	{
		SparseMatrix m(1, 1);
		m.get(2, 1);
	}



	void insertFail(void)
	{
		SparseMatrix m(3, 4);
		m.set(-1, 4, 0);
	}



	void multiplicationFail1(void)
	{
		SparseMatrix m(3, 4);
		vector<int> x(3, 1);
		m.multiply(x);
	}



	void multiplicationFail2(void)
	{
		SparseMatrix a(3, 4), b(5, 6);
		a.multiply(b);
	}



	void additionFail1(void)
	{
		SparseMatrix a(3, 4), b(3, 5);
		a.add(b);
	}



	void additionFail2(void)
	{
		SparseMatrix a(3, 4), b(4, 4);
		a.add(b);
	}



	void additionFail3(void)
	{
		SparseMatrix a(3, 4), b(4, 5);
		a.add(b);
	}



	void testVectorMultiplication1(void)
	{
		// [ 0 0 1 ]   [ 2 ]   [  3 ]
		// [ 2 0 3 ] × [ 0 ] = [ 13 ]
		// [ 0 4 7 ]   [ 3 ]   [ 21 ]

		SparseMatrix m(3);
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

		assertEquals("vector multiplication #1", m.multiply(x), result);
	}



	void testVectorMultiplication2(void)
	{
		// [ 0 0 0 ]   [ 1 ]   [ 0 ]
		// [ 0 0 0 ] × [ 1 ] = [ 0 ]
		// [ 0 0 0 ]   [ 1 ]   [ 0 ]

		SparseMatrix m(3);
		vector<int> x(3, 1);
		vector<int> result(3, 0);

		assertEquals("vector multiplication #2", m.multiply(x), result);
	}



	void testVectorMultiplication3(void)
	{
		// [ 1 2 3 ]   [ 0 ]   [ 0 ]
		// [ 4 5 6 ] × [ 0 ] = [ 0 ]
		// [ 7 8 9 ]   [ 0 ]   [ 0 ]

		SparseMatrix m(3);
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

		assertEquals("vector multiplication #3", m.multiply(x), result);
	}



	void testAddition1(void)
	{
		// [ 0 0 0 ]   [ 1 2 3 ]   [ 1 2 3 ]
		// [ 0 0 0 ] + [ 4 5 6 ] = [ 4 5 6 ]
		// [ 0 0 0 ]   [ 7 8 9 ]   [ 7 8 9 ]

		SparseMatrix a(3);
		SparseMatrix b(3);
		b.set(1, 1, 1)
			.set(2, 1, 2)
			.set(3, 1, 3)
			.set(4, 2, 1)
			.set(5, 2, 2)
			.set(6, 2, 3)
			.set(7, 3, 1)
			.set(8, 3, 2)
			.set(9, 3, 3);

		assertEquals("addition #1", a.add(b), b);
	}



	void testAddition2(void)
	{
		// [ -1 -2 -3 ]   [ 1 2 3 ]   [ 0 0 0 ]
		// [ -4 -5 -6 ] + [ 4 5 6 ] = [ 0 0 0 ]
		// [ -7 -8 -9 ]   [ 7 8 9 ]   [ 0 0 0 ]

		SparseMatrix a(3);
		a.set(-1, 1, 1)
			.set(-2, 1, 2)
			.set(-3, 1, 3)
			.set(-4, 2, 1)
			.set(-5, 2, 2)
			.set(-6, 2, 3)
			.set(-7, 3, 1)
			.set(-8, 3, 2)
			.set(-9, 3, 3);

		SparseMatrix b(3);
		b.set(1, 1, 1)
			.set(2, 1, 2)
			.set(3, 1, 3)
			.set(4, 2, 1)
			.set(5, 2, 2)
			.set(6, 2, 3)
			.set(7, 3, 1)
			.set(8, 3, 2)
			.set(9, 3, 3);

		assertEquals("addition #2", a.add(b), SparseMatrix(3));
	}



	void testAddition3(void)
	{
		// [ 1 0 1 ]   [ 0 1 0 ]   [ 1 1 1 ]
		// [ 0 1 0 ] + [ 1 0 1 ] = [ 1 1 1 ]
		// [ 1 0 1 ]   [ 0 1 0 ]   [ 1 1 1 ]

		SparseMatrix a(3);
		a.set(1, 1, 1)
			.set(1, 1, 3)
			.set(1, 2, 2)
			.set(1, 3, 1)
			.set(1, 3, 3);

		SparseMatrix b(3);
		b.set(1, 1, 2)
			.set(1, 2, 1)
			.set(1, 2, 3)
			.set(1, 3, 2);

		SparseMatrix result(3);
		result.set(1, 1, 1)
			.set(1, 1, 2)
			.set(1, 1, 3)
			.set(1, 2, 1)
			.set(1, 2, 2)
			.set(1, 2, 3)
			.set(1, 3, 1)
			.set(1, 3, 2)
			.set(1, 3, 3);

		assertEquals("addition #3", a.add(b), result);
	}



	void testMultiplication1(void)
	{
		// [ 1 2 3 ]   [ 1 1 1 ]   [  3  6  3 ]
		// [ 4 5 6 ] × [ 1 1 1 ] = [  9 15  9 ]
		// [ 7 8 9 ]   [ 0 1 0 ]   [ 15 24 15 ]

		SparseMatrix a(3);
		a.set(1, 1, 1)
			.set(2, 1, 2)
			.set(3, 1, 3)
			.set(4, 2, 1)
			.set(5, 2, 2)
			.set(6, 2, 3)
			.set(7, 3, 1)
			.set(8, 3, 2)
			.set(9, 3, 3);

		SparseMatrix b(3);
		b.set(1, 1, 1)
			.set(1, 1, 2)
			.set(1, 1, 3)
			.set(1, 2, 1)
			.set(1, 2, 2)
			.set(1, 2, 3)
			.set(1, 3, 2);

		SparseMatrix result(3);
		result.set(3, 1, 1)
			.set(6, 1, 2)
			.set(3, 1, 3)
			.set(9, 2, 1)
			.set(15, 2, 2)
			.set(9, 2, 3)
			.set(15, 3, 1)
			.set(24, 3, 2)
			.set(15, 3, 3);

		assertEquals("multiplication #1", a.multiply(b), result);
	}



	void testMultiplication2(void)
	{
		// [ 1 0 1 ]   [ 0 0 0 ]   [ 0 0 0 ]
		// [ 0 0 1 ] × [ 0 0 0 ] = [ 0 0 0 ]
		// [ 2 2 0 ]   [ 0 0 0 ]   [ 0 0 0 ]

		SparseMatrix a(3);
		a.set(1, 1, 1)
			.set(1, 1, 3)
			.set(1, 2, 3)
			.set(2, 3, 1)
			.set(2, 3, 2);

		SparseMatrix b(3);
		SparseMatrix result(3);

		assertEquals("multiplication #2", a.multiply(b), result);
	}



	void testMultiplication3(void)
	{
		// [ 1 0 0 ]   [ 1 2 3 ]   [ 1 2 3 ]
		// [ 0 1 0 ] × [ 4 5 6 ] = [ 4 5 6 ]
		// [ 0 0 1 ]   [ 7 8 9 ]   [ 7 8 9 ]

		SparseMatrix a(3);
		a.set(1, 1, 1)
			.set(1, 2, 2)
			.set(1, 3, 3);

		SparseMatrix b(3);
		b.set(1, 1, 1)
			.set(2, 1, 2)
			.set(3, 1, 3)
			.set(4, 2, 1)
			.set(5, 2, 2)
			.set(6, 2, 3)
			.set(7, 3, 1)
			.set(8, 3, 2)
			.set(9, 3, 3);

		assertEquals("multiplication #3.1", a.multiply(b), b);
		assertEquals("multiplication #3.2", b.multiply(a), b);
	}

#endif
