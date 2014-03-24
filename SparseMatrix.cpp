#include <vector>
#include <iostream>
#include "helpers.h"
#include "SparseMatrix.h"

using namespace std;



SparseMatrix::SparseMatrix(int n)
{
	this->construct(n, n);
}



SparseMatrix::SparseMatrix(int rows, int columns)
{
	this->construct(rows, columns);
}



void SparseMatrix::construct(int rows, int columns)
{
	if (rows < 1 || columns < 1) {
		throw "Matrix dimensions cannot be zero or negative.";
	}

	this->m = rows;
	this->n = columns;

	for (int i = 0; i < columns; i++) {
		this->rows.push_back(0);
	}

	this->rows.push_back(1);
}



int SparseMatrix::get(int row, int col) const
{
	this->validateCoordinations(row, col);

	if (this->rows[row - 1] == 0) { // empty row
		return 0;
	}

	int nnz = getFirstNextNonZero(this->rows, row - 1);

	for (int j = this->rows[row - 1] - 1; j < nnz - 1 && this->cols[j] <= col; j++) {
		if (this->cols[j] == col) {
			return this->vals[j];
		}
	}

	return 0;
}



SparseMatrix & SparseMatrix::insert(int value, int row, int col)
{
	this->validateCoordinations(row, col);

	// TODO: delete element when inserting 0

	int nnz = getFirstNextNonZero(this->rows, row - 1);

	bool inserted = false;

	if (this->rows[row - 1] == 0) {
		this->rows[row - 1] = nnz;
		this->vals.insert(this->vals.begin() + nnz - 1, value);
		this->cols.insert(this->cols.begin() + nnz - 1, col);
		inserted = true;

	} else {
		for (int j = this->rows[row - 1]; j < nnz; j++) {
			if (this->cols[j - 1] == col) { // just overwrite the value
				this->vals[j - 1] = value;
				break;

			} else if (col < this->cols[j - 1]) {
				this->vals.insert(this->vals.begin() + j - 1, value);
				this->cols.insert(this->cols.begin() + j - 1, col);
				inserted = true;
				break;

			} else if (j == nnz - 1) {
				this->vals.insert(this->vals.begin() + j, value);
				this->cols.insert(this->cols.begin() + j, col);
				inserted = true;
			}
		}
	}

	if (inserted) {
		for (int i = row; i < (int) this->rows.size(); i++) {
			if (this->rows[i] != 0) {
				this->rows[i]++;
			}
		}
	}

	return *this;
}



vector<int> SparseMatrix::multiply(const vector<int> & x) const
{
	if (this->n != (int) x.size()) {
		throw "Cannot multiply: Matrix column count and vector size don't match.";
	}

	vector<int> result(this->m, 0);

	for (int i = 0; i < this->m; i++) {
		if (this->rows[i] != 0) {
			int nnz = getFirstNextNonZero(this->rows, i);
			for (int j = this->rows[i] - 1; j < nnz - 1; j++) {
				result[i] += x[this->cols[j] - 1] * this->vals[j];
			}
		}
	}

	return result;
}



SparseMatrix SparseMatrix::multiply(const SparseMatrix & m) const
{
	if (this->n != m.m) {
		throw "Cannot multiply: Left matrix column count and right matrix row count don't match.";
	}

	SparseMatrix result(this->m, m.n);

	int a;

	for (int i = 1; i <= this->m; i++) {
		for (int j = 1; j <= m.n; j++) {
			a = 0;

			for (int k = 1; k <= this->n; k++) {
				a += this->get(i, k) * m.get(k, j);
			}

			if (a != 0) {
				result.insert(a, i, j);
			}
		}
	}

	return result;
}



SparseMatrix SparseMatrix::add(const SparseMatrix & m) const
{
	if (this->m != m.m || this->n != m.n) {
		throw "Cannot add: matrices dimensions don't match.";
	}

	SparseMatrix result(this->m, this->n);

	int a;

	for (int i = 1; i <= this->m; i++) {
		for (int j = 1; j <= this->n; j++) {
			a = this->get(i, j) + m.get(i, j);

			if (a != 0) {
				result.insert(a, i, j);
			}
		}
	}

	return result;
}



void SparseMatrix::validateCoordinations(int row, int col) const
{
	if (row < 1 || col < 1 || row > this->m || col > this->n) {
		throw "Coordinations out of range.";
	}
}



bool operator == (const SparseMatrix & a, const SparseMatrix & b)
{
	return a.vals == b.vals && a.cols == b.cols && a.rows == b.rows;
}



bool operator != (const SparseMatrix & a, const SparseMatrix & b)
{
	return !(a == b);
}



ostream & operator << (ostream & os, const SparseMatrix & matrix)
{
	printArray<int>(os, "vals", matrix.vals);
	printArray<int>(os, "cols", matrix.cols);
	printArray<int>(os, "rows", matrix.rows);

	return os;
}
