/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#ifndef __HELPERS_H__

	#define	__HELPERS_H__

	#include <vector>
	#include <iostream>

	using namespace std;


	// === GENERATORS =========================================

	template<typename T>
	vector<T> generateRandomVector(int size)
	{
		vector<T> vector(size, 0);

		for (int i = 0; i < size; i++) {
			vector[i] = rand() % 101;
		}

		return vector;
	}


	template<typename T>
	vector<vector<T> > generateRandomMatrix(int rows, int columns)
	{
		vector<vector<T> > matrix(rows, vector<int>(columns, 0));

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				matrix[i][j] = rand() % 101;
			}
		}

		return matrix;
	}


	// === OUTPUT HELPERS =========================================

	template<typename T>
	ostream & operator << (ostream & os, const vector<T> & v)
	{
		os << "[";

		for (int i = 0, len = v.size(); i < len; i++) {
			if (i != 0) {
				os << ", ";
			}

			os << v[i];
		}

		os << "]";

		return os;
	}

#endif
