/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include <vector>
#include <iostream>
#include "exceptions.h"
#include "SparseMatrix.h"

using namespace std;


// === CREATION ==============================================

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
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T> & matrix)
{
    this->deepCopy(matrix);
}


template<typename T>
SparseMatrix<T> & SparseMatrix<T>::operator = (const SparseMatrix<T> & matrix)
{
    if (&matrix != this) {
        this->destruct();
        this->deepCopy(matrix);
    }

    return *this;
}


template<typename T>
void SparseMatrix<T>::deepCopy(const SparseMatrix<T> & matrix)
{
    this->m = matrix.m;
    this->n = matrix.n;
    this->rows = new vector<int>(*(matrix.rows));

    if (matrix.vals != NULL) {
        this->cols = new vector<int>(*(matrix.cols));
        this->vals = new vector<T>(*(matrix.vals));
    }
}


template<typename T>
SparseMatrix<T>::~SparseMatrix(void)
{
    this->destruct();
}


template<typename T>
void SparseMatrix<T>::construct(int rows, int columns)
{
    if (rows < 1 || columns < 1) {
        throw InvalidDimensionsException("Matrix dimensions cannot be zero or negative.");
    }

    this->m = rows;
    this->n = columns;

    this->vals = NULL;
    this->cols = NULL;
    this->rows = new vector<int>(rows + 1, 1);
}


template<typename T>
void SparseMatrix<T>::destruct(void)
{
    if (this->vals != NULL) {
        delete this->vals;
        delete this->cols;
    }

    delete this->rows;
}


// === GETTERS / SETTERS ==============================================

template<typename T>
int SparseMatrix<T>::getRowCount(void) const
{
    return this->m;
}


template<typename T>
int SparseMatrix<T>::getColumnCount(void) const
{
    return this->n;
}


// === VALUES ==============================================

