#ifndef _ARRAY_H_

#define _ARRAY_H_

#include "define.h"

typedef struct
{
	int count;
	int arr[LEN];
} array;

void print_array(array cities, char msg[MSG_LEN]);

void add_elem(array *cities, const int elem);

int get_elem(array array, int const index);

int del_elem(array *array, int elem);

array copy_arr(array arr);

#endif