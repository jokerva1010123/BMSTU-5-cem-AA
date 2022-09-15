#include <stdio.h>

#include "brute_force.h"

#include "matrix.h"
#include "city.h"
#include "array.h"

int get_path_cost(array cities, int matrix[LEN][LEN])
{
	int cost = 0;

	for (int i = 0; i < cities.count - 1; i++)
		cost += matrix[cities.arr[i]][cities.arr[i + 1]];

	return cost;
}

array get_shortest_path(array cities, int matrix[LEN][LEN])
{
	array result[DEPTH_OF_RECURSION];
	array res_arr;

	int min_cost;
	int curr_cost;
	int index = 0;

	int routes_count = 0;

	// Добавляем первый элемент в res_arr -
	// Это будет начальной точкой.
	del_elem(&cities, 0);
	add_elem(&res_arr, 0);
	get_routes(&cities, &res_arr, result, &routes_count);

	min_cost = get_path_cost(result[index], matrix);
	// printf("min_cost = %d\n", min_cost);
	// print_array(result[0], "RESULT");
	for (int i = 1; i < routes_count; i++)
	{
		curr_cost = get_path_cost(result[i], matrix);
		// printf("curr_cost = %d\n", curr_cost);
		// print_array(result[i], "RESULT");
		if (curr_cost < min_cost)
		{
			min_cost = curr_cost;
			index = i;
		}
	}

	// printf("min_cost = %d\n", min_cost);
	// print_array(result[index], "Наименьший путь");
	return result[index];
}

void get_routes(array *cities, array *res_arr, array result[DEPTH_OF_RECURSION], int *count)
{
	int elem;
	array tmp;

	if (!cities->count)
	{
		// Добавляем в конец первый элемент.
		add_elem(res_arr, get_elem(*res_arr, 0));
		result[*count] = *res_arr;
		(*count)++;
		del_elem(res_arr, res_arr->count - 1);

		// print_array(*cities, "cities");
		// print_array(*res_arr, "res_arr");
		// printf("count = %d\n\n", *count);
	}

	for (int i = 0; i < cities->count; i++)
	{
		elem = get_elem(*cities, i);
		// printf("elem: %d \n", elem);
		add_elem(res_arr, elem);

		tmp = copy_arr(*cities);
		del_elem(&tmp, i);

		get_routes(&tmp, res_arr, result, count);

		// print_array(*res_arr, "res_arr");
		// print_array(tmp, "tmp");

		del_elem(res_arr, res_arr->count - 1);
	}
}