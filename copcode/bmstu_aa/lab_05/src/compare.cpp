#include "../inc/compare.hpp"
#include "../inc/matrix.hpp"
#include "../inc/conveyor.hpp"


void compare_time(void)
{   
    std::cout << BLUE <<
        "\nЗTome conveyor\n\n"
              << BASE_COLOR;

    printf(" matrix size %s|%s number matrix %s|%s  time end  \n"
           "%s-----------------------------------------------\n%s",
            PURPLE, BASE_COLOR, PURPLE, BASE_COLOR, PURPLE, BASE_COLOR);

    for (int i = 50; i < 2000; i *= 2)
    {
        parallel_processing(100, 100, i, false, true);
    }


    std::cout << BLUE <<
        "\nTime for linear\n\n"
              << BASE_COLOR;

    printf(" matrix size %s|%s number matrix %s|%s  time end  \n"
           "%s-----------------------------------------------\n%s",
            PURPLE, BASE_COLOR, PURPLE, BASE_COLOR, PURPLE, BASE_COLOR);

    for (int i = 50; i < 2000; i *= 2)
    {
        linear_processing(100, 100, i, false, true);
    }
    

    std::cout << GREEN <<
        "\nTime conveyor size\n\n"
              << BASE_COLOR;

    printf(" matrix size %s|%s number matrix %s|%s  time end  \n\n"
           "%s-----------------------------------------------\n%s",
            PURPLE, BASE_COLOR, PURPLE, BASE_COLOR, PURPLE, BASE_COLOR);

    for (int i = 20; i < 1000; i *= 2)
    {
        parallel_processing(i, i, 100, false, true);
    }


    std::cout << GREEN <<
        "\nTime linear size\n\n"
              << BASE_COLOR;

    printf(" matrix size %s|%s number matrix %s|%s  time end  \n"
           "%s-----------------------------------------------\n%s",
            PURPLE, BASE_COLOR, PURPLE, BASE_COLOR, PURPLE, BASE_COLOR);

    for (int i = 20; i < 1000; i *= 2)
    {
        linear_processing(i, i, 100, false, true);
    }
}
