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

class Staircase {

public:

	Staircase() {
		_size = 0;
	}

	Staircase(int const &size) {
		_size = size;

		std::stringstream sstr;
		for (int line = 1; line <= size; line++) {
			for (int spaces = size - line; spaces > 0; spaces--)
				sstr << " ";

			for (int symbols = 0; symbols < line; symbols++)
				sstr << "#";

			sstr << std::endl;
		}
		_staircase = sstr.str();
	}

	std::string ToString() {
		return _staircase;
	}

private:

	int _size;
	std::string _staircase;
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

TEST_CASE("This test will create and add big ints from generated and hardcoded values", "[BigInt]") {

	// setup the varibale we use for the addition tests
	int testCountArray[NUM_TESTS];
	int realCountArray[NUM_TESTS];

	std::cout << "Generating " << NUM_TESTS << " test values for operator+ test:" << std::endl;
	for (int i = 0; i < NUM_TESTS; i++) {
		std::cout << "Generating... " << int((float)i / (float)NUM_TESTS * 100.0) << "%\r";
		std::cout.flush();

		// create a random bigint and will see if we the same exact string
		// back out
		Staircase testStaircase = Staircase(i);
		std::string testString = testStaircase.ToString();
		testCountArray[i] = std::count(testString.begin(), testString.end(), '#');
		realCountArray[i] = (i * (i + 1)) / 2;
	}

	std::string StaircaseTest2;
	StaircaseTest2.append("    #\n");
	StaircaseTest2.append("   ##\n");
	StaircaseTest2.append("  ###\n");
	StaircaseTest2.append(" ####\n");
	StaircaseTest2.append("#####\n");

	std::string StaircaseTest1;
	StaircaseTest1.append("         #\n");
	StaircaseTest1.append("        ##\n");
	StaircaseTest1.append("       ###\n");
	StaircaseTest1.append("      ####\n");
	StaircaseTest1.append("     #####\n");
	StaircaseTest1.append("    ######\n");
	StaircaseTest1.append("   #######\n");
	StaircaseTest1.append("  ########\n");
	StaircaseTest1.append(" #########\n");
	StaircaseTest1.append("##########\n");

	std::string StaircaseTest3;
	StaircaseTest3.append("                                       #\n");
	StaircaseTest3.append("                                      ##\n");
	StaircaseTest3.append("                                     ###\n");
	StaircaseTest3.append("                                    ####\n");
	StaircaseTest3.append("                                   #####\n");
	StaircaseTest3.append("                                  ######\n");
	StaircaseTest3.append("                                 #######\n");
	StaircaseTest3.append("                                ########\n");
	StaircaseTest3.append("                               #########\n");
	StaircaseTest3.append("                              ##########\n");
	StaircaseTest3.append("                             ###########\n");
	StaircaseTest3.append("                            ############\n");
	StaircaseTest3.append("                           #############\n");
	StaircaseTest3.append("                          ##############\n");
	StaircaseTest3.append("                         ###############\n");
	StaircaseTest3.append("                        ################\n");
	StaircaseTest3.append("                       #################\n");
	StaircaseTest3.append("                      ##################\n");
	StaircaseTest3.append("                     ###################\n");
	StaircaseTest3.append("                    ####################\n");
	StaircaseTest3.append("                   #####################\n");
	StaircaseTest3.append("                  ######################\n");
	StaircaseTest3.append("                 #######################\n");
	StaircaseTest3.append("                ########################\n");
	StaircaseTest3.append("               #########################\n");
	StaircaseTest3.append("              ##########################\n");
	StaircaseTest3.append("             ###########################\n");
	StaircaseTest3.append("            ############################\n");
	StaircaseTest3.append("           #############################\n");
	StaircaseTest3.append("          ##############################\n");
	StaircaseTest3.append("         ###############################\n");
	StaircaseTest3.append("        ################################\n");
	StaircaseTest3.append("       #################################\n");
	StaircaseTest3.append("      ##################################\n");
	StaircaseTest3.append("     ###################################\n");
	StaircaseTest3.append("    ####################################\n");
	StaircaseTest3.append("   #####################################\n");
	StaircaseTest3.append("  ######################################\n");
	StaircaseTest3.append(" #######################################\n");
	StaircaseTest3.append("########################################\n");

	// perform the to string tests to make sure our BigInt class is not
	// destroying the data
	SECTION("Performing tests") {

		std::string result = Staircase(10).ToString();
		REQUIRE(StaircaseTest1.compare(result) == 0);
		result = Staircase(5).ToString();
		REQUIRE(StaircaseTest2.compare(result) == 0);
		result = Staircase(40).ToString();
		REQUIRE(StaircaseTest3.compare(result) == 0);

		for (int i = 0; i < NUM_TESTS; i++) {
			REQUIRE(realCountArray[i] == testCountArray[i]);
		}


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
		int size = atoi(inputValue.c_str());

		for (int i = 0; i < size; i++) {
			// read in each next number and
			// add it to the array
			std::cin >> inputValue;

		}

		// print the final result
		std::cout << inputValue;
	}

	return 0;
}
#endif
