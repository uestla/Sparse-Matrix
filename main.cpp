#include <vector>
#include <iostream>
#include "tests.h"
#include "testslib.h"
#include "SparseMatrix.h"

using namespace std;



int main(int argc, char ** argv)
{
	try {
		assertException("constructor fail #1", constructorFail1, "Matrix dimensions cannot be zero or negative.");
		assertException("constructor fail #2", constructorFail2, "Matrix dimensions cannot be zero or negative.");
		assertException("constructor fail #3", constructorFail3, "Matrix dimensions cannot be zero or negative.");
		assertException("constructor fail #4", constructorFail4, "Matrix dimensions cannot be zero or negative.");
		assertException("constructor fail #5", constructorFail5, "Matrix dimensions cannot be zero or negative.");

		assertException("get() fail", getFail, "Coordinations out of range.");
		assertException("insert() fail", insertFail, "Coordinations out of range.");

		assertException("multiply() fail #1", multiplicationFail1, "Cannot multiply: Matrix column count and vector size don't match.");
		assertException("multiply() fail #2", multiplicationFail2, "Cannot multiply: Left matrix column count and right matrix row count don't match.");

		assertException("add() fail #1", additionFail1, "Cannot add: matrices dimensions don't match.");
		assertException("add() fail #2", additionFail2, "Cannot add: matrices dimensions don't match.");
		assertException("add() fail #3", additionFail3, "Cannot add: matrices dimensions don't match.");

		testVectorMultiplication1();
		testVectorMultiplication2();
		testVectorMultiplication3();

		testAddition1();
		testAddition2();
		testAddition3();

	} catch (const char * message) {
		cout << "Tests failed: " << message << endl;
		return 1;
	}

	return 0;

	/* try {
		SparseMatrix m(3);
		cout << m << endl;
		print(m, cout);

		m.insert(1, 1, 2);
		cout << m << endl;
		print(m, cout);

		m.insert(6, 3, 2);
		cout << m << endl;
		print(m, cout);

		m.insert(7, 1, 1);
		cout << m << endl;
		print(m, cout);

		m.insert(-4, 1, 2);
		cout << m << endl;
		print(m, cout);

		m.insert(5, 2, 1);
		cout << m << endl;
		print(m, cout);


		SparseMatrix mm(4);
		mm.insert(10, 1, 1);
		cout << mm << endl;

		mm.insert(3, 2, 1);
		cout << mm << endl;

		mm.insert(9, 2, 2);
		cout << mm << endl;

		mm.insert(7, 3, 2);
		cout << mm << endl;

		mm.insert(8, 3, 3);
		cout << mm << endl;

		mm.insert(7, 3, 4);
		cout << mm << endl;

		mm.insert(3, 4, 1);
		cout << mm << endl;

		mm.insert(8, 4, 3);
		cout << mm << endl;

		mm.insert(7, 4, 4);
		cout << mm << endl;

		print(mm, cout);

		vector<int> x;
		x.push_back(1);
		x.push_back(2);
		x.push_back(3);
		x.push_back(4);

		print("result", mm.multiply(x));

	} catch (const char * message) {
		cout << "error: " << message << endl;
	}

	return 0; */
}
