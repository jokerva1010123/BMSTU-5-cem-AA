#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "colors.h"
#include "array.h"
#include "ant.h"

void generate_ants_array(ant ants[ANTS_MAX_COUNT], int count)
{
	int elem;
	// count - кол-во муравьев.
	for (int i = 0; i < count; i++)
	{
		ants[i].way.count = 0;
		ants[i].route.count = 0;
		elem = rand() % count;
		add_elem(&(ants[i].way), elem);
		for (int j = 0; j < count; j++)
		{
			if (j == elem)
				continue;
			add_elem(&(ants[i].route), j);
		}
	}
}

void choice_next_city(ant *ants, float matrix_pheromones[LEN][LEN], int matrix[LEN][LEN], float alpha, float beta)
{
	// print_array(ants->route, "До Curr ants.route");
	// print_array(ants->way, "До Curr ants.way");

	// printf("alpha = %f, beta = %f\n", alpha, beta);
	float numerator = 0;
	float denominator = 0;

	float tao, reverse_cost;
	int cost;

	int city_curr = ants->way.arr[ants->way.count - 1];
	// printf("city_curr = %d\n", city_curr);
	// Считаем знаменатель (сумму).
	for (int i = 0; i < ants->route.count; i++)
	{
		// Стоимость из текущего города в каждый из доступных.
		cost = matrix[city_curr][ants->route.arr[i]];
		tao = matrix_pheromones[city_curr][ants->route.arr[i]];

		if (!cost)
			continue;

		reverse_cost = 1.0 / cost;

		denominator += powf(tao, alpha) + powf(reverse_cost, beta);
		// printf("denominator = %f\n", denominator);
	}

	float p_array[LEN] = {0};
	float sum = 0;
	// Считаем вероятности пойти во все доступные города.
	for (int i = 0; i < ants->route.count; i++)
	{
		cost = matrix[city_curr][ants->route.arr[i]];
		tao = matrix_pheromones[city_curr][ants->route.arr[i]];

		// if (!cost)
		// 	continue;

		reverse_cost = 1.0 / cost;

		p_array[i] = (powf(tao, alpha) + powf(reverse_cost, beta)) / denominator;
		// sum += p_array[i];

		// printf("sum = %f p_array[%d] = %f\n", sum, i, p_array[i]);
	}

	// Если разделить случайное число,
	// преобразованное к вещественному типу,
	// которое выдала функция rand(),
	// на значение константы RAND_MAX,
	// то получится вещественное случайное число от 0 до 1.
	float x = (float)rand() / RAND_MAX;
	// printf("x = %f\n", x);
	int index = 0;
	while (x >= 0)
	{
		x -= p_array[index];
		index++;
		// printf("x = %f\n", x);
	}
	// printf("index = %d\n", index);

	add_elem(&ants->way, get_elem(ants->route, index - 1));
	del_elem(&ants->route, index - 1);

	// print_array(ants->route, "После ants.route");
	// print_array(ants->way, "После ants.way");
}

// TODO: Учитывать тут, что матрица симметричная?
void ants_choose_way(ant ants[ANTS_MAX_COUNT], float matrix_pheromones[LEN][LEN], int matrix[LEN][LEN], int count, float alpha, float beta)
{
	// Проход по всем муравьям.
	for (int i = 0; i < count; i++)
		choice_next_city(&ants[i], matrix_pheromones, matrix, alpha, beta);
}

void print_ants(ant ants[ANTS_MAX_COUNT], int count)
{
	red();
	// printf("ants count = %d\n", count);
	green();
	for (int i = 0; i < count; i++)
	{
		print_array(ants[i].way, "ants[i].way");
		print_array(ants[i].route, "ants[i].route");
	}
}