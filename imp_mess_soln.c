#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int * * getAdjMatrix(int *);
void printAdjMatrix(int * *, int);
void destroyMatrix(int * *, int);
int findMinTime(int * *, int);
int findMinDistNode(int *, int *, int);
int findMaxDist(int *, int);

int * * getAdjMatrix(int * size)
{
	int num, i, j;
	char flag = 1;
	char * temp = malloc(sizeof(char) * 11); /*integer cannot be over 10 digits long*/
	int * * adj_mat;

	do
	{
		printf("Enter number of towns:\n");
		scanf("%s", temp);
		num = atoi(temp);
		if(num <= 0)
		{
			flag = 0;
			printf("Incorrect input, try again\n");
		}
		else
		{
			adj_mat = malloc(sizeof(int *) * (num - 1));
			printf("Enter adjacency matrix:\n");

			for(i = 0; i < (num - 1); i++)
			{
				adj_mat[i] = (int *) calloc((i + 1), sizeof(int) * (i + 1));

				for(j = 0; j <= i; j++)
				{
					scanf("%s", temp);
					adj_mat[i][j] = atoi(temp);

					if(adj_mat[i][j] < 1 && strcmp(temp, "x") != 0)
					{
						printf("Incorrect input, try again\n");
						i = num;
						flag = 0;
						break;
					}
					else if(!strcmp(temp, "x"))
						adj_mat[i][j] = -1;
				}
			}
		}
	} while(!flag);
	* size = num;
	free(temp);
	return adj_mat;
}

void printAdjMatrix(int * * adj_mat, int size)
{
	int i, j;
	for(i = 0; i < (size - 1); i++)
	{
		for(j = 0; j <= i; j++)
		{
			printf("%d, ", adj_mat[i][j]);
		}
		printf("\n");
	}
}

void destroyMatrix(int * * adj_mat, int size)
{
	int i;
	for(i = 0; i < (size - 1); i++)
	{
		free(adj_mat[i]);
	}
	free(adj_mat);
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
		minNode = findMinDistNode(distSet, visitSet, size);
		visitSet[i] = 1;

		for(j = 0; j < size; j++)
		{
			if(!visitSet[j] && adj_mat[minNode][j] > 0 && distSet[minNode] != INT_MAX && 
				(distSet[minNode] + adj_mat[minNode][j]) < distSet[j])
			{
				distSet[j] = distSet[minNode] + adj_mat[minNode][j];
			}
		}
	}

	minTime = findMaxDist(distSet, size);
	free(distSet);
	free(visitSet);
	return minTime;
}

int findMinDistNode(int * distSet, int * visitSet, int size)
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

int findMaxDist(int * distSet, int size)
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
	printf("size is: %d\n", size);
	printAdjMatrix(temp, size);
	minTime = findMinTime(temp, size);
	printf("The minimum time to get the message across is: %d\n", minTime);
	destroyMatrix(temp, size);
	return 0;
}