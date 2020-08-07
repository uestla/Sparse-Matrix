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


	// === GENERATORS =========================================

	template<typename T>
	std::vector<T> generateRandomVector(int size)
	{
		std::vector<T> vector(size, 0);

		for (int i = 0; i < size; i++) {
			vector[i] = rand() % 101;
		}

		return vector;
	}


	template<typename T>
	std::vector<std::vector<T> > generateRandomMatrix(int rows, int columns)
	{
		std::vector<std::vector<T> > matrix(rows, std::vector<int>(columns, 0));

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				matrix[i][j] = rand() % 101;
			}
		}

		return matrix;
	}


	// === STANDARD OPERATIONS =========================================

	template<typename T>
	std::vector<std::vector<T> > addMatrices(const std::vector<std::vector<T> > & a, const std::vector<std::vector<T> > & b)
	{
		int rows = a.size();
		int cols = a.front().size();

		std::vector<std::vector<T> > result(rows, std::vector<int>(cols, 0));

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result[i][j] = a[i][j] + b[i][j];
			}
		}

		return result;
	}


	template<typename T>
	std::vector<std::vector<T> > subtractMatrices(const std::vector<std::vector<T> > & a, const std::vector<std::vector<T> > & b)
	{
		int rows = a.size();
		int cols = a.front().size();

		std::vector<std::vector<T> > result(rows, std::vector<int>(cols, 0));

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result[i][j] = a[i][j] - b[i][j];
			}
		}

		return result;
	}


	template<typename T>
	std::vector<T> multiplyMatrixByVector(const std::vector<std::vector<T> > & m, const std::vector<T> & v)
	{
		int rows = m.size();
		int cols = v.size();

		std::vector<T> result(rows, 0);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result[i] += m[i][j] * v[j];
			}
		}

		return result;
	}


	template<typename T>
	std::vector<std::vector<T> > multiplyMatrices(const std::vector<std::vector<T> > & a, const std::vector<std::vector<T> > & b)
	{
		int rowsA = a.size();
		int colsA = a.front().size();
		int colsB = b.front().size();

		std::vector<std::vector<T> > result(rowsA, std::vector<int>(colsB, 0));

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
	std::ostream & operator << (std::ostream & os, const std::vector<T> & v)
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
