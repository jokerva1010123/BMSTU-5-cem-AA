def input_number(msg):
    num = -1
    while num <= 0:
        try:
            num = int(input(msg))
            if num <= 0:
                print("Введите натуральное число!")
        except Exception:
            print("Введите натуральное число!")
    return num


def input_matrix(msg):
    print(msg)
    n = input_number("Введите количество строк: ")
    m = input_number("Введите количество столбцов: ")
    matrix = []
    print("Введите элементы матрицы (построчно):")
    for i in range(n):
        matrix.append(list(map(int, input().split())))
        while len(matrix[i]) != m:
            print("Неправильное количество чисел в строке! Попробуйте снова!")
            matrix[i] = list(map(int, input().split()))
    return matrix, n, m


def print_matrix(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            print("{:4d}  ".format(matrix[i][j]), end='')
        print()

