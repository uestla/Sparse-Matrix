# SparseMatrix Makefile

all: build

build:
	g++ -Wall -pedantic tests/run.cpp src/SparseMatrix/SparseMatrix.cpp -o tests/SparseMatrix-tests

test:
	./tests/SparseMatrix-tests.exe
