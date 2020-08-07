# SparseMatrix Makefile

all: test

build:
	g++ -Wall -pedantic tests/run.cpp -o tests/SparseMatrix-tests

test: build
	./tests/SparseMatrix-tests.exe

debug:
	g++ -Wall -pedantic -g tests/run.cpp -o tests/SparseMatrix-tests-gdb
	gdb tests/SparseMatrix-tests-gdb.exe
