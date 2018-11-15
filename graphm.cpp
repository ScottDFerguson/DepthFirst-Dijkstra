// ------------------------------------------------ graphm.cpp --------------------------------------------------------
// Scott Ferguson CSS 343
// 11-1-2015
// 11-12-2015
// --------------------------------------------------------------------------------------------------------------------
// Purpose - To provide the functions for grahm.h. This program is designed to implament Dijkstra's algorithm
// --------------------------------------------------------------------------------------------------------------------
// Assumptions-text file will be in the correct format
// Only integers will be used as nodes
// if there exists a node that has no node to connect to is has a weight of infinity
// --------------------------------------------------------------------------------------------------------------------

#include "graphm.h"
#include <climits>
#include <iomanip>

// --------------------------------------------------------------------------------------------------------------------

// ------------------------------------GraphM()------------------------------------------------------------------------
// Description: Constructor for the object
// Creates new object with size 0, and sets the Tables to essentially null
// --------------------------------------------------------------------------------------------------------------------
GraphM::GraphM():size(0) {

   for (int i = 1; i < MAXNODES; i++) {

      for(int j = 1; j < MAXNODES; j++) {

         T[i][j].visited = false;
         T[i][j].dist = INT_MAX; 
         T[i][j].path = 0;

         C[i][j] = INT_MAX;
      }
   }
} // eoGraphM()


// ------------------------------------buildGraph(ifstream)------------------------------------------------------------
// Description: builds the graph from a text file
// uses insertEdge(int, int, int) to accomplish 
// --------------------------------------------------------------------------------------------------------------------
void GraphM::buildGraph(ifstream& file) {   

   int source = 0; // starting node
   int next = 0; // connecting node
   int cost = 0; // cost of the connection

   file >> size; // how large the data is

   if (size > 0) {   // crash catch
      for(int i = 0; i <= size; i++) { // go through all of the data

         data[i].setData(file); // assign to nodeData's data
      }

      for (;;) { // keep going until break

         file >> source >> next >> cost; // insert to correct variables

         if (file.eof()) break; // no more lines of data, empty file protection

         if (source == 0 || next == 0 || cost == 0) // no more input
            break;  

         insertEdge(source, next, cost); // insert the edge with the collected data
      }
   }
} // eobuildGraph(ifstream)

// ------------------------------------insertEdge(int, int, int)-------------------------------------------------------
// Description: inserts an edge between two nodes
// --------------------------------------------------------------------------------------------------------------------
void GraphM::insertEdge(const int from, const int to, const int cost) {

   if (from >= 1 && from <= size && to >= 1 && to <= size && cost >= 0 && cost <= INT_MAX) { // crash protection
      C[from][to] = cost; // insert cost into the cost table
   }
} // eoinsertEdge(int, int, int)

// ------------------------------------removeEdge(int, int)------------------------------------------------------------
// Description: removes an edge from one node to another
// --------------------------------------------------------------------------------------------------------------------
void GraphM::removeEdge(const int from,const int to) {

   // if statement to check for valid source and destination
   if(from >= 1 && from <= size && to >= 1 && to <= size)
      if(C[from][to] < INT_MAX)
         C[from][to] = INT_MAX;
} // eoremoveEdge(int, int)

// ------------------------------------findShortestPath()--------------------------------------------------------------
// Description: finds the shortest path from one node to another
// the foundation for this method was taken from the assignment description
// --------------------------------------------------------------------------------------------------------------------
void GraphM::findShortestPath() {

   for(int source = 1; source <= size; source++) {
      T[source][source].dist = 0;

      for(int i = 1; i <= size; i++) {
    
         int v = 0;
         int min = INT_MAX;

         for(int i = 1; i <= size; i++) {

            if(T[source][i].dist < min && T[source][i].visited == false) {
               min = T[source][i].dist;
               v = i;
            }
         }
         
         if(v == 0) 
            break;

         T[source][v].visited = true;
         
         for(int w = 1; w <= size; w++){

            if(C[v][w] < INT_MAX && T[source][w].visited == false){
               if(T[source][w].dist > (T[source][v].dist + C[v][w]))
               {
                  T[source][w].dist = T[source][v].dist + C[v][w];
                  T[source][w].path = v;
               }   
            }
         }              
      }
   }
} // eofindShortestPath()

// ------------------------------------displayAll()--------------------------------------------------------------------
// Description: prints out all nodes, their weight, and connecting nodes
// --------------------------------------------------------------------------------------------------------------------
void GraphM::displayAll() const {

   cout << "Description         From node   To node   Dijkstra's     Path" << endl; // title
   
   for(int i = 1; i <= size; i++) { // go through the whole table
      cout << data[i] << endl << endl;
      
      for(int j = 1; j <= size; j++) {

         if(i != j) {
            cout << setw(25) << i << setw(11) << j; // spacing
            if(T[i][j].dist != INT_MAX) { // not infinity
               cout << setw(9) << T[i][j].dist;
               cout << setw(13);
               getPathRecursively(i, j);
            }
            else 
               cout << setw(9) << "----";
            cout << endl;
         }
      }
   }
   cout << endl;
}// eodisplayAll()

// ------------------------------------display(int, int)---------------------------------------------------------------
// Description: displays the path from one node to another
// by calling two recursive functions
// --------------------------------------------------------------------------------------------------------------------
void GraphM::display(const int from,const int to) const {

   cout << setw(5) << from << setw(10) << to << setw(10); // title

   if(T[from][to].dist  != INT_MAX) { // not infinity
      cout << T[from][to].dist; // distence
      cout << setw(13);
      getPathRecursively(from, to); // call recursive function
      cout << endl;
      getDataRecursively(from, to); // call recursive function
      cout << endl << endl;
   }
   else 
      cout << "----" << endl << endl;
}// eodisplay(int, int)

// ------------------------------------getPathRecursively(int, int)----------------------------------------------------
// Description: gets the path from one node to another
// --------------------------------------------------------------------------------------------------------------------
void GraphM::getPathRecursively(const int from, const int to) const {

   if (from != to) { // nodes are not the same
      if (T[from][to].path != 0){ // weight is not 0
        getPathRecursively(from, T[from][to].path); // use recursion to go back
      }
   }
   cout << to << " "; // print out
} // eogetPathRecursively(int, int)

// ------------------------------------getPathData(int, int)-----------------------------------------------------------
// Description: gets the data from one node to another
// --------------------------------------------------------------------------------------------------------------------
void GraphM::getDataRecursively(const int from, const int to) const {

   if (from != to) { // nodes are not the same
      if (T[from][to].path != 0) {
        getDataRecursively(from, T[from][to].path); // use recursion to go back
      }
   }
   cout << data[T[from][to].path] << endl; // print out the path
} // eogetPathData(int, int)
