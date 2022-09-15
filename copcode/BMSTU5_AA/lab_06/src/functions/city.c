#include <stdio.h>

#include "city.h"
#include "colors.h"

void print_cities(array cities, char city_names[LEN])
{
	green();
	printf("count: %d\n", cities.count);
	for (int i = 0; i < cities.count; i++)
		printf("%d: %c\t", cities.arr[i], city_names[cities.arr[i]]);
	puts("\n");
}

void create_cities_array(array *cities, int const count)
{
	cities->count = count;
	for (int i = 0; i < count; i++)
		cities->arr[i] = i;
}

int find_city(char cities[LEN], char city, int *count)
{
	int i = 0;
	while (i < *count)
	{
		if (city == cities[i])
			return i;
		i++;
	}
	cities[i] = city;
	(*count)++;
	return i;
}