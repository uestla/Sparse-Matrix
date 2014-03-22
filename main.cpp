#include <vector>
#include <iostream>
#include "SparseMatrix.h"

using namespace std;



int main(int argc, char ** argv)
{
	try {
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

	} catch (const char * message) {
		cout << "error: " << message << endl;
	}

	return 0;
}
