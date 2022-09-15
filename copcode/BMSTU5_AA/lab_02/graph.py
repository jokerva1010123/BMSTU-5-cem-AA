# # !/usr/bin/python
# # -*- coding: utf-8 -*-
import matplotlib.pyplot as plt

lenMatrix = [11, 21, 31, 41, 51, 61, 71, 81, 91, 101]

multiplication = [0.2165, 1.4288, 4.619, 10.6453, 20.2012, 35.3632, 58.5323, 88.6608, 125.916, 168.87]
WinogradMult = [0.1731, 1.0691, 3.3009, 7.5519, 14.43, 25.6929, 41.9793, 62.4315, 87.5135, 116.94]
WinogradOptimization = [0.0891, 0.5213, 1.5841, 3.5756, 6.8016, 13.4514, 20.9525, 30.1312, 43.4626, 63.0787]

fig, ax = plt.subplots()

ax.plot(lenMatrix, multiplication, label="Стандартный алгоритм")

ax.plot(lenMatrix, WinogradMult, label="Алгоритм Винограда")

ax.plot(lenMatrix, WinogradOptimization, label="Алгоритм Винограда с оптимизациями")

ax.legend()
ax.grid()
ax.set_xlabel('Размерность')
ax.set_ylabel('Время (с)')

plt.show()
