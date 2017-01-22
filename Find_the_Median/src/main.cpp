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
#include <functional>

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
//https://www.hackerrank.com/challenges/find-the-median


//     _____    ____    _____    ______
//    / ____|  / __ \  |  __ \  |  ____|
//   | |      | |  | | | |  | | | |__
//   | |      | |  | | | |  | | |  __|
//   | |____  | |__| | | |__| | | |____
//    \_____|  \____/  |_____/  |______|
//
// letters generated at http://patorjk.com/software/taag


class MedianArray {

public:

	int FindMedian(int const size, const int* const list) {
		int* array = new int[size];
		memcpy(array, list, size);
		int k = size / 2;
		int median = select(array, 0, size - 1, k);
		delete[] array;
		return median;
	}

private:

	void swap(int* list, int i, int j) {
		int temp = list[i];
		list[i] = list[j];
		list[j] = temp;
	};

	int partition(int* list, int leftIndex, int rightIndex, int pivotIndex) {

		int pivotValue = list[pivotIndex];
		swap(list, pivotIndex, rightIndex);
		int storeIndex = leftIndex;
		for (int i = leftIndex; i < rightIndex - 1; i++) {
			if (list[i] < pivotValue) {
				swap(list, storeIndex, i);
				storeIndex++;
			}
		}
		swap(list, rightIndex, storeIndex);
		return storeIndex;
	};

	int select(int* list, int leftIndex, int rightIndex, int k) {

		if (leftIndex == rightIndex)
			return list[leftIndex];
		int pivotIndex = leftIndex + floor(rand() % (rightIndex - leftIndex + 1));
		pivotIndex = partition(list, leftIndex, rightIndex, pivotIndex);
		if (k == pivotIndex) {
			return list[k];
		}
		else if (k < pivotIndex) {
			return select(list, leftIndex, pivotIndex - 1, k);
		}
		else {
			return select(list, pivotIndex + 1, rightIndex, k);
		}
	};
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

TEST_CASE("Testing adding values to the sorted array") {

	// we may be generating a lot of tests, so let the user now this is taking place
	std::cout << "Generating " << NUM_TESTS << " tests:" << std::endl;
	for (int n = 0; n < NUM_TESTS; n++) {
		std::cout << "Testing... " << int((float)n / (float)NUM_TESTS * 100.0) << "%\r";
		std::cout.flush();

		// We can create random tests very easy without recreating a sorting algorothm
		// so we will use random value to stress test the class. Our hardcoded tests 
		// will make sure that the sort algorithm is returning the correct results.
		MedianArray testArray;
		
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

		int size = std::atoi(inputValue.c_str());
		SortedArray nextArray;
		for (int i = 0; i < size; i++) {
			std::cin >> inputValue;
			int position = std::atoi(inputValue.c_str());
			std::cin >> inputValue;
			std::string inputString =inputValue;
			nextArray.PushValue(position, inputString);
		}
		std::cout << nextArray.ToString() << std::endl;
		
	}

	return 0;
}
#endif
