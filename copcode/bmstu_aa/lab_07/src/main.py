import nltk
from string import punctuation

automobiles = {
    'Lada Granta': 3,
    'Mazda 6': 4,
    'Toyota Mark II': 5,
    'Subaru Impreza': 5,
    'Mazda 3': 4,
    'Niva 4x4': 2,
    'Ford Mustang': 5,
    'Lamborgini Huracan': 5,
    'Nissan Skyline': 4,
    'Nissan Silvia': 4,
    'Toyota Land Cruiser': 4,
    'BMW X6': 5,
    'BMW X5': 5,
    'BMW M4': 5,
    'Колесница': 1
}


def term_get(feature):
    if feature == 'очень медленные':
        return 1
    elif feature == 'медленные':
        return 2
    elif feature == 'средние':
        return 3
    elif feature == 'быстрые':
        return 4
    elif feature == 'очень быстрые':
        return 5
    return None


def mass_to_feature(mass):
    ret = []
    prov = []
    for i in mass:
        if i not in prov:
            prov.append(i)
    for i in prov:
        if i == 1:
            ret.append('очень медленные')
        if i == 2:
            ret.append('медленные')
        if i == 3:
            ret.append('средние')
        if i == 4:
            ret.append('быстрые')
        if i == 5:
            ret.append('очень быстрые')
    return ret


def perror(*msg):
    if not isinstance(msg, str):
        msg = " ".join([str(m) for m in msg if not isinstance(m, str) or m])
    print(msg)


def take_auto(token):
    words = ['автомобили', 'авто', 'автомобилей', 'автомобиль']
    for word in words:
        if word == token:
            return True
    return False


def get_auto_from_tokens(tokens):
    for token in tokens:
        if take_auto(token):
            return True
    return False


def find_terms(tokens):
    fit_classes = []
    no = 0
    very = 0
    for token in tokens:
        if token == 'не':
            no = 1
        elif token == 'очень':
            very = 1
        elif token == 'медленные':
            if no == 1 and very == 1:
                fit_classes = [3, 4]
            elif no == 1 and very == 0:
                fit_classes = [3, 4, 5]
            elif no == 0 and very == 1:
                fit_classes = [1]
            else:
                fit_classes = [2]
        elif token == 'средние':
            fit_classes = 3
        elif token == 'быстрые':
            if no == 1 and very == 1:
                fit_classes = [2, 3]
            elif no == 1 and very == 0:
                fit_classes = [1, 2, 3]
            elif no == 0 and very == 1:
                fit_classes = [5]
            else:
                fit_classes = [4]
        else:
            no = 0
            very = 0
    return fit_classes


text = "очень быстрые автомобили"
# text = input('Введите запрос:\n')

tokens = nltk.word_tokenize(text.lower(), language="russian")
tokens = [token for token in tokens if token not in punctuation]

# В вопросе спрашивают про муравейники?
print('Разбор запроса:', tokens)

if not get_auto_from_tokens(tokens):
    perror("В вопросе нет слова 'автомобиль'")
    exit(1)

fit_classes = find_terms(tokens)
terms = mass_to_feature(fit_classes)
print(terms)

print('Выявленные термы: ')
for i in range(len(terms) - 1):
    print('\t' + terms[i])
print('\t' + terms[len(terms) - 1])

print('Результаты запроса:')
for auto, id_class in automobiles.items():
    if id_class in fit_classes:
        print('\t' + auto + '-' + mass_to_feature([id_class])[0])
