#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <exception>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <bitset>
#include <cstring>
#define HASH_SIZE 128

//#define TEST_BUILD
//#define DEBUG_PRINT

#ifdef TEST_BUILD
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#endif

#ifdef DEBUG_PRINT
#define D(x) x
#else
#define D(x)
#endif

//https://www.hackerrank.com/challenges/diagonal-difference


class Matrix {

public:

	Matrix(int const &row, int const &column) {
		_mat = new int[row*column];
		std::memset(_mat, 0, row*column);
		_rows = row;
		_columns = column;
	}

	Matrix(int const &row, int const &column, int const * const array, bool const &row_major = true) {
		_mat = new int[row*column];
		_rows = row;
		_columns = column;
		std::memcpy(_mat, array, row*column*sizeof(int));

		if (!row_major) {
			MatrixInplaceTranspose(_mat, row, column);
		}
	}

	void SetData(int const &row, int const& column, int const& value) {
		_mat[row*_columns + column] = value;
	}

	int GetData(int const &row, int const& column) {
		return _mat[row*_columns + column];
	}

	int GetRows() {
		return _rows;
	}

	int GetColumns() {
		return _columns;
	}

	int GetPrimaryDiaganolSum() {
		int limiter = _rows >= _columns ? _columns : _rows;
		int sum = 0;
		for (int i = 0; i < limiter; i++){
			sum += _mat[i*_columns + i];
		}
		return sum;
	}

	int GetSecondaryDiaganolSum() {
		int limiter = _rows >= _columns ? _columns-1 : _rows-1;
		int sum = 0;
		for (int i = limiter; i >= 0; i--) {
			sum += _mat[(limiter - i)*_columns + i];
		}
		return sum;
	}

	std::string ToString() {
		std::stringstream sstr;
		for (int y = 0; y < _rows; y++) {
			for (int x = 0; x < _columns; x++) {
				sstr << _mat[y*_columns + x] << " ";
			}
			sstr << std::endl;
		}
		return sstr.str();
	}

private:

	// http://www.geeksforgeeks.org/inplace-m-x-n-size-matrix-transpose/
	// Non-square matrix transpose of matrix of size r x c and base address A
	void MatrixInplaceTranspose(int *A, int r, int c)
	{
		int size = r*c - 1;
		int t; // holds element to be replaced, eventually becomes next element to move
		int next; // location of 't' to be moved
		int cycleBegin; // holds start of cycle
		int i; // iterator
		std::bitset<HASH_SIZE> b; // hash to mark moved elements

		b.reset();
		b[0] = b[size] = 1;
		i = 1; // Note that A[0] and A[size-1] won't move
		while (i < size)
		{
			cycleBegin = i;
			t = A[i];
			do
			{
				// Input matrix [r x c]
				// Output matrix 
				// i_new = (i*r)%(N-1)
				next = (i*r) % size;
				std::swap(A[next], t);
				b[i] = 1;
				i = next;
			} while (i != cycleBegin);

			// Get Next Move (what about querying random location?)
			for (i = 1; i < size && b[i]; i++)
				;
			std::cout << std::endl;
		}
	}

	int _rows;
	int _columns;
	int *_mat;
};

#ifdef TEST_BUILD

#define NUM_TESTS 1000

TEST_CASE("Add two BigInts", "[operator+]") {

	int digitsProcessed = 0;
	std::cout << "Generating " << NUM_TESTS << " test values for operator+ test:" << std::endl;

	std::vector<Matrix> matArray;
	int intArray[NUM_TESTS];
	int intArray2[NUM_TESTS];
	for (int i = 0; i < NUM_TESTS/2; i++) {
		std::cout << "Generating... " << int((float)i / (float)(NUM_TESTS / 2) * 100.0) << "%\r";
		std::cout.flush();
		int square = rand() % 50 + 1;
		int row = square;
		int column = square;
		int *tempArray = new int[row*column];
		int sum = 0;
		int sum2 = 0;
		for (int y = 0; y < row; y++) {
			for (int x = 0; x < column; x++) {
				int nextValue = rand() % NUM_TESTS;
				D(std::cout << nextValue << " ");
				tempArray[y*column + x] = nextValue;
				if (x == y) {
					sum += nextValue;
				}
				if (row >= column) {
					if (((column - 1) - x) == y) 
						sum2 += nextValue;
				}
				else {
					if (x == (row-1) - y)
						sum2 += nextValue;
				}
			}
			D(std::cout << std::endl);
		}
		D(std::cout << "Prime Diag = " << sum << std::endl);

		intArray[i] = sum;
		intArray2[i] = sum2;
		matArray.push_back(Matrix(row, column, tempArray));
	}
	for (int i = NUM_TESTS/2; i < NUM_TESTS; i++) {
		std::cout << "Generating... " << int((float)i / (float)NUM_TESTS * 100.0) << "%\r";
		std::cout.flush();
		int square = rand() % 50 + 1;
		int row = square;
		int column = square;
		int sum = 0;
		int sum2 = 0;
		Matrix mat = Matrix(row, column);

		for (int y = 0; y < row; y++) {
			for (int x = 0; x < column; x++) {
				int nextValue = rand() % NUM_TESTS;
				D(std::cout << nextValue << " ");
				mat.SetData(y, x, nextValue);
				if (x == y) {
					sum += nextValue;
				}
				if (row >= column) {
					if (((column - 1) - x) == y)
						sum2 += nextValue;
				}
				else {
					if (x == (row - 1) - y)
						sum2 += nextValue;
				}
				
			}
			D(std::cout << std::endl);
		}
		D(std::cout << "Prime Diag = " << sum << std::endl);

		intArray[i] = sum;
		intArray2[i] = sum2;
		matArray.push_back(mat);
	}

	SECTION("resizing smaller changes size but not capacity") {
		for (int i = 0; i < NUM_TESTS; i++) {
			D(std::cout << matArray.at(i).ToString());
			REQUIRE(intArray[i] == matArray.at(i).GetPrimaryDiaganolSum());
			REQUIRE(intArray2[i] == matArray.at(i).GetSecondaryDiaganolSum());
		}
	}
}

#endif


#ifndef CATCH_CONFIG_MAIN
int main (int argc, char *argv[]) {

	std::string inputValue;
	while (std::cin >> inputValue) {
		int matrixN = atoi(inputValue.c_str());
		Matrix matrix = Matrix(matrixN, matrixN);
		for (int y = 0; y < matrixN; y++) {
			for (int x = 0; x < matrixN; x++) {
				std::cin >> inputValue;
				matrix.SetData(y, x, std::atoi(inputValue.c_str()));
			}
		}
		int diag_diff = abs(matrix.GetPrimaryDiaganolSum() - matrix.GetSecondaryDiaganolSum());

		std::cout << diag_diff << std::endl;
	}

	return 0;
}
#endif
