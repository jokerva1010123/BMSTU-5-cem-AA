#include <vector>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <array>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include<bits/stdc++.h>

using namespace std;

void find_standard(double **matrix, int n, int m, double *max_element, int *posi, int *posj, double average)
{
    *max_element = matrix[0][0];
    *posi = -1;
    *posj = -1;
    for (int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            if (*max_element < matrix[i][j])
                *max_element = matrix[i][j];
            if (matrix[i][j] > average)
                if (*posi == -1)
                {
                    *posi = i;
                    *posj = j;
                }
                else if (matrix[*posi][*posj] > matrix[i][j])
                {
                    *posi = i;
                    *posj = j;
                }
        }
}

void for_parallel(double **matrix, int n, int m, double *max_element, int *posi, int *posj, double average, int st, int en)
{
    for (int i = st; i < en; i++)
        for(int j = 0; j < m; j++)
        {
            if (*max_element < matrix[i][j])
                *max_element = matrix[i][j];
            if (matrix[i][j] > average)
                if (*posi == -1)
                {
                    *posi = i;
                    *posj = j;
                }
                else if (matrix[*posi][*posj] > matrix[i][j])
                {
                    *posi = i;
                    *posj = j;
                }
        }
}

int  find_parallel(double **matrix, int n, int m, double *max_element, int *posi, int *posj, double average, int size)
{
    *posi = -1;
    *posj = -1;
    *max_element = matrix[0][0];
    thread potok[size]; 
    int step = n/size;
    int st = 0, en = step;
    int start = clock(); 
    for (int i = 0; i < size; i++)
    {
        if (i == size - 1)
            en = n;
        potok[i] = thread(for_parallel, matrix, n, m, max_element, posi, posj, average, st, en);
        st = en;
        en += step;
    }
    for (int i = 0; i < size; i++)
        potok[i].join();
    int end2 = clock();
    return end2 - start;
}

void test()
{
    int arr[9] = {50, 100, 200, 300, 500, 750, 1000, 2000, 5000};
    double s = 1, max_element;
    
    
    for (int size = 1; size <= 9; size ++)
    {
        s = 1;
        double *matrix[arr[size]];
        for (int i = 0; i < arr[size]; i++)
        matrix[i] = new double[arr[size]];
        for (int i = 0; i < arr[size]; i++)
            for (int j = 0; j < arr[size]; j++)
            {
                matrix[i][j] = (rand() % 101) + 1;
                s *= matrix[i][j];
            }
        double average = pow(s, (1.0)/(arr[size] * arr[size]));
        int posi, posj;
        int start = clock();
        for (int i = 0; i < 200; i++)
            find_standard(matrix, arr[size], arr[size], &max_element, &posi, &posj, average);
        int end = clock();
        cout << "Run without parallel: " << 1.0*(end - start)/200 << '\n';
    
        double x = 0;
        cout << "Run parallel with " << arr[size] << " potok" << ": ";
        for (int i = 0; i < 200; i++)
            x += find_parallel(matrix, arr[size], arr[size], &max_element, &posi, &posj, average, 32);
        cout << x/200 << '\n';
    }
}

int main()
{
    srand(time(0));
    /*int n, m;
    cout << "Input size of matrix(n x m): ";
    cin >> n >> m;

    double *matrix[n];
    for (int i = 0; i < n ; i++)
        matrix[i] = new double[m];
    
    cout << "Input " << n << " rows of matrix\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> matrix[i][j];

    double s = 1, max_element;

    for (int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            s *= matrix[i][j];
        
    if (s < 0 && (m * n % 2 == 0))
    {
        cout << "Can't find average of matrix\n";
        return 0;
    }

    double average = pow(s, 1.0/(m * n));
    int special_posi, special_posj;
    int size = 4;
    find_standard(matrix, n, m, &max_element, &special_posi, &special_posj, average);
    find_parallel(matrix, n, m, &max_element, &special_posi, &special_posj, average, size);

    if (special_posi == -1)
    {
        cout << "Can't find number greater than average of matrix\n";
        exit(0);
    }

    matrix[special_posi][special_posj] = max_element;

    for (int i = 0; i < n; i++, cout << "\n")
        for(int j = 0; j < m; j++)
            cout << matrix[i][j] << ' ';

    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);*/
    test();
    return 0;
}