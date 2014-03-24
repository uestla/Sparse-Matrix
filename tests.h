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
		m.insert(-1, 4, 0);
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
		m.insert(1, 1, 3)
			.insert(2, 2, 1)
			.insert(3, 2, 3)
			.insert(4, 3, 2)
			.insert(7, 3, 3);

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
		m.insert(1, 1, 1)
			.insert(2, 1, 2)
			.insert(3, 1, 3)
			.insert(4, 2, 1)
			.insert(5, 2, 2)
			.insert(6, 2, 3)
			.insert(7, 3, 1)
			.insert(8, 3, 2)
			.insert(9, 3, 3);

		vector<int> x(3, 0);
		vector<int> result(3, 0);

		assertEquals("vector multiplication #3", m.multiply(x), result);
	}

#endif
