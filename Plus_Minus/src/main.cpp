#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <exception>
#include <stdlib.h>
#include <stdexcept>

#define UNIT_TEST_BUILD

// setup Catch unit testing if this is a test build
// it will create a new main for us
#ifdef UNIT_TEST_BUILD
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#endif

// Debug print is useful for quickly debugging
// output for things that may happen over time
#ifdef DEBUG_PRINT
#define D(x) x
#else
#define D(x)
#endif

// This challenge can be found here
//https://www.hackerrank.com/challenges/plus-minus


//     _____    ____    _____    ______
//    / ____|  / __ \  |  __ \  |  ____|
//   | |      | |  | | | |  | | | |__
//   | |      | |  | | | |  | | |  __|
//   | |____  | |__| | | |__| | | |____
//    \_____|  \____/  |_____/  |______|
//
// letters generated at http://patorjk.com/software/taag

class CountedArray {

public:

	CountedArray() {
		_positiveValues = 0;
		_negativeValues = 0;
		_zeroValues = 0;
	}

	CountedArray(int const &size, int const * const array) {
		_positiveValues = 0;
		_negativeValues = 0;
		_zeroValues = 0;
		for (int i = 0; i < size; i++) {
			if (array[i] > 0) {
				_positiveValues++;
			}
			else if (array[i] < 0) {
				_negativeValues++;
			}
			else {
				_zeroValues++;
			}
			_array.push_back(array[i]);
		}
	}

	double GetPositiveRatio() {
		if (_array.size() > 0)
			return  (double)_positiveValues / (double)_array.size();
		else
			return 0;
	}

	double GetNegativeRatio() {
		if (_array.size() > 0)
			return  (double)_negativeValues / (double)_array.size();
		else
			return 0;
	}

	double GetZeroRatio() {
		if (_array.size() > 0)
			return  (double)_zeroValues / (double)_array.size();
		else
			return 0;
	}

	void PushValue(int const &value) {
		if (value > 0) {
			_positiveValues++;
		}
		else if (value < 0) {
			_negativeValues++;
		}
		else {
			_zeroValues++;
		}
		_array.push_back(value);
	}

	std::string ToString() {
		std::stringstream sstr;
		for (int i = 0; i < _array.size(); i++) {
			sstr << _array.at(i) << " ";
		}
		return sstr.str();
	}

private:

	std::vector<int> _array;
	int _positiveValues;
	int _negativeValues;
	int _zeroValues;
};

#ifdef UNIT_TEST_BUILD
//    _______   ______    _____   _______
//   |__   __| |  ____|  / ____| |__   __|
//      | |    | |__    | (___      | |
//      | |    |  __|    \___ \     | |
//      | |    | |____   ____) |    | |
//      |_|    |______| |_____/     |_|
//
// letters generated at http://patorjk.com/software/taag

// control the number of random generated tests
#define NUM_TESTS 10000

