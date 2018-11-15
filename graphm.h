// ------------------------------------------------ graphm.h ------------------------------------------------------------
// Scott Ferguson CSS 343
// 11-1-2015
// 11-12-2015
// --------------------------------------------------------------------------------------------------------------------
// Purpose - To provide the structure for grahm.cpp. This program is designed to implament Dijkstra's algorithm
// --------------------------------------------------------------------------------------------------------------------
// Assumptions-text file will be in the correct format
// Only integers will be used as nodes
// if there exists a node that has no node to connect to is has a weight of infinity
// --------------------------------------------------------------------------------------------------------------------
#ifndef GRAPHM_H
#define GRAPHM_H
#include <string>	  
#include <iostream>	  
#include <fstream>	  
#include <iomanip> 	  
#include "limits.h"	  
#include "nodedata.h" 

const int MAXNODES = 101; // index 0 is not used

struct TableType {
	bool visited; // whether node has been visited
	int dist; // shortest distance from source known so far
	int path; // previous node in path of min dist
};
// --------------------------------------------------------------------------------------------------------------------

class GraphM {

	// public functions
	public:

		// constructor
		GraphM();

		// insert all data into a graph
		void buildGraph(ifstream&); 

		// insert an edge into the graph
		void insertEdge(const int,const int, const int);  

		// remove an edge
		void removeEdge(const int,const int); 

		// Dijkstra's algorithm
		void findShortestPath(); 

		// display all of the data
		void displayAll() const; 

		// display from one one to another
		void display(const int,const int) const; 

	// private functions
	private:    

		NodeData data[MAXNODES]; // data for graph nodes 
		int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix
		int size; // number of nodes in the graph
		TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path

		// recursive helper functions

		// dislay the path from one node to another
		void getPathRecursively(const int,const int) const; 

		// display the information from one node to another
		void getDataRecursively(const int, const int) const; 
};
#endif