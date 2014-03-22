#include <vector>
#include <iostream>
#include "helpers.h"
#include "SparseMatrix.h"

using namespace std;



SparseMatrix::SparseMatrix(unsigned int n)
{
	this->construct(n, n);
}



SparseMatrix::SparseMatrix(unsigned int m, unsigned int n)
{
	this->construct(m, n);
}



void SparseMatrix::construct(unsigned int m, unsigned int n)
{
	if (m < 1 || n < 1) {
		throw "Matrix dimensions cannot be zero or negative.";
	}

	this->m = m;
	this->n = n;

	for (unsigned int i = 0; i < n; i++) {
		this->rows.push_back(0);
	}

	this->rows.push_back(1);
}



SparseMatrix & SparseMatrix::insert(int value, unsigned int row, unsigned int col)
{
	if (row < 1 || col < 1 || row > this->n || col > this->m) {
		throw "Element coordinations out of range.";
	}

	unsigned int nnz = getFirstNextNonZero(this->rows, row - 1);

	if (this->rows[row - 1] == 0) {
		this->rows[row - 1] = nnz;
		this->vals.insert(this->vals.begin() + nnz - 1, value);
		this->cols.insert(this->cols.begin() + nnz - 1, col);

		for (unsigned int i = row; i < this->rows.size(); i++) {
			if (this->rows[i] != 0) {
				this->rows[i]++;
			}
		}

	} else {
		for (unsigned int j = this->rows[row - 1]; j < nnz; j++) {
			if (this->cols[j - 1] == col) { // just overwrite the value
				this->vals[j - 1] = value;

			} else if (this->cols[j - 1] > col) {
				this->vals.insert(this->vals.begin() + j - 1, value);
				this->cols.insert(this->cols.begin() + j - 1, col);

				for (unsigned int i = j; i < this->rows.size(); i++) {
					if (this->rows[i] != 0) {
						this->rows[i]++;
					}
				}

				break;
			}
		}
	}

	return *this;
}



int SparseMatrix::get(unsigned int row, unsigned int col) const
{
	if (row < 1 || col < 1 || row > this->n || col > this->m) {
		throw "Element coordinations out of range.";
	}

	if (this->rows[row - 1] == 0) { // empty row
		return 0;
	}

	for (unsigned int j = this->rows[row - 1], nnz = getFirstNextNonZero(this->rows, row - 1); j < nnz; j++) {
		if (this->cols[j - 1] == col) {
			return this->vals[j - 1];
		}
	}

	return 0;
}



ostream & operator << (ostream & os, const SparseMatrix & matrix)
{
	printArray<int>(os, "vals", matrix.vals);
	printArray<unsigned int>(os, "cols", matrix.cols);
	printArray<unsigned int>(os, "rows", matrix.rows);

	return os;
}
