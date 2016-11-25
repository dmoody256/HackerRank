#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
#include <sstream>
#include <exception>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <chrono>

#define TEST_BUILD

#ifdef TEST_BUILD
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#endif

#ifdef DEBUG_PRINT 
#define D(x) x
#else 
#define D(x)
#endif

//https://www.hackerrank.com/challenges/a-very-big-sum


class BigInt {
public:

	BigInt() {
		_bigIntData = "";
	}

	BigInt(const std::string &targetString) {
		if (targetString.compare("") && targetString.find_first_not_of("0123456789") != std::string::npos) {
			throw std::invalid_argument("Tried to make bigint from somehting that was not a number");
		}
		else {
			SetNumber(targetString);
		}
	}

	const std::string const ToString() const{
		return _bigIntString;
	}

	const std::string const ToData() const {
		return _bigIntData;
	}

	BigInt& operator=(std::string targetString)
	{
		SetNumber(targetString);
		return *this;
	}

private:

	void SetNumber(std::string targetString) {
		_bigIntString = _bigIntData = targetString;
		std::reverse(_bigIntData.begin(), _bigIntData.end());
	}

	std::string _bigIntString;
	std::string _bigIntData;

};

bool operator==(const BigInt& lhs, const BigInt& rhs)
{
	return !lhs.ToString().compare(rhs.ToString());
}

BigInt operator + (const BigInt& lhs, const BigInt& rhs)
{
	// determine which string is larger and record how many digits match for both strings
	std::string result = "";
	std::string smallString = rhs.ToData().size() >= lhs.ToData().size() ? lhs.ToData() : rhs.ToData();
	std::string largeString = rhs.ToData().size() < lhs.ToData().size() ? lhs.ToData() : rhs.ToData();
	unsigned int matchedSize = smallString.size();

	unsigned int carry = 0;

	// add all the digits together
	D(std::cout << "First Loop: matchedsize = " << matchedSize << ", " << smallString << " + " << largeString << std::endl);
	for (int i = 0; i < matchedSize; i++) {
		
		int sum = (smallString.at(i) - 48) + (largeString.at(i) - 48) + carry;
		D(std::cout << smallString.at(i) << " + " << largeString.at(i) << " + " << carry << " = " << sum);
		if (sum > 9) {
			carry = 1;
			sum -= 10;
		}
		else {
			carry = 0;
		}
		D(std::cout << ", carry = " << carry << std::endl);
		result.append(1, sum + 48);
	}

	for (int i = matchedSize; i < largeString.size(); i++) {
		int sum = (largeString.at(i) - 48) + carry;
		D(std::cout << largeString.at(i) << " + " << carry << " = " << sum << std::endl);
		if (sum > 9) {
			carry = 1;
			sum -= 10;
		}
		else {
			carry = 0;
		}
		D(std::cout << ", carry = " << carry << std::endl);
		result.append(1, sum + 48);
	}

	if(carry)
		result.append("1");
	D(std::cout << "final carry = " << carry << std::endl);

	std::reverse(result.begin(), result.end());

	return BigInt(result);
}

#ifdef TEST_BUILD

#define NUM_TESTS 1000

std::string generateRandomNumberString(int len) {
	std::stringstream ranNum;
	for (int i = 0; i < len; ++i) {
		ranNum << rand() % 10;
	}
	return ranNum.str();
}

TEST_CASE("Add two BigInts", "[operator+]") {

	int digitsProcessed = 0;
	std::cout << "Generating " << NUM_TESTS << " test values for operator+ test:" << std::endl;

	std::vector<BigInt> bigIntArray;
	std::vector<BigInt> bigIntArray2;
	double intArray[NUM_TESTS];
	double intArray2[NUM_TESTS];

	std::vector<BigInt> bigIntArray_strings;
	std::vector<std::string> bigIntStringArray;

	for (int i = 0; i < NUM_TESTS; i++) {
		std::cout << "Generating... " << int((float)i / (float)NUM_TESTS * 100.0) << "%\r";
		std::cout.flush();
		bigIntStringArray.push_back(generateRandomNumberString(rand() % NUM_TESTS));
		digitsProcessed += bigIntStringArray[i].size();
		bigIntArray_strings.push_back(BigInt(bigIntStringArray[i]));
	}

	for (int i = 0; i < NUM_TESTS; i++) {
		std::cout << "Generating... " << int((float)i / (float)NUM_TESTS * 100.0) << "%\r";
		std::cout.flush();
		std::string string1 = generateRandomNumberString(rand() % 10);
		std::string string2 = generateRandomNumberString(rand() % 10);
		intArray[i] = std::atoll(string1.c_str());
		intArray2[i] = std::atoll(string2.c_str());
		bigIntArray.push_back(BigInt(string1));
		bigIntArray2.push_back(BigInt(string2));
	}

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

	static const std::vector<BigInt> bigIntHardCodeOperon1_vec(bigIntHardCodeOperon1, bigIntHardCodeOperon1 + sizeof(bigIntHardCodeOperon1) / sizeof(bigIntHardCodeOperon1[0]));
	static const std::vector<BigInt> bigIntHardCodeOperon2_vec(bigIntHardCodeOperon2, bigIntHardCodeOperon2 + sizeof(bigIntHardCodeOperon2) / sizeof(bigIntHardCodeOperon2[0]));
	static const std::vector<BigInt> bigIntHardCodeSum_vec(bigIntHardCodeSum, bigIntHardCodeSum + sizeof(bigIntHardCodeSum) / sizeof(bigIntHardCodeSum[0]));

	SECTION("resizing bigger changes size and capacity") {
		for (int i = 0; i < NUM_TESTS; i++) {
			double intResult = intArray[i] + intArray2[i];
			BigInt bigIntResult = bigIntArray.at(i) + bigIntArray2.at(i);
			REQUIRE(intResult == std::atoll(bigIntResult.ToString().c_str()));
		}

		for (int i = 0; i < bigIntHardCodeOperon1_vec.size(); i++) {
			BigInt bigIntResult = bigIntHardCodeOperon1_vec.at(i) + bigIntHardCodeOperon2_vec.at(i);
			REQUIRE(bigIntHardCodeSum_vec.at(i) == bigIntResult);
		}

	}
	SECTION("resizing smaller changes size but not capacity") {
		for (int i = 0; i < NUM_TESTS; i++) {
			REQUIRE(bigIntStringArray.at(i) == bigIntArray_strings.at(i).ToString());
		}
	}
}

#endif


#ifndef CATCH_CONFIG_MAIN
int main (int argc, char *argv[]) {

	int numOperons = 0;
	std::vector<std::deque<char> > operons;

	std::string nextLine;
	std::getline(std::cin, nextLine);
	try {

		numOperons = std::atoi(nextLine.c_str());
		std::getline(std::cin, nextLine);
		std::vector<std::string> operonStrings;
		operonStrings = Split(nextLine, ' ');

		for (int i = 0; i < numOperons; i++) {
			operons.push_back(createBigInt(operonStrings.at(i)));
		}
		for (int i = 0; i < numOperons; i++) {
			printf("read in int: %s\n", bigIntToString(operons.at(i)).c_str());
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}

	//std::deque<char> sum = addBigInts(operons);

	return 0;
}
#endif