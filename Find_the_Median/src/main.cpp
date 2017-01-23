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
		memcpy(array, list, size*sizeof(int));
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
		for (int i = leftIndex; i < rightIndex ; i++) {
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
		MedianArray testArray;
		std::vector<int> list;
		int testSize = rand() % 100000;
		if (testSize % 2 == 0)
			testSize++;
		for (int i = 0; i < testSize; i++)
			list.push_back(rand() % 1000);
		for (int i = 0; i < testSize + 2; i++)
			list.push_back(testSize / 2);
		int medianResult = testArray.FindMedian(list.size(), &list.at(0));
		REQUIRE(medianResult == testSize / 2);
	}
	MedianArray testArray;
	static const int staticTest1[] = { 766, 442, 432, 191, 467, 753, 911, 223, 136, 479, 189, 396, 468, 193, 616, 393, 299, 403, 380, 33, 571, 358, 350, 95, 992, 828, 9, 339, 11, 652, 526, 529, 667, 947, 829, 232, 530, 353, 472, 971, 342, 99, 449, 124, 507, 10, 770, 4, 360, 7, 860, 938, 745, 850, 935, 362, 34, 642, 729, 448, 980, 227, 926, 85, 550, 0, 287, 964, 988, 863, 979, 667, 721, 607, 766, 968, 125, 321, 83, 268, 530, 214, 438, 989, 153, 726, 835, 892, 460, 614, 690, 370, 249, 820, 0, 687, 845, 179, 302, 800, 505, 441, 411, 456, 99, 581, 776, 591, 337, 228, 337, 872, 282, 894, 905, 364, 351, 538, 794, 40, 899, 353, 677, 872, 23, 324, 157, 278, 243, 262, 866, 998, 105, 182, 795, 64, 289, 382, 868, 602, 714, 908, 75, 448, 23, 92, 487, 196, 726, 896, 201, 152, 681, 314, 549, 430, 333, 293, 195, 582, 990, 454, 180, 627, 326, 745, 910, 432, 358, 731, 642, 907, 647, 20, 77, 197, 176, 926, 135, 938, 362, 235, 3, 996, 510, 41, 603, 238, 127, 695, 483, 234, 41, 850, 32, 803, 368, 155, 15, 235, 278, 938, 2, 158, 552, 256, 703, 902, 7, 226, 693, 195, 161, 498, 14, 466, 279, 39, 256, 688, 968, 868, 434, 702, 807, 260, 571, 17, 852, 543, 977, 782, 443, 314, 143, 38, 918, 293, 540, 378, 386, 576, 918, 661, 854, 538, 645, 175, 986, 659, 304, 967, 836, 371, 982, 673, 305, 632, 717, 465, 686, 373, 135, 979, 561, 375, 70, 630, 21, 846, 914, 554, 730, 8, 969, 161, 723, 522, 946, 949, 884, 741, 824, 82, 544, 33, 780, 708, 163, 821, 316, 693, 115, 648, 36, 151, 626, 485, 252, 831, 616, 141, 88, 243, 106, 578, 448, 615, 959, 394, 30, 397, 702, 454, 970, 308, 572, 900, 365, 349, 722, 558, 357, 152, 141, 452, 655, 31, 306, 708, 670, 919, 571, 930, 909, 79, 815, 203, 317, 920, 165, 611, 916, 450, 368, 892, 444, 750, 316, 183, 212, 544, 72, 984, 265, 651, 650, 914, 524, 888, 313, 351, 592, 989, 447, 714, 248, 622, 199, 647, 34, 905, 980, 216, 872, 201, 978, 299, 603, 437, 152, 302, 51, 894, 301, 194, 669, 623, 86, 228, 906, 375, 480, 359, 434, 606, 687, 888, 904, 459, 217, 138, 581, 12, 963, 327, 854, 235, 531, 368, 23, 302, 573, 684, 18, 531, 81, 812, 243, 912, 273, 94, 94, 692, 931, 107, 620, 705, 927, 69, 355, 517, 741, 910, 588, 389, 372, 658, 924, 624, 965, 962, 461, 538, 247, 10, 999, 104, 904, 353, 198, 998, 193, 562, 420, 128, 916, 845, 41, 571, 374, 869, 134, 363, 16, 280, 976, 54, 67, 545, 800, 899, 701, 400, 205, 559, 593, 82, 705, 710, 695, 829, 786, 37, 331, 614, 141, 896, 997, 60, 884, 656, 618, 210, 594, 674, 802, 948, 916, 98, 952, 690, 684, 963, 45, 160, 112, 78, 601, 859, 217, 360, 10, 231, 236, 448, 94, 12, 231, 766, 270, 480, 755, 290, 846, 131, 138, 126, 734, 305, 361, 321, 663, 492, 152, 59, 797, 921, 711, 81, 534, 437, 633, 678, 377, 265, 544, 952, 860, 444, 895, 67, 159, 299, 137, 651, 649, 459, 215, 888, 951, 127, 853, 731, 548, 420, 99, 343, 274, 222, 392, 945, 233, 150, 29, 19, 575, 758, 188, 913, 655, 864, 83, 913, 679, 771, 37, 550, 313, 610, 256, 784, 657, 582, 867, 883, 301, 755, 974, 429, 546, 364, 120, 448, 111, 9, 496, 534, 626, 749, 91, 190, 212, 954, 332, 733, 507, 70, 303, 242, 59, 334, 700, 546, 516, 192, 437, 418, 886, 574, 659, 246, 898, 735, 868, 212, 783, 236, 897, 225, 21, 611, 759, 388, 824, 65, 172, 722, 854, 975, 69, 146, 453, 67, 438, 870, 559, 408, 170, 918, 905, 806, 415, 99, 537, 147, 679, 210, 231, 317, 528, 285, 718, 688, 479, 16, 764, 224, 169, 527, 859, 620, 762, 240, 270, 3, 963, 900, 434, 829, 482, 203, 217, 988, 429, 858, 864, 333, 894, 210, 513, 697, 948, 453, 423, 98, 72, 13, 101, 4, 269, 906, 185, 499, 450, 309, 532, 410, 978, 369, 660, 933, 181, 491, 419, 153, 830, 648, 638, 927, 963, 564, 263, 705, 698, 389, 678, 178, 639, 241, 287, 430, 910, 262, 232, 327, 47, 175, 305, 679, 155, 339, 698, 62, 204, 494, 853, 970, 168, 111, 94, 433, 859, 93, 944, 817, 243, 858, 717, 249, 62, 455, 958, 962, 788, 110, 502, 453, 42, 401, 396, 449, 805, 996, 97, 142, 439, 776, 520, 860, 973, 93, 734, 733, 142, 403, 736, 257, 880, 38, 434, 226, 11, 222, 745, 563, 755, 42, 219, 93, 318, 37, 828, 142, 820, 941, 6, 983, 132, 673, 750, 846, 965, 607, 784, 132, 194, 122, 610, 45, 718, 190, 428, 282, 81, 782, 206, 913, 747, 475, 526, 371, 293, 135, 543, 972, 177, 491, 946, 6, 799, 922, 414, 322, 351, 652, 741, 469, 417, 599, 620, 398, 790, 946, 234, 29, 428, 373, 874, 620, 979, 604, 828, 222, 383, 61, 616, 767, 542, 174, 86, 121, 148, 879, 99, 690, 903, 395, 8, 319, 763, 967, 535, 527, 989, 76, 438, 232, 976, 0, 0, 753, 260, 210, 747, 215, 899, 188, 549, 16, 531, 43, 678, 643, 733, 565, 78, 146, 337, 770, 597, 825, 1, 26, 676, 465, 748, 260, 149, 973, 913, 379, 874, 717, 38, 488, 455, 80, 599, 911, 82, 22, 771, 378, 83, 693, 982, 344, 866, 600, 351, 674, 696, 85, 183, 435, 507, 334, 308, 33, 243, 62, 191, 876, 564, 853, 338, 726, 471, 327, 979, 563, 367, 509, 742, 978, 502, 707, 550, 540, 463, 811, 162, 412, 818, 711, 904, 584, 291, 220, 829, 32, 935, 236, 84, 382, 938, 32, 633, 974, 838 };
	static const int staticTest1Median = 466;
	REQUIRE(staticTest1Median == testArray.FindMedian(1001, staticTest1));
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
