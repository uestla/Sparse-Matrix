#ifndef __TESTSLIB_H__

	#define	__TESTSLIB_H__

	#include <cstring>
	#include <sstream>
	#include <iostream>

	using namespace std;



	void testException(const char * testname, void (*callback)(void), const char * message)
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

		cout << "Test '" << testname << "' passed successfully." << endl;
	}

#endif
