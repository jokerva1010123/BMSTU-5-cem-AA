#include <stdio.h>

#include "ant_algorithm.h"
#include "brute_force.h"
#include "matrix.h"
#include "array.h"
#include "ant.h"

#include "colors.h"

int calculate_Q(int matrix[LEN][LEN], int count)
{
	int Q = 0;

	for (int i = 0; i < count; i++)
		for (int j = 0; j < i; j++)
			Q += matrix[i][j];

	return Q * 2;
}

void add_pheromones(int matrix[LEN][LEN], float matrix_pheromones[LEN][LEN], int count, int Q, ant ants[ANTS_MAX_COUNT])
{
	int city_first, city_second;
	int curr_cost;
	float delta_tao = 0;

	// Цикл по всем муравьям.
	// Вычисляем delta_tao.
	for (int i = 0; i < count; i++)
	{
		curr_cost = get_path_cost(ants[i].way, matrix);

		delta_tao += (float)Q / curr_cost;

		// printf("Q = %d; curr_cost = %d; delta_tao = %f\n", Q, curr_cost, delta_tao);
	}

	// Цикл по всем муравьям.
	for (int i = 0; i < count; i++)
	{
		// Обновляем все форомоны у пути, который прошел i-ый муравей.
		// (Не забываем про то, что матрица семметричная)
		for (int j = 0; j < ants[i].way.count - 1; j++)
		{
			city_first = ants[i].way.arr[j];
			city_second = ants[i].way.arr[j + 1];
			// printf("От %d К %d\n", city_first, city_second);
			matrix_pheromones[city_first][city_second] = matrix_pheromones[city_first][city_second] + delta_tao;
			matrix_pheromones[city_second][city_first] = matrix_pheromones[city_second][city_first] + delta_tao;
		}
		// printf("\n");
	}
}

void correct_pheromones(float matrix_pheromones[LEN][LEN], int count)
{
	for (int i = 0; i < count; i++)
		for (int j = 0; j < i; j++)
			if (matrix_pheromones[i][j] <= 0.1)
				matrix_pheromones[i][j] = matrix_pheromones[j][i] = 0.1;
}

void evaporation(float matrix_pheromones[LEN][LEN], int count, float p)
{
	float tmp = 1 - p;
	for (int i = 0; i < count; i++)
		for (int j = 0; j < i; j++)
		{
			matrix_pheromones[i][j] = tmp * matrix_pheromones[i][j];
			matrix_pheromones[j][i] = tmp * matrix_pheromones[j][i];
		}
}

void print_matrix_pheromones(float matrix_pheromones[LEN][LEN], int count)
{
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
			printf("%f ", matrix_pheromones[i][j]);
		printf("\n");
	}
}

array ant_algorithm(int matrix[LEN][LEN], int count, array cities, int tmax, float p, float alpha, float beta)
{
	// printf("tmax = %d, p = %f alpha = %f, beta = %f\n", tmax, p, alpha, beta);

	int Q = calculate_Q(matrix, count);
	// printf("Q = %d\n", Q);

	array best_way = copy_arr(cities);
	add_elem(&best_way, get_elem(best_way, 0));
	// print_array(best_way, "Начальное best_way");

	int best_cost = get_path_cost(best_way, matrix);
	int curr_cost = 0;
	// printf("best_cost = %d\n", best_cost);

	float matrix_pheromones[LEN][LEN];
	fill_matrix(matrix_pheromones, count, PHEROMONE_MIN);

	ant ants[ANTS_MAX_COUNT];

	// generate_ants_array(ants, count);
	// print_ants(ants, count);
	// for (int i = 0; i < count - 1; i++)
	// 	ants_choose_way(ants, matrix_pheromones, matrix, count, alpha, beta);

	// for (int i = 0; i < count; i++)
	// 	add_elem(&ants[i].way, get_elem(ants[i].way, 0));

	// print_ants(ants, count);

	// red();
	// print_matrix_pheromones(matrix_pheromones, count);
	// evaporation(matrix_pheromones, count, p);
	// printf("\n\n\n");
	// print_matrix_pheromones(matrix_pheromones, count);

	// add_pheromones(matrix, matrix_pheromones, count, Q, ants);

	// print_matrix_pheromones(matrix_pheromones, count);

	// Цикл по дням.
	for (int t = 0; t < tmax; t++)
	{
		// Муравьев столько же, сколько и городов.
		// Поэтому кол-во == count.
		generate_ants_array(ants, count);

		// print_ants(ants, count);

		// Цикл по городам.
		// Один город не учитываем,
		// потому что мы с него начали.
		for (int i = 0; i < count - 1; i++)
		{
			// print_ants(ants, count);

			// Муравьи выбирают путь.
			ants_choose_way(ants, matrix_pheromones, matrix, count, alpha, beta);
		}

		// Добавляем последний город.
		// (Муравей должен вернуться в начальный город).
		for (int i = 0; i < count; i++)
			add_elem(&ants[i].way, get_elem(ants[i].way, 0));

		// print_ants(ants, count);

		// Ищем минимальный путь.
		for (int i = 0; i < count; i++)
		{
			curr_cost = get_path_cost(ants[i].way, matrix);
			if (curr_cost < best_cost)
			{
				best_cost = curr_cost;
				best_way = copy_arr(ants[i].way);

				// red();
				// printf("curr_cost = %d best_cost = %d\n", curr_cost, best_cost);
				// print_array(best_way, "best_way");
			}
		}

		evaporation(matrix_pheromones, count, p);
		add_pheromones(matrix, matrix_pheromones, count, Q, ants);
		correct_pheromones(matrix_pheromones, count);
	}

	return best_way;
}