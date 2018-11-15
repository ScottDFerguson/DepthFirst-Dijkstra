// ------------------------------------------------ graphl.h ----------------------------------------------------------
// Scott Ferguson CSS 343
// 11-8-2015
// 11-12-2015
// --------------------------------------------------------------------------------------------------------------------
// Purpose - To provide the functions for grahpl.h. This program is designed to a depth first search
// --------------------------------------------------------------------------------------------------------------------
// Assumptions-text file will be in the correct format
// Only integers will be used as nodes
// the insert and remove methods were added to make graphl copy the structure of graphm
// --------------------------------------------------------------------------------------------------------------------

#include "graphl.h" 

// --------------------------------------------------------------------------------------------------------------------

// ------------------------------------GraphL()------------------------------------------------------------------------
// Description: Constructor for the object
// Creates a new object and sets its parameters to 0, or equivalent
// --------------------------------------------------------------------------------------------------------------------
GraphL::GraphL():size(0) {

} // eoGrpahL()

// ------------------------------------~GraphL()-----------------------------------------------------------------------
// Description: Deconstructor for the object
// destroys the object by calling remove(int), and then setting it to NULL
// --------------------------------------------------------------------------------------------------------------------
GraphL::~GraphL() {

	for(int i = 0; i <= size; i++) { // go through the size

		while(adjList[i].edgeHead != NULL)
			remove(i); // call removeNode
		
		delete adjList[i].data; // delete the data
		adjList[i].data = NULL; // set the data to null
	}
	size = 0; // make the size 0
} // eo~GraphL()

// ------------------------------------buildGraph(ifstream)------------------------------------------------------------
// Description: builds the graph from a text file
// uses insert(int, int) to accomplish
// this function isbased off of graphm.cpp's buildGraph(ifstrea) function
// --------------------------------------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& file) {

	int source = 0; // source node
	int next = 0; // next node
	
	file >> size;
	
	for(int i = 0; i <= size; i++) { // set initial values

		adjList[i].data = new NodeData;
		adjList[i].data->setData(file);
		adjList[i].visited = false;
		adjList[i].edgeHead = NULL;
	}

	for(;;) { // insert

		file >> source >> next; // get values
		
		if(source == 0 || next == 0) // 0 0 stop
			break;	
		
		insert(source, next); // insert
	}		
}// eobuildGraph(ifstream)

// ------------------------------------displayGraph()------------------------------------------------------------------
// Description: displays the graph, including names, and paths
// --------------------------------------------------------------------------------------------------------------------
void GraphL::displayGraph() {

	cout << "Graph:" << endl; // title

	for(int i = 1; i <= size; i++) { // go throught the array

		cout << "Node " << i << "       "; // node number
		cout << *adjList[i].data << endl << endl; // node data
		
		if(adjList[i].edgeHead != NULL)	{ // not NULL
			EdgeNode* current; // node to navigate
			current = adjList[i].edgeHead;
			
			while(current != NULL) { // an edge to go to
				cout << setw(8) << "edge " << i << " " << current->adjGraphNode << endl;
				current = current->nextEdge;
			}
		}
	}
	cout << endl;
} // eodisplayGraph()

// ------------------------------------depthFirstSearch()--------------------------------------------------------------
// Description: displays the graph, including names, and paths
// --------------------------------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch() {

	for(int i = 1; i <= size; i++) { // all nodes not visited
		adjList[i].visited = false;
	}
	
	cout << "Depth-fisrt ordering: "; // title
	
	for(int i = 1; i <= size; i++) { // call a recursive helper
		if(adjList[i].visited == false) // not visited
			dfsRecursively(i); 
	}
	cout << endl << endl;
}// eodepthFirstSearch()

// ------------------------------------dfsRecursively()----------------------------------------------------------------
// Description: displays the graph, including names, and paths
// --------------------------------------------------------------------------------------------------------------------
void GraphL::dfsRecursively(int currentNode) {

	adjList[currentNode].visited = true; // current is visited
	cout << currentNode << " "; // output the node
	
	EdgeNode* current = adjList[currentNode].edgeHead;

	while(current != NULL) { // while not NULL
		if(adjList[current->adjGraphNode].visited == false) // not visited
			dfsRecursively(current->adjGraphNode); 
		current = current->nextEdge; // move current
	}
}// eodfsRecursively()

// ------------------------------------insert(int, int)----------------------------------------------------------------
// Description: inserts a node 
// --------------------------------------------------------------------------------------------------------------------
void GraphL::insert(int source, int next) {

	EdgeNode* newNode = new EdgeNode; // new node
	newNode->adjGraphNode = next; // set the new node
	
	if(adjList[source].edgeHead == NULL) { // equals NULL
		newNode->nextEdge = NULL;
		adjList[source].edgeHead = newNode; // edgehead equals the new node
	}
	else {
		newNode->nextEdge = adjList[source].edgeHead; // next edge equals the edgehead
		adjList[source].edgeHead = newNode;
	}
} // eoinsert(int, int)

// ------------------------------------remove(int)---------------------------------------------------------------------
// Description: removes a node at the given destination
// --------------------------------------------------------------------------------------------------------------------
void GraphL::remove(int node) {

	EdgeNode* temp;
	temp = adjList[node].edgeHead;
	adjList[node].edgeHead = adjList[node].edgeHead->nextEdge;
	
	temp->nextEdge = NULL;
	delete temp;
	temp = NULL;
}// eoremove(int)
