#include <stdio.h>
#include "array.h"

void print_array(sarray cities, char msg[1000])
{
    printf("%s\ncount: %d\n", msg, cities.len);

    for (int i = 0; i < cities.len; i++)
        printf("%d  ", cities.array[i]);
    puts("\n");
}

void add_element(sarray *cities, const int element)
{
    cities->array[cities->len] = element;
    (cities->len)++;
}

int get_element(sarray arr, int const index)
{
    if (index > arr.len)
    {
        return NOTFOUND;
    }

    return arr.array[index];
}

int del_element(sarray *cities, int index)
{
    if (index > cities->len)
    {
        return NOTFOUND;
    }

    int tmp, element = cities->array[index];

    for (int i = index; i < cities->len; i++)
    {
        tmp = cities->array[i];
        cities->array[i] = cities->array[i + 1];
        cities->array[i + 1] = tmp;
    }

    (cities->len)--;

    return element;
}

sarray copy_array(sarray arr)
{
    sarray result;
    result.len = arr.len;

    for (int i = 0; i < arr.len; i++)
        result.array[i] = arr.array[i];

    return result;
}
