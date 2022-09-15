from copy import deepcopy
from color import *
import numpy as np


class Matrix:
    n, m = 0, 0
    matrix = list()

    def __init__(self, n, m, list_of_lists=None):
        self.n, self.m = n, m
        if list_of_lists:
            self.matrix = deepcopy(list_of_lists)
        else:
            self.matrix = np.full((n, m), 0)

    def output(self):
        print(TURQUOISE, end='')
        for i in range(self.n):
            for j in range(self.m):
                print(self.matrix[i][j], end=' ')
            print()

    def fill(self, list_of_lists):
        self.matrix = deepcopy(list_of_lists)

    def size(self):
        return (self.n, self.m)

    def __getitem__(self, index):
        return self.matrix[index]

    def __setitem__(self, key, value):
        self.matrix[key] = value
