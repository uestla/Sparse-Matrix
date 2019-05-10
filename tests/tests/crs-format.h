/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include "../testslib.h"
#include "../SparseMatrixMock.h"


void testInternalStorage(void)
{
	cout << "internal storage..." << flush;

	/*
		"Standard" matrix
		[ 1  0 4 5 ]
		[ 2 -1 0 0 ]
		[ 0  0 3 2 ]

		should be stored as
		rows:    [ 1, 4, 6, 8 ]
		columns: [ 1, 3, 4, 1, 2, 3, 4 ]
		values:  [ 1, 4, 5, 2, -1, 3, 2 ]
	*/

	SparseMatrixMock<int> m1(3, 4);
	m1.set(1, 1, 1)
		.set(4, 1, 3)
		.set(5, 1, 4)
		.set(2, 2, 1)
		.set(-1, 2, 2)
		.set(3, 3, 3)
		.set(2, 3, 4);

	vector<int> rowPointers1;
	rowPointers1.push_back(1);
	rowPointers1.push_back(4);
	rowPointers1.push_back(6);
	rowPointers1.push_back(8);
	assertEquals<vector<int> >(rowPointers1, *(m1.getRowPointers()), "Incorrect internal row pointers");

	vector<int> columnPointers1;
	columnPointers1.push_back(1);
	columnPointers1.push_back(3);
	columnPointers1.push_back(4);
	columnPointers1.push_back(1);
	columnPointers1.push_back(2);
	columnPointers1.push_back(3);
	columnPointers1.push_back(4);
	assertEquals<vector<int> >(columnPointers1, *(m1.getColumnPointers()), "Incorrect internal column pointers");

	vector<int> values1;
	values1.push_back(1);
	values1.push_back(4);
	values1.push_back(5);
	values1.push_back(2);
	values1.push_back(-1);
	values1.push_back(3);
	values1.push_back(2);
	assertEquals<vector<int> >(values1, *(m1.getValues()), "Incorrect internal values storage");


	/*
		Matrix with empty row
		[ 10 0 0 2 ]
		[  0 0 0 0 ]
		[  3 1 0 4 ]

		should be stored as
		rows:    [ 1, 3, 3, 6 ]
		columns: [ 1, 4, 1, 2, 4 ]
		values:  [ 10, 2, 3, 1, 4 ]
	*/

	SparseMatrixMock<int> m2(3, 4);
	m2.set(10, 1, 1)
		. set(2, 1, 4)
		. set(3, 3, 1)
		. set(1, 3, 2)
		. set(4, 3, 4);

	vector<int> rowPointers2;
	rowPointers2.push_back(1);
	rowPointers2.push_back(3);
	rowPointers2.push_back(3);
	rowPointers2.push_back(6);
	assertEquals<vector<int> >(rowPointers2, *(m2.getRowPointers()), "Incorrect internal row pointers");

	vector<int> columnPointers2;
	columnPointers2.push_back(1);
	columnPointers2.push_back(4);
	columnPointers2.push_back(1);
	columnPointers2.push_back(2);
	columnPointers2.push_back(4);
	assertEquals<vector<int> >(columnPointers2, *(m2.getColumnPointers()), "Incorrect internal column pointers");

	vector<int> values2;
	values2.push_back(10);
	values2.push_back(2);
	values2.push_back(3);
	values2.push_back(1);
	values2.push_back(4);
	assertEquals<vector<int> >(values2, *(m2.getValues()), "Incorrect internal values storage");


	/*
		Previous matrix after adding non-zero element to empty row

		should be stored as
		rows:    [ 1, 3, 4, 7 ]
		columns: [ 1, 4, 2, 1, 2, 4 ]
		values:  [ 10, 2, 5, 3, 1, 4 ]
	 */

	SparseMatrixMock<int> m3 = m2;
	m3.set(5, 2, 2);

	vector<int> rowPointers3;
	rowPointers3.push_back(1);
	rowPointers3.push_back(3);
	rowPointers3.push_back(4);
	rowPointers3.push_back(7);
	assertEquals<vector<int> >(rowPointers3, *(m3.getRowPointers()), "Incorrect internal row pointers");

	vector<int> columnPointers3;
	columnPointers3.push_back(1);
	columnPointers3.push_back(4);
	columnPointers3.push_back(2);
	columnPointers3.push_back(1);
	columnPointers3.push_back(2);
	columnPointers3.push_back(4);
	assertEquals<vector<int> >(columnPointers3, *(m3.getColumnPointers()), "Incorrect internal column pointers");

	vector<int> values3;
	values3.push_back(10);
	values3.push_back(2);
	values3.push_back(5);
	values3.push_back(3);
	values3.push_back(1);
	values3.push_back(4);
	assertEquals<vector<int> >(values3, *(m3.getValues()), "Incorrect internal values storage");

	/*
		Previous matrix with removed the only non-zero element on 2nd row (should be equal to 2nd matrix)

		should be stored as
		rows:    [ 1, 3, 3, 6 ]
		columns: [ 1, 4, 1, 2, 4 ]
		values:  [ 10, 2, 3, 1, 4 ]
	 */

	SparseMatrixMock<int> m4 = m3;
	m4.set(0, 2, 2);

	assertEquals<vector<int> >(rowPointers2, *(m4.getRowPointers()), "Incorrect internal row pointers");
	assertEquals<vector<int> >(columnPointers2, *(m4.getColumnPointers()), "Incorrect internal column pointers");
	assertEquals<vector<int> >(values2, *(m4.getValues()), "Incorrect internal values storage");

	cout << " OK" << endl;
}
