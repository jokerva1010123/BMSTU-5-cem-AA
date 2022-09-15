#ifndef _ANT_

#define _ANT_

#include "define.h"
#include "array.h"

typedef struct
{
	// Пройденный муравьем путь.
	// Т.е. список вершин, которые
	// муравей уже посетил.
	array way;
	// Маршрут.
	// Т.е. список вершин, которые
	// Муравей должен посетить.
	array route;
	// int cost;
} ant;

void ants_choose_way(ant ants[ANTS_MAX_COUNT], float matrix_pheromones[LEN][LEN], int matrix[LEN][LEN], int count, float alpha, float beta);

void generate_ants_array(ant ants[ANTS_MAX_COUNT], int count);

void print_ants(ant ants[ANTS_MAX_COUNT], int count);

#endif