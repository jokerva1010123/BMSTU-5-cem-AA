#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <time.h>
#include <thread>

//Возвращает матрицу matrix без row-ой строки и col-того столбца, результат в newMatrix
void getMatrixWithoutRowAndCol(int **matrix, int size, int row, int col, int **newMatrix)
{
    int offsetRow = 0; //Смещение индекса строки в матрице
    int offsetCol = 0; //Смещение индекса столбца в матрице
    for(int i = 0; i < size-1; i++)
    {
        //Пропустить row-ую строку
        if(i == row)
        {
            offsetRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
        }

        offsetCol = 0; //Обнулить смещение столбца
        for(int j = 0; j < size-1; j++)
        {
            //Пропустить col-ый столбец
            if(j == col)
            {
                offsetCol = 1; //Встретили нужный столбец, проускаем его смещением
            }

            newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
        }
    }
}

//Вычисление определителя матрицы разложение по первой строке
int matrixDettime(int **matrix, int size)
{
    time_t startt, endt;
    int det = 0;
    int degree = 1; // (-1)^(1+j) из формулы определителя
    startt = clock();
    //Условие выхода из рекурсии
    if(size == 1)
    {
        return matrix[0][0];
    }
        //Условие выхода из рекурсии
    else if(size == 2)
    {
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    }
    else
    {
        //Матрица без строки и столбца
        int **newMatrix = new int*[size-1];
        for(int i = 0; i < size-1; i++)
        {
            newMatrix[i] = new int[size-1];
        }

        //Раскладываем по 0-ой строке, цикл бежит по столбцам
        for(int j = 0; j < size; j++)
        {
            //Удалить из матрицы i-ю строку и j-ый столбец
            //Результат в newMatrix
            getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

            //Рекурсивный вызов
            //По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть сумма из формулы)
            //где minor_j - дополнительный минор элемента matrix[0][j]
            // (напомню, что минор это определитель матрицы без 0-ой строки и j-го столбца)
            det = det + (degree * matrix[0][j] * matrixDettime(newMatrix, size-1));
            //"Накручиваем" степень множителя
            degree = -degree;
        }

        //Чистим память на каждом шаге рекурсии(важно!)
        for(int i = 0; i < size-1; i++)
        {
            delete [] newMatrix[i];
        }
        delete [] newMatrix;
    }

    endt = clock();
    return endt - startt;
}

int matrixDet(int **matrix, int size)
{
    int det = 0;
    int degree = 1; // (-1)^(1+j) из формулы определителя
    //Условие выхода из рекурсии
    if(size == 1)
    {
        return matrix[0][0];
    }
        //Условие выхода из рекурсии
    else if(size == 2)
    {
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    }
    else
    {
        //Матрица без строки и столбца
        int **newMatrix = new int*[size-1];
        for(int i = 0; i < size-1; i++)
        {
            newMatrix[i] = new int[size-1];
        }

        //Раскладываем по 0-ой строке, цикл бежит по столбцам
        for(int j = 0; j < size; j++)
        {
            //Удалить из матрицы i-ю строку и j-ый столбец
            //Результат в newMatrix
            getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

            //Рекурсивный вызов
            //По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть сумма из формулы)
            //где minor_j - дополнительный минор элемента matrix[0][j]
            // (напомню, что минор это определитель матрицы без 0-ой строки и j-го столбца)
            det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size-1));
            //"Накручиваем" степень множителя
            degree = -degree;
        }

        //Чистим память на каждом шаге рекурсии(важно!)
        for(int i = 0; i < size-1; i++)
        {
            delete [] newMatrix[i];
        }
        delete [] newMatrix;
    }

    return det;
}

