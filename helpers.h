#ifndef __HELPERS_H__

	#define	__HELPERS_H__

	#include <vector>
	#include "SparseMatrix.h"

	using namespace std;



	unsigned int getFirstNextNonZero(const vector<unsigned int> & array, unsigned int index)
	{
		for (unsigned int i = index + 1, len = array.size(); i < len; i++) {
			if (array[i] != 0) {
				return array[i];
			}
		}

		return 0;
	}



	void print(const SparseMatrix & matrix, ostream & os)
	{
		for (unsigned int i = 1; i <= matrix.n; i++) {
			for (unsigned int j = 1; j <= matrix.m; j++) {
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

		for (unsigned int i = 0, len = array.size(); i < len; i++) {
			os << array[i];

			if (i != len - 1) {
				os << ", ";
			}
		}

		os << "]" << endl;
	}

#endif
