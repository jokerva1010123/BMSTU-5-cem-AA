# # !/usr/bin/python
# # -*- coding: utf-8 -*-
import matplotlib.pyplot as plt

lenArr = [100, 300, 500, 700, 900]

sort_bubble = [0.0004, 0.0025, 0.0072, 0.0152, 0.0253]
sort_insert = [0.0, 0.0, 0.0001, 0.0001, 0.0001]
sort_quick_recursion = [0.0, 0.0, 0.0003, 0.0005, 0.0006]

fig, ax = plt.subplots()

ax.plot(lenArr, sort_bubble, label="Пузырек")

ax.plot(lenArr, sort_insert, label="Вставки")

ax.plot(lenArr, sort_quick_recursion, label="QuickSort")

ax.legend()
ax.grid()
ax.set_xlabel('Размерность')
ax.set_ylabel('Время (с)')

plt.show()
