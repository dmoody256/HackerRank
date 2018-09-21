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
#include <stdexcept>

namespace suffixtrees
{

class Node;


class Edge
{
public:
	
	static std::string& originalString;

	Edge(int start, int* end)
	: start(start),
	  end(nullptr),
	  next_node(nullptr)
	{
		setEndPointer(end);
	}

	int getLength() const   
	{ 
		if(end)
			return *end-start; 
		else
			throw std::runtime_error("End pointer cannot be NULL!");
		
	}

	Node* getNextNode() const { return next_node; }

    std::string getEdgeString() const 
	{
		return originalString.substr(start, getLength());
	}

	char getStartChar() const
	{
		return originalString.at(start);
	}

	char getStartPosition() const
	{
		return start;
	}

	void setNextNode(Node* node)
	{
		next_node = node;
	}

	void setEndPointer(const int* endPosition)
	{
		if(endPosition)
			end = endPosition;
		else
			throw std::invalid_argument("End pointer must not be NULL!");
	
	}

	

private:

	const int start;
	const int* end;
	
	Node* next_node;
};


class Node
{
public:

	Node(int id, int edgeEnd)
	: nodeID(id),
		parentEdgeEnd(edgeEnd),
		suffix_link(nullptr)
	{}

	int getNodeId() const
	{
		return nodeID;
	}

	Node* getSuffixLink() const
	{
		return suffix_link;
	}

	std::vector<Edge*> getEdges() const
	{
		return edges;
	}

	void addEdge(Edge* edge)
	{
		if(edge)
			edges.push_back(edge);
		else
			throw std::invalid_argument( "Must pass a non NULL Edge object" );
	}

	void setSuffixLink(Node* node)
	{
		suffix_link = node;
	}
\
	const int* getParentEndPosition() const
	{
		return &parentEdgeEnd;
	}

	Edge* findEdge(int startPosition)
	{
		for( auto edge : getEdges())
			if(edge->getStartPosition() == startPosition)
				return edge;
		return nullptr;
	}

	Edge* findEdge(char startChar)
	{
		for( auto edge : getEdges())
			if(edge->getStartChar() == startChar)
				return edge;
		return nullptr;
	}

private:

	Node()
	  : nodeID(-1),
	    parentEdgeEnd(-1),
		suffix_link(nullptr)
	{}

	const int parentEdgeEnd;
	const int nodeID;
	
	Node* suffix_link;

	std::vector<Edge*> edges;
};

class ActivePoint
{
public:

	ActivePoint()
	: active_node(nullptr),
	  active_edge(nullptr),
	  active_length(0)
	{};

	ActivePoint(Node* active_node, Edge* active_edge, int active_length)
	: active_node(active_node),
	  active_edge(active_edge),
	  active_length(active_length)
	{};

	Node* active_node;
	Edge* active_edge;
	int active_length;
};

class SuffixTree
{
	
public:
	

	static const bool debug = true;
	
