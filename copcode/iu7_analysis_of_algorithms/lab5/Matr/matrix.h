#ifndef MATR_MATRIX_H
#define MATR_MATRIX_H

#include <iostream>
#include <vector>

template <typename Type>
class Matrix {
public:
    Matrix(int n_len, int m_len, Type value) {
        row_length = n_len;
        column_length = m_len;

        std::vector<Type> row;

        for (int i = 0; i < column_length; ++i) {
            row.push_back(value);
        }
        for (int j = 0; j < row_length; ++j) {
            matrix.push_back(row);
        }
    };

    void show();
    int get_row_length() const {
        return row_length;
    };
    int get_column_length() const {
        return column_length;
    };
    Matrix<Type> multiplicate(Matrix<Type> value) const;

    std::vector<Type> &operator [](int i) {
        return matrix[i];
    }

    Matrix<Type> operator * (const Matrix<Type> value) const {
        return multiplicate(value);
    }

private:
    int row_length;
    int column_length;
    std::vector<std::vector<Type>> matrix;
};

template <typename Type>
Matrix<Type> Matrix<Type>::multiplicate(Matrix<Type> value) const {
    Matrix<Type> result(row_length, value.get_column_length(), 0);
    for (int i = 0; i < row_length; ++i) {
        for (int j = 0; j < column_length; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < column_length; ++k) {
                result[i][j] += matrix[i][k] * value[k][j];
            }
        }
    }

    return result;
}

template <typename Type>
void Matrix<Type>::show() {
    for (int i = 0; i < row_length; i++) {
        for (int j = 0; j < column_length; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

#endif //MATR_MATRIX_H
