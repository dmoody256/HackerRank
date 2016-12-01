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

class SortedArray {

public:

	SortedArray() {
		_size = 0;
	}

	void PushValue(int const &position, std::string const &string) {
		
		ListItem item;
		item.originalPosition = _size;
		item.string = string;
		_array[position].push_back(item);
		_size++;
	}

private:

	struct ListItem {
		int originalPosition;
		std::string string;
	} typedef ListItem;
	int _size;
	std::map< int, std::vector< ListItem > > _array;

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

TEST_CASE("Testing adding values to the sorted array") {

	SortedArray testArray;
	
	int randTestSize = rand() % 100;
	for (int i = 0; i < randTestSize; i++) {
		int position = rand() % 26;
		int stringsize = rand() % 10;
		std::string nextString;
		for (int j = 0; j < stringsize; j++) {
			nextString.append(1, position + 65);
		}
		testArray.PushValue(position, nextString);
	}

	int test = 5;

	

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

		std::cout << inputValue << std::endl;
		

	}

	return 0;
}
#endif
