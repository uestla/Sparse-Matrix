#ifndef __TESTSLIB_H__

	#define	__TESTSLIB_H__

	#include <string>
	#include <cstring>
	#include <sstream>
	#include <iostream>

	using namespace std;


	class FailureException
	{

		public:

			FailureException(const string & testname, const string & message) : testname(testname), message(message)
			{}


			inline string getTestName(void) const
			{
				return this->testname;
			}


			inline string getMessage(void) const
			{
				return this->message;
			}


		protected:

			string testname, message;

	};


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

				throw FailureException(testname, oss.str());
			}

		} catch (const exception & e) {
			throw FailureException(testname, "Exception expected but none thrown.");
		}

		success(testname);
	}


	template<class T>
	void assertEquals(const char * testname, const T & a, const T & b)
	{
		if (a != b) {
			throw FailureException(testname, "Objects not equal when they should be.");
		}

		success(testname);
	}

#endif