TEST_CASE("Testing different generated arrays", "[CountedArray]") {

	// setup the varibale we use for the addition tests
	std::vector<CountedArray> intArray;
	double positiveResults[NUM_TESTS];
	double negativeResults[NUM_TESTS];
	double zeroResults[NUM_TESTS];

	// we may be generating a lot of tests, so let the user now this is taking place
	std::cout << "Generating " << NUM_TESTS << " test values for operator+ test:" << std::endl;
	for (int i = 0; i < NUM_TESTS/2; i++) {
		std::cout << "Generating... " << int((float)i / (float)(NUM_TESTS) * 100.0) << "%\r";
		std::cout.flush();

		int size = (rand() % NUM_TESTS) +1;
		int posCount = 0;
		int negCount = 0;
		int zeroCount = 0;
		CountedArray countedArray = CountedArray();
		for (int j = 0; j < size; j++) {
			int number = rand() % (NUM_TESTS / 10);
			if (number == 0) {
				zeroCount++;
			}
			else if (rand() % 2 == 0) {
				number *= -1;
				negCount++;
			}
			else {
				posCount++;
			}
			countedArray.PushValue(number);
		}
		
		// create a random bigint and will see if we the same exact string
		// back out
		positiveResults[i] = (double)posCount / (double)(size);
		negativeResults[i] = (double)negCount / (double)(size);
		zeroResults[i] = (double)zeroCount / (double)(size);
		intArray.push_back(countedArray);
	}
	for (int i = NUM_TESTS / 2; i < NUM_TESTS; i++) {
		std::cout << "Generating... " << int((float)i / (float)NUM_TESTS * 100.0) << "%\r";
		std::cout.flush();
		
		int posCount = 0;
		int negCount = 0;
		int zeroCount = 0;
		int tempArray[NUM_TESTS / 2];
		for (int j = 0; j < NUM_TESTS / 10; j++) {
			int number = rand() % 2;
			if (number == 0) {
				zeroCount++;
			}
			else if (rand() % 2 == 0) {
				number *= -1;
				negCount++;
			}
			else {
				posCount++;
			}
			tempArray[j] = number;
		}

		// create a random bigint and will see if we the same exact string
		// back out
		positiveResults[i] = (double)posCount / (double)(NUM_TESTS / 10);
		negativeResults[i] = (double)negCount / (double)(NUM_TESTS / 10);
		zeroResults[i] = (double)zeroCount / (double)(NUM_TESTS / 10);
		intArray.push_back(CountedArray(NUM_TESTS / 10, tempArray));
	}

	static const int intHardCode1[] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //20
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //40
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  //60
	};
	static const int intHardCode2[] = {
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, //20
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1     //39
	};
	static const int intHardCode3[] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //20
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //40
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   //59
	};
	static const int intHardCode4[] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //20
		1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //40
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0    //59
	};
	static const int intHardCode5[] = {
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //20
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //40
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 //60
	};

	// perform the to string tests to make sure our BigInt class is not 
	// destroying the data
	SECTION("Testing CountedArrays") {
		for (int i = 0; i < NUM_TESTS; i++) {
			REQUIRE(positiveResults[i] == intArray.at(i).GetPositiveRatio());
			REQUIRE(negativeResults[i] == intArray.at(i).GetNegativeRatio());
			REQUIRE(zeroResults[i] == intArray.at(i).GetZeroRatio());
		}

		CountedArray hardCodeTest1 = CountedArray(60, intHardCode1);
		REQUIRE(0 == hardCodeTest1.GetPositiveRatio());
		REQUIRE(0 == hardCodeTest1.GetNegativeRatio());
		REQUIRE(1 == hardCodeTest1.GetZeroRatio());

		CountedArray hardCodeTest2 = CountedArray(39, intHardCode2);
		REQUIRE(0 == hardCodeTest2.GetPositiveRatio());
		REQUIRE(1 == hardCodeTest2.GetNegativeRatio());
		REQUIRE(0 == hardCodeTest2.GetZeroRatio());

		CountedArray hardCodeTest3 = CountedArray(59, intHardCode3);
		REQUIRE(1 == hardCodeTest3.GetPositiveRatio());
		REQUIRE(0 == hardCodeTest3.GetNegativeRatio());
		REQUIRE(0 == hardCodeTest3.GetZeroRatio());

		CountedArray hardCodeTest4 = CountedArray(59, intHardCode4);
		REQUIRE((double)26 / (double)59 == hardCodeTest4.GetPositiveRatio());
		REQUIRE(0 == hardCodeTest4.GetNegativeRatio());
		REQUIRE((double)33 / (double)59 == hardCodeTest4.GetZeroRatio());

		CountedArray hardCodeTest5 = CountedArray(60, intHardCode5);
		REQUIRE((double)1 / (double)60 == hardCodeTest5.GetPositiveRatio());
		REQUIRE((double)20 / (double)60 == hardCodeTest5.GetNegativeRatio());
		REQUIRE((double)39 / (double)60 == hardCodeTest5.GetZeroRatio());
	}
}


#endif



#ifndef CATCH_CONFIG_MAIN
//    __  __              _____   _   _
//   |  \/  |     /\     |_   _| | \ | |
//   | \  / |    /  \      | |   |  \| |
//   | |\/| |   / /\ \     | |   | . ` |
//   | |  | |  / ____ \   _| |_  | |\  |
//   |_|  |_| /_/    \_\ |_____| |_| \_|
//
// letters generated at http://patorjk.com/software/taag

int main (int argc, char *argv[]) {

	std::string inputValue;
	while (std::cin >> inputValue) {

		// we expect the first value to be the number of
		// operons to read in on the next line
		int operons = atoi(inputValue.c_str());

		for (int i = 0; i < operons; i++) {
			// read in each next number and
			// add it to the result
			std::cin >> inputValue;
		}

		// print the final result
		std::cout << inputValue << std::endl;
	}

	return 0;
}
#endif
