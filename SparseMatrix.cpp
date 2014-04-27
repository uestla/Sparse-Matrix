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



SparseMatrix::~SparseMatrix(void)
{
	if (this->vals != NULL) {
		delete this->vals;
		delete this->cols;
	}

	delete this->rows;
}



void SparseMatrix::construct(int rows, int columns)
{
	if (rows < 1 || columns < 1) {
		throw "Matrix dimensions cannot be zero or negative.";
	}

	this->m = rows;
	this->n = columns;

	this->vals = this->cols = NULL;
	this->rows = new vector<int>(rows + 1, 1);
}



int SparseMatrix::get(int row, int col) const
{
	this->validateCoordinations(row, col);

	int actual;

	for (int i = this->rows->at(row - 1) - 1; i < this->rows->at(row) - 1; i++) {
		actual = this->cols->at(i);

		if (actual == col) {
			return this->vals->at(i);

		} else if (actual > col) {
			break;
		}
	}

	return 0;
}



SparseMatrix & SparseMatrix::set(int val, int row, int col)
{
	this->validateCoordinations(row, col);

	int pos = this->rows->at(row - 1) - 1;
	int actual;

	for (; pos < this->rows->at(row) - 1; pos++) {
		actual = this->cols->at(pos);

		if (actual == col) {
			break;

		} else if (actual > col) {
			break;
		}
	}

	if (pos == this->rows->at(row) - 1) {
		if (val != 0) {
			this->insert(pos, row, col, val);
		}

	} else {
		if (val == 0) {
			this->remove(pos, row);

		} else {
			(*this->vals)[pos] = val;
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



void SparseMatrix::insert(int index, int row, int col, int val)
{
	if (this->vals == NULL) {
		this->vals = new vector<int>(1, val);
		this->cols = new vector<int>(1, col);

	} else {
		this->vals->insert(this->vals->begin() + index, val);
		this->cols->insert(this->cols->begin() + index, col);
	}

	for (int i = row; i <= this->m; i++) {
		(*(this->rows))[i] = (*(this->rows))[i] + 1;
	}
}



void SparseMatrix::remove(int index, int row)
{
	this->vals->erase(this->vals->begin() + index);
	this->cols->erase(this->cols->begin() + index);

	for (int i = row; i <= this->m; i++) {
		(*(this->rows))[i] = (*(this->rows))[i] - 1;
	}
}



bool operator == (const SparseMatrix & a, const SparseMatrix & b)
{
	return ((a.vals == NULL && b.vals == NULL)
				|| (a.vals != NULL && b.vals != NULL && *(a.vals) == *(b.vals)))
			&& ((a.cols == NULL && b.cols == NULL)
				|| (a.cols != NULL && b.cols != NULL && *(a.cols) == *(b.cols)))
			&& *(a.rows) == *(b.rows);
}



bool operator != (const SparseMatrix & a, const SparseMatrix & b)
{
	return !(a == b);
}



ostream & operator << (ostream & os, const SparseMatrix & matrix)
{
	for (int i = 1; i <= matrix.m; i++) {
		for (int j = 1; j <= matrix.n; j++) {
			if (j != 1) {
				os << " ";
			}

			os << matrix.get(i, j);
		}

		if (i < matrix.m) {
			os << endl;
		}
	}

	return os;
}
