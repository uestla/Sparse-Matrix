/**
 * This file is part of the SparseMatrix library
 *
 * Copyright (c) 2014-2016 Petr Kessler (https://kesspess.cz)
 *
 * @license  MIT
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include <string>
#include <iostream>
#include "../testslib.h"
#include "../SparseMatrixMock.h"

using namespace std;


struct person
{
	person(void) : firstname(""), lastname("") {}
	person(const person & p) : firstname(p.firstname), lastname(p.lastname) {}
	person(const string & f, const string & l) : firstname(f), lastname(l) {}
	string firstname, lastname;
};


bool operator == (const person & a, const person & b)
{
	return a.firstname == b.firstname
			&& a.lastname == b.lastname;
}


string joinStrings(const string & a, const string & b)
{
	string c = a;

	if (a.length() && b.length()) {
		c += " ";
	}

	c += b;
	return c;
}


person operator + (const person & a, const person & b)
{
	return person(joinStrings(a.firstname, b.firstname), joinStrings(a.lastname, b.lastname));
}


person operator * (const person & a, const person & b)
{
	if (a == person("", "") || b == person("", "")) {
		return person("", "");
	}

	return person(joinStrings(a.firstname, b.lastname), joinStrings(a.lastname, b.firstname));
}


ostream & operator << (ostream & os, const person & p)
{
	os << p.firstname << ", " << p.lastname;
	return os;
}


void testElementTypes(void)
{
	cout << "custom element types..." << flush;

	// addition

	SparseMatrix<person> a(4, 5);
	a.set(person("John", "Doe"), 3, 2);

	SparseMatrix<person> b(4, 5);
	b.set(person("Foo", "Bar"), 3, 2);

	SparseMatrix<person> sum = a.add(b);
	assertEquals<person>(person("John Foo", "Doe Bar"), sum.get(3, 2));


	// matrix-matrix multiplication

	SparseMatrix<person> c(5, 3);
	c.set(person("Foo", "Bar"), 2, 3);

	SparseMatrix<person> product = a.multiply(c);

	for (int i = 1, rows = product.getRowCount(); i <= rows; i++) {
		for (int j = 1, cols = product.getColumnCount(); j <= cols; j++) {
			person value = product.get(i, j);

			if (i == 3 && j == 3) {
				assertEquals<person>(person("John Bar", "Doe Foo"), value);

			} else {
				assertEquals<person>(person(), value);
			}
		}
	}


	// vector-matrix multiplication

	vector<person> people;
	people.push_back(person("John", "Doe"));
	people.push_back(person("Foo", "Bar"));
	people.push_back(person("Willy", "Wonka"));
	people.push_back(person("Jon", "Snow"));
	people.push_back(person("Bridget", "Johnes"));

	vector<person> result = a.multiply(people);
	assertEquals<person>(person(), result[0]);
	assertEquals<person>(person(), result[1]);
	assertEquals<person>(person("John Bar", "Doe Foo"), result[2]);
	assertEquals<person>(person(), result[3]);

	cout << " OK" << endl;
}
