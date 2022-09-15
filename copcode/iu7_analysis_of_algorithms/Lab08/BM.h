#ifndef LAB08_BM_H
#define LAB08_BM_H

# include <limits.h>
# include <string.h>
# include <stdio.h>

# define NO_OF_CHARS 256

// функция для получения максимума 2х целых
int max (int a, int b) { return (a > b)? a: b; }

// The preprocessing function for Boyer Moore's
// bad character heuristic
// Функция предварительной обработки для плохого характера Бойера Мура
void badCharHeuristic( char *str, int size,
                       int badchar[NO_OF_CHARS])
{
    int i;

    // Инициализировать все вхождения как -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Заполнение фактического значения последнего вхождения символа
    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

/* Функция поиска по шаблону, использующая эвристику плохого характера алгоритма Бойера Мура */
int *search( char *txt,  char *pat) {
    int m = (int) strlen(pat);
    int n = (int) strlen(txt);

    int *result = new int[];

    int badchar[NO_OF_CHARS];

    /* Заполнение массива плохих символов, вызвав функцию предварительной обработки badCharHeuristic () для данного шаблона */
    badCharHeuristic(pat, m, badchar);

    int s = 0;  // s - смещение шаблона относительно текста
    while (s <= (n - m)) {
        int j = m - 1;

        /* Keep reducing index j of pattern while
           characters of pattern and text are
           matching at this shift s */
        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        /* If the pattern is present at current
           shift, then index j will become -1 after
           the above loop */
        if (j < 0) {
//            printf("\n pattern occurs at shift = %d\n", s);
                result = s;
            /* Shift the pattern so that the next
               character in text aligns with the last
               occurrence of it in pattern.
               The condition s+m < n is necessary for
               the case when pattern occurs at the end
               of text */
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;

        } else
            /* Shift the pattern so that the bad character
               in text aligns with the last occurrence of
               it in pattern. The max function is used to
               make sure that we get a positive shift.
               We may get a negative shift if the last
               occurrence  of bad character in pattern
               is on the right side of the current
               character. */
            s += max(1, j - badchar[txt[s + j]]);
    }

    return result;
}

#endif //LAB08_BM_H