	SuffixTree(std::string input)
	: nodeCount(0),
	  root(nodeCount, 0),
	  originalString(input),
	  ap(&root, nullptr, 0),
	  remainder(0),
	  position(0)
	{
		if(debug) { std::cout << "Creating new suffix tree from: " << input << std::endl; }

		Edge::originalString = originalString;

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
		for( auto edge : ap.active_node->getEdges())
		{
			if(edge->getStartChar() == next){
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
				if(remainder == 1){

					if(debug) { std::cout << "Adding new edge for: " << next << std::endl; }
					Edge* edge = new Edge(position, &position);
					ap.active_node->addEdge(edge);

					if(lastNode && ap.active_edge == nullptr)
					{
						ap.active_edge = edge;
					}
				}
				else
				{

					if(debug) { std::cout << "Clearing excess remainder: " << remainder << std::endl; }

					nodeCount++;
					Node* node = new Node(nodeCount, ap.active_edge->getStartPosition() + ap.active_length);
					
					if(debug) { std::cout << "Creating new node: " << node->getNodeId() << std::endl; }

					ap.active_edge->setNextNode(node);
					ap.active_edge->setEndPointer(node->getParentEndPosition());

					if(debug) { std::cout << "Updating active edge: " <<  ap.active_edge->getEdgeString() << std::endl; }

					Edge* edge1 = new Edge(*node->getParentEndPosition(), &position);
					Edge* edge2 = new Edge(position, &position);
					node->addEdge(edge1);
					node->addEdge(edge2);
					
					if(debug) { std::cout << "Creating first edge on new node: " <<  edge1->getEdgeString() << std::endl; }
					if(debug) { std::cout << "Creating second edge on new node: " <<  edge2->getEdgeString() << std::endl; }

					if(lastNode != NULL)
					{
						lastNode->setSuffixLink(node);
					}
					lastNode = node;

					if(ap.active_node == &root)
					{
						ap.active_length--;
						ap.active_edge = ap.active_node->findEdge(originalString.at(position - ap.active_length));
						if(debug && ap.active_edge) { std::cout << "Setting new active point: " << ap.active_edge->getEdgeString() << std::endl; }
					}
					else
					{
						if(ap.active_node->getSuffixLink() == NULL)
						{
							ap.active_node = &root;
						}
						else
						{
							Node* nextnode = ap.active_node->getSuffixLink();
							while(nextnode->getSuffixLink() != NULL)
							{
								nextnode = nextnode->getSuffixLink();
							}
							ap.active_node = nextnode;
						}
					}
				}
				
				remainder--;
			}
		}
		else
		{
			ap.active_length++;
			Edge* edge = ap.active_node->findEdge(next);
			if(edge->getEdgeString().at(ap.active_length) != next)
			{
				ap.active_edge = ap.active_node->findEdge(next);
			}
			
			
		}

		position++;

		for(auto edge : ap.active_node->getEdges())
		{
			if(ap.active_edge == edge && ap.active_length == edge->getLength())
			{
				if(edge->getNextNode() == NULL)
				{
					throw std::runtime_error("Should not have LEAF node as active edge!");
				}
				ap.active_node = edge->getNextNode();
				ap.active_edge = nullptr;
				ap.active_length = 0;
				break;
			}
		}
		
		if(debug) { std::cout << "remainder: " << remainder << std::endl; }
		if(debug) { std::cout << "position: " << position << std::endl; }
		if(debug)			
		{
			if(ap.active_node) { std::cout << "active_point.active_node: " << ap.active_node->getNodeId() << std::endl; }
			else			   { std::cout << "active_point.active_node: NULL" << std::endl; }	 
		}
		if(debug)
		{
			if(ap.active_edge) { std::cout << "active_point.active_edge: " << ap.active_edge->getEdgeString() << std::endl; }
			else               { std::cout << "active_point.active_edge: NULL" << std::endl; }
		}
		if(debug) { std::cout << "active_point.active_length: " << ap.active_length << std::endl; }

		if(debug) {PrintTree();}

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
			space.append("|              ");
		}
		std::stringstream suffixNode;
		if(root->getSuffixLink() != NULL)
		{
			suffixNode << " (->" << root->getSuffixLink()->getNodeId() << ")";
		}
		std::cout << "* " << root->getNodeId() << suffixNode.str() << std::endl;

		std::string dashes = "--------------";
		for ( auto edge : root->getEdges())
		{

			std::cout << space << "|" << std::endl;
			std::cout << space << "| " << edge->getEdgeString() << std::endl;

			if(edge->getNextNode() != NULL)
			{
				std::cout << space << "+" << dashes;

				PrintBranch(edge->getNextNode(), depth+1);
			}
			else
			{
				std::cout << space << "+" << dashes << "* LEAF" << std::endl;
			}
		}
		
	}

	int nodeCount;
	std::string originalString;
	ActivePoint ap;
	int remainder;
	int position;
	Node root;

};

std::string empty;
std::string& Edge::originalString = empty;

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

	suffixtrees::SuffixTree tree("abcabxabcd");
	tree.PrintTree();

	return 0;
}
#endif
