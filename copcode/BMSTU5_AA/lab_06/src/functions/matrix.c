#include <stdio.h>

#include "matrix.h"
#include "colors.h"

void print_matrix(int matrix[LEN][LEN], int const count)
{
	// printf("count: %d\n  ", count);

	blue();
	for (int i = 0; i < count; i++)
		printf("%d\t", i);
	puts("");

	for (int i = 0; i < count; i++)
	{
		printf("%d ", i);
		for (int j = 0; j < count; j++)
			printf("%d\t", matrix[i][j]);
		puts("");
	}
	puts("");
}

void fill_matrix(float matrix[LEN][LEN], int count, float num)
{
	for (int i = 0; i < count; i++)
		for (int j = 0; j < i; j++)
			matrix[i][j] = matrix[j][i] = num;
}