template<typename T>
T SparseMatrix<T>::get(int row, int col) const
{
    this->validateCoordinates(row, col);

    int currCol;

    for (int pos = this->rows->at(row - 1) - 1; pos < this->rows->at(row) - 1; pos++)
    {
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
bool SparseMatrix<T>::removeAnyEdge(int row, int& col)
{
    for (col = 1; col <= this->n; ++col)
    {
        this->validateCoordinates(row, col);

        int pos = this->rows->at(row - 1) - 1;
        int currCol = 0;

        for (; pos < this->rows->at(row) - 1; pos++)
        {
            currCol = this->cols->at(pos);

            if (currCol >= col)
                break;
        }

        if (currCol == col)
        {
            this->remove(pos, row);

            return true;
        }
    }
    return false;
}
template<typename T>
bool SparseMatrix<T>::removeEdge(int row, int col)
{
    this->validateCoordinates(row, col);

    int currCol;

    for (int pos = this->rows->at(row - 1) - 1; pos < this->rows->at(row) - 1; pos++)
    {
        currCol = this->cols->at(pos);

        if (currCol == col)
        {
            remove(pos, row);
            return true;
        }
        else if (currCol > col)
        {
            break;
        }
    }

    return false;
}

template<typename T>
vector<T> SparseMatrix<T>::getNeighbors(int row)
{
    vector<T> neighbors;
    for (int col = 1; col <= this->n; ++col)

    {
        this->validateCoordinates(row, col);

        int currCol;


        for (int pos = this->rows->at(row - 1) - 1; pos < this->rows->at(row) - 1; pos++)
        {
            currCol = this->cols->at(pos);

            if (currCol == col)
                neighbors.push_back(this->vals->at(pos));
            else if (currCol > col)
                break;
        }
    }

    return neighbors;
}

template<typename T>
SparseMatrix<T> & SparseMatrix<T>::set(int row, int col, T val)
{
    this->validateCoordinates(row, col);

    int pos = this->rows->at(row - 1) - 1;
    int currCol = 0;

    for (; pos < this->rows->at(row) - 1; pos++) {
        currCol = this->cols->at(pos);

        if (currCol >= col) {
            break;
        }
    }

    if (currCol != col) {
        if (!(val == T())) {
            this->insert(pos, row, col, val);
        }

    } else if (val == T()) {
        this->remove(pos, row);

    } else {
        this->vals->at(pos) = val;
    }

    return *this;
}


// === OPERATIONS ==============================================

template<typename T>
vector<T> SparseMatrix<T>::multiply(const vector<T> & x) const
{
    if (this->n != (int) x.size()) {
        throw InvalidDimensionsException("Cannot multiply: Matrix column count and vector size don't match.");
    }

    vector<T> result(this->m, T());

    if (this->vals != NULL) { // only if any value set
        for (int i = 0; i < this->m; i++) {
            T sum = T();
            for (int j = this->rows->at(i); j < this->rows->at(i + 1); j++) {
                sum = sum + this->vals->at(j - 1) * x[this->cols->at(j - 1) - 1];
            }

            result[i] = sum;
        }
    }

    return result;
}


template<typename T>
vector<T> SparseMatrix<T>::operator * (const vector<T> & x) const
{
    return this->multiply(x);
}


template<typename T>
SparseMatrix<T> SparseMatrix<T>::multiply(const SparseMatrix<T> & m) const
{
    if (this->n != m.m) {
        throw InvalidDimensionsException("Cannot multiply: Left matrix column count and right matrix row count don't match.");
    }

    SparseMatrix<T> result(this->m, m.n);

    T a;

    // TODO: more efficient?
    // @see http://www.math.tamu.edu/~srobertp/Courses/Math639_2014_Sp/CRSDescription/CRSStuff.pdf

    for (int i = 1; i <= this->m; i++) {
        for (int j = 1; j <= m.n; j++) {
            a = T();

            for (int k = 1; k <= this->n; k++) {
                a = a + this->get(i, k) * m.get(k, j);
            }

            result.set(a, i, j);
        }
    }

    return result;
}


template<typename T>
SparseMatrix<T> SparseMatrix<T>::operator * (const SparseMatrix<T> & m) const
{
    return this->multiply(m);
}


template<typename T>
SparseMatrix<T> SparseMatrix<T>::add(const SparseMatrix<T> & m) const
{
    if (this->m != m.m || this->n != m.n) {
        throw InvalidDimensionsException("Cannot add: matrices dimensions don't match.");
    }

    SparseMatrix<T> result(this->m, this->n);

    // TODO: more efficient?
    // @see http://www.math.tamu.edu/~srobertp/Courses/Math639_2014_Sp/CRSDescription/CRSStuff.pdf

    for (int i = 1; i <= this->m; i++) {
        for (int j = 1; j <= this->n; j++) {
            result.set(this->get(i, j) + m.get(i, j), i, j);
        }
    }

    return result;
}


template<typename T>
SparseMatrix<T> SparseMatrix<T>::operator + (const SparseMatrix<T> & m) const
{
    return this->add(m);
}


template<typename T>
SparseMatrix<T> SparseMatrix<T>::subtract(const SparseMatrix<T> & m) const
{
    if (this->m != m.m || this->n != m.n) {
        throw InvalidDimensionsException("Cannot subtract: matrices dimensions don't match.");
    }

    SparseMatrix<T> result(this->m, this->n);

    // TODO: more efficient?
    // @see http://www.math.tamu.edu/~srobertp/Courses/Math639_2014_Sp/CRSDescription/CRSStuff.pdf

    for (int i = 1; i <= this->m; i++) {
        for (int j = 1; j <= this->n; j++) {
            result.set(this->get(i, j) - m.get(i, j), i, j);
        }
    }

    return result;
}


template<typename T>
SparseMatrix<T> SparseMatrix<T>::operator - (const SparseMatrix<T> & m) const
{
    return this->subtract(m);
}

template<typename T>
int SparseMatrix<T>::numberOfRowElement(int row) const
{
    validateCoordinates(row, 1);
    return this->rows->at(row) - this->rows->at(row - 1);

}




// === HELPERS / VALIDATORS ==============================================

template<typename T>
void SparseMatrix<T>::validateCoordinates(int row, int col) const
{
    if (row < 1 || col < 1 || row > this->m || col > this->n) {
        throw InvalidCoordinatesException("Coordinates out of range.");
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
