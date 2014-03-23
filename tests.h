#ifndef __TESTS_H__

	#define	__TESTS_H__

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

#endif
