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
#include <string.h> // memcpy

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
//https://www.hackerrank.com/challenges/insertion-sort


//     _____    ____    _____    ______
//    / ____|  / __ \  |  __ \  |  ____|
//   | |      | |  | | | |  | | | |__
//   | |      | |  | | | |  | | |  __|
//   | |____  | |__| | | |__| | | |____
//    \_____|  \____/  |_____/  |______|
//
// letters generated at http://patorjk.com/software/taag

#ifdef UNIT_TEST_BUILD
double ShiftsRequired(int const size, const int* const list) {
	int* array = new int[size];
	double shifts = 0;
	memcpy(array, list, size * sizeof(int));
	for (int i = 1; i < size; i++) {
		int temp = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > temp) {
			array[j + 1] = array[j];
			j = j - 1;
			shifts++;
		}
		array[j + 1] = temp;
	}
	delete[] array;
	return shifts;
};
#endif

class InsertionSort {

public:

	double ShiftsRequired(int const size, const int* const list){
		int* sortedArray = new int[size];
		int* unsortedArray = new int[size];
		memcpy(sortedArray, list, size * sizeof(int));
		memcpy(unsortedArray, list, size * sizeof(int));
		numShifts = 0;
		
		MergeSort(unsortedArray, 0, size, sortedArray);

		delete[] sortedArray;
		delete[] unsortedArray;
		return numShifts;
	};
private:

	double numShifts;

	void MergeSort(int* unsortedArray, int const begin, int const end, int* sortedArray) {

		if (end - begin < 2) {
			return;
		}

		int mid = (end + begin) / 2;

		MergeSort(sortedArray, begin, mid, unsortedArray);
		MergeSort(sortedArray, mid, end, unsortedArray);
		merge(unsortedArray, begin, mid, end, sortedArray);

	}

	void merge(int* unsortedArray, int const begin, int mid, int const end, int* sortedArray) {
		int i = begin;
		int j = mid;
		for (int k = begin; k < end; k++) {
			if (i < mid && (j >= end || unsortedArray[i] <= unsortedArray[j])) {
				if (i > k)
					numShifts += (i - k);
				sortedArray[k] = unsortedArray[i];
				i++;
				
			}
			else {
				if(j > k)
					numShifts += (j-k);
				sortedArray[k] = unsortedArray[j];
				j++;
				
			}
		}
	}

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
#define NUM_TESTS 200

TEST_CASE("Testing adding values to the sorted array") {

	// we may be generating a lot of tests, so let the user now this is taking place
	std::cout << "Generating " << NUM_TESTS << " tests:" << std::endl;
	for (int n = 0; n < NUM_TESTS; n++) {
		std::cout << "Testing... " << int((float)n / (float)NUM_TESTS * 100.0) << "%\r";
		std::cout.flush();

		// We can create random tests very easy without recreating a sorting algorothm
		// so we will use random value to stress test the class. Our hardcoded tests 
		// will make sure that the sort algorithm is returning the correct results.
		InsertionSort testClass;
		std::vector<int> testArray;
		int randTestSize = rand() % 1000000;
		for (int i = 0; i < randTestSize; i++) {
			testArray.push_back(rand() % 100000000);
		}

		REQUIRE(ShiftsRequired(randTestSize, &testArray.at(0)) == testClass.ShiftsRequired(randTestSize, &testArray.at(0)));
	}

	InsertionSort testArray;
	static const int staticArray1[] = { 1,2,3,4,5 };
	static const int staticArray1Shifts = 0;
	REQUIRE(staticArray1Shifts == testArray.ShiftsRequired(5, staticArray1));

	static const int staticArray2[] = { 5,2,3,4,1 };
	static const int staticArray2Shifts = 7;
	REQUIRE(staticArray2Shifts == testArray.ShiftsRequired(5, staticArray2));

	static const int staticArray3[] = { 2,1,3,1,2 };
	static const int staticArray3Shifts = 4;
	REQUIRE(staticArray3Shifts == testArray.ShiftsRequired(5, staticArray3));

	static const int staticArray4[] = { 1 };
	static const int staticArray4Shifts = 0;
	REQUIRE(staticArray4Shifts == testArray.ShiftsRequired(1, staticArray4));

	static const int staticArray5[] = { 4,7,2,8,5,4,7,2,5,2,7 };
//2	//2, 4, 7, 8, 5, 4, 7, 2, 5, 2, 7
//2	//2, 4, 5, 7, 8, 4, 7, 2, 5, 2, 7
//3	//2, 4, 4, 5, 7, 8, 7, 2, 5, 2, 7
//1	//2, 4, 4, 5, 7, 7, 8, 2, 5, 2, 7
//6	//2, 2, 4, 4, 5, 7, 7, 8, 5, 2, 7
//3	//2, 2, 4, 4, 5, 5, 7, 7, 8, 2, 7
//7 //2, 2, 2, 4, 4, 5, 5, 7, 7, 8, 7
//1	//2, 2, 2, 4, 4, 5, 5, 7, 7, 7, 8
	static const int staticArray5Shifts = 25;
	REQUIRE(staticArray5Shifts == testArray.ShiftsRequired(11, staticArray5));
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

		int loops = std::atoi(inputValue.c_str());
		for (int i = 0; i < loops; i++) {
			int size;
			std::cin >> size;
			std::vector<int> list;
			for (int j = 0; j < size; j++) {
				int value;
				std::cin >> value;
				list.push_back(value);
			}
			InsertionSort nextArray;
			std::cout <<  nextArray.ShiftsRequired(size, &list.at(0)) << std::endl;
		}
	}

	return 0;
}
#endif
