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


	// === STANDARD OPERATIONS =========================================

	template<typename T>
	vector<vector<T> > addMatrices(const vector<vector<T> > & a, const vector<vector<T> > & b)
	{
		int rows = a.size();
		int cols = a.front().size();

		vector<vector<T> > result(rows, vector<int>(cols, 0));

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result[i][j] = a[i][j] + b[i][j];
			}
		}

		return result;
	}


	template<typename T>
	vector<T> multiplyMatrixByVector(const vector<vector<T> > & m, const vector<T> & v)
	{
		int rows = m.size();
		int cols = v.size();

		vector<T> result(rows, 0);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result[i] += m[i][j] * v[j];
			}
		}

		return result;
	}


	template<typename T>
	vector<vector<T> > multiplyMatrices(const vector<vector<T> > & a, const vector<vector<T> > & b)
	{
		int rowsA = a.size();
		int colsA = a.front().size();
		int colsB = b.front().size();

		vector<vector<T> > result(rowsA, vector<int>(colsB, 0));

		for (int i = 0; i < rowsA; i++) {
			for (int j = 0; j < colsB; j++) {
				result[i][j] = 0;

				for (int k = 0; k < colsA; k++) {
					result[i][j] += a[i][k] * b[k][j];
				}
			}
		}

		return result;
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
