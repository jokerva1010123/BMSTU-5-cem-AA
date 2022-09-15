import json
import matplotlib.pyplot as plt
import numpy as np
class Film:
    def __init__(self, name, year):
        self.name = name
        self.year = year
class Segment:
    def __init__(self, letter, beg, end, freq):
        self.letter = letter
        self.beg = beg
        self.end = end
        self.freq = freq
def filmsComp(f, k):
    if f.name > k:
        return 1
    elif f.name < k:
        return -1
    else:
        return 0
def segComp(s, k):
    if s.letter > k:
        return 1
    elif s.letter < k:
        return -1
    else:
        return 0
def search(d, key, comp):
    for i in range(len(d)):
        if comp(d[i], key) == 0:
            return d[i], i + 1
    return "not found", len(d)

def binSearch(d, key, comp, lo, hi):
    cmp = 0
    while lo < hi:
        cmp += 1
        mid = (lo+hi)//2
        midval = d[mid]
        if comp(midval, key) < 0:
            lo = mid+1
            cmp += 1
        elif comp(midval, key) > 0: 
            hi = mid
            cmp += 2
        else:
            cmp += 2
            return d[mid], cmp
    return "not found", cmp
def make_segments(d):
    segments = []
    first = '\n'
    j = -1
    d.sort(key = lambda f: f.name)
    for i in range (len(d)):
        if d[i].name[0] != first:
            if j != -1:
                segments[j].end = i - 1
            
            segments.append(Segment(d[i].name[0], i, -1, 1))
            j += 1
            first = d[i].name[0]
        else:
            segments[j].freq += 1
    segments.sort(key = lambda s: s.freq, reverse = True)
    return segments

def segSearch(d, segments, key, comp):
    t = search(segments, key.lower()[0], segComp)
    tmp = binSearch(d, key, comp, t[0].beg, t[0].end + 1)
    return tmp[0], t[1] + tmp[1]

d = []
di = {}
segments = []
with open("1.json", "r") as read_file:
    data = json.load(read_file)
size = 0
cmps = []
x = []
move = 20
for i in data:
    move -= 1
    if move > 0:
        continue
    if size == 100:
        break
    di[i["nativeName"].lower()] = 1
    if len(di) > size:
        d.append(Film(i["nativeName"].lower(), i["data"]["general"]["crYearOfProduction"]))
        size += 1
for i in range (100):
    print("{} & {} \\\\".format(i, d[i].name))
##for i in range (100):
##    cmps.append(search(d, d[i].name, filmsComp)[1])
##    x.append(i)
##cmps.sort(reverse = True)
##plt.xlabel("индексы фильмов")
##plt.ylabel("количество сравнений")
##plt.hist(x, 100, weights = cmps)
##plt.show()

##for i in range (100):
##    cmps.append(binSearch(d, d[i].name, filmsComp, 0, len(d))[1])
##    x.append(i)
##cmps.sort(reverse = True)
##plt.xlabel("индексы фильмов")
##plt.ylabel("количество сравнений")
##plt.hist(x, 100, weights = cmps)
##plt.show()

##segs = make_segments(d)
##for i in range (len(d)):
##    cmps.append(segSearch(d, segs, d[i].name, filmsComp)[1])
##    x.append(i)
##cmps.sort(reverse = True)
##plt.xlabel("индексы фильмов")
##plt.ylabel("количество сравнений")
##plt.hist(x, 100, weights = cmps)
##plt.show()

key = "особо опасен"
t = search(d, key, filmsComp)
print(t[0].year, t[1])

d.sort(key = lambda f: f.name)
t = binSearch(d, key, filmsComp, 0, len(d))
print(t[0].year, t[1])

segs = make_segments(d)
t = segSearch(d, segs, key, filmsComp)
print(t[0].year, t[1])


