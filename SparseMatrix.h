/**
 * This file is part of the SparseMatrix library
 *
 * Copyright (c) 2014 Petr Kessler (http://kesspess.1991.cz)
 *
 * @license  MIT
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#ifndef __SPARSEMATRIX_H__

	#define	__SPARSEMATRIX_H__

	#include <vector>
	#include <iostream>

	using namespace std;



	class SparseMatrix
	{

		public:

			/**
			 * Creates a square matrix
			 *
			 * @param  n number of rows and columns
			 */
			SparseMatrix(int n);



			/**
			 * Creates a non-square matrix
			 *
			 * @param  rows number of rows
			 * @param  columns number of columns
			 */
			SparseMatrix(int rows, int columns);



			/**
			 * Element value getter
			 *
			 * @param  row
			 * @param  col
			 * @return value of element or 0 if value has not been set yet
			 */
			int get(int row, int col) const;



			/**
			 * Element value setter
			 *
			 * @param  value
			 * @param  row
			 * @param  col
			 * @return self for fluent interface
			 */
			SparseMatrix & insert(int value, int row, int col);



			/**
			 * Multiplies matrix with vector
			 *
			 * @param  x vector
			 * @return result of the product
			 */
			vector<int> multiply(const vector<int> & x) const;



			/**
			 * Multiplies matrix by another matrix
			 *
			 * @param  m
			 * @return result of the product
			 */
			SparseMatrix multiply(const SparseMatrix & m) const;



			/**
			 * Adds another matrix to this matrix
			 *
			 * @param  m
			 * @return result of the sum
			 */
			SparseMatrix add(const SparseMatrix & m) const;



			/**
			 * Compares two matrices
			 *
			 * @param  a
			 * @param  b
			 * @return are both matrices equal?
			 */
			friend bool operator == (const SparseMatrix & a, const SparseMatrix & b);



			/**
			 * Compares two matrices
			 *
			 * @param  a
			 * @param  b
			 * @return are both matrices unequal?
			 */
			friend bool operator != (const SparseMatrix & a, const SparseMatrix & b);



			/**
			 * Prints the internal matrix vectors
			 *
			 * @param  output stream
			 * @param  matrix to print
			 * @return output stream for fluent interface
			 */
			friend ostream & operator << (ostream & os, const SparseMatrix & matrix);



			/**
			 * Prints matrix in human friendly format
			 *
			 * @param  matrix to print
			 * @param  output stream
			 */
			friend void print(const SparseMatrix & matrix, ostream & os);



		protected:

			int m, n;

			vector<int> vals, cols, rows;

			/**
			 * Common internal constructor
			 *
			 * @param  m number of rows
			 * @param  n number of columns
			 */
			void construct(int m, int n);



			/**
			 * Element coordination validator
			 *
			 * @param  row
			 * @param  col
			 */
			void validateCoordinations(int row, int col) const;

	};

#endif
