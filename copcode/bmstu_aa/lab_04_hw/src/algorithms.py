# Обычный Левенштейн
def levenstein():
    str_1 = input()                                                                                           # 1
    str_2 = input()                                                                                           # 2
    n = len(str_1)                                                                                            # 3
    m = len(str_2)                                                                                            # 4
    matrix = [[0] * (n + 1) for _ in range(m + 1)]                                                            # 5
    for i in range(m + 1):                                                                                    # 6
        for j in range(n + 1):                                                                                # 7
            if i == 0 and j > 0:                                                                              # 8
                matrix[i][j] = j                                                                              # 9
            if j == 0 and i > 0:                                                                              # 10
                matrix[i][j] = i                                                                              # 11
            if i > 0 and j > 0:                                                                               # 12
                res = 1                                                                                       # 13
                if str_1[j - 1] == str_2[i - 1]:                                                              # 14
                    res = 0                                                                                   # 15
                matrix[i][j] = min(matrix[i][j - 1] + 1, matrix[i - 1][j] + 1, matrix[i - 1][j - 1] + res)    # 16
    return matrix[m][n]
