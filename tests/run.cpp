/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include <ctime>
#include <cstdlib>
#include <iostream>
#include "testslib.h"

#include "../src/SparseMatrix/SparseMatrix.cpp"
#include "tests/constructor.h"
#include "tests/get-set.h"
#include "tests/multiplication.h"
#include "tests/addition.h"
#include "tests/subtraction.h"
#include "tests/crs-format.h"
#include "tests/output.h"
#include "tests/custom-type.h"

using namespace std;


int main(int argc, char ** argv)
{
	srand(time(NULL)); // used at random matrices / vectors generating

	try {

		testConstructorFail1();
		testConstructorFail2();
		testConstructorFail3();
		testConstructorFail4();
		testGetFail();
		testSetFail();
		testMultiplicationFail1();
		testMultiplicationFail2();
		testAdditionFail1();
		testAdditionFail2();
		testAdditionFail3();
		testSubtractionFail1();
		testSubtractionFail2();
		testSubtractionFail3();
		testGettersAndSetters();
		testInternalStorage();
		testOutput();
		testVectorMultiplication();
		testMatricesMultiplication();
		testAddition();
		testSubtraction();
		testElementTypes();

	} catch (const FailureException & e) {
		cout << " - FAIL: '" << e.getMessage() << "'" << endl;
		return 1;
	}

	return 0;
}
