from random import *

sizes = [i for i in range(3, 14, 1)]

alphabet = "sdfghjklqwertyuiopzxcvbnma"

file = open("strings.txt", "w")

for i in sizes:
    string1 = ""
    string2 = ""
    for j in range(i):
        string1 += choice(alphabet)
        string2 += choice(alphabet)
    file.write(string1 + "\n" + string2 + "\n")

file.close()
