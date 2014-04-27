/**
 * This file is part of the SparseMatrix library
 *
 * Copyright (c) 2014 Petr Kessler (http://kesspess.1991.cz)
 *
 * @license  MIT
 * @link     https://github.com/uestla/Sparse-Matrix
 */

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

	for (int i = 0; i <= rows; i++) {
		this->rows.push_back(1);
	}
}



int SparseMatrix::get(int row, int col) const
{
	this->validateCoordinations(row, col);

	for (int i = this->rows[row - 1] - 1; i < this->rows[row] - 1; i++) {
		if (this->cols[i] == col) {
			return this->vals[i];
		}
	}

	return 0;
}



SparseMatrix & SparseMatrix::set(int value, int row, int col)
{
	this->validateCoordinations(row, col);

	int pos = this->rows[row - 1] - 1;

	for (; pos < this->rows[row] - 1; pos++) {
		if (this->cols[pos] == col) {
			break;

		} else if (col < this->cols[pos]) {
			break;
		}
	}

	if (pos < (int) this->cols.size() && this->cols[pos] == col) {
		if (value == 0) {
			this->remove(pos, row);

		} else {
			this->vals[pos] = value;
		}

	} else if (value != 0) {
		this->insert(this->rows[row] - 1, row, col, value);
	}

	return *this;
}



vector<int> SparseMatrix::multiply(const vector<int> & x) const
{
	if (this->n != (int) x.size()) {
		throw "Cannot multiply: Matrix column count and vector size don't match.";
	}

	vector<int> result(this->m, 0);

	for (int i = 1; i <= this->m; i++) {
		for (int j = 1; j <= this->n; j++) {
			result[i - 1] += this->get(i, j) * x[j - 1];
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

			result.set(a, i, j);
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

	for (int i = 1; i <= this->m; i++) {
		for (int j = 1; j <= this->n; j++) {
			result.set(this->get(i, j) + m.get(i, j), i, j);
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



void SparseMatrix::insert(int index, int row, int col, int value)
{
	this->cols.insert(this->cols.begin() + index, col);
	this->vals.insert(this->vals.begin() + index, value);

	for (int i = row; i <= this->m; i++) {
		this->rows[i]++;
	}
}



void SparseMatrix::remove(int index, int row)
{
	this->cols.erase(this->cols.begin() + index);
	this->vals.erase(this->vals.begin() + index);

	for (int i = row; i <= this->m; i++) {
		this->rows[i]--;
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
