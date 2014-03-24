#ifndef __TESTSLIB_H__

	#define	__TESTSLIB_H__

	#include <cstring>
	#include <sstream>
	#include <iostream>

	using namespace std;



	void success(const char * name)
	{
		cout << "Test '" << name << "' passed successfully." << endl;
	}



	void assertException(const char * testname, void (*callback)(void), const char * message)
	{
		try {
			callback();
			throw exception();

		} catch (const char * msg) {
			if (strcmp(msg, message) != 0) {
				ostringstream oss;
				oss << "Exception message '" << message << "' expected, but '" << msg << "' given.";
				throw oss.str().c_str();
			}

		} catch (const exception & e) {
			throw "Exception expected but none thrown.";
		}

		success(testname);
	}



	template<class T>
	void assertEquals(const char * testname, const T & a, const T & b)
	{
		if (a != b) {
			throw "Objects not equal when they should be.";
		}

		success(testname);
	}

#endif
