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

	struct Node;
	struct Edge
	{
		int start;
		int* end;
		Node* next_node;
	} typedef Edge;

	struct Node
	{
		int nodeID;
		Node* suffix_link;
		std::vector<Edge*> edges;
		int nodePrintSize;
	} typedef Node;

	struct ActivePoint
	{
		Node* active_node;
		char active_edge;
		int active_length;
	} typedef ActivePoint;

	static const bool debug = true;
	SuffixTree(std::string input)
	{
		if(debug) { std::cout << "Creating new suffix tree from: " << input << std::endl; }
		original_string = input;
		nodeCount = 0;
		root.nodeID = nodeCount;

		active_point.active_node = &root;
		active_point.active_edge = '\0';
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
		if(debug) { std::cout << "-------------------------------- " << std::endl; }
		if(debug) { std::cout << "Inserting char: " << next << std::endl; }

		bool found = false;
		for( auto edge : active_point.active_node->edges)
		{
			if(original_string.at(edge->start) == next){
				found = true;
				if(debug) { std::cout << "Found existing edge: " << next << std::endl; }
				break;
			}
		}

		remainder++;

		if(!found)
		{
			Node* lastNode = NULL;
			while (remainder > 0)
			{
				if(remainder == 1 || active_point.active_edge == '\0'){

					if(debug) { std::cout << "Adding new edge for: " << next << std::endl; }
					Edge* edge = new Edge();
					edge->start = position;
					edge->end = &position;
					edge->next_node = NULL;
					root.edges.push_back(edge);
				}
				else
				{
					
					if(debug) { std::cout << "Clearing excess remainder: " << remainder << std::endl; }
					Edge* active_edge = NULL;
					for( auto edge : active_point.active_node->edges)
					{
						if(debug) { std::cout << "Checking edge: " << original_string.at(edge->start) << " against active edge: " << active_point.active_edge << std::endl; }
						if(original_string.at(edge->start) == active_point.active_edge)
						{
							active_edge = edge;
							if(debug) { std::cout << "Found active edge: " << active_point.active_edge << std::endl; }
							break;
						}
					}
					
					Node* node = new Node();
					nodeCount++;
					node->nodeID = nodeCount;

					if(debug) { std::cout << "Creating new node: " << nodeCount << std::endl; }

					active_edge->next_node = node;
					active_edge->end = new int(active_edge->start + active_point.active_length);
					if(debug) { std::cout << "Updating active edge: " <<  original_string.substr(active_edge->start, *active_edge->end-active_edge->start) << std::endl; }

					Edge* edge1 = new Edge();
					edge1->start = *active_edge->end;
					edge1->end = &position;
					edge1->next_node = NULL;
					if(debug) { std::cout << "Creating first edge on new node: " <<  original_string.substr(edge1->start, *edge1->end+1-edge1->start) << std::endl; }

					Edge* edge2 = new Edge();
					edge2->start = position;
					edge2->end = &position;
					edge2->next_node = NULL;
					if(debug) { std::cout << "Creating second edge on new node: " <<  original_string.substr(edge2->start, *edge2->end+1-edge2->start) << std::endl; }

					node->edges.push_back(edge1);
					node->edges.push_back(edge2);

					if(lastNode != NULL)
					{
						lastNode->suffix_link = node;
					}
					lastNode = node;
					
					if(active_point.active_node == &root)
					{
						active_point.active_length--;
						active_point.active_edge = original_string.at(position-active_point.active_length);
						if(debug) { std::cout << "Setting new active point: " << active_point.active_edge << std::endl; }
					}
					else
					{
						if(active_point.active_node->suffix_link == NULL)
						{
							active_point.active_node = &root;
						}
						else
						{
							Node* nextnode = active_point.active_node->suffix_link;
							while(nextnode->suffix_link != NULL)
							{
								nextnode = nextnode->suffix_link;
							}
							active_point.active_node = nextnode;
						}
					}
				}
				remainder--;
			}
			
		}
		else
		{
			if(active_point.active_edge == '\0' || remainder < 2 )
				active_point.active_edge = next;
			active_point.active_length++;
		}

		position++;

		for(auto edge : active_point.active_node->edges)
		{
			if(active_point.active_edge == original_string.at(edge->start) && active_point.active_length == (*edge->end-edge->start))
			{
				if(edge->next_node == NULL)
				{
					std::cout << "ERROR" << std::endl;
				}
				active_point.active_node = edge->next_node;
				active_point.active_edge = '\0';
				active_point.active_length = 0;
				break;
			}
		}
		
		if(debug) { std::cout << "remainder: " << remainder << std::endl; }
		if(debug) { std::cout << "position: " << position << std::endl; }
		if(debug) { std::cout << "active_point.active_node: " << active_point.active_node->nodeID << std::endl; }
		if(debug) { std::cout << "active_point.active_edge: " << active_point.active_edge << std::endl; }
		if(debug) { std::cout << "active_point.active_length: " << active_point.active_length << std::endl; }

	}

	void PrintTree()
	{
		PrintBranch(&root, 0);
	}

	void PrintBranch(Node* root, int depth)
	{
		std::string space;
		for(int i = 0; i < depth; i++)
		{
			space.append("               ");
		}
		std::cout << "* " << root->nodeID << std::endl;

		std::string dashes = "--------------";
		for ( auto edge : root->edges)
		{

			std::cout << space << "|" << std::endl;
			std::cout << space << "| " << original_string.substr(edge->start, *edge->end-edge->start) << std::endl;

			if(edge->next_node != NULL)
			{
				std::cout << space << "+" << dashes;

				PrintBranch(edge->next_node, ++depth);
			}
			else
			{
				std::cout << space << "+" << dashes << "* LEAF" << std::endl;
			}
		}
		
	}
	int nodeCount;
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

	SuffixTree tree("abcabxabcd");
	tree.PrintTree();

	return 0;
}
#endif
