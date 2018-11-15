// ------------------------------------------------ graphl.h ------------------------------------------------------------
// Scott Ferguson CSS 343
// 11-8-2015
// 11-12-2015
// ----------------------------------------------------------------------------------------------------------------------
// Purpose - To provide the structure for grahpl.cpp. This program is designed to a depth first search
// ----------------------------------------------------------------------------------------------------------------------
// Assumptions-text file will be in the correct format
// Only integers will be used as nodes
// the insert and remove methods were added to make graphl copy the structure of graphm
// ----------------------------------------------------------------------------------------------------------------------

#ifndef GRAPHL_H
#define GRAPHL_H
#include <string>	
#include <iostream>	
#include <fstream>	
#include <iomanip> 	
#include "limits.h" 
#include "nodedata.h" 

class GraphL {

	// public functions

	public:

		const static int MAXNODES = 101; // max number

		// constructor
		GraphL();  

		// deconstructor
		~GraphL(); 
		
		// build the graph from a text file
		void buildGraph(ifstream&); 

		// display the DFS graph
		void displayGraph();	

		// start the process of finding the DFS 
		void depthFirstSearch();	

		// recursively find the DFS	   
		void dfsRecursively(int);	

		// insert a node and an edge
		void insert(int, int); 

		// remove a node and an edge
		void remove(int);	
	
	// private functions
	private:

		struct EdgeNode;		 
		struct GraphNode 		 
		{
			EdgeNode* edgeHead;  
			NodeData* data; 	
			bool visited;		 
		};
		
		struct EdgeNode
		{
			int adjGraphNode; 	 
			EdgeNode* nextEdge;
		};	
		GraphNode adjList[MAXNODES]; 
		int size; 					      
};
#endif