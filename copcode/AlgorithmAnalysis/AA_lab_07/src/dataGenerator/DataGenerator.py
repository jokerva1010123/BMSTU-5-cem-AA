from faker import *
from random import randint

ZZZAP = 4000


def generateDictionary():
    faker = Faker("ru_RU")
    f = open("dictionary4000.csv", 'w')
    for id in range(ZZZAP):
        death = faker.bs()
        line = "{};{}\n".format(id, death)

        f.write(line)
    f.close()


if __name__ == "__main__":
    generateDictionary()
