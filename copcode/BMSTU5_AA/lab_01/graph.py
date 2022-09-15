# # !/usr/bin/python
# # -*- coding: utf-8 -*-
import matplotlib.pyplot as plt

lenStr = [2, 3, 5, 7, 8]

Lev = [0.0007119840000000544,0.0011876439999998212,0.00284833200000012,0.005319380000000207,0.0068956949999998685,]

LevRec = [0.0005104090000001005,0.0028905320000001122,0.03515859499999996,0.9786283950000001,5.369717228]

fig, ax = plt.subplots()

ax.plot(lenStr, Lev, label="Левенштейн")

ax.plot(lenStr, LevRec, label="Левенштейн (Рекурсивная)")

ax.legend()
ax.grid()
ax.set_xlabel('Длина строки')
ax.set_ylabel('Время (с)')

plt.show()