#include "../inc/read.hpp"


void read_number_action(int &action)
{   
    std::cout << YELLOW << 
            "\nmenu\n\n"
            "\t1. linear\n"
            "\t2. conveyor\n"
            "\t3. time analysis\n"
            "\t0. exit \n\n"
            "\tInput: "
            << BASE_COLOR << "\n";

    int r = scanf("%d", &action);
    if (r != 1)
        throw no_number_entered_error(__FILE__, __LINE__);

    if (action < MIN_COMMAND_NUMBER || action > MAX_COMMAND_NUMBER)
        throw number_action_error(__FILE__, __LINE__);
}


void read_number_rows_columns(int &n, int &m)
{   
    std::cout << BLUE << "\nInput num of rows: " << BASE_COLOR;

    int r = scanf("%d", &n);
    if (r != 1)
        throw no_number_entered_error(__FILE__, __LINE__);
        
    if (n <= 0)
        throw number_row_error(__FILE__, __LINE__);

    std::cout << BLUE << "Input number of cols: " << BASE_COLOR;
    
    r = scanf("%d", &m);
    if (r != 1)
        throw no_number_entered_error(__FILE__, __LINE__);

    if (m <= 0)
        throw number_column_error(__FILE__, __LINE__);
}

void read_number_matrices(int &cnt)
{
     std::cout << GREEN << "\ninput nums of matrixes: " << BASE_COLOR;

    int r = scanf("%d", &cnt);
    if (r != 1)
        throw no_number_entered_error(__FILE__, __LINE__);
        
    if (cnt <= 0)
        throw number_matrices_error(__FILE__, __LINE__);

    std::cout << "\n";
}
