/**
 * This file is part of the SparseMatrix library
 *
 * Copyright (c) 2014-2016 Petr Kessler (http://kesspess.1991.cz)
 *
 * @license  MIT
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#ifndef __SPARSEMATRIX_H__

	#define	__SPARSEMATRIX_H__

	#include <vector>
	#include <iostream>

	using namespace std;

	template <typename T>
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
			 * Creates a general matrix
			 *
			 * @param  rows number of rows
			 * @param  columns number of columns
			 */
			SparseMatrix(int rows, int columns);


			/**
			 * Copy constructor
			 *
			 * @param  m instance to be copied
			 */
			SparseMatrix(const SparseMatrix<T> & m);


			/**
			 * Assignment operator
			 *
			 * @param  m matrix we're assigning
			 * @return deep copy of assigned matrix
			 */
			SparseMatrix<T> & operator = (const SparseMatrix<T> & m);


			~SparseMatrix(void);


			/**
			 * Element getter
			 *
			 * @param  row
			 * @param  col
			 * @return element at given position or empty element if not set yet
			 */
			T get(int row, int col) const;


			/**
			 * Element setter
			 *
			 * @param  value
			 * @param  row
			 * @param  col
			 * @return self for fluent interface
			 */
			SparseMatrix & set(T val, int row, int col);


			/**
			 * Multiplies matrix with vector
			 *
			 * @param  x vector
			 * @return result of the product
			 */
			vector<T> multiply(const vector<T> & x) const;


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
			 * Sends internal storage info to given output stream
			 *
			 * @param  os output stream
			 * @return void
			 */
			void printInfo(ostream & os) const;


			/**
			 * Compares two matrices
			 *
			 * @param  a
			 * @param  b
			 * @return are both matrices equal?
			 */
			template<typename X>
			friend bool operator == (const SparseMatrix<X> & a, const SparseMatrix<X> & b);


			/**
			 * Compares two matrices
			 *
			 * @param  a
			 * @param  b
			 * @return are both matrices unequal?
			 */
			template<typename X>
			friend bool operator != (const SparseMatrix<X> & a, const SparseMatrix<X> & b);


			/**
			 * Prints matrix in human friendly format
			 *
			 * @param  output stream
			 * @param  matrix to print
			 * @return output stream for fluent interface
			 */
			template<typename X>
			friend ostream & operator << (ostream & os, const SparseMatrix<X> & matrix);


		protected:

			int m, n;

			vector<int> * cols, * rows;
			vector<T> * vals;

			/**
			 * Common internal constructor
			 *
			 * @param  m number of rows
			 * @param  n number of columns
			 */
			void construct(int m, int n);


			/**
			 * Copies matrix (used in copy constructor and assignment operator)
			 *
			 * @param  m matrix to be copied
			 * @return void
			 */
			void deepCopy(const SparseMatrix<T> & m);


			/**
			 * Element coordinate validator
			 *
			 * @param  row
			 * @param  col
			 */
			void validateCoordinates(int row, int col) const;


			/**
			 * Inserts given value into the matrix
			 *
			 * @param  index at which the new element will be placed
			 * @param  row
			 * @param  col
			 * @param  val
			 */
			void insert(int index, int row, int col, T val);


			/**
			 * Removes value from the matrix
			 *
			 * @param  index
			 * @param  row
			 */
			void remove(int index, int row);

	};

#endif
