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
#include "tests.h"

using namespace std;


int main(int argc, char ** argv)
{
	try {
		assertException("constructor fail #1", constructorFail1, "Matrix dimensions cannot be zero or negative.");
		assertException("constructor fail #2", constructorFail2, "Matrix dimensions cannot be zero or negative.");
		assertException("constructor fail #3", constructorFail3, "Matrix dimensions cannot be zero or negative.");
		assertException("constructor fail #4", constructorFail4, "Matrix dimensions cannot be zero or negative.");

		assertException("get() fail", getFail, "Coordinates out of range.");
		assertException("set() fail", setFail, "Coordinates out of range.");

		assertException("multiply() fail #1", multiplicationFail1, "Cannot multiply: Matrix column count and vector size don't match.");
		assertException("multiply() fail #2", multiplicationFail2, "Cannot multiply: Left matrix column count and right matrix row count don't match.");

		assertException("add() fail #1", additionFail1, "Cannot add: matrices dimensions don't match.");
		assertException("add() fail #2", additionFail2, "Cannot add: matrices dimensions don't match.");
		assertException("add() fail #3", additionFail3, "Cannot add: matrices dimensions don't match.");

		testInsertion();
		testInternalStorage();

		testVectorMultiplication1();
		testVectorMultiplication2();
		testVectorMultiplication3();

		testAddition1();
		testAddition2();
		testAddition3();

		testMultiplication1();
		testMultiplication2();
		testMultiplication3();

	} catch (const FailureException & e) {
		cerr << e.getTestName() << " - FAIL: '" << e.getMessage() << "'." << endl;
		return 1;
	}

	return 0;
}
