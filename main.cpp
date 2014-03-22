#include <vector>
#include <iostream>
#include "SparseMatrix.h"

using namespace std;



void print(const char * name, const vector<int> & x)
{
	cout << name << " = [";

	for (unsigned int i = 0, size = x.size(); i < size; i++) {
		cout << x[i];

		if (i != size - 1) {
			cout << ", ";
		}
	}

	cout << "]" << endl;
}



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


		SparseMatrix mm(4);
		mm.insert(10, 1, 1);
		mm.insert(3, 2, 1);
		mm.insert(9, 2, 2);
		mm.insert(7, 3, 2);
		mm.insert(8, 3, 3);
		mm.insert(7, 3, 4);
		mm.insert(3, 4, 1);
		mm.insert(8, 4, 3);
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

	return 0;
}
