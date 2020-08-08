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
#include "inc/testslib.h"
#include "inc/helpers.h"

#include "../src/SparseMatrix/SparseMatrix.cpp"
#include "cases/constructor.cpp"
#include "cases/values.cpp"
#include "cases/multiplication.cpp"
#include "cases/addition.cpp"
#include "cases/subtraction.cpp"
#include "cases/crs-format.cpp"
#include "cases/output.cpp"
#include "cases/custom-type.cpp"


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
		std::cout << " - FAIL: '" << e.getMessage() << "'" << std::endl;
		return 1;
	}

	return 0;
}
