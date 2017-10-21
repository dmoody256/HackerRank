#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <exception>
#include <stdlib.h>
#include <stdexcept>

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
//https://www.hackerrank.com/challenges/a-very-big-sum


//     _____    ____    _____    ______ 
//    / ____|  / __ \  |  __ \  |  ____|
//   | |      | |  | | | |  | | | |__   
//   | |      | |  | | | |  | | |  __|  
//   | |____  | |__| | | |__| | | |____ 
//    \_____|  \____/  |_____/  |______|
//                                      
// letters generated at http://patorjk.com/software/taag

/*
This class is a string wrapper with some methods and operators
doing simple arithmetic with strings that only contain numbers
*/
class BigInt {

public:

	/*
	Default constuctor will initialize the BigInt to zero
	*/
	BigInt() {
		_bigIntData = "0";
		_bigIntString = "0";
	}

	/*
	Create a big int from a std::string, this will test if the 
	string passed is a valid number (does not contain non 
	number characters)
	*/
	BigInt(const std::string &targetString) {
		if (targetString.compare("") && targetString.find_first_not_of("0123456789") != std::string::npos) {
			throw std::invalid_argument("Tried to make BigInt from something that was not a number!");
		}
		else {
			SetNumber(targetString);
		}
	}

	/*
	Output the string that this big int is storing
	*/
	std::string const ToString() const{
		return _bigIntString;
	}

	/*
	When doing operations on the BigInt it is useful to 
	get the reversed string since operations generally
	are carried out from the Least Significant Bit
	*/
	std::string const ToData() const {
		return _bigIntData;
	}

	/*
	strings can be copied directly into a BigInt
	*/
	BigInt& operator=(std::string targetString)
	{
		SetNumber(targetString);
		return *this;
	}

private:

	/*
	A utility function stores the string and the reversed 
	data string
	*/
	void SetNumber(std::string targetString) {
		_bigIntString = _bigIntData = targetString;
		std::reverse(_bigIntData.begin(), _bigIntData.end());
	}

	// storage members
	std::string _bigIntString;
	std::string _bigIntData;

};

/*
String compare is use to compare two big ints since BigInt
wraps std::string
*/
bool operator==(const BigInt& lhs, const BigInt& rhs)
{
	return !lhs.ToString().compare(rhs.ToString());
}

/*
+ operator does the addition for two big ints
by going though each character (digit) in the string and
performing a addition operation for the two digits in the same 
position of each string. Use carry values to propagate the 
carry to more significant digits.
*/
BigInt operator + (const BigInt& lhs, const BigInt& rhs)
{
	// determine which string is the larger, result string will hold the result
	// of the addition operation as we move through the two numbers
	std::string result = "";
	std::string smallString = rhs.ToData().size() >= lhs.ToData().size() ? lhs.ToData() : rhs.ToData();
	std::string largeString = rhs.ToData().size() < lhs.ToData().size() ? lhs.ToData() : rhs.ToData();
	
	// record how many digits match for both strings and setup carry placeholder
	unsigned int matchedSize = smallString.size();
	unsigned int carry = 0;

	// first for loop will go through the strings where there are matching digits
	// from both sides and perform the addition
	D(std::cout << "First Loop: matchedsize = " << matchedSize << ", " << smallString << " + " << largeString << std::endl);
	for (int i = 0; i < matchedSize; i++) {

		// we can quickly covert ascii by -48 from the char value
		int sum = (smallString.at(i) - 48) + (largeString.at(i) - 48) + carry;
		D(std::cout << smallString.at(i) << " + " << largeString.at(i) << " + " << carry << " = " << sum);
		
		// check to see if we need a carry and extract it from the sum
		// we just got
		if (sum > 9) {
			carry = 1;
			sum -= 10;
		}
		else {
			carry = 0;
		}

		// add out addition to the result string
		D(std::cout << ", carry = " << carry << std::endl);
		result.append(1, sum + 48);
	}

	// Second loop will finish off the rest of the numbers from the larger string
	// keeping in mind that the carry can propogate though all steps in this loop
	for (int i = matchedSize; i < largeString.size(); i++) {

		// add the carry
		int sum = (largeString.at(i) - 48) + carry;
		D(std::cout << largeString.at(i) << " + " << carry << " = " << sum << std::endl);

		// carry can potentially put us over 9 so we need to check like normal
		if (sum > 9) {
			carry = 1;
			sum -= 10;
		}
		else {
			carry = 0;
		}
		D(std::cout << ", carry = " << carry << std::endl);
		// add this addition for this digits place to the result
		result.append(1, sum + 48);
	}

	// the can be one final carry value placing a 1 as the new Most Significant Digit
	if(carry)
		result.append("1");
	D(std::cout << "final carry = " << carry << std::endl);

	// we want to return the result BigInt so reverse our 
	// result into a normal left ot right string and make the 
	// return the new BigInt
	std::reverse(result.begin(), result.end());

	return BigInt(result);
}


