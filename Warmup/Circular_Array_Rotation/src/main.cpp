#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
#include <sstream>
#include <exception>
#include <stdlib.h>
#include <stdexcept>

//#define UNIT_TEST_BUILD

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

/*
Wrapper for a std::vector array that keeps track of right rotations 
(moving all elements to the right and then the last element to the front)
*/
class CircularArray {

public:

	/*
	Constructor takes a size an existing array to build from. It will copy
	the array to its own internal std::vector
	*/
	CircularArray(int const &size, int const * const inputArray) {
		_rotations = 0;
		for (int i = 0; i < size; i++) {
			_array.push_back(inputArray[i]);
		}
	}

	/*
	Performs a Right Rotation on the array (moving all elements to the right 
	and then the last element to the front). This class will keep a index for
	how many rotations have been done instead of actually moving any memory
	*/
	void RotateRight(int const &rotations) {
		_rotations += rotations;
		if (_rotations > _array.size()) {
			int overRotations = _rotations / _array.size();
			_rotations = _rotations - (overRotations*_array.size());
		}
	}

	/*
	Calculates the position in the array based off the number of rotations applied
	and gets the value at that position (0 is considered first position)
	*/
	int GetValue(int const &position) {
		int calculatePostion = position - _rotations;
		if (calculatePostion < 0) {
			calculatePostion += _array.size();
		}
		return _array.at(calculatePostion);
	}

private:
	int _rotations;
	std::vector<int> _array;

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
#define NUM_TESTS 1000



TEST_CASE("Testing different generated arrays", "[CircularArray]") {

	// setup the varibales for storing the generated test data
	std::vector<CircularArray> circularArrays;
	int intArray[NUM_TESTS];

	// we may be generating a lot of tests, so let the user now this is taking place
	D(std::cout << "Generating " << NUM_TESTS << " test values for operator+ test:" << std::endl);
	for (int i = 0; i < NUM_TESTS; i++) {
		D(std::cout << "Generating... " << int((float)i / (float)(NUM_TESTS) * 100.0) << "%\r");
		D(std::cout.flush());

		int tempArray[NUM_TESTS];
		int numRotations = (rand() & NUM_TESTS -1) + 1;
		for (int j = 0; j < NUM_TESTS; j++) {
			if (j == NUM_TESTS - numRotations) {
				tempArray[j] = 1;
			}
			else {
				tempArray[j] = 0;
			}
		}
		circularArrays.push_back(CircularArray(NUM_TESTS, tempArray));
		intArray[i] = numRotations;
	}

	// hard coded test data
	static const int intHardCode1[] = {
		0,1,2,3,4,5,6,7
	};
	static const int intHardCode2[] = {
		5,4,3,2,1
	};
	static const int intHardCode3[] = {
		5
	};

	// perform check the test results
	SECTION("Testing CountedArrays") {
		for (int i = 0; i < NUM_TESTS; i++) {
			circularArrays.at(i).RotateRight(intArray[i]);
			REQUIRE(1 == circularArrays.at(i).GetValue(0));
		}

		CircularArray testArray1 = CircularArray(8, intHardCode1);
		testArray1.RotateRight(2);
		REQUIRE(5 == testArray1.GetValue(7));
		REQUIRE(3 == testArray1.GetValue(5));
		REQUIRE(6 == testArray1.GetValue(0));

		testArray1.RotateRight(2);
		REQUIRE(3 == testArray1.GetValue(7));
		REQUIRE(1 == testArray1.GetValue(5));
		REQUIRE(4 == testArray1.GetValue(0));
		testArray1.RotateRight(8);
		REQUIRE(3 == testArray1.GetValue(7));
		REQUIRE(1 == testArray1.GetValue(5));
		REQUIRE(4 == testArray1.GetValue(0));

		CircularArray testArray2 = CircularArray(5, intHardCode2);
		testArray2.RotateRight(2);
		REQUIRE(4 == testArray2.GetValue(3));
		REQUIRE(2 == testArray2.GetValue(0));

		testArray2.RotateRight(2);
		REQUIRE(1 == testArray2.GetValue(3));
		REQUIRE(4 == testArray2.GetValue(0));
		testArray2.RotateRight(10);
		REQUIRE(1 == testArray2.GetValue(3));
		REQUIRE(4 == testArray2.GetValue(0));

		CircularArray testArray3 = CircularArray(1, intHardCode3);
		testArray3.RotateRight(2);
		REQUIRE(5 == testArray3.GetValue(0));
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

		// read in the size of the next staircase
		int size = atoi(inputValue.c_str());
		std::cin >> inputValue;
		int rotations = atoi(inputValue.c_str());
		std::cin >> inputValue;
		int queries = atoi(inputValue.c_str());

		std::vector<int> tempArray;
		for (int i = 0; i < size; i++) {
			std::cin >> inputValue;
			tempArray.push_back(atoi(inputValue.c_str()));
		}

		std::vector<int> queryArray;
		for (int i = 0; i < queries; i++) {
			std::cin >> inputValue;
			queryArray.push_back(atoi(inputValue.c_str()));
		}

		CircularArray circArray = CircularArray(tempArray.size(), &tempArray.at(0));
		circArray.RotateRight(rotations);

		for (int i = 0; i < queries; i++) {
			std::cout << circArray.GetValue(queryArray.at(i)) << std::endl;
		}

	}

	return 0;
}
#endif
