#ifndef __HELPERS_H__

	#define	__HELPERS_H__

	#include <vector>
	#include "SparseMatrix.h"

	using namespace std;



	int getFirstNextNonZero(const vector<int> & array, int index)
	{
		for (int i = index + 1, size = array.size(); i < size; i++) {
			if (array[i] != 0) {
				return array[i];
			}
		}

		return 0;
	}



	void print(const SparseMatrix & matrix, ostream & os)
	{
		for (int i = 1; i <= matrix.n; i++) {
			for (int j = 1; j <= matrix.m; j++) {
				os << matrix.get(i, j) << " ";
			}

			os << endl;
		}

		os << endl;
	}



	template<class T>
	void printArray(ostream & os, const char * name, vector<T> array)
	{
		os << name << ": [";

		for (unsigned int i = 0, size = array.size(); i < size; i++) {
			os << array[i];

			if (i != size - 1) {
				os << ", ";
			}
		}

		os << "]" << endl;
	}

#endif
