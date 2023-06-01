import numpy as np
from random import randint


def generate_matrix(size, rand_start, rand_end):
    matrix = np.zeros((size, size), dtype = int)

    for i in range(size):
        for j in range(size):
            if (i == j):
                num = 0
            else:
                num = randint(rand_start, rand_end)

            matrix[i][j] = num
            matrix[j][i] = num

    return matrix


def generate_matrix_file(file_name, size, rand_start, rand_end):
    matrix = generate_matrix(size, rand_start, rand_end)
    file = open("../data/" + file_name, "w")

    for i in range(size):
        string = ""

        for j in range(size):
            string += str(matrix[i][j])
            string += " "

        string += "\n"
        file.write(string)

    file.close()

    return "\nФайл успешно создан\n", file_name


def generate_file():
    file_name = input("\nВведите имя файла:")
    size = int(input("Введите размер матрицы:"))

    rand_start = int(input("\nВведите начальное число рандома:"))
    rand_end   = int(input("Введите конечное число рандома:"))

    print(generate_matrix_file(file_name, size, rand_start, rand_end))