#ifdef TEST_BUILD
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

/*
generate some rand big number strings
NOTE: this test does not see the RNG
it is expected that you use Catch command
line --rng-seed <'time'|number> to seed
*/
std::string generateRandomNumberString(int len) {
	std::stringstream ranNum;
	for (int i = 0; i < len; ++i) {
		ranNum << rand() % 10;
	}
	return ranNum.str();
}


TEST_CASE("This test will create and add big ints from generated and hardcoded values", "[BigInt]") {

	// setup the varibale we use for the addition tests
	std::vector<BigInt> bigIntArray;
	std::vector<BigInt> bigIntArray2;
	double intArray[NUM_TESTS];
	double intArray2[NUM_TESTS];

	// setup the variables for the to string test
	std::vector<BigInt> bigIntArray_strings;
	std::vector<std::string> bigIntStringArray;

	for (int i = 0; i < NUM_TESTS; i++) {
		// create a random bigint and will see if we the same exact string
		// back out
		bigIntStringArray.push_back(generateRandomNumberString(rand() % NUM_TESTS));
		bigIntArray_strings.push_back(BigInt(bigIntStringArray[i]));
	}

	// generate tests for the addition test
	for (int i = 0; i < NUM_TESTS; i++) {

		// create the number strings we will be using std::atoll to convert
		// to a number so we have to limit the size here, for bigger numbers 
		// we do hard coded tests
		std::string string1 = generateRandomNumberString(rand() % 10);
		std::string string2 = generateRandomNumberString(rand() % 10);

		// convert the string numbers into long long so we can add them later
		// store everything in the arraus
		intArray[i] = std::atoll(string1.c_str());
		intArray2[i] = std::atoll(string2.c_str());
		bigIntArray.push_back(BigInt(string1));
		bigIntArray2.push_back(BigInt(string2));
	}

	// here we write our hardcoded tests for the larger numbers
	static const BigInt bigIntHardCodeOperon1[] = {
		"0"
		"100000001",
		"1000000000001",
		"100000000000000000001",
		"1000000000000000000000001",
		"10000000000000000000000000001",
		"100000000000000000000000000000001",
		"10000000000000000000000000000000000000001",
		"1000000000000000000000000000000000000000000000001",
		"100000000000000000000000000000000000000000000000000000001",
		"9999999999999999999999",
		"9999999999999999999999999999999999999999999999999",
		"9999999999999999999999999999999999999999999999999",
		"8070348572037465023476501862481273498126501982651",
		"407561304876501763540875234726387423740912301283701273673640523606491278364091736498752340762354917623549162534971523041396451293764519231976345913745691345013465703475630475613407563045107435601237561"
	};


	static const BigInt bigIntHardCodeOperon2[] = {
		"0"
		"100000002",
		"1000000000002",
		"100000000000000000002",
		"1000000000000000000000002",
		"10000000000000000000000000002",
		"100000000000000000000000000000002",
		"10000000000000000000000000000000000000002",
		"1000000000000000000000000000000000000000000000002",
		"100000000000000000000000000000000000000000000000000000002",
		"1",
		"1",
		"9999999999999999999999999999999999999999999999999",
		"2873465028736405826340562304985601986450198264051263",
		"1978695716934736594376502347560417608751340172530487125307324081752301723564072354072354017235041725301782305718230561872458374384765018734658734650713648957123645034786598374650976578346592364985761097865190837561203987461209376534785130746510237461023754123071203476102374561275102356"
	};

	static const BigInt bigIntHardCodeSum[] = {
		"0"
		"200000003",
		"2000000000003",
		"200000000000000000003",
		"2000000000000000000000003",
		"20000000000000000000000000003",
		"200000000000000000000000000000003",
		"20000000000000000000000000000000000000003",
		"2000000000000000000000000000000000000000000000003",
		"200000000000000000000000000000000000000000000000000000003",
		"10000000000000000000000",
		"10000000000000000000000000000000000000000000000000",
		"19999999999999999999999999999999999999999999999998",
		"2881535377308443291364038806848083259948324766033914",
		"1978695716934736594376502347560417608751340172530487125307324081752301723564072354072761578539918227065323180952956949296199286686048720008332375174320140235487736771285350715413331495970141527520732620906587288854968506693185722448530822091523703164499384598684611039147481996876339917"
	};

	// store the hard coded arrays in a vector to make it a bit more useable
	static const std::vector<BigInt> bigIntHardCodeOperon1_vec(bigIntHardCodeOperon1, bigIntHardCodeOperon1 + sizeof(bigIntHardCodeOperon1) / sizeof(bigIntHardCodeOperon1[0]));
	static const std::vector<BigInt> bigIntHardCodeOperon2_vec(bigIntHardCodeOperon2, bigIntHardCodeOperon2 + sizeof(bigIntHardCodeOperon2) / sizeof(bigIntHardCodeOperon2[0]));
	static const std::vector<BigInt> bigIntHardCodeSum_vec(bigIntHardCodeSum, bigIntHardCodeSum + sizeof(bigIntHardCodeSum) / sizeof(bigIntHardCodeSum[0]));

	// perform the to string tests to make sure our BigInt class is not 
	// destroying the data
	SECTION("Performing to string tests") {
		for (int i = 0; i < NUM_TESTS; i++) {
			REQUIRE(bigIntStringArray.at(i) == bigIntArray_strings.at(i).ToString());
		}
	}
	 
	// this test perform many addition tests with smaller number of digits 
	SECTION("Performing generate BigInt string test (limited to 10 digits)") {
		for (int i = 0; i < NUM_TESTS; i++) {
			double intResult = intArray[i] + intArray2[i];
			BigInt bigIntResult = bigIntArray.at(i) + bigIntArray2.at(i);
			REQUIRE(intResult == std::atoll(bigIntResult.ToString().c_str()));
		}
	}

	// this tests our hardcoded data and lets us test much larger numbers
	SECTION("Performing the hardcoded addition tests for larger numbers"){
		for (int i = 0; i < bigIntHardCodeOperon1_vec.size(); i++) {
			BigInt bigIntResult = bigIntHardCodeOperon1_vec.at(i) + bigIntHardCodeOperon2_vec.at(i);
			REQUIRE(bigIntHardCodeSum_vec.at(i) == bigIntResult);
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
		int operons = atoi(inputValue.c_str());

		BigInt result;
		for (int i = 0; i < operons; i++) {
			// read in each next number and 
			// add it to the result
			std::cin >> inputValue;
			result = result + BigInt(inputValue);
		}

		// print the final result
		std::cout << result.ToString() << std::endl;
	}

	return 0;
}
#endif