void for_parallel(int size, int **matrix, int *det, int *degree)
{
    //Матрица без строки и столбца
    int **newMatrix = new int*[size-1];
    for(int i = 0; i < size-1; i++)
    {
        newMatrix[i] = new int[size-1];
    }

    //Раскладываем по 0-ой строке, цикл бежит по столбцам
    for(int j = 0; j < size; j++)
    {
        //Удалить из матрицы i-ю строку и j-ый столбец
        //Результат в newMatrix
        getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

        //Рекурсивный вызов
        //По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть сумма из формулы)
        //где minor_j - дополнительный минор элемента matrix[0][j]
        // (напомню, что минор это определитель матрицы без 0-ой строки и j-го столбца)
        *det = *det + (*degree * matrix[0][j] * matrixDet(newMatrix, size-1));
        //"Накручиваем" степень множителя
        *degree = -(*degree);
    }

    //Чистим память на каждом шаге рекурсии(важно!)
    for(int i = 0; i < size-1; i++)
    {
        delete [] newMatrix[i];
    }
    delete [] newMatrix;
}

int matrixDetparalleltime(int **matrix, int size)
{
    time_t startt, endt;
    int det = 0;
    int degree = 1; // (-1)^(1+j) из формулы определителя

    startt = clock();
    //Условие выхода из рекурсии
    if(size == 1)
    {
        return matrix[0][0];
    }
        //Условие выхода из рекурсии
    else if(size == 2)
    {
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    }
    else
    {
        std::thread mas_potoks[size];
        for (int k = 0; k < size; k++)
        {
            mas_potoks[k] = std::thread(for_parallel, size, matrix, &det, &degree);
        }

        for (int k = 0; k < size; k++)
            mas_potoks[k].join();
    }

    endt = clock();
    return endt - startt;
}

int matrixDetparallel(int **matrix, int size)
{
    int det = 0;
    int degree = 1; // (-1)^(1+j) из формулы определителя

    //Условие выхода из рекурсии
    if(size == 1)
    {
        return matrix[0][0];
    }
        //Условие выхода из рекурсии
    else if(size == 2)
    {
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    }
    else
    {
        std::thread mas_potoks[size];
        for (int k = 0; k < size; k++)
        {
            mas_potoks[k] = std::thread(for_parallel, size, matrix, &det, &degree);
        }

        for (int k = 0; k < size; k++)
            mas_potoks[k].join();
    }

    return det;
}

int **allocate_matrix(int rows, int columns)
{
    int **ptrs, *data;

    ptrs = new int*[rows];
    if (!ptrs)
        return NULL;

    data = new int[rows * columns];
    if (!data)
    {
        free(ptrs);

        return NULL;
    }

    for (int i = 0; i < rows; i++)
        ptrs[i] = data + i * columns;

    return ptrs;
}

int input_matrix(int rows, int columns, int **matrix)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
                return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void free_matrix(int **ptrs)
{
    free(ptrs[0]);

    free(ptrs);
}

