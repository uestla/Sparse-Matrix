/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#include <string>
#include <vector>
#include <iostream>
#include "../inc/testslib.h"
#include "../inc/SparseMatrixMock.h"


std::string joinStrings(const std::string & a, const std::string & b)
{
	std::string c = a;

	if (a.length() && b.length()) {
		c += " ";
	}

	c += b;
	return c;
}


struct person
{

	person(void) : firstname(""), lastname("")
	{}


	person(const person & p) : firstname(p.firstname), lastname(p.lastname)
	{}


	person(const std::string & f, const std::string & l) : firstname(f), lastname(l)
	{}


	bool operator == (const person & p) const
	{
		return this->firstname == p.firstname && this->lastname == p.lastname;
	}


	person operator + (const person & p) const
	{
		return person(joinStrings(this->firstname, p.firstname), joinStrings(this->lastname, p.lastname));
	}


	person operator - (const person & p) const
	{
		return person(p.lastname, this->lastname);
	}


	person operator * (const person & p) const
	{
		if (*this == person() || p == person()) {
			return person();
		}

		return person(joinStrings(this->firstname, p.lastname), joinStrings(this->lastname, p.firstname));
	}


	std::string firstname, lastname;

};


std::ostream & operator << (std::ostream & os, const person & p)
{
	os << p.firstname << ", " << p.lastname;
	return os;
}


void testElementTypes(void)
{
	std::cout << "custom element types..." << std::flush;

	// addition

	SparseMatrix::SparseMatrix<person> a(4, 5);
	a.set(person("John", "Doe"), 2, 1);

	SparseMatrix::SparseMatrix<person> b(4, 5);
	b.set(person("Foo", "Bar"), 2, 1);

	SparseMatrix::SparseMatrix<person> sum = a.add(b);
	assertEquals<person>(person("John Foo", "Doe Bar"), sum.get(2, 1));


	// subtraction

	SparseMatrix::SparseMatrix<person> diff = a.subtract(b);
	assertEquals<person>(person("Bar", "Doe"), diff.get(2, 1));


	// matrix-matrix multiplication

	SparseMatrix::SparseMatrix<person> c(5, 3);
	c.set(person("Foo", "Bar"), 1, 2);

	SparseMatrix::SparseMatrix<person> product = a.multiply(c);

	for (int i = 0, rows = product.getRowCount(); i < rows; i++) {
		for (int j = 0, cols = product.getColumnCount(); j < cols; j++) {
			person value = product.get(i, j);

			if (i == 2 && j == 2) {
				assertEquals<person>(person("John Bar", "Doe Foo"), value);

			} else {
				assertEquals<person>(person(), value);
			}
		}
	}


	// vector-matrix multiplication

	std::vector<person> people;
	people.push_back(person("John", "Doe"));
	people.push_back(person("Foo", "Bar"));
	people.push_back(person("Willy", "Wonka"));
	people.push_back(person("Jon", "Snow"));
	people.push_back(person("Bridget", "Johnes"));

	std::vector<person> result = a.multiply(people);
	assertEquals<person>(person(), result[0]);
	assertEquals<person>(person(), result[1]);
	assertEquals<person>(person("John Bar", "Doe Foo"), result[2]);
	assertEquals<person>(person(), result[3]);

	std::cout << " OK" << std::endl;
}
