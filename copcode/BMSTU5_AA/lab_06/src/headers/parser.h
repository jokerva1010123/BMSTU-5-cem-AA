#ifndef _PARSER_H_

#define _PARSER_H_

#include "define.h"

#include "array.h"

int parser(FILE *f, char cities[LEN], int matrix[LEN][LEN]);

int parser_in_gv(char name_file[MAX_LEN_FILE_NAME], char cities[LEN], int matrix[LEN][LEN], array result, int const count, char clr[MAX_LEN_COLOR]);

#endif