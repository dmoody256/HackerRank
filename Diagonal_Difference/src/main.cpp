#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <exception>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>

#ifdef TEST_BUILD
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#endif

#ifdef DEBUG_PRINT
#define D(x) x
#else
#define D(x)
#endif

//https://www.hackerrank.com/challenges/diagonal-difference



#ifndef CATCH_CONFIG_MAIN
int main (int argc, char *argv[]) {

	std::string inputValue;
	while (std::cin >> inputValue) {
		
		std::cout << inputValue << std::endl;
	}

	return 0;
}
#endif
