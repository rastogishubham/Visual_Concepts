#include <stdio.h>
#include <stdlib.h>
#include "imp_mess_soln.h"

int * * getAdjMatrix(int * size)
{
	int num, i, j;
	char flag = 1;

	/* integer cannot be over 10 digits long
	   temp is used to store the string input
	   from the user for error checking */
	char * temp = malloc(sizeof(char) * 11);
	int * * adj_mat;
	/* A do while loop is used to accept input
	   till the input is correct */
	do
	{
		printf("Enter number of towns:\n");
		scanf("%s", temp);
		num = atoi(temp);
		/* If the value of atoi is 0 then it can be an ivalid input,
		   if the number entered is 0 or less than 0, that is invalid
		   as well */
		if(num <= 0)
		{
			flag = 0;
			printf("Incorrect input, try again\n");
		}
		else
		{
			adj_mat = malloc(sizeof(int *) * num);
			printf("Enter adjacency matrix:\n");

			for(i = 1; i < num; i++)
			{
				/* calloc is used to set every index to zero, this
				   is advantageous because the time from one city
				   to itself has to be zero */
				adj_mat[i] = (int *) calloc(num, sizeof(int) * num);

				for(j = 0; j < i; j++)
				{
					scanf("%s", temp);
					adj_mat[i][j] = atoi(temp);

					/* If the user inputs a number which is less than
					   or equal to 0 or it is not an x, since we use
					   the same variable to input numbers or 'x' atoi
					   will return a 0 if x is entered, hence && is
					   used in the if condition */
					if(adj_mat[i][j] <= 0 && strcmp(temp, "x") != 0)
					{
						printf("Incorrect input, try again\n");
						/* To break out of outer for loop */
						i = num;
						flag = 0;
						break;
					}
					/* if the user enters x, then the adjacency matrix
					   uses -1 to represent that a message cannot travel
					   between those two cities */
					else if(!strcmp(temp, "x"))
						adj_mat[i][j] = -1;
				}
			}
		}
	} while(!flag);

	/* The first row of the adjacency matrix is not never
	   entered by the user so it is just allocated here 
	   instead */
	adj_mat[0] = (int *) calloc(num, sizeof(int) * num);
	* size = num;
	free(temp);

	/* This function call completes the upper 
	   triangle of the adjacency matrix */
	adj_mat = completeAdjMatrix(adj_mat, num);
	return adj_mat;
}

void printAdjMatrix(int * * adj_mat, int size)
{
	int i, j;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			printf("%d, ", adj_mat[i][j]);
		}
		printf("\n");
	}
}

void destroyMatrix(int * * adj_mat, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		free(adj_mat[i]);
	}
	free(adj_mat);
}

int * * completeAdjMatrix(int * * adj_mat, int size)
{
	int i, j;

	/* Simple loop is used to fill the upper triangle
	   which is easy as time from city x to city y is
	   the same as time from city y to city x */
	for(i = 0; i < size; i++)
	{
		for(j = (size - 1); j > i; j--)
		{
			adj_mat[i][j] = adj_mat[j][i];
		}
	}
	return adj_mat;
}

int findMinTime(int * * adj_mat, int size)
{
	/* This is the distance set, that will
	   contain the distance from the source
	   node (capitol city) to every other
	   node in the empire. distSet[i] is the
	   distance from capitol city to city i+1 */
	int * distSet = malloc(sizeof(int) * size);

	/* This is the visited set, it contains the set of all
	   nodes visited during the shortest path calculation.
	   visitSet[i] will be 1 if the node has been visited
	   else it will be 0, hence the use of calloc */
	int * visitSet = (int *) calloc(size, sizeof(int) * size);
	int minNode, i, j, minTime;

	/* Distance from source node
	   to itself is 0 */
	distSet[0] = 0;

	/* Here a simple loop is being used 
	   to assign the distance from the
	   source node to every other node
	   as infinity or INT_MAX in our
	   case */
	for(i = 1; i < size; i++)
		distSet[i] = INT_MAX;
	
	/* We visit the closest node that has not been visited
	   update the distance of the the nodes adjacent to it
	   if the distance is lower than the distance in the 
	   distance set */
	for(i = 0; i < (size - 1); i++)
	{
		minNode = findMinTimeNode(distSet, visitSet, size);
		visitSet[minNode] = 1;

		for(j = 0; j < size; j++)
		{
			if(!visitSet[j] && adj_mat[minNode][j] > 0 && distSet[minNode] != INT_MAX && 
				(distSet[minNode] + adj_mat[minNode][j]) < distSet[j])
			{
				distSet[j] = distSet[minNode] + adj_mat[minNode][j];
			}
		}
	}

	/* The minimum time taken for the message
	   to reach every city is the maximum in
	   the distance set */
	minTime = findMaxTime(distSet, size);
	free(distSet);
	free(visitSet);
	return minTime;
}

int findMinTimeNode(int * distSet, int * visitSet, int size)
{
	int i, minNode, min = INT_MAX;
	
	/* To find the city to visit next,
	   we have to see if we have not
	   visited it next and if it has
	   not yet been visited */
	for(i = 0; i < size; i++)
	{
		if(!visitSet[i] && distSet[i] < min)
		{
			minNode = i;
			min = distSet[i];
		}
	}
	return minNode;
}

int findMaxTime(int * distSet, int size)
{
	int i, max = INT_MIN;
	for(i = 0; i < size; i++)
	{
		if(distSet[i] > max)
			max = distSet[i];
	}
	return max;
}

int main(int argc, char * * argv)
{
	int size, minTime;
	int * * temp = getAdjMatrix(&size);
	minTime = findMinTime(temp, size);
	printf("The minimum time to get the message across is: %d\n", minTime);
	destroyMatrix(temp, size);
	return 0;
}