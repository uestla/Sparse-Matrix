/**
 * This file is part of the SparseMatrix library
 *
 * Copyright (c) 2014-2016 Petr Kessler (http://kesspess.1991.cz)
 *
 * @license  MIT
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include <vector>
#include <iostream>
#include "SparseMatrix.h"

using namespace std;


template<typename T>
SparseMatrix<T>::SparseMatrix(int n)
{
	this->construct(n, n);
}


template<typename T>
SparseMatrix<T>::SparseMatrix(int rows, int columns)
{
	this->construct(rows, columns);
}


template<typename T>
void SparseMatrix<T>::construct(int rows, int columns)
{
	if (rows < 1 || columns < 1) {
		throw "Matrix dimensions cannot be zero or negative.";
	}

	this->m = rows;
	this->n = columns;

	this->vals = NULL;
	this->cols = NULL;
	this->rows = new vector<int>(rows + 1, 1);
}


template<typename T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T> & matrix)
{
	this->deepCopy(matrix);
}


template<typename T>
SparseMatrix<T> & SparseMatrix<T>::operator = (const SparseMatrix<T> & matrix)
{
	if (&matrix != this) {
		this->deepCopy(matrix);
	}

	return *this;
}


template<typename T>
void SparseMatrix<T>::deepCopy(const SparseMatrix<T> & matrix)
{
	this->m = matrix.m;
	this->n = matrix.n;
	this->cols = new vector<int>(*(matrix.cols));
	this->rows = new vector<int>(*(matrix.rows));
	this->vals = new vector<T>(*(matrix.vals));
}


template<typename T>
SparseMatrix<T>::~SparseMatrix(void)
{
	if (this->vals != NULL) {
		delete this->vals;
		delete this->cols;
	}

	delete this->rows;
}


template<typename T>
T SparseMatrix<T>::get(int row, int col) const
{
	this->validateCoordinates(row, col);

	int currCol;

	for (int pos = this->rows->at(row - 1) - 1; pos < this->rows->at(row) - 1; pos++) {
		currCol = this->cols->at(pos);

		if (currCol == col) {
			return this->vals->at(pos);

		} else if (currCol > col) {
			break;
		}
	}

	return T();
}


template<typename T>
SparseMatrix<T> & SparseMatrix<T>::set(T val, int row, int col)
{
	this->validateCoordinates(row, col);

	int pos = this->rows->at(row - 1) - 1;
	int currCol = 0;

	for (; pos < this->rows->at(row) - 1; pos++) {
		currCol = this->cols->at(pos);

		if (currCol == col) {
			break;

		} else if (currCol > col) {
			break;
		}
	}

	if (currCol != col) {
		if (val != T()) {
			this->insert(pos, row, col, val);
		}

	} else if (val == T()) {
		this->remove(pos, row);

	} else {
		this->vals->at(pos) = val;
	}

	return *this;
}


template<typename T>
vector<T> SparseMatrix<T>::multiply(const vector<T> & x) const
{
	if (this->n != (int) x.size()) {
		throw "Cannot multiply: Matrix column count and vector size don't match.";
	}

	vector<T> result(this->m, T());

	if (this->vals != NULL) { // only if some values set
		int row = 1;

		for (int i = 0, len = this->vals->size(); i < len; i++) {
			if (this->rows->at(row) - 1 == i) {
				row++;
			}

			result[row - 1] += this->vals->at(i) * x[this->cols->at(i) - 1];
		}
	}

	return result;
}


template<typename T>
SparseMatrix<T> SparseMatrix<T>::multiply(const SparseMatrix<T> & m) const
{
	if (this->n != m.m) {
		throw "Cannot multiply: Left matrix column count and right matrix row count don't match.";
	}

	SparseMatrix<T> result(this->m, m.n);

	T a;

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


template<typename T>
SparseMatrix<T> SparseMatrix<T>::add(const SparseMatrix<T> & m) const
{
	if (this->m != m.m || this->n != m.n) {
		throw "Cannot add: matrices dimensions don't match.";
	}

	SparseMatrix<T> result(this->m, this->n);

	for (int i = 1; i <= this->m; i++) {
		for (int j = 1; j <= this->n; j++) {
			result.set(this->get(i, j) + m.get(i, j), i, j);
		}
	}

	return result;
}


template<typename T>
void SparseMatrix<T>::validateCoordinates(int row, int col) const
{
	if (row < 1 || col < 1 || row > this->m || col > this->n) {
		throw "Coordinates out of range.";
	}
}


template<typename T>
void SparseMatrix<T>::insert(int index, int row, int col, T val)
{
	if (this->vals == NULL) {
		this->vals = new vector<T>(1, val);
		this->cols = new vector<int>(1, col);

	} else {
		this->vals->insert(this->vals->begin() + index, val);
		this->cols->insert(this->cols->begin() + index, col);
	}

	for (int i = row; i <= this->m; i++) {
		this->rows->at(i) = this->rows->at(i) + 1;
	}
}


template<typename T>
void SparseMatrix<T>::remove(int index, int row)
{
	this->vals->erase(this->vals->begin() + index);
	this->cols->erase(this->cols->begin() + index);

	for (int i = row; i <= this->m; i++) {
		this->rows->at(i) = this->rows->at(i) - 1;
	}
}


// === FRIEND FUNCTIONS =========================================

template<typename T>
bool operator == (const SparseMatrix<T> & a, const SparseMatrix<T> & b)
{
	return ((a.vals == NULL && b.vals == NULL)
				|| (a.vals != NULL && b.vals != NULL && *(a.vals) == *(b.vals)))
			&& ((a.cols == NULL && b.cols == NULL)
				|| (a.cols != NULL && b.cols != NULL && *(a.cols) == *(b.cols)))
			&& *(a.rows) == *(b.rows);
}


template<typename T>
bool operator != (const SparseMatrix<T> & a, const SparseMatrix<T> & b)
{
	return !(a == b);
}


template<typename T>
ostream & operator << (ostream & os, const SparseMatrix<T> & matrix)
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


// === BASIC TYPES DECLARATIONS =========================================

template class SparseMatrix<int>;
template class SparseMatrix<float>;
template class SparseMatrix<double>;

template bool operator == (const SparseMatrix<int> & a, const SparseMatrix<int> & b);
template bool operator != (const SparseMatrix<int> & a, const SparseMatrix<int> & b);
template bool operator == (const SparseMatrix<float> & a, const SparseMatrix<float> & b);
template bool operator != (const SparseMatrix<float> & a, const SparseMatrix<float> & b);
template bool operator == (const SparseMatrix<double> & a, const SparseMatrix<double> & b);
template bool operator != (const SparseMatrix<double> & a, const SparseMatrix<double> & b);

template ostream & operator << (ostream & os, const SparseMatrix<int> & m);
template ostream & operator << (ostream & os, const SparseMatrix<float> & m);
template ostream & operator << (ostream & os, const SparseMatrix<double> & m);
