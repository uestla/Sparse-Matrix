/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#ifndef __TESTSLIB_H__

	#define	__TESTSLIB_H__

	#include <string>
	#include <vector>
	#include <cstring>
	#include <sstream>
	#include <iostream>
	#include <typeinfo>
	#include <exception>


	class FailureException : public std::exception
	{

		public:

			FailureException(const std::string & message) : std::exception(), message(message)
			{}


			virtual ~FailureException(void) throw ()
			{}


			inline std::string getMessage(void) const
			{
				return this->message;
			}


		protected:

			std::string message;

	};


	void assertException(const char * exceptionClass, void (*callback)(void))
	{
		try {
			callback();

		} catch (const std::exception & e) {
			std::string actualClass(typeid(e).name());

			if (strstr(actualClass.c_str(), exceptionClass) == NULL) {
				std::ostringstream oss;
				oss << "Exception class '" << exceptionClass << "' expected, but '" << actualClass << "' thrown.";

				throw FailureException(oss.str());
			}

			return ;
		}

		throw FailureException("Exception expected but none thrown.");
	}


	template<typename T>
	void assertEquals(const T & a, const T & b, const char * message = NULL)
	{
		if (!(a == b)) {
			std::ostringstream oss;
			if (message == NULL) {
				oss << "Objects not equal when they should be." << std::endl;

			} else {
				oss << message << std::endl;
			}

			oss << a << std::endl << "expected, but" << std::endl << b << " given";
			throw FailureException(oss.str());
		}
	}


	template<typename X, typename Y>
	void assertEquals(const X & a, const Y & b, const char * message = NULL)
	{
		if (!(a == b)) {
			std::ostringstream oss;
			if (message == NULL) {
				oss << "Objects not equal when they should be." << std::endl;

			} else {
				oss << message << std::endl;
			}

			oss << a << std::endl << "expected, but" << std::endl << b << " given";
			throw FailureException(oss.str());
		}
	}

#endif
