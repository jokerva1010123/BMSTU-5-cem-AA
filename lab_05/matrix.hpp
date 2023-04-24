#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <bits/stdc++.h>

using namespace std;

struct matrix{
    std::vector<vector<double>> matr;
    int n, m;
};

using matrix_t = struct matrix;

struct matrix_state
{
    bool stage_1;
    bool stage_2;
    bool stage_3;
};

using matrix_state_t = struct matrix_state;

matrix_t generate_matrix(int n, int m);
matrix_t change_matrix(matrix_t matrix);
matrix_t truncate_matrix(matrix_t matrix);
matrix_t mul_matrix(matrix_t matrixA, matrix_t matrixB);

#endif