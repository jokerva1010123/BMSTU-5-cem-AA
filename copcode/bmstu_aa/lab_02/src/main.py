from multi_matrix import matrix_multiply, vinograd, optimized_vinograd
from cdio import input_matrix, print_matrix
from proc_time import analyze_algorythms

MSG = ["Классический",
       "Винограда",
       "Винограда с оптимизацией"]


if __name__ == '__main__':
    choice = 1
    while choice != 0:
        print("Меню")
        print("1. Умножение матриц:")
        print("     - Классический")
        print("     - Винограда")
        print("     - Винограда с оптимизацией")
        print("2. Замеры процессорного времени")
        print("0. Выход")

        print(">  ", end='')
        choice = int(input())

        if choice == 1:
            matrix1, row1, col1 = input_matrix("Ввод первой матрицы")
            matrix2, row2, col2 = input_matrix("Ввод второй матрицы")
            # print ("{} = {}".format(col1, row2))
            while col1 != row2:
                print("Матрицы такого размера нельзя перемножать!")
                matrix1 = input_matrix("Ввод первой матрицы:")
                matrix2 = input_matrix("Ввод второй матрицы:")

            print("\n", "=" * 75)
            print("Классический алгоритм перемножения матриц")
            matrix_res = matrix_multiply(matrix1, matrix2)
            print("Результат:")
            print_matrix(matrix_res)

            print("\n", "=" * 75)
            print("Алгоритм Винограда")
            matrix_res = vinograd(matrix1, matrix2)
            print("Результат:")
            print_matrix(matrix_res)

            print("\n", "=" * 75)
            print("Алгорит Винограда с оптимизацией")
            matrix_res = optimized_vinograd(matrix1, matrix2)
            print("Результат:")
            print_matrix(matrix_res)
            print()

        elif choice == 2:
            analyze_algorythms()
