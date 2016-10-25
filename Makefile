# SparseMatrix Makefile

all: test

test:
	g++ -Wall -pedantic tests/run.cpp src/**/*.cpp -o tests/SparseMatrix-tests
	./tests/SparseMatrix-tests.exe

debug:
	g++ -Wall -pedantic -g tests/run.cpp src/**/*.cpp -o tests/SparseMatrix-tests-gdb
	gdb tests/SparseMatrix-tests-gdb.exe
