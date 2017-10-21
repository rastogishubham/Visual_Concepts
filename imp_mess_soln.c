#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * * getAdjMatrix(int *);
void printAdjMatrix(int * *, int);
void destroyMatrix(int * *, int);

int * * getAdjMatrix(int * size)
{
	int num, i, j;
	char flag = 1;
	char * temp = malloc(sizeof(char) * 10); /*integer cannot be over 10 digits long*/
	int * * adj_mat;

	do
	{
		printf("Enter number of towns:\n");
		scanf("%s", temp);
		num = atoi(temp);
		printf("num is: %d\n", num);
		if(num <= 0)
		{
			flag = 0;
			printf("Incorrect input, try again\n");
		}
		else
		{
			adj_mat = malloc(sizeof(int *) * (num));
			printf("Enter adjacency matrix:\n");

			for(i = 1; i < num; i++)
			{
				adj_mat[i] = malloc(sizeof(int) * num);

				for(j = 0; j < i; j++)
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
	adj_mat[0] = malloc(sizeof(int) * num);
	* size = num;
	free(temp);
	return adj_mat;
}

void printAdjMatrix(int * * adj_mat, int size)
{
	int i, j;
	for(i = 1; i < size; i++)
	{
		for(j = 0; j < i; j++)
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

int main(int argc, char * * argv)
{
	int size;
	int * * temp = getAdjMatrix(&size);
	printf("size is: %d\n", size);
	printAdjMatrix(temp, size);
	destroyMatrix(temp, size);
	return 0;
}