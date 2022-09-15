#include <stdio.h>

#include "array.h"
#include "colors.h"

void print_array(array cities, char msg[MSG_LEN])
{
	green();
	printf("%s\ncount: %d\n", msg, cities.count);
	yellow();
	for (int i = 0; i < cities.count; i++)
		printf("%d  ", cities.arr[i]);
	puts("\n");
	blue();
}

void add_elem(array *cities, const int elem)
{
	cities->arr[cities->count] = elem;
	(cities->count)++;
}

int get_elem(array array, int const index)
{
	if (index > array.count)
		return NOT_FOUND;

	return array.arr[index];
}

int del_elem(array *array, int const index)
{
	if (index > array->count)
		return NOT_FOUND;

	int tmp, elem = array->arr[index];

	for (int i = index; i < array->count; i++)
	{
		tmp = array->arr[i];
		array->arr[i] = array->arr[i + 1];
		array->arr[i + 1] = tmp;
	}

	(array->count)--;

	return elem;
}

array copy_arr(array arr)
{
	array result;
	result.count = arr.count;

	for (int i = 0; i < arr.count; i++)
		result.arr[i] = arr.arr[i];

	return result;
}

// int i = 0, tmp, del_elem;

// while ((i < array->count) && !(array->arr[i] == elem))
// 	i++;

// if (array->count == i)
// 	return NOT_FOUND;

// del_elem = array->arr[i];
// // printf("count: %d i: %d\n", array->count, i);
// for (; i < array->count; i++)
// {
// 	tmp = array->arr[i];
// 	array->arr[i] = array->arr[i + 1];
// 	array->arr[i + 1] = tmp;
// }

// (array->count)--;

// return del_elem;