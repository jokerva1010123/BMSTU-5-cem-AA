def matrix_multiply(matrix1, matrix2):
    matrix_res = [[0] * len(matrix2[0]) for _ in range(len(matrix1))]
    for i in range(len(matrix1)):
        for j in range(len(matrix2[0])):
            matrix_res[i][j] = 0
            for k in range(len(matrix1[0])):
                matrix_res[i][j] = matrix_res[i][j] + matrix1[i][k] * matrix2[k][j]
    return matrix_res


def vinograd(matrix1, matrix2):
    rows1 = len(matrix1)
    columns2 = len(matrix2[0])
    columns1 = len(matrix1[0])
    matrix_res = [[0] * columns2 for _ in range(rows1)]
    row = [0] * rows1
    column = [0] * columns2

    for i in range(rows1):
        for j in range(columns1 // 2):
            row[i] = row[i] + matrix1[i][2 * j] * matrix1[i][2 * j + 1]

    for i in range(columns2):
        for j in range(columns1 // 2):
            column[i] = column[i] + matrix2[2 * j][i] * matrix2[2 * j + 1][i]

    for i in range(rows1):
        for j in range(columns2):
            matrix_res[i][j] = -row[i] - column[j]
            for k in range(columns1 // 2):
                matrix_res[i][j] = matrix_res[i][j] + (matrix1[i][2 * k + 1] + matrix2[2 * k][j]) * (matrix1[i][2 * k] + matrix2[2 * k + 1][j])

    if columns1 % 2 == 1:
        for i in range(rows1):
            for j in range(columns2):
                matrix_res[i][j] = matrix_res[i][j] + matrix1[i][columns1 - 1] * matrix2[columns1 - 1][j]

    return matrix_res


def optimized_vinograd(matrix1, matrix2):
    rows1 = len(matrix1)
    columns2 = len(matrix2[0])
    columns1 = len(matrix1[0])
    matrix_res = [[0] * columns2 for _ in range(rows1)]
    row = [0] * rows1
    column = [0] * columns2

    for i in range(rows1):
        for j in range(columns1 // 2):
            row[i] += matrix1[i][j << 1] * matrix1[i][(j << 1) + 1]

    for i in range(columns2):
        for j in range(columns1 // 2):
            column[i] += matrix2[j << 1][i] * matrix2[(j << 1) + 1][i]

    for i in range(rows1):
        buf = -row[i]
        for j in range(columns2):
            matrix_res[i][j] = buf - column[j]
            for k in range(columns1 // 2):
                ind = k << 1
                matrix_res[i][j] += (matrix1[i][ind + 1] + matrix2[ind][j]) * (matrix1[i][ind] + matrix2[ind + 1][j])

    if columns1 % 2 == 1:
        for i in range(rows1):
            buf = matrix1[i][columns1 - 1]
            for j in range(columns2):
                matrix_res[i][j] += buf * matrix2[columns1 - 1][j]

    return matrix_res