#ifndef _BRUTE_FORCE_H_

#define _BRUTE_FORCE_H_

#include "define.h"
#include "array.h"

void get_routes(array *cities, array *res_arr, array result[DEPTH_OF_RECURSION], int *count);

array get_shortest_path(array cities, int matrix[LEN][LEN]);

int get_path_cost(array cities, int matrix[LEN][LEN]);

#endif