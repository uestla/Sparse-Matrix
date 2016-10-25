/**
 * This file is part of the SparseMatrix library
 *
 * Copyright (c) 2014-2016 Petr Kessler (http://kesspess.1991.cz)
 *
 * @license  MIT
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#ifndef __SPARSEMATRIX_MOCK_H__

	#define __SPARSEMATRIX_MOCK_H__

	#include "../src/SparseMatrix/SparseMatrix.h"

	using namespace std;


	/**
	 * This class is used only for testing purposes CSR format
	 *
	 * @internal
	 */
	template <typename T>
	class SparseMatrixMock : public SparseMatrix<T>
	{

		public:

			SparseMatrixMock(int n) : SparseMatrix<T>(n)
			{}


			SparseMatrixMock(int rows, int columns) : SparseMatrix<T>(rows, columns)
			{}


			/** @return Non-empty values in the matrix */
			vector<T> * getValues(void)
			{
				return this->vals;
			}


			/** @return Column pointers */
			vector<int> * getColumnPointers(void)
			{
				return this->cols;
			}


			/** @return Row pointers */
			vector<int> * getRowPointers(void)
			{
				return this->rows;
			}

	};

#endif
