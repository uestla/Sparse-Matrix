#include <vector>
#include <iostream>
#include "tests.h"
#include "testslib.h"
#include "SparseMatrix.h"

using namespace std;



int main(int argc, char ** argv)
{
	try {
		testException("Constructor fail #1", constructorFail1, "Matrix dimensions cannot be zero or negative.");
		testException("Constructor fail #2", constructorFail2, "Matrix dimensions cannot be zero or negative.");
		testException("Constructor fail #3", constructorFail3, "Matrix dimensions cannot be zero or negative.");
		testException("Constructor fail #4", constructorFail4, "Matrix dimensions cannot be zero or negative.");
		testException("Constructor fail #5", constructorFail5, "Matrix dimensions cannot be zero or negative.");

		testException("get() fail", getFail, "Coordinations out of range.");
		testException("insert() fail", insertFail, "Coordinations out of range.");

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
