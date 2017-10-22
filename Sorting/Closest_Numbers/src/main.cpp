#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
#include <sstream>
#include <exception>
#include <stdlib.h>
#include <map>
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
This class will sort a list of counted strings in the form of:

n string1
n string2
n string3
n string4

where n is any positive integer which represent the
position the string should be sorted to. It then
replaces the first half of passed strings to a "-".

This class sorts the array by storing the values in a organized fashion
so they are easily read later. The sorting takes O(n).
*/
class ClosestNumbersArray {

public:

	/*
	Default Constructor
	*/
	ClosestNumbersArray(int const &length, int const * const array) {
		_minDiff = 0;
		_array.assign(array, array + length);
		std::sort(_array.begin(), _array.end());
		for (int i = 0; i < length; i++) {
			if (i > 0) {
				if (i == 1) {
					_minDiff = std::abs(_array.at(1) - _array.at(0));
					_minDiffPairs.push_back(0);
				}
				else if (_minDiff == std::abs(_array.at(i) - _array.at(i-1))){
					_minDiffPairs.push_back(i - 1);
				}
				else if (_minDiff > std::abs(_array.at(i) - _array.at(i - 1))) {
					_minDiffPairs.clear();
					_minDiff = std::abs(_array.at(i) - _array.at(i - 1));
					_minDiffPairs.push_back(i - 1);
				}
			}
		}
	}

	/*
	Now we can create a string by going through the n elements in our organized arrays.
	*/
	std::string ToString() {
		std::stringstream sstr;
		for (int i = 0; i < _minDiffPairs.size(); i++) {
			sstr << _array.at(_minDiffPairs.at(i)) << " " << _array.at(_minDiffPairs.at(i) + 1);
			if (i != _minDiffPairs.size() - 1) {
				sstr << " ";
			}
		}
		return sstr.str();
	}

private:
	int _minDiff;
	std::vector<int> _array;
	std::vector<int> _minDiffPairs;
	
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
#define NUM_TESTS 100

TEST_CASE("find the closest number"){

	static const std::vector<int> testArray1 = {
		-20, 
		-3916237, 
		-357920,
		-3620601, 
		7374819,
		-7330761,
		30,
		6246457,
		-6461594,
		266854 
	};

	ClosestNumbersArray answer1 = ClosestNumbersArray(testArray1.size(), &testArray1.at(0));
	REQUIRE(std::string("-20 30").compare(answer1.ToString()) == 0);

	static const std::vector<int> testArray2 = {
		-20, 
		-3916237, 
		-357920,
		-3620601, 
		7374819,
		-7330761,
		30,
		6246457,
		-6461594,
		266854,
		-520,
		-470
	};

	ClosestNumbersArray answer2 = ClosestNumbersArray(testArray2.size(), &testArray2.at(0));
	REQUIRE(std::string("-520 -470 -20 30").compare(answer2.ToString()) == 0);

	static const std::vector<int> testArray3 = {
		5, 4, 3, 2
	};

	ClosestNumbersArray answer3 = ClosestNumbersArray(testArray3.size(), &testArray3.at(0));
	REQUIRE(std::string("2 3 3 4 4 5").compare(answer3.ToString()) == 0);

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

		int size = std::atoi(inputValue.c_str());

		std::vector<int> tempArray;
		for (int i = 0; i < size; i++) {
			std::cin >> inputValue;
			tempArray.push_back(std::atoi(inputValue.c_str()));
		}

		ClosestNumbersArray answer = ClosestNumbersArray(tempArray.size(), &tempArray.at(0));
		
		std::cout << answer.ToString() << std::endl;
		
	}

	return 0;
}
#endif
