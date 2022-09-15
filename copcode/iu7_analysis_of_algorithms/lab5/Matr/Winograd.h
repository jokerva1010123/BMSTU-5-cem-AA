#ifndef MATR_WINOGRAD_H
#define MATR_WINOGRAD_H

#include "matrix.h"
#include <thread>
#include <memory>

template <typename Type>
Matrix<Type> Winograd(Matrix<Type> matrix1, Matrix<Type> matrix2) {
    Matrix<Type> result(matrix1.get_row_length(), matrix2.get_column_length(), 0);

    int d = matrix1.get_column_length()/2;

    std::unique_ptr<Type[]> rowFactor(new Type[matrix1.get_row_length()]);    // Объявление rowFactor
    for (int i = 0; i < matrix1.get_row_length(); i++)
        rowFactor[i] = 0;    // Заполнение rowFactor нулями

    // Вычисление значений для rowFactor
    for (int i = 0; i < matrix1.get_row_length(); i++) {
        for (int j = 0; j < d; j++) {
            rowFactor[i] = rowFactor[i] + matrix1[i][2*j] * matrix1[i][2*j + 1];
        }
    }

    std::unique_ptr<Type[]> columnFactor(new Type[matrix2.get_column_length()]);    // Объявление columnFactor
    for (int i = 0; i < matrix1.get_row_length(); i++)
        columnFactor[i] = 0;     // Заполнение columnFactor нулями

    // Вычисление значений для columnFactor
    for (int i = 0; i < matrix2.get_column_length(); i++) {
        for (int j = 0; j < d; j++) {
            columnFactor[i] = columnFactor[i] + matrix2[2*j][i] * matrix2[2*j + 1][i];
        }
    }

    // Вычисление результирующей матрицы
    for (int i = 0; i < matrix1.get_row_length(); i++) {
        for (int j = 0; j < matrix2.get_column_length(); j++) {
            result[i][j] = -rowFactor[i] - columnFactor[j];
            for (int k = 0; k < d; k++) {
                result[i][j] = result[i][j] + ((matrix1[i][2*k] + matrix2[2*k + 1][j]) * (matrix1[i][2*k + 1] + matrix2[2*k][j]));
            }
        }
    }


    // Прибавление членов в случае нечетной общей размерности
    if (matrix1.get_column_length() % 2) {
        for (int i = 0; i < matrix1.get_row_length(); i++) {
            for (int j = 0; j < matrix2.get_column_length(); j++) {
                result[i][j] = result[i][j] + matrix1[i][matrix1.get_column_length()-1] * matrix2[matrix1.get_column_length()-1][j];
            }
        }
    }

    return result;
}



template <typename Type>
Matrix<Type> Winograd_optimized(Matrix<Type> matrix1, Matrix<Type> matrix2) {
    Matrix<Type> result(matrix1.get_row_length(), matrix2.get_column_length(), 0);

    int d = matrix1.get_column_length()/2;
    const int matrix_1_row_length = matrix1.get_row_length();
    const int matrix_1_column_length = matrix1.get_column_length();
    const int matrix_2_column_length = matrix2.get_column_length();

    std::unique_ptr<Type[]> rowFactor(new Type[matrix_1_row_length]); // Объявление rowFactor
    auto row_func = [](Matrix<Type> matrix1, Type* rowFactor, int matrix_1_row_length, int d) {
        for (int i = 0; i < matrix_1_row_length; ++i)
            rowFactor[i] = 0;    // Заполнение rowFactor нулями

        // Вычисление значений для rowFactor
        for (int i = 0; i < matrix_1_row_length; ++i) {
            for (int j = 0; j < d; ++j) {
                int two_j = 2*j;
                rowFactor[i] += matrix1[i][two_j] * matrix1[i][two_j + 1];
            }
        }
    };
    std::thread row_thread(row_func, matrix1, rowFactor.get(), matrix_1_row_length, d);

    std::unique_ptr<Type[]> columnFactor(new Type[matrix_2_column_length]);    // Объявление columnFactor
    auto col_func = [](Matrix<Type> matrix2, Type* columnFactor, int matrix_2_column_length, int d) {
        for (int i = 0; i < matrix_2_column_length; ++i)
            columnFactor[i] = 0;     // Заполнение columnFactor нулями

        // Вычисление значений для columnFactor
        for (int i = 0; i < matrix_2_column_length; ++i) {
            for (int j = 0; j < d; ++j) {
                int two_j = 2*j;
                columnFactor[i] += matrix2[two_j][i] * matrix2[two_j + 1][i];
            }
        }
    };
    std::thread column_thread(col_func, matrix2, columnFactor.get(), matrix_2_column_length, d);

    row_thread.join();
    column_thread.join();

    // Вычисление результирующей матрицы
    for (int i = 0; i < matrix_1_row_length; ++i) {
        for (int j = 0; j < matrix_2_column_length; ++j) {
            result[i][j] = -rowFactor[i] - columnFactor[j];
            for (int k = 0; k < d; k++) {
                int two_k = 2*k;
                result[i][j] += (matrix1[i][two_k] + matrix2[two_k + 1][j]) * (matrix1[i][two_k + 1] + matrix2[two_k][j]);

            }
        }
    }

    // Прибавление членов в случае нечетной общей размерности
    if (matrix_1_column_length % 2) {
        for (int i = 0; i < matrix_1_row_length; ++i) {
            for (int j = 0; j < matrix_2_column_length; j++) {
                result[i][j] += matrix1[i][matrix_1_column_length-1] * matrix2[matrix_1_column_length-1][j];
            }
        }
    }

    return result;
}


template <typename Type>
Matrix<Type> classic_mult(Matrix<Type> matrix1, Matrix<Type> matrix2) {
    int matr1_row = matrix1.get_row_length();
    int matr1_col = matrix1.get_column_length();
    int matr2_col = matrix2.get_column_length();

    Matrix<Type> result(matr1_row, matr2_col, 0);
    for (int i = 0; i < matr1_row; ++i) {
        for (int j = 0; j < matr1_col; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < matr1_col; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

template <typename Type>
Matrix<Type> classic_mult_parall(Matrix<Type> matrix1, Matrix<Type> matrix2) {
    int matr1_row = matrix1.get_row_length();
    int matr1_col = matrix1.get_column_length();
    int matr2_col = matrix2.get_column_length();

    auto thread_count = 16;//std::thread::hardware_concurrency();

    std::thread threads[thread_count];

    Matrix<Type> result(matr1_row, matr2_col, 0);

    auto classic = [](Matrix<Type> matrix1, Matrix<Type> matrix2, Matrix<Type> &result,
                      int matr1_row, int matr1_col, int number, int count) {
        for (int i = number; i < matr1_row; i+=count) {
            for (int j = 0; j < matr1_col; ++j) {
                result[i][j] = 0;
                for (int k = 0; k < matr1_col; ++k) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
    };

    for (int i = 0; i < thread_count; ++i) {
        threads[i] = std::thread(classic, matrix1, matrix2, std::ref(result),
                                 matr1_row, matr1_col,
                                 i, thread_count);
    }
    for (int i = 0; i < thread_count; ++i)
        if (threads[i].joinable())
            threads[i].join();

    return result;
}

//template <typename Type>
//void winogradThread(const Matrix<Type> &matrix1, const Matrix<Type> &matrix2, Matrix<Type> &result,
//                    Type* rowFactor, Type* columnFactor, int matr1_row, int matr1_col, int mat2_col,
//                    int number, int count) {
//    int d = matr1_col/2;
//    for (int i = number; i < matr1_row; i += count) {
//        for (int j = 0; j < mat2_col; ++j) {
//            result[i][j] = -rowFactor[i] - columnFactor[j];
//            for (int k = 0; k < d; ++k) {
//                result[i][j] += (matrix1[i][2*k+1] + matrix2[2*k][j]) * (matrix1[i][2*k] + matrix2[2*k+1][j]);
//            }
//        }
//    }
//}

template <typename Type>
Matrix<Type> Winograd_parall(Matrix<Type> matrix1, Matrix<Type> matrix2) {
    Matrix<Type> result(matrix1.get_row_length(), matrix2.get_column_length(), 0);

    int d = matrix1.get_column_length()/2;
    const int matrix_1_row_length = matrix1.get_row_length();
    const int matrix_1_column_length = matrix1.get_column_length();
    const int matrix_2_column_length = matrix2.get_column_length();

    std::unique_ptr<Type[]> rowFactor(new Type[matrix_1_row_length]); // Объявление rowFactor
    auto row_func = [](Matrix<Type> matrix1, Type* rowFactor, int matrix_1_row_length, int d) {
        for (int i = 0; i < matrix_1_row_length; ++i)
            rowFactor[i] = 0;    // Заполнение rowFactor нулями

        // Вычисление значений для rowFactor
        for (int i = 0; i < matrix_1_row_length; ++i) {
            for (int j = 0; j < d; ++j) {
                int two_j = 2*j;
                rowFactor[i] += matrix1[i][two_j] * matrix1[i][two_j + 1];
            }
        }
    };
    std::thread row_thread(row_func, matrix1, rowFactor.get(), matrix_1_row_length, d);

    std::unique_ptr<Type[]> columnFactor(new Type[matrix_2_column_length]);    // Объявление columnFactor
    auto col_func = [](Matrix<Type> matrix2, Type* columnFactor, int matrix_2_column_length, int d) {
        for (int i = 0; i < matrix_2_column_length; ++i)
            columnFactor[i] = 0;     // Заполнение columnFactor нулями

        // Вычисление значений для columnFactor
        for (int i = 0; i < matrix_2_column_length; ++i) {
            for (int j = 0; j < d; ++j) {
                int two_j = 2*j;
                columnFactor[i] += matrix2[two_j][i] * matrix2[two_j + 1][i];
            }
        }
    };
    std::thread column_thread(col_func, matrix2, columnFactor.get(), matrix_2_column_length, d);

    row_thread.join();
    column_thread.join();

    auto thread_count = 16;//std::thread::hardware_concurrency();
    std::thread threads[thread_count];

    auto winogradThread = [](Matrix<Type> matrix1, Matrix<Type> matrix2, Matrix<Type> &result,
            Type* rowFactor, Type* columnFactor, int matr1_row, int matr1_col, int mat2_col,
            int number, int count)  {
        int d = matr1_col/2;
        for (int i = number; i < matr1_row; i += count) {
            for (int j = 0; j < mat2_col; ++j) {
                result[i][j] = -rowFactor[i] - columnFactor[j];
                for (int k = 0; k < d; ++k) {
                    result[i][j] += (matrix1[i][2*k+1] + matrix2[2*k][j]) * (matrix1[i][2*k] + matrix2[2*k+1][j]);
                }
            }
        }
    };

    for (int i = 0; i < thread_count; ++i)
        threads[i] = std::thread(winogradThread, matrix1, matrix2, std::ref(result),
                                 rowFactor.get(), columnFactor.get(), matrix_1_row_length, matrix_1_column_length,
                                 matrix_2_column_length, i, thread_count);

    for (int i = 0; i < thread_count; ++i)
        if (threads[i].joinable())
            threads[i].join();

    // Прибавление членов в случае нечетной общей размерности
    if (matrix_1_column_length % 2) {
        for (int i = 0; i < matrix_1_row_length; ++i) {
            for (int j = 0; j < matrix_2_column_length; j++) {
                result[i][j] += matrix1[i][matrix_1_column_length-1] * matrix2[matrix_1_column_length-1][j];
            }
        }
    }

    return result;
}


#endif //MATR_WINOGRAD_H
