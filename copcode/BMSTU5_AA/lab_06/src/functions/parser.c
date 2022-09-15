#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "colors.h"
#include "matrix.h"
#include "city.h"

int parser(FILE *f, char cities[LEN], int matrix[LEN][LEN])
{
    char city_first;
    char city_second;
    int cost, count = 0;
    int i, j;

    // Пропускам инфу.
    char str1[100];
    char str2[] = "--";
    while (!strstr(str1, str2))
        fscanf(f, "%s", str1);
    fseek(f, -4, SEEK_CUR);

    while (!feof(f))
    {

        fscanf(f, "    %c -- %c [label=\"%d\"];", &city_first, &city_second, &cost);

        if ((city_first == '}') || (city_second == '}'))
            break;
        // printf("%c %c %d\n", city_first, city_second, cost);
        i = find_city(cities, city_first, &count);
        j = find_city(cities, city_second, &count);
        // printf("%d %d %d\n", i, j, cost);
        matrix[i][j] = cost;
        matrix[j][i] = cost;
    }

    return count;
}

int parser_in_gv(char name_file[MAX_LEN_FILE_NAME], char cities[LEN], int matrix[LEN][LEN], array result, int const count, char clr[MAX_LEN_COLOR])
{
    // cities можно юзать, чтобы города не цифрами называть, а именами.
    FILE *f = fopen(name_file, "w");
    char first, second;

    if (!f)
    {
        printf("Ошибка при попытки открыть файл.\n");
        return ERROR_OPEN_FILE;
    }

    fputs(TEXT_INFO_BEGIN, f);

    int flag = FALSE;

    for (int i = 0; i < count; i++)
        for (int j = 0; j < i; j++)
        {
            first = cities[j];
            second = cities[i];

            for (int k = 0; k < result.count - 1; k++)
                if ((i == result.arr[k]) && j == (result.arr[k + 1]) || (j == result.arr[k]) && i == (result.arr[k + 1]))
                    flag = TRUE;

            if (flag)
                fprintf(f, "    %d -- %d [label=\"%d\", color=%s, penwidth=2.0];\n", i, j, matrix[i][j], clr);
            else
                fprintf(f, "    %d -- %d [label=\"%d\"];\n", i, j, matrix[i][j]);

            flag = FALSE;
        }

    // for (int i = 0; i < result.count - 1; i++)
    // fprintf(f, "    %c -- %c [color=red];\n", cities[result.arr[i]], cities[result.arr[i + 1]]);

    fputs(TEXT_INFO_END, f);

    fclose(f);

    return OK;
}
