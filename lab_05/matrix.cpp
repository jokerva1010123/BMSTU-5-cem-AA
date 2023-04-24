#include "matrix.hpp"

using namespace std;

matrix_t generate_matrix(int n, int m)
{
    matrix_t matrix;
    matrix.n = n;
    matrix.m = m;
    matrix.matr.resize(n);
    for(int i = 0; i < n; i++)
        matrix.matr[i].resize(m);
    for (int i = 0; i < matrix.n; i++)
        for (int j = 0; j < matrix.m; j++)
            matrix.matr[i][j] = rand() % 90 + 10;
    return matrix;
}

matrix_t change_matrix(matrix_t matrix)
{
    int posi = -1, posj = -1;
    double sum = 1.0, average = 1.0, max_element = matrix.matr[0][0];
    for(int i = 0; i < matrix.n; i++)
        for(int j = 0; j < matrix.m; j++)
            sum *= matrix.matr[i][j];
    average = pow(sum, 1.0/(matrix.n * matrix.m));
    for(int i = 0; i < matrix.n; i++)
        for(int j = 0; j < matrix.m; j++)
        {
            max_element = max(max_element, matrix.matr[i][j]);
            if(matrix.matr[i][j] > average)
            {
                if(posi == -1)
                {
                    posi = i;
                    posj = j;
                }
                else if(matrix.matr[i][j] < matrix.matr[posi][posj])
                {
                    posi = i;
                    posj = j;
                }
            }
        }
    matrix.matr[posi][posj] = max_element;
    return matrix;
}

matrix_t truncate_matrix(matrix_t matrix)
{
    matrix_t tmp_matrix;
    tmp_matrix.n = matrix.m;
    tmp_matrix.m = matrix.n;
    tmp_matrix.matr.resize(tmp_matrix.n);
    for(int i = 0; i < tmp_matrix.n; i++)
        tmp_matrix.matr[i].resize(tmp_matrix.m);
    for (int i = 0; i < tmp_matrix.n; i++)
        for(int j = 0; j < tmp_matrix.m; j++)
            tmp_matrix.matr[i][j] = matrix.matr[j][i];
    return tmp_matrix;
}

matrix_t mul_matrix(matrix_t matrixA, matrix_t matrixB)
{
    matrix_t tmp_matrix;
    tmp_matrix.n = matrixA.n;
    tmp_matrix.m = matrixB.m;
    tmp_matrix.matr.resize(tmp_matrix.n);
    for(int i = 0; i < tmp_matrix.n; i++)
        tmp_matrix.matr[i].resize(tmp_matrix.m);
    for (int i = 0; i < tmp_matrix.n; i++)
        for(int j = 0; j < tmp_matrix.m; j++)
        {
            tmp_matrix.matr[i][j] = 0;
            for(int k = 0; k < matrixA.m; k++)
                tmp_matrix.matr[i][j] = matrixA.matr[i][k] * matrixB.matr[k][j];
        }
    return tmp_matrix;
}