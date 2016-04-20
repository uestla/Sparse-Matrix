# Sparse Matrix library

Sparse Matrix library implements sparse matrix using [CSR](http://netlib.org/linalg/html_templates/node91.html#SECTION00931100000000000000) format. Using this library should be as intuitive as possible (see examples below).

## Usage

### Loading

To load the library just include the header file.

```cpp
#include "SparseMatrix.h"
```


### Matrix creation

The constructor takes one or two arguments depending on if we want to create a square or non-square matrix. By default, values of all matrix elements are 0.

```cpp
SparseMatrix<int> a(3); // 3×3 matrix
SparseMatrix<int> b(3, 5); // 3×5 matrix (3 rows, 5 columns)
```


### Matrix operations

#### Setting element

For inserting new element there is a method `set()`, which takes 3 arguments - what (value) and where (row, column) we want to insert.

```cpp
SparseMatrix<int> a(3);
a.set(-5, 2, 3); // inserts value -5 on 2nd row into 3rd column
```

#### Getting element

To get the value of specific element use method `get()`:

```cpp
SparseMatrix<int> a(3);
a.get(2, 3); // returns value of the element on 2nd row in 3rd column (returns 0 if no value has been assigned yet)
```

#### Vector multiplication

We can multiply the matrix by vector (but only if the vector has a proper dimension).

```cpp
SparseMatrix<int> a(3);
vector<int> x(3, 2);
vector<int> result = a.multiply(x);
```

#### Matrix multiplication

We can also multiply the matrix by another matrix (again - only if the matrix has proper dimensions).

```cpp
SparseMatrix<int> a(3, 4);
SparseMatrix<int> b(4, 5);
SparseMatrix<int> result = a.multiply(b);
```

#### Matrix addition

When two matrices have the same dimensions, we can add them together.

```cpp
SparseMatrix<int> a(3, 4);
SparseMatrix<int> b(3, 4);
SparseMatrix<int> result = a.add(b);
```


#### Matrix printing

When we want to print the matrix in human readable form, we can simply send it to the output stream.

```cpp
SparseMatrix<int> a(3);
std::cout << a << endl;
```
