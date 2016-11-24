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
//https://www.hackerrank.com/challenges/a-very-big-sum


#if _MSC_VER >= 0x1700
#    define HACKERRANK_RVAL_MOVE(x) std::move(x)
#elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && ( defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L )
#    define HACKERRANK_RVAL_MOVE(x) std::move(x)
#else
#    define HACKERRANK_RVAL_MOVE(x) (x)
#endif

void Split(const std::string& s, const char delim, std::vector<std::string>& elems, const std::size_t maxElems = 0)
{
	std::istringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(HACKERRANK_RVAL_MOVE(item));
		if (elems.size() == maxElems)
		{
			break;
		}
	}
	if (elems.size() == maxElems && ss.good() && maxElems > 0)
	{
		std::string remainder;
		std::getline(ss, remainder, '\0');
		elems.back() += delim + remainder;
	}
}

std::vector<std::string> Split(const std::string& s, const char delim, const std::size_t maxElems = 0)
{
	std::vector<std::string> elems;
	Split(s, delim, elems, maxElems);
	return HACKERRANK_RVAL_MOVE(elems);
}

#ifdef TEST_BUILD
std::string generateRandomNumberString(int len) {
	srand(time(NULL));
	std::stringstream ranNum;
	for (int i = 0; i < len; ++i) {
		ranNum << rand() % 10;
	}
	return ranNum.str();
}
#endif


class BigInt {
public:

	BigInt() {
		_bigIntData = "";
	}

	BigInt(const std::string &bigIntString) {
		if (bigIntString.compare("") && bigIntString.find_first_not_of("0123456789") != std::string::npos) {
			throw std::invalid_argument("Tried to make bigint from somehting that was not a number");
		}
		else {
			_bigIntData = bigIntString;
		}
	}

	const std::string const toString() const{
		return _bigIntData;
	}

	BigInt& operator=(std::string string)
	{
		_bigIntData = string;
		return *this;
	}

private:

	std::string _bigIntData;

};

BigInt operator + (const BigInt& lhs, const BigInt& rhs)
{
	// determine which string is larger and record how many digits match for both strings
	std::string result = "";
	std::string smallString = rhs.toString().size() >= lhs.toString().size() ? lhs.toString() : rhs.toString();
	std::string largeString = rhs.toString().size() < lhs.toString().size() ? lhs.toString() : rhs.toString();
	unsigned int matchedSize = smallString.size();

	unsigned int carry = 0;

	// add all the digits together
	for (int i = matchedSize - 1; i >= 0; i--) {
		int sum = (smallString.at(i) - 48) + (largeString.at(i) - 48) + carry;
		if (sum > 9) {
			carry = 1;
			sum -= 10;
		}
		else {
			carry = 0;
		}
		result.append(1, sum + 48);
	}

	
	


	std::reverse(result.begin(), result.end());

	return BigInt(result);
}

#ifdef TEST_BUILD

#define NUM_TESTS 1000

TEST_CASE("Add two BigInts", "[operator+]") {

	int digitsProcessed = 0;
	std::cout << "Generating " << NUM_TESTS << " test values for operator+ test:" << std::endl;

	std::vector<BigInt> bigIntArray;
	std::vector<BigInt> bigIntArray2;
	int intArray[NUM_TESTS];
	int intArray2[NUM_TESTS];

	for (int i = 0; i < NUM_TESTS; i++) {
		std::cout << "Generating... " << int((float)i / (float)NUM_TESTS * 100.0) << "%\r";
		std::cout.flush();
		std::string string1 = generateRandomNumberString(5);
		std::string string2 = generateRandomNumberString(5);
		intArray[i] = atoi(string1.c_str());
		intArray2[i] = atoi(string2.c_str());
		bigIntArray.push_back(BigInt(string1));
		bigIntArray2.push_back(BigInt(string2));
	}

	for (int i = 0; i < NUM_TESTS; i++) {
		int intResult = intArray[i] + intArray2[i];
		BigInt bigIntResult = bigIntArray.at(i) + bigIntArray2.at(i);
		REQUIRE(intResult == atoi(bigIntResult.toString().c_str()));
	}

}

TEST_CASE("Convert string to BigInt and back to string", "[toString]") {

	int digitsProcessed = 0;
	std::cout << "Generating " << NUM_TESTS << " test values for toString test:" << std::endl;
	std::vector<BigInt> bigIntArray;
	std::vector<std::string> bigIntStringArray;

	for (int i = 0; i < NUM_TESTS; i++) {
		std::cout << "Generating... " << int((float)i / (float)NUM_TESTS * 100.0) << "%\r";
		std::cout.flush();
		bigIntStringArray.push_back(generateRandomNumberString(rand() % NUM_TESTS));
		digitsProcessed += bigIntStringArray[i].size();
		bigIntArray.push_back(BigInt(bigIntStringArray[i]));
	}

	for (int i = 0; i < NUM_TESTS; i++) {
		REQUIRE(bigIntStringArray.at(i) == bigIntArray.at(i).toString());
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