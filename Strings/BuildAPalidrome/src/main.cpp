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
//https://www.hackerrank.com/challenges/find-the-median


//     _____    ____    _____    ______
//    / ____|  / __ \  |  __ \  |  ____|
//   | |      | |  | | | |  | | | |__
//   | |      | |  | | | |  | | |  __|
//   | |____  | |__| | | |__| | | |____
//    \_____|  \____/  |_____/  |______|
//
// letters generated at http://patorjk.com/software/taag

class SuffixTree
{
	
public:


	struct Edge
	{
		int start;
	} typedef Edge;

	struct Node
	{
		int nodeID;
		Node* suffix_link;
		std::vector<Edge*> edges;
	} typedef Node;

	struct ActivePoint
	{
		Node* active_node;
		int active_edge;
		int active_length;
	} typedef ActivePoint;

	static const bool debug = true;
	SuffixTree(std::string input)
	{
		if(debug) { std::cout << "Creating new suffix tree from: " << input << std::endl; }
		original_string = input;
		root.nodeID = 0;
		root.suffix_link = 0;
	
		active_point.active_node = &root;
		active_point.active_edge = 0;
		active_point.active_length = 0;

		remainder = 0;
		position = 0;
		for(int i = 0; i < input.size(); i++)
		{
			InsertNext(input.at(i));
		}
		
		
	}

	void InsertNext(char next)
	{
		bool found = false;
		for( auto edge : active_point.active_node->edges)
		{
			std::string sub = original_string.substr(edge->start, position - edge->start);
			if(sub.at(0) == next){
				found = true;
				break;
			}
		}

		if(!found)
		{
			
			Edge* edge = new Edge();
			edge->start = position;
			root.edges.push_back(edge);
			position++;
		}
		else
		{
			

		}
	}

	void PrintTree()
	{
		std::cout << "root" << std::endl;

		if(root.edges.size() > 0)
		{
			std::cout << "|" << std::endl;
		}
			
		int count = 0;
		int last_size = 0;
		for ( auto& edge : root.edges)
		{
			std::string sub = original_string.substr(edge->start, position - edge->start);
			
			if(count == 0)
			{
				std::cout << "|";
			}
			else
			{
				for(int i = 0; i < last_size; i++)
				{
					std::cout << "-";	
				}
				std::cout << "--|";	
				
			}
			last_size = sub.size()-1;
			count++;
		}
		std::cout << std::endl;	
		count = 0;
		for ( auto& edge : root.edges)
		{
			std::string sub = original_string.substr(edge->start, position - edge->start);
			if(count == 0)
			{
				std::cout << "|" ;
				last_size = sub.size();
			}
			else
			{
				for(int i = 0; i < last_size-1; i++)
				{
					std::cout << " ";	
				}
				std::cout << "  |";	
				last_size = sub.size();
			}
			
			count++;
		}
		std::cout << std::endl;	
		count = 0;
		for ( auto edge : root.edges)
		{
			std::string sub = original_string.substr(edge->start, position - edge->start);
			if(count == 0)
			{
				std::cout << sub;
				last_size = sub.size()-1;
			}
			else
			{
				for(int i = 0; i < last_size-1; i++)
				{
					std::cout << " ";	
				}
				std::cout << sub;
				last_size = sub.size();
			}
			
			count++;
		}
	}
	std::string original_string;
	ActivePoint active_point;
	int remainder;
	int position;
	Node root;

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

	SuffixTree tree("abcd");
	tree.PrintTree();

	return 0;
}
#endif
