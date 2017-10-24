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
					   or equal to 0 or it is not an x (since an x 
					   would cause atoi to return 0 as well, I have
					   to use and && in the if condition) */
					if(adj_mat[i][j] <= 0 && strcmp(temp, "x") != 0)
					{
						printf("Incorrect input, try again\n");
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
	adj_mat[0] = (int *) calloc(num, sizeof(int) * num);
	* size = num;
	free(temp);
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
	int * distSet = malloc(sizeof(int) * size);
	int * visitSet = (int *) calloc(size, sizeof(int) * size);
	int minNode, i, j, minTime;

	distSet[0] = 0;
	for(i = 1; i < size; i++)
		distSet[i] = INT_MAX;
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

	minTime = findMaxTime(distSet, size);
	free(distSet);
	free(visitSet);
	return minTime;
}

int findMinTimeNode(int * distSet, int * visitSet, int size)
{
	int i, minNode, min = INT_MAX;
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
	/*printAdjMatrix(temp, size);*/
	minTime = findMinTime(temp, size);
	printf("The minimum time to get the message across is: %d\n", minTime);
	destroyMatrix(temp, size);
	return 0;
}