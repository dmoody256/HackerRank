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
	ClosestNumbersArray(int const &length, double const * const array) {
		_minDiff = 0;
		_array.assign(array, array + length);
		std::sort(_array.begin(), _array.end());
		for (int i = 0; i < length; i++) {
			if (i > 0) {
				if (i == 1) {
					_minDiff = std::fabs(_array.at(1) - _array.at(0));
					_minDiffPairs.push_back(0);
				}
				else if (_minDiff == std::fabs(_array.at(i) - _array.at(i-1))){
					_minDiffPairs.push_back(i - 1);
				}
				else if (_minDiff > std::fabs(_array.at(i) - _array.at(i - 1))) {
					_minDiffPairs.clear();
					_minDiff = std::fabs(_array.at(i) - _array.at(i - 1));
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
	double _minDiff;
	std::vector<double> _array;
	std::vector<double> _minDiffPairs;
	
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

		std::vector<double> tempArray;
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
