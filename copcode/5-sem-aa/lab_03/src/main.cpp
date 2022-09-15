#include <iostream>
#include "Array.h"
#include <sys/time.h>
typedef struct
{
    int f, s;
}at;
int cmp(int a, int b)
{
    return a - b;
}
std::ostream& operator<<(std::ostream& os, at elem)
{
    std::cout << "{ " << elem.f << ", " << elem.s << "} ";
    return os;
}
template <typename Type>
double checkTime(Array<Type> &a, int (*cmp)(Type, Type), void (Array<Type>::*sort)(int (*cmp)(Type, Type)))
{
    struct timeval tv_start, tv_stop;
    double time = 0;
    for (int i = 0; i < 100; i++) {
        for (size_t i = 0; i < a.getLength(); i++)
            a[i] = a.getLength() - i;
        clock_t sTime = clock();
        (a.*sort)(cmp);
        clock_t eTime = clock();
        time += (eTime - sTime);
    }
    time /= .001 * CLOCKS_PER_SEC;
    return time;
}
int main() {
    int length = 10;
    Array<int> b(length, 0);
    for (int i = 0; i < length; i++)
        b[i] = rand() % 10 - 5;
    std::cout << b <<std::endl;
    b.qsort(cmp);
    std::cout << b;

    // latex
//    for (int size = 100; size < 1100; size += 100) {
//        printf("%d &", size);
//        Array<int> a(size, 0);
//        printf(" %.2lf &", checkTime(a, cmp, &Array<int>::bubble));
//        printf(" %.2lf &", checkTime(a, cmp, &Array<int>::selection));
//        printf(" %.2lf  \\\\ \n\\hline", checkTime(a, cmp, &Array<int>::qsort));
//        printf("\n");
//    }

    // python
//    printf("[");
//    for (int size = 100; size < 1100; size += 100) {
//        Array<int> a(size, 0);
//        if (size != 1000)
//            printf("%d, ", size);
//        else
//            printf("%d", size);
//    }
//    printf("]\n");
//
//    printf("[");
//    for (int size = 100; size < 1100; size += 100) {
//        Array<int> a(size, 0);
//        if (size != 1000)
//            printf("%.2lf, ", checkTime(a, cmp, &Array<int>::bubble));
//        else
//            printf("%.2lf", checkTime(a, cmp, &Array<int>::bubble));
//    }
//    printf("]\n");
//
//    printf("[");
//    for (int size = 100; size < 1100; size += 100) {
//        Array<int> a(size, 0);
//        if (size != 1000)
//            printf("%.2lf, ", checkTime(a, cmp, &Array<int>::selection));
//        else
//            printf("%.2lf", checkTime(a, cmp, &Array<int>::selection));
//    }
//    printf("]\n");
//
//    printf("[");
//    for (int size = 100; size < 1100; size += 100) {
//        Array<int> a(size, 0);
//        if (size != 1000)
//            printf("%.2lf, ", checkTime(a, cmp, &Array<int>::qsort));
//        else
//            printf("%.2lf", checkTime(a, cmp, &Array<int>::qsort));
//    }
//    printf("]\n");
    return 0;
}
