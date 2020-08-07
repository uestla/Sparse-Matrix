/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#ifndef __SPARSEMATRIX_MOCK_H__

	#define __SPARSEMATRIX_MOCK_H__

	#include <vector>
	#include "../../src/SparseMatrix/SparseMatrix.h"


	/**
	 * This class is used only for testing purposes
	 *
	 * @internal
	 */
	template <typename T>
	class SparseMatrixMock : public SparseMatrix::SparseMatrix<T>
	{

		public:

			SparseMatrixMock(int n) : SparseMatrix::SparseMatrix<T>(n)
			{}


			SparseMatrixMock(int rows, int columns) : SparseMatrix::SparseMatrix<T>(rows, columns)
			{}


			/** @return Non-empty values in the matrix */
			std::vector<T> * getValues(void)
			{
				return this->vals;
			}


			/** @return Column pointers */
			std::vector<int> * getColumnPointers(void)
			{
				return this->cols;
			}


			/** @return Row pointers */
			std::vector<int> * getRowPointers(void)
			{
				return this->rows;
			}


			/**
			 * Sends internal storage info to given output stream
			 *
			 * @param  os output stream
			 * @return void
			 */
			void printInfo(std::ostream & os) const
			{
				std::vector<int>::iterator intIt;

				os << "rows (" << this->rows->size() << "): [";

				for (intIt = this->rows->begin(); intIt < this->rows->end(); intIt++) {
					if (intIt > this->rows->begin()) {
						os << ", ";
					}

					os << *intIt;
				}

				os << "]";

				os << std::endl << "cols";
				if (this->cols == NULL) {
					os << ": NULL";

				} else {
					os << " (" << this->cols->size() << "): [";

					for (intIt = this->cols->begin(); intIt < this->cols->end(); intIt++) {
						if (intIt > this->cols->begin()) {
							os << ", ";
						}

						os << *intIt;
					}

					os << "]";
				}

				os << std::endl << "vals";
				if (this->vals == NULL) {
					os << ": NULL";

				} else {
					typename std::vector<T>::iterator valIt;

					os << " (" << this->vals->size() << "): [";

					for (valIt = this->vals->begin(); valIt < this->vals->end(); valIt++) {
						if (valIt > this->vals->begin()) {
							os << ", ";
						}

						os << *valIt;
					}

					os << "]";
				}
			}


			/** @return Constructed SparseMatrix */
			static SparseMatrixMock<T> fromVectors(std::vector<std::vector<T> > vec)
			{
				SparseMatrixMock<T> matrix(vec.size(), vec[0].size());

				for (int i = 0, len = vec.size(); i < len; i++) {
					for (int j = 0, len = vec[i].size(); j < len; j++) {
						matrix.set(vec[i][j], i + 1, j + 1);
					}
				}

				return matrix;
			}

	};


	template<typename T>
	bool operator == (const SparseMatrix::SparseMatrix<T> & sparse, const std::vector<std::vector<T> > & classical)
	{
		for (int i = 0, rows = classical.size(); i < rows; i++) {
			for (int j = 0, cols = classical[i].size(); j < cols; j++) {
				if (sparse.get(i + 1, j + 1) != classical[i][j]) {
					return false;
				}
			}
		}

		return true;
	}

#endif