void print_matrix(int **matrix, int rows, int columns)
{
    printf("\n");
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int **fill_random_matrix(int rows, int columns, int **matrix)
{
    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix[i][j] = rand();

    return matrix;
}

int main(void)
{
    printf("Menu \n");
    printf("1. Simple algorithm to find det with minors \n");
    printf("2. Parallel algorithm to find det with minors \n");
    printf("3. Time analysis \n");
    printf("0. Exit \n");

    printf("Input: ");
    int key = 0;
    if (scanf("%d", &key) != 1 || key > 4 || key < 0)
    {
        printf("Input number from 0 to 4 \n");
        return EXIT_FAILURE;
    }
    switch (key)
    {
        case 1:
        {
            int rows1, columns1;
            printf("\ninput number of cols and rows of matrix 1: ");
            if (scanf("%d %d", &rows1, &columns1) != 2)
                return EXIT_FAILURE;

            int **matrix1;
            matrix1 = allocate_matrix(rows1, columns1);

            int check = 0;
            if ((check = input_matrix(rows1, columns1, matrix1)) != EXIT_SUCCESS)
                return EXIT_FAILURE;

            int det = matrixDet(matrix1, rows1);
            print_matrix(matrix1, rows1, columns1);
            printf("det = %d", det);
            free_matrix(matrix1);
            return EXIT_SUCCESS;
        }
        case 2:
        {
            int rows1, columns1;
            printf("\ninput number of cols and rows of matrix 1: ");
            if (scanf("%d %d", &rows1, &columns1) != 2)
                return EXIT_FAILURE;

            int **matrix1;
            matrix1 = allocate_matrix(rows1, columns1);

            int check = 0;
            if ((check = input_matrix(rows1, columns1, matrix1)) != EXIT_SUCCESS)
                return EXIT_FAILURE;

            int det = matrixDetparallel(matrix1, rows1);
            print_matrix(matrix1, rows1, columns1);
            printf("det = %d", det);
            free_matrix(matrix1);
            return EXIT_SUCCESS;
        }
        case 3:
        {
            int rows1, columns1;
            for (int size = 1; size < 10; size++)
            {
                int **matrix1;
                matrix1 = allocate_matrix(size, size);
                fill_random_matrix(size, size, matrix1);
                time_t totaltime = 0;
                for (int i = 0; i < 100; i++)
                {
                    totaltime += matrixDet(matrix1, size);
                }
                printf("\nwithout parallel = %lf \n", (float)totaltime/(100 * CLOCKS_PER_SEC));
                totaltime = 0;
                for (int i = 0; i < 100; i++)
                {
                    totaltime += matrixDetparallel(matrix1, size);
                }
                printf("\nwith parallel = %lf \n", (float)totaltime/(100 * CLOCKS_PER_SEC));
                free_matrix(matrix1);
            }
            return EXIT_SUCCESS;
        }
        case 0:
            return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}



//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <memory.h>
//#include <time.h>
//#include <thread>
//#include "cdio.h"
//#include "const.h"
//#include "process.h"
//
//////Возвращает матрицу matrix без row-ой строки и col-того столбца, результат в newMatrix
////void getMatrixWithoutRowAndCol(int **matrix, int size, int row, int col, int **newMatrix)
////{
////    int offsetRow = 0; //Смещение индекса строки в матрице
////    int offsetCol = 0; //Смещение индекса столбца в матрице
////    for(int i = 0; i < size-1; i++)
////	{
////        //Пропустить row-ую строку
////        if(i == row)
////		{
////            offsetRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
////        }
////
////        offsetCol = 0; //Обнулить смещение столбца
////        for(int j = 0; j < size-1; j++)
////		{
////            //Пропустить col-ый столбец
////            if(j == col)
////			{
////                offsetCol = 1; //Встретили нужный столбец, проускаем его смещением
////            }
////
////            newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
////        }
////    }
////}
//
////int matrixDet(int **matrix, int size)
////{
////    int det = 0;
////    int degree = 1; // (-1)^(1+j) из формулы определителя
////    //Условие выхода из рекурсии
////    if(size == 1)
////	{
////        return matrix[0][0];
////    }
////    //Условие выхода из рекурсии
////    else if(size == 2)
////	{
////        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
////    }
////    else
////	{
////        //Матрица без строки и столбца
////        int **newMatrix = new int*[size-1];
////        for(int i = 0; i < size-1; i++)
////		{
////            newMatrix[i] = new int[size-1];
////        }
////
////        //Раскладываем по 0-ой строке, цикл бежит по столбцам
////        for(int j = 0; j < size; j++)
////		{
////            getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);
////            det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size-1));
////            degree = -degree;
////        }
////
////        //Чистим память на каждом шаге рекурсии(важно!)
////        for(int i = 0; i < size-1; i++)
////		{
////            delete [] newMatrix[i];
////        }
////        delete [] newMatrix;
////    }
////
////    return det;
////}
//
//
//int main()
//{
//    int ch = 0, n, choice = -1, flag = 1;
//    double **matrix1, **matrix2, *first_row1, *first_row2, p;
//
//    while (flag == 1)
//    {
//        choice = -1;
//        printf("Menu: \n");
//        printf("1. Input new data\n");
//        printf("2. Print matrix1\n");
//        printf("3. Simple algorithm \n");
//        printf("4. Parallel algorithm\n");
//        printf("5. Time analisys \n");
//        printf("0. Exit \n");
//        printf(">");
//        while (ch != 1 || choice < 0 || choice > 5)
//        {
//            ch = scanf("%d", &choice);
//            if (ch != 1)
//                printf("Input number between 0 - 5\n");
//        }
//
//        if (choice == 1)
//        {
//            ch = input_matrix_size(&n);
//            if (ch != OK)
//                return ch;
//
//            matrix1 = allocate_matrix(n, n);
//            matrix1 = fill_random_matrix(n, n, matrix1);
//            first_row1 = matrix1[0];
//
//            matrix2 = allocate_matrix(n, n);
//            matrix2 = copy_matrix(matrix1, n, n);
//            first_row2 = matrix2[0];
//
//            printf("Input number p: \n");
//            ch = scanf("%lf", &p);
//            if (ch != 1)
//            {
//                printf("Error!");
//                return 1;
//            }
//        }
//        else if (choice == 2)
//        {
//            print_matrix(matrix1, n, n);
//            print_matrix(matrix2, n, n);
//        }
//        else if (choice == 3)
//        {
//            delete_nodes(matrix1, &n, p);
//            print_matrix(matrix1, n, n);
//        }
//        else if (choice == 4)
//        {
//            delete_nodes_parallel(matrix2, &n, p);
//            print_matrix(matrix2, n, n);
//        }
//        else if (choice == 5)
//        {
//            n = 1000;
//
//            time_t startt, endt, time1, time2;
//
//            for (int i = 0; i < 100; i++)
//            {
//                matrix1 = allocate_matrix(n, n);
//                matrix1 = fill_random_matrix(n, n, matrix1);
//                first_row1 = matrix1[0];
//
//                matrix2 = allocate_matrix(n, n);
//                matrix2 = copy_matrix(matrix1, n, n);
//                first_row2 = matrix2[0];
//
//
//                startt = clock();
//                delete_nodes_parallel(matrix1, &n, p);
//                endt = clock();
//                time1 += endt - startt;
//
//                startt = clock();
//                delete_nodes(matrix2, &n, p);
//                endt = clock();
//                time2 += endt - startt;
//            }
//            printf("parallel: %lf\n", (float)time1/(100 * CLOCKS_PER_SEC)/20);
//            printf("simple: %lf\n", (float)time2/(100 * CLOCKS_PER_SEC)/20);
////            for (int i = 1000; i < 1250; i += 10)
////            {
////                time1 = 0;
////                time2 = 0;
////                n = i;
////                matrix1 = allocate_matrix(n, n);
////                matrix2 = allocate_matrix(n, n);
////                matrix1 = fill_random_matrix(n, n, matrix1);
////                matrix2 = copy_matrix(matrix1, n, n);
////                first_row1 = matrix1[0];
////                first_row2 = matrix2[0];
////
////                for (int j = 0; j < 100; j++)
////                {
////                    startt = clock();
////                    delete_nodes(matrix1, &n, p);
////                    endt = clock();
////                    time1 += endt - startt;
////                }
////                for (int j = 0; j < 100; j++)
////                {
////                    startt = clock();
////                    delete_nodes_parallel(matrix2, &n, p, 10);
////                    endt = clock();
////                    time2 += endt - startt;
////                }
////                printf("%d. %lf    %lf\n", i, (float)time1/(100 * CLOCKS_PER_SEC)/100, (float)time2/(100 * CLOCKS_PER_SEC)/100);
////                free_matrix(matrix1, first_row1);
////                free_matrix(matrix2, first_row2);
////            }
//        }
//        else
//            flag = 0;
//    }
//
//    free_matrix(matrix1, first_row1);
//    free_matrix(matrix2, first_row2);
//    return OK;
//
////    int num = 0;
////    std::thread mas_potoks[5];
////    for (int k = 0; k < 5; k++)
////    {
////        mas_potoks[k] = std::thread(number_add, &num);
////        printf("%d", num);
////        mas_potoks[k].join();
////
////    }
//}
