#ifndef __SPARSEMATRIX_H__

	#define	__SPARSEMATRIX_H__

	#include <vector>
	#include <iostream>

	using namespace std;



	class SparseMatrix
	{

		public:

			SparseMatrix(unsigned int n);
			SparseMatrix(unsigned int rows, unsigned int columns);

			int get(unsigned int row, unsigned int col) const;
			SparseMatrix & insert(int value, unsigned int row, unsigned int col);

			vector<int> multiply(const vector<int> & x) const;
			SparseMatrix multiply(const SparseMatrix & m) const;

			SparseMatrix add(const SparseMatrix & m) const;

			friend ostream & operator << (ostream & os, const SparseMatrix & matrix);
			friend void print(const SparseMatrix & matrix, ostream & os);



		protected:

			unsigned int m, n;

			vector<int> vals;
			vector<unsigned int> cols, rows;

			void construct(unsigned int m, unsigned int n);
			void validateCoordinations(unsigned int row, unsigned int col) const;

	};

#endif
