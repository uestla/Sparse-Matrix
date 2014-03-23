#include <vector>
#include <iostream>
#include "helpers.h"
#include "SparseMatrix.h"

using namespace std;



SparseMatrix::SparseMatrix(unsigned int n)
{
	this->construct(n, n);
}



SparseMatrix::SparseMatrix(unsigned int rows, unsigned int columns)
{
	this->construct(rows, columns);
}



void SparseMatrix::construct(unsigned int rows, unsigned int columns)
{
	if (rows < 1 || columns < 1) {
		throw "Matrix dimensions cannot be zero or negative.";
	}

	this->m = rows;
	this->n = columns;

	for (unsigned int i = 0; i < columns; i++) {
		this->rows.push_back(0);
	}

	this->rows.push_back(1);
}



int SparseMatrix::get(unsigned int row, unsigned int col) const
{
	this->validateCoordinations(row, col);

	if (this->rows[row - 1] == 0) { // empty row
		return 0;
	}

	unsigned int nnz = getFirstNextNonZero(this->rows, row - 1);

	for (unsigned int j = this->rows[row - 1] - 1; j < nnz - 1; j++) {
		if (this->cols[j] == col) {
			return this->vals[j];
		}
	}

	return 0;
}



SparseMatrix & SparseMatrix::insert(int value, unsigned int row, unsigned int col)
{
	this->validateCoordinations(row, col);

	// TODO: delete element when inserting 0

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
		bool inserted = false;

		for (unsigned int j = this->rows[row - 1]; j < nnz; j++) {
			if (this->cols[j - 1] == col) { // just overwrite the value
				this->vals[j - 1] = value;
				inserted = true;
				break;

			} else if (col < this->cols[j - 1]) {
				this->vals.insert(this->vals.begin() + j - 1, value);
				this->cols.insert(this->cols.begin() + j - 1, col);

				for (unsigned int i = row; i < this->rows.size(); i++) {
					if (this->rows[i] != 0) {
						this->rows[i]++;
					}
				}

				inserted = true;
				break;
			}
		}

		if (!inserted) {
			this->vals.insert(this->vals.begin() + nnz - 1, value);
			this->cols.insert(this->cols.begin() + nnz - 1, col);

			for (unsigned int i = row; i < this->rows.size(); i++) {
				if (this->rows[i] != 0) {
					this->rows[i]++;
				}
			}
		}
	}

	return *this;
}



vector<int> SparseMatrix::multiply(const vector<int> & x) const
{
	if (this->n != x.size()) {
		throw "Matrix column count and vector size don't match.";
	}

	vector<int> result(this->m, 0);

	for (unsigned int i = 0; i < this->m; i++) {
		if (this->rows[i] != 0) {
			unsigned int nnz = getFirstNextNonZero(this->rows, i);
			for (unsigned int j = this->rows[i] - 1; j < nnz - 1; j++) {
				result[i] += x[this->cols[j] - 1] * this->vals[j];
			}
		}
	}

	return result;
}



SparseMatrix SparseMatrix::multiply(const SparseMatrix & m) const
{
	if (this->n != m.m) {
		throw "Left matrix column count and right matrix row count don't match.";
	}

	SparseMatrix result(this->m, m.n);

	int a;

	for (unsigned int i = 1; i <= this->m; i++) {
		for (unsigned int j = 1; j <= m.n; j++) {
			a = 0;

			for (unsigned int k = 1; k <= this->n; k++) {
				a += this->get(i, k) * m.get(k, j);
			}

			if (a != 0) {
				result.insert(a, i, j);
			}
		}
	}

	return result;
}



void SparseMatrix::validateCoordinations(unsigned int row, unsigned int col) const
{
	if (row < 1 || col < 1 || row > this->m || col > this->n) {
		throw "Coordinations out of range.";
	}
}



ostream & operator << (ostream & os, const SparseMatrix & matrix)
{
	printArray<int>(os, "vals", matrix.vals);
	printArray<unsigned int>(os, "cols", matrix.cols);
	printArray<unsigned int>(os, "rows", matrix.rows);

	return os;
}
