#ifndef __SPARSEMATRIX_H__

	#define	__SPARSEMATRIX_H__

	#include <vector>
	#include <iostream>

	using namespace std;



	class SparseMatrix
	{

		public:

			SparseMatrix(int n);
			SparseMatrix(int rows, int columns);

			int get(int row, int col) const;
			SparseMatrix & insert(int value, int row, int col);

			vector<int> multiply(const vector<int> & x) const;
			SparseMatrix multiply(const SparseMatrix & m) const;

			SparseMatrix add(const SparseMatrix & m) const;

			friend bool operator == (const SparseMatrix & a, const SparseMatrix & b);
			friend bool operator != (const SparseMatrix & a, const SparseMatrix & b);
			friend ostream & operator << (ostream & os, const SparseMatrix & matrix);
			friend void print(const SparseMatrix & matrix, ostream & os);



		protected:

			int m, n;

			vector<int> vals, cols, rows;

			void construct(int m, int n);
			void validateCoordinations(int row, int col) const;

	};

#endif
