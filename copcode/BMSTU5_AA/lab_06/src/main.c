// sfdp -Tpng graph.gv -o graph.png
// Результат png-шник (путь: color=red, penwidth=3.0)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#include "define.h"
#include "colors.h"

#include "brute_force.h"
#include "matrix.h"
#include "parser.h"
#include "city.h"
#include "array.h"
#include "ant_algorithm.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    // srand(_getpid());

    array cities; // Города представленые числами (индексами).

    char city_names[LEN]; // Города представленые буквами.
    int matrix[LEN][LEN]; // матрица смежности

    FILE *f = fopen(argv[1], "r");

    if (!f)
    {
        printf("Ошибка при попытки открыть файл.\n");
        return ERROR_OPEN_FILE;
    }

    int count = parser(f, city_names, matrix);

    fclose(f);

    create_cities_array(&cities, count);

    print_cities(cities, city_names);
    print_matrix(matrix, count);

    array result = get_shortest_path(cities, matrix);
    int min_path_simple = get_path_cost(result, matrix);
    print_array(result, "result");
    red();
    printf("result simple = %d\n", min_path_simple);

    array result_ant = ant_algorithm(matrix, count, cities, 50, 0.4, 0.7, 0.3);
    int min_path_ant = get_path_cost(result_ant, matrix);
    print_array(result_ant, "result ant");
    red();
    printf("result ant = %d\n", min_path_ant);

    parser_in_gv(RESULT_FILE_NAME_SIMPLE, city_names, matrix, result, count, "red");
    system(CREATE_RESULT_FILE_SIMPLE);
    system(OPEN_RESULT_FILE_SIMPLE);

    parser_in_gv(RESULT_FILE_NAME_ANT, city_names, matrix, result_ant, count, "blue");
    system(CREATE_RESULT_FILE_ANT);
    system(OPEN_RESULT_FILE_ANT);

    return OK;
}
