/**
 * This file is part of the SparseMatrix library
 *
 * Copyright (c) 2014 Petr Kessler (http://kesspess.1991.cz)
 *
 * @license  MIT
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#ifndef __HELPERS_H__

	#define	__HELPERS_H__

	#include <vector>
	#include "SparseMatrix.h"

	using namespace std;



	/**
	 * Prints matrix in human friendly format
	 *
	 * @param  matrix to print
	 * @param  output stream
	 */
	void print(const SparseMatrix & matrix, ostream & os)
	{
		for (int i = 1; i <= matrix.m; i++) {
			for (int j = 1; j <= matrix.n; j++) {
				if (j != 1) {
					os << " ";
				}

				os << matrix.get(i, j);
			}

			os << endl;
		}

		os << endl;
	}



	/**
	 * Prints vector in human friendy format.
	 * NOTE: vector elements have to have 'operator <<' defined!
	 *
     * @param os
     * @param name
     * @param array
     */
	template<class T>
	void printArray(ostream & os, const char * name, vector<T> array)
	{
		os << name << ": [";

		for (unsigned int i = 0, size = array.size(); i < size; i++) {
			os << array[i];

			if (i != size - 1) {
				os << ", ";
			}
		}

		os << "]" << endl;
	}

#endif
