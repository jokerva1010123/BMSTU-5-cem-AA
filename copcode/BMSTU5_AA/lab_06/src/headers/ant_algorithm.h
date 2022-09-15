#ifndef _ANT_ALGORITHM_h_

#define _ANT_ALGORITHM_h_

#include "define.h"
#include "array.h"

array ant_algorithm(int matrix[LEN][LEN], int count, array cities, int tmax, float p, float alpha, float beta);

int calculate_Q(int matrix[LEN][LEN], int count);

#endif