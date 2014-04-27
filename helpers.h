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
	 * Prints vector in human friendy format.
	 * NOTE: vector elements have to have 'operator <<' defined!
	 *
	 * @param os
	 * @param name
	 * @param array
	 */
	template<class T>
	void printArray(ostream & os, const char * name, const vector<T> * array)
	{
		os << name << ": [";

		if (array != NULL) {
			for (unsigned int i = 0, size = array->size(); i < size; i++) {
				os << array->at(i);

				if (i != size - 1) {
					os << ", ";
				}
			}
		}

		os << "]";
	}



	/**
	 * Prints matrix in human friendly format
	 *
	 * @param  matrix to print
	 * @param  output stream
	 */
	void print(const SparseMatrix & matrix, ostream & os)
	{
		printArray(os, "vals", matrix.vals);
		os << endl;

		printArray(os, "cols", matrix.cols);
		os << endl;

		printArray(os, "rows", matrix.rows);
	}

#endif
