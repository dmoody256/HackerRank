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
class SortedArray {

public:

	/*
	Default Constructor
	*/
	SortedArray() {
		_size = 0;
	}

	/*
	As we push items we will sort them by storing them in an organized way
	*/
	void PushValue(int const &position, std::string const &string) {
		
		ListItem item;
		item.originalPosition = _size;
		item.string = string;
		_array[position].push_back(item);
		_size++;
	}

	/*
	Now we can create a string by going through the n elements in our organized arrays.
	*/
	std::string ToString() {
		std::stringstream sstr;
		for (std::map < int, std::vector < ListItem > >::iterator it = _array.begin(); it != _array.end(); it++) {
			for (int i = 0; i < it->second.size(); i++) {
				if ((float)it->second.at(i).originalPosition / (float)_size >= .5) {
					sstr << it->second.at(i).string;
				}
				else {
					sstr << "-";
				}

				sstr << " ";
			}
			
		}
		std::string returnString = sstr.str();
		return returnString.substr(0, returnString.size() - 1);
	}

private:

	// convience structore for keeping track of the original
	// position for when we want convert the first set of values
	// to dashes
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
#define NUM_TESTS 100

TEST_CASE("Testing adding values to the sorted array") {

	// we may be generating a lot of tests, so let the user now this is taking place
	D(std::cout << "Generating " << NUM_TESTS << " tests:" << std::endl);
	for (int n = 0; n < NUM_TESTS; n++) {
		D(std::cout << "Testing... " << int((float)n / (float)NUM_TESTS * 100.0) << "%\r");
		D(std::cout.flush());

		// We can create random tests very easy without recreating a sorting algorothm
		// so we will use random value to stress test the class. Our hardcoded tests 
		// will make sure that the sort algorithm is returning the correct results.
		SortedArray testArray;
		std::stringstream answer;
		std::vector<int> positionCounter;
		int randTestSize = rand() % 10000;
		if (randTestSize % 2 == 1)
		{
			randTestSize--;
		}
		for (int i = 0; i < randTestSize; i++) {
			std::stringstream posString;
			posString << i;
			testArray.PushValue(i, posString.str());
			if ((float)i / (float)randTestSize >= .5) {
				answer << i << " ";
			}
			else {
				answer << "- ";
			}
		}
	
		std::string answerString = answer.str();
		answerString = answerString.substr(0, answerString.size() - 1);
		std::string testString = testArray.ToString();
		REQUIRE(answerString == testString);
	}

	static const int hardCode1Positions[]		= {      0,    0,   1,      2};
	static const std::string hardCode1Strings[] = { "This", "is", "a", "test"};
	SortedArray testHardCode1Array;
	for (int i = 0; i < 4; i++) {
		testHardCode1Array.PushValue(hardCode1Positions[i], hardCode1Strings[i]);
	}
	REQUIRE(testHardCode1Array.ToString() == "- - a test");

	static const int hardCode2Positions[] =		  {      4,    1,   1,      2,      8,         4,        6,    2,      5,       4,      1,   0 ,     8,       2};
	static const std::string hardCode2Strings[] = { "This", "is", "a", "test", "Some", "Strings", "should", "be", "gone", "which", "ones", "do", "you", "think"};
	SortedArray testHardCode2Array;
	for (int i = 0; i < 14; i++) {
		testHardCode2Array.PushValue(hardCode2Positions[i], hardCode2Strings[i]);
	}
	REQUIRE(testHardCode2Array.ToString() == "do - - ones - be think - - which gone - - you");

	SortedArray testHardCode3Array;
	REQUIRE(testHardCode3Array.ToString() == "");

	static const int hardCode4Positions[] = { 4,    1 };
	static const std::string hardCode4Strings[] = { "This", "is" };
	SortedArray testHardCode4Array;
	for (int i = 0; i < 2; i++) {
		testHardCode4Array.PushValue(hardCode4Positions[i], hardCode4Strings[i]);
	}
	REQUIRE(testHardCode4Array.ToString() == "is -");

	static const int hardCode5Positions[] = { 1,    1,   1,      1,     1,         1,        1,    1,     1,       1,      1,   1 ,     1,       1 };
	static const std::string hardCode5Strings[] = { "This", "is", "a", "test", "Some", "Strings", "should", "be", "gone", "which", "ones", "do", "you", "think" };
	SortedArray testHardCode5Array;
	for (int i = 0; i < 14; i++) {
		testHardCode5Array.PushValue(hardCode5Positions[i], hardCode5Strings[i]);
	}
	REQUIRE(testHardCode5Array.ToString() == "- - - - - - - be gone which ones do you think");

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
