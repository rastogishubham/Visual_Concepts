#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* Amount of time taken for solution: 4 hours (includes testing and commenting)*/

/* The algorithm considered for this solution was an implementation of dijkstra's
   algorithm to find the shortest path from a node (capitol city) to every other
   node in the graph (represented by the adjacency matrix). The algorithm uses 
   two sets (which are represented by two arrays) the distance set and the 
   visited set. The distance set contains the distance from the source node to 
   every other node in the graph. As we know that the distance (or time for our
   example) for a message to go from a town to itself is 0. The distance of the
   source node from the source node is set to 0, the rest of the distance is set
   to infinity (which is represented by INT_MAX in our case). Our visited set is
   initially empty. We then visit the node which is the closest and has not been
   visited yet. Which would be capitol city. Then we add capitol city to the 
   visited set and update the distance from it, to every city it is directly
   connected to, only if the distance we calculated is less than the distance in
   the distance set. We then repeat this process till we have visited all the
   nodes. At the end, we get the shortest distance (or time) from the source node
   to every other node. If we find the maximum from all of these, we will get the
   minimum time the message takes to reach every city in the empire. */

/* This function returns the lower triangular portion 
   of the Adjacency matrix entered by the user */
int * * getAdjMatrix(int *);

/* This function is used for testing purposes only,
   it prints the adjacency matrix entered by the user */
void printAdjMatrix(int * *, int);

/* This function is used to free all the allocated memory
   for the the adjacency matrix */
void destroyMatrix(int * *, int);

/* This function is used to complete the upper triangular
   portion of the adjacency matrix and returns the
   completed matrix */
int * * completeAdjMatrix(int * *, int);

/* This function returns the minimum time the message
   from capitol city is received to every city in the 
   empire. It uses dijkstra's algorithm to find the 
   smallest path from the source node (capitol city)
   to every other city in the empire. */
int findMinTime(int * *, int);

/* This function returns next node to be visited in the 
   graph represented by the adjacency matrix. This is 
   required for the algorithm to find the shortest path
   to all cities in the empire. */
int findMinTimeNode(int *, int *, int);

/* This function returns the maximum time from the 
   distance set. Therefore it returns the minimum
   time it will take for all cities to receive the
   message*/
int findMaxTime(int *, int);