#include <iostream>
#include <cstdarg>
#include <cstring>
#include <fstream>

int minimum(int n, ...)
{
    va_list  vl;
    va_start(vl, n);
    int k = va_arg(vl, int), min = k;
    for (int i = 0; i < n - 1; i++)
    {
        k = va_arg(vl, int);
        if (k < min)
            min = k;
    }
    va_end(vl);
    return min;
}
int levCache(const char * s1, const char * s2)
{
    size_t n = strlen(s1) + 1;
    size_t m = strlen(s2) + 1;

    int *fs = (int *)malloc(n * sizeof(int));
    int *ss = (int *)malloc(n * sizeof(int));
    for (size_t i = 0; i < n; i++)
        fs[i] = i;

    for (size_t i = 1; i < m; i++)
    {
        ss[0] = i;
        for (size_t j = 1; j < n; j++)
            ss[j] = minimum(3,
                        fs[j] + 1,
                        ss[j - 1] + 1,
                        fs[j - 1] + (s2[i - 1] != s1[j - 1]) );
        for (size_t j = 0; j < n; j++) {
            fs[j] = ss[j];
        }
    }

    int rv = ss[n - 1];
    free(fs);
    free(ss);

    return rv;
}

int _recLev(const char * s1, const char * s2, int n, int m)
{
    if (n == 0)
        return m;
    if (m == 0)
        return n;

    return minimum(3,
                   _recLev(s1, s2, n - 1, m) + 1,
                   _recLev(s1, s2, n - 1, m - 1) + (s1[n - 1] != s2[m - 1]),
                   _recLev(s1, s2, n, m - 1) + 1);
}

int recLev(const char * s1, const char * s2)
{
    return _recLev(s1, s2, strlen(s1), strlen(s2));
}

int _recDamLev(const char * s1, const char * s2, int n, int m)
{
    if (n == 0)
        return m;
    if (m == 0)
        return n;
    int min = minimum(3,
                _recDamLev(s1, s2, n, m - 1) + 1,
                _recDamLev(s1, s2, n - 1, m) + 1,
                _recDamLev(s1, s2, n - 1, m - 1) + (s1[n - 1] != s2[m - 1]));

    if (n > 1 && m > 1 && s1[n - 1] == s2[m - 2] && s1[n - 2] == s2[m - 1])
        min = minimum(2, min, _recDamLev(s1, s2, n - 2, m - 2) + 1);
    return min;
}

int recDamLev(const char * s1, const char * s2)
{
    return _recDamLev(s1, s2, strlen(s1), strlen(s2));
}
void free_matrix(int **matr, int n, int m)
{
    for (int i = 0; i < n; i++)
        free(matr[i]);
    free(matr);
}
int ** alloc_matrix(int n, int m)
{
    int **matr = (int **) calloc(n, sizeof (int *));
    if (matr == NULL)
        return NULL;
    for (int i = 0; i < n; i++) {
        matr[i] = (int *) malloc(m * sizeof(int));
        if (matr[i] == NULL)
            free_matrix(matr, n , m);
    }
    return matr;
}
static int _recLevCache(const char * s1, const char * s2, int n, int m, int ** matr)
{
    if (matr[n][m] == -1)
    {
        matr[n][m] = minimum(3,
                             _recLevCache(s1, s2, n, m - 1, matr) + 1,
                             _recLevCache(s1, s2, n - 1, m, matr) + 1,
                             _recLevCache(s1, s2, n - 1, m - 1, matr) + (s1[n - 1] != s2[m - 1]));
    }
    return matr[n][m];
}

int recLevCache(const char * s1, const char * s2)
{
    int n = strlen(s1);
    int m = strlen(s2);

    int **matr = alloc_matrix(n + 1, m + 1);

    for (int i = 0; i < n + 1; i++)
        matr[i][0] = i;
    for (int i = 0; i < m + 1; i++)
        matr[0][i] = i;
    for (int i = 1; i < n + 1; i++)
        for (int j = 1; j < m + 1; j++)
            matr[i][j] = -1;
    int rv = _recLevCache(s1, s2, n, m, matr);
    free_matrix(matr, n, m);
    return rv;
}

double checkTime(int (*algo)(const char *, const char *), const char *s1, const char *s2)
{
    int times = 10;
    double time = 0;
    for (int i = 0; i < times; i++) {
        clock_t sTime = clock();
        algo(s1, s2);
        clock_t eTime = clock();
        time += (eTime - sTime);
    }
    time /= times;
    return time;
}
using namespace std;
int main() {
    string s1, s2;
    cin>> s1;
    cin>> s2;
    cout << recLev(s1.c_str(), s2.c_str());
    cout << recLevCache(s1.c_str(), s2.c_str());
    cout << recDamLev(s1.c_str(), s2.c_str());
    cout << levCache(s1.c_str(), s2.c_str());
//    string s1[10];
//    string s2[10];
//
//    ifstream istr("/Users/kate/Desktop/aa/lab_01/src/strings.txt");
//    if (istr.is_open())
//    {
//        for (int i = 0; i < 10; i++)
//            istr >> s1[i] >> s2[i];
//
//        istr.close();

        //python
//        int (*(funcs[4]))(const char *, const char *) = {levCache, recDamLev, recLev, recLevCache};
//        printf("x = [");
//        for (int j = 0; j < 10; j++) {
//            if (j != 9)
//                printf("%d, ", j + 3);
//            else
//                printf("%d]\n", j + 3);
//        }
//        printf("y1 = [");
//        for (int j = 0; j < 10; j++) {
//            if (j != 9)
//                printf("%.2lf, ", checkTime(funcs[0], s1[j].c_str(), s2[j].c_str()));
//            else
//                printf("%.2lf]\n", checkTime(funcs[0], s1[j].c_str(), s2[j].c_str()));
//        }
//        printf("y2 = [");
//        for (int j = 0; j < 10; j++) {
//            if (j != 9)
//                printf("%.2lf, ", checkTime(funcs[1], s1[j].c_str(), s2[j].c_str()));
//            else
//                printf("%.2lf]\n", checkTime(funcs[1], s1[j].c_str(), s2[j].c_str()));
//        }
//        printf("y3 = [");
//        for (int j = 0; j < 10; j++) {
//            if (j != 9)
//                printf("%.2lf, ", checkTime(funcs[2], s1[j].c_str(), s2[j].c_str()));
//            else
//                printf("%.2lf]\n", checkTime(funcs[2], s1[j].c_str(), s2[j].c_str()));
//        }
//        printf("y4 = [");
//        for (int j = 0; j < 10; j++) {
//            if (j != 9)
//                printf("%.2lf, ", checkTime(funcs[3], s1[j].c_str(), s2[j].c_str()));
//            else
//                printf("%.2lf]\n", checkTime(funcs[3], s1[j].c_str(), s2[j].c_str()));
//        }

            // latex
//        for (int j = 0; j < 10; j++) {
//            printf("%d &", j + 3);
//            for (int i = 0; i < 3; i++) {
//                printf(" %.2lf &", checkTime(funcs[i], s1[j].c_str(), s2[j].c_str()));
//            }
//            printf(" %.2lf  \\\\ \n\\hline", checkTime(funcs[3], s1[j].c_str(), s2[j].c_str()));
//            printf("\n");
//        }
//    }

    return 0;
}
