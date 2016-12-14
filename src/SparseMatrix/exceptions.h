/**
 * This file is part of the SparseMatrix library
 *
 * Copyright (c) 2014-2016 Petr Kessler (https://kesspess.cz)
 *
 * @license  MIT
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#ifndef __SPARSEMATRIX_EXCEPTIONS_H__

	#define	__SPARSEMATRIX_EXCEPTIONS_H__

	#include <exception>

	using namespace std;


	class Exception : public exception
	{

		public:

			explicit Exception(const string & message) : exception(), message(message)
			{}


			virtual ~Exception(void) throw ()
			{}


			inline string getMessage(void) const
			{
				return this->message;
			}


		protected:

			string message;

	};


	class InvalidDimensionsException : public Exception
	{

		public:

			InvalidDimensionsException(const string & message) : Exception(message)
			{}

	};


	class InvalidCoordinatesException : public Exception
	{

		public:

			InvalidCoordinatesException(const string & message) : Exception(message)
			{}

	};

#endif