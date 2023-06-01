import itertools as it

a = [i for i in range(5)]
for x in it.permutations(a):
    print(x)