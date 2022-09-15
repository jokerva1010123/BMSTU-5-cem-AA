#ifndef _CITY_H_

#define _CITY_H_

#include "define.h"
#include "array.h"

int find_city(char cities[LEN], char city, int *count);

void print_cities(array cities, char city_names[LEN]);

void create_cities_array(array *cities, int const count);

#endif