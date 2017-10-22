#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
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
This function only works with the format:

HH:MM:SSAM

or 

HH:MM:SSPM

and will convert it into military  time.
*/
std::string ConvertTime12to24(std::string inputTime) {

	// check if we have AM or PM
	bool PM = inputTime.at(8) == 'P';
	
	// get the current time in hours and convert to 
	// number so we can operate on it
	std::stringstream outputTime;
	std::stringstream sstr;
	sstr << inputTime.at(0);
	sstr << inputTime.at(1);
	int hours = std::atoi(sstr.str().c_str());

	// adjust the hours based off military time 
	int AMPM_adjust;
	if (!PM && hours == 12) {
		AMPM_adjust = -12;
	}
	else if (!PM && hours != 12 || PM && hours == 12) {
		AMPM_adjust = 0;
	}
	else {
		AMPM_adjust = 12;
	}
	hours += AMPM_adjust;

	// add a zerop if we need it
	if (hours < 10) {
		outputTime << "0";
	}
	outputTime << hours << ":";

	// the rest of tume is the same so no conversion needed
	outputTime << inputTime.at(3);
	outputTime << inputTime.at(4);
	outputTime << ":";

	outputTime << inputTime.at(6);
	outputTime << inputTime.at(7);

	return outputTime.str();
}

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

TEST_CASE("Perfrom tests", "[Convert Time]") {

	// we can test every possible input and output
	// so we will build a table for each with several for 
	// loops
	std::stringstream sstr;
	std::vector<std::string> timeArray;
	std::vector<std::string> milTimeArray;

	// first generate the table for AMPM time
	D(std::cout << "Generating test values for time test:" << std::endl);
	for (int i = 0; i < 2; i++) {
		std::string AMPM = "AM";
		if (i) {
			AMPM = "PM";
		}
		for (int Mins = 0; Mins < 60; Mins++) {
			for (int Seconds = 0; Seconds < 60; Seconds++) {
				std::stringstream sstr;
				sstr << "12:";

				if (Mins < 10) {
					sstr << "0";
				}
				sstr << Mins << ":";

				if (Seconds < 10) {
					sstr << "0";
				}
				sstr << Seconds << AMPM;

				timeArray.push_back(sstr.str());
			}
		}

		for (int Hours = 1; Hours < 12; Hours++) {
			for (int Mins = 0; Mins < 60; Mins++) {
				for (int Seconds = 0; Seconds < 60; Seconds++) {
					std::stringstream sstr;

					if (Hours < 10) {
						sstr << "0";
					}
					sstr << Hours << ":";

					if (Mins < 10) {
						sstr << "0";
					}
					sstr << Mins << ":";

					if (Seconds < 10) {
						sstr << "0";
					}
					sstr << Seconds << AMPM;

					timeArray.push_back(sstr.str());
					D(std::cout << "Generating... " << sstr.str() << "%\r");
					D(std::cout.flush());
				}
			}
		}
	}

	//generate the table for military time
	for (int Hours = 0; Hours < 24; Hours++) {
		for (int Mins = 0; Mins < 60; Mins++) {
			for (int Seconds = 0; Seconds < 60; Seconds++) {
				std::stringstream sstr;

				if (Hours < 10) {
					sstr << "0";
				}
				sstr << Hours << ":";

				if (Mins < 10) {
					sstr << "0";
				}
				sstr << Mins << ":";

				if (Seconds < 10) {
					sstr << "0";
				}
				sstr << Seconds;

				milTimeArray.push_back(sstr.str());
				D(std::cout << "Generating... " << sstr.str() << "%\r");
				D(std::cout.flush());
			}
		}
	}

	// not a direct test, but good test for our tests
	REQUIRE(timeArray.size() == milTimeArray.size());

	// test the tables agaisnt each other
	for (int i = 0; i < timeArray.size(); i++) {
		REQUIRE(milTimeArray.at(i) == ConvertTime12to24(timeArray.at(i)));
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
		std::cout << ConvertTime12to24(inputValue) << std::endl;
	}

	return 0;
}
#endif
