# Обычный Левенштейн
def levenstein(str_1, str_2, info=False):
    n, m = len(str_1), len(str_2)
    matrix = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(m + 1):
        for j in range(n + 1):
            if j == 0 and i > 0:
                matrix[i][j] = i
            if i == 0 and j > 0:
                matrix[i][j] = j
            if i > 0 and j > 0:
                if str_1[j - 1] == str_2[i - 1]:
                    res = 0
                else:
                    res = 1
                matrix[i][j] = min(
                    matrix[i][j - 1] + 1,
                    matrix[i - 1][j] + 1,
                    matrix[i - 1][j - 1] + res)

    if info:
        print_matrix(str_1, str_2, matrix)
    return matrix[m][n]


# Дамерау-Левенштейн (нерекурсивный)
def damerau_levenstein(str_1, str_2, info=False):
    n, m = len(str_1), len(str_2)
    matrix = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(m + 1):
        for j in range(n + 1):
            if i == 0 and j == 0:
                matrix[i][j] = 0
            if j == 0 and i > 0:
                matrix[i][j] = i
            if i == 0 and j > 0:
                matrix[i][j] = j
            if i > 0 and j > 0:
                if str_1[j - 1] == str_2[i - 1]:
                    res = 0
                else:
                    res = 1
                matrix[i][j] = min(
                    matrix[i][j - 1] + 1,
                    matrix[i - 1][j] + 1,
                    matrix[i - 1][j - 1] + res)

                # Если есть возможность перестановки
                if str_1[j - 1] == str_2[i - 2] and str_1[j - 2] == str_2[i - 1]:
                    matrix[i][j] = min(
                        matrix[i][j],
                        matrix[i - 2][j - 2] + 1)

    if info:
        print_matrix(str_1, str_2, matrix)
    return matrix[m][n]


# Дамерау-Левенштейн (рекурсивный)
def damerau_levenstein_recursive(str_1, str_2, info=False):
    n, m = len(str_1), len(str_2)

    if m == 0:
        return n
    if n == 0:
        return m

    if str_1[-1] == str_2[-1]:
        mistake = 0
    else:
        mistake = 1

    res = min(damerau_levenstein_recursive(str_1, str_2[:-1]) + 1,
              damerau_levenstein_recursive(str_1[:-1], str_2) + 1,
              damerau_levenstein_recursive(str_1[:-1], str_2[:-1]) + mistake)
    if n > 1 and m > 1 and str_1[-1] == str_2[-2] and str_1[-2] == str_2[-1]:
        res = min(res, damerau_levenstein_recursive(str_1[:-2], str_2[:-2]) + 1)
    return res


# Основная рекурсивная функция Дамерау-Левенштейна с кешем
def damerau_levenstein_recursive_cache(str_1, str_2, matrix):
    n, m = len(str_1), len(str_2)

    if m == 0:
        matrix[m][n] = n
    elif n == 0:
        matrix[m][n] = m
    else:
        if matrix[m][n - 1] == -1:
            damerau_levenstein_recursive_cache(str_1[:-1], str_2, matrix)
        if matrix[m - 1][n] == -1:
            damerau_levenstein_recursive_cache(str_1, str_2[:-1], matrix)
        if matrix[m - 1][n - 1] == -1:
            damerau_levenstein_recursive_cache(str_1[:-1], str_2[:-1], matrix)

        matrix[m][n] = min(matrix[m][n - 1] + 1,
                           matrix[m - 1][n] + 1,
                           matrix[m - 1][n - 1] + int(str_1[-1] != str_2[-1]))

        if n > 1 and m > 1 and str_1[-1] == str_2[-2] and str_1[-2] == str_2[-1]:
            matrix[m][n] = min(matrix[m][n],
                               matrix[m - 2][n - 2] + 1)

        return


# Дамерау-Левенштейн (рекурсивный с кешем) (создание матрицы)
def damerau_levenstein_recursive_cache_matrix(str_1, str_2, info=False):
    n, m = len(str_1), len(str_2)

    matrix = [[-1] * (n + 1) for _ in range(m + 1)]
    damerau_levenstein_recursive_cache(str_1, str_2, matrix)

    if info:
        print_matrix(str_1, str_2, matrix)
    return matrix[m][n]


def print_matrix(str_1, str_2, matrix):
    n, m = len(str_1), len(str_2)
    print("  |    ", end='')
    for i in range(n):
        print("{}  ".format(str_1[i].upper()), end='')
    print()
    print("-" * (n * 3 + 6))
    for i in range(m + 1):
        if i >= 1:
            print("{} | ".format(str_2[i - 1].upper()), end='')
        else:
            print("  | ", end='')
        for j in range(n + 1):
            print("{}  ".format(matrix[i][j]), end='')
        print()

    print("Ответ: {}".format(matrix[m][n]))
