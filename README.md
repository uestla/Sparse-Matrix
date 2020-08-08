# Sparse Matrix

C++ implementation of sparse matrix using [CRS format](http://netlib.org/linalg/html_templates/node91.html#SECTION00931100000000000000).

[![Buy me a Coffee](https://www.paypalobjects.com/en_US/i/btn/btn_donate_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=KWQJ7VTXZMZLS)


## Usage

### Creation

SparseMatrix comes as a template class, so we have to specify the element type.

```cpp
SparseMatrix::SparseMatrix<int> matrix(3); // 3×3 matrix of integers
SparseMatrix::SparseMatrix<int> matrix2(4, 5); // 4×5 matrix - 4 rows, 5 columns

SparseMatrix::SparseMatrix<int> matrix3(matrix); // copy constructor
SparseMatrix::SparseMatrix<int> matrix4 = matrix2; // deep copy assignment
```

All values are now equal to `<type>()`, which for type `int` is `0`.

### Values

To set or get value, use methods `set()` and `get()`:

```cpp
int val;
matrix.set(-5, 2, 3); // sets -5 on 2nd row and 3rd column
val = matrix.get(2, 3); // val = -5
val = matrix.get(1, 1); // val = 0
```

When accessing invalid coordinates, `InvalidCoordinatesException` is thrown. Please note that **rows and columns are indexed from 1**.

### Operations

SparseMatrix is implemented as an immutable object - all operations create new matrix instead of changing the matrix the operation is called on.

#### Matrix-Vector multiplication

Number of columns in the matrix has to be the same as the size of the vector, otherwise `InvalidDimensionsException` is thrown.

```cpp
SparseMatrix::SparseMatrix<int> mat(4, 5);
std::vector<int> vec(5, 2);

std::vector<int> result;
result = mat.multiply(vec); // method
result = mat * vec; // operator
```

#### Matrix-Matrix multiplication

Number of columns in the left matrix must be same as number of rows in the right matrix, otherwise `InvalidDimensionsException` is thrown.

```cpp
SparseMatrix::SparseMatrix<int> matrixA(2, 3);
SparseMatrix::SparseMatrix<int> matrixB(3, 4);

SparseMatrix::SparseMatrix<int> product; // will be of size 2×4
product = matrixA.multiply(matrixB); // method
product = matrixA * matrixB; // operator
```

#### Matrix-Matrix addition / subtraction

You can also add and subtract matrices together. Both matrices has to have same dimentions, otherwise `InvalidDimensionsException` is thrown.

```cpp
SparseMatrix::SparseMatrix<int> matrixA(4, 7);
SparseMatrix::SparseMatrix<int> matrixB(4, 7);

SparseMatrix::SparseMatrix<int> sum;
sum = matrixA.add(matrixB); // method
sum = matrixA + matrixB; // operator

SparseMatrix::SparseMatrix<int> diff;
diff = matrixA.subtract(matrixB); // method
diff = matrixA - matrixB; // operator
```

#### Matrix-Matrix comparison

```cpp
SparseMatrix::SparseMatrix<int> matrixA(3);
SparseMatrix::SparseMatrix<int> matrixB(3);

bool areSame = matrixA == matrixB; // true
```

#### Dimensions

To access matrix dimensions use simple getters:

```cpp
int rows = matrix.getRowCount();
int cols = matrix.getColumnCount();
```

#### Printing matrix

Basic output streaming is implemented. Note that output operator must be implemented for the element type as well.

```cpp
SparseMatrix::SparseMatrix<int> matrix(3, 4);
matrix.set(2, 1, 1);
matrix.set(7, 1, 3);
matrix.set(4, 2, 2);
matrix.set(1, 3, 4);

std::cout << matrix << std::endl;

/*
2 0 7 0
0 4 0 0
0 0 0 1
*/
```

### Custom element type

If integers/floats are not enough, you can always use your own element type.

Make sure your type implements:

* empty constructor (which represents the zero value)
* copying constructor
* comparison `operator ==` so that it is possible to tell whether a value is zero-ish
* adding `operator +`
* subtracting `operator -`
* product `operator *`
* output `operator <<` to be able to nicely output the matrix

You can see a simple custom element example in [the tests](tests/cases/custom-type.cpp).


-----------

Any questions / issues / pull requests / [donations](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=KWQJ7VTXZMZLS) are very welcome! :-)
