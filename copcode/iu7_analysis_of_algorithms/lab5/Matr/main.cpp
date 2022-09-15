#include "Winograd.h"

#include <chrono>
#include <ctime>
//#include "Matrix.h"

void test(int a) {
    //std::cout << std::thread::hardware_concurrency() << std::endl;

    int b;
    a = b = 100;

    Matrix<int> matr(a,b, 1);
    int k = 1;
    for (int i = 0; i < a; ++i) {
        for (int &j : matr[i]) {
            j = k;
            k++;
        }
    }
//    matr.show();
    auto classic = 0;
    auto winograd = 0;
    auto winorad_opt = 0;


//    matr.show();

    Matrix<int> matr2 = matr;
    //std::cout << std::endl;
//    matr2.show();
// for (int i = 0; i < 5; ++i) {
    auto start = std::chrono::high_resolution_clock::now();
    Matrix<int>matr_result = classic_mult(matr, matr2);
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    //std::cout << std::endl;
    auto ms = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
    std::cout << "Classic time: " << ms << std::endl;
//    matr_result.show();
//        classic += ms;


    auto start_1 = std::chrono::high_resolution_clock::now();
    Matrix<int> winograd_result = Winograd(matr, matr2);
    auto end_1 = std::chrono::high_resolution_clock::now();
    auto dur_1 = end_1 - start_1;
    auto ms_1 = std::chrono::duration_cast<std::chrono::microseconds>(dur_1).count();
    std::cout << "Winograd time: " << ms_1 << std::endl;
    winograd += ms_1;

    auto start_2 = std::chrono::high_resolution_clock::now();
    Matrix<int> winograd_result_opt = classic_mult_parall(matr, matr2);
    auto end_2 = std::chrono::high_resolution_clock::now();
    auto dur_2 = end_2 - start_2;
    auto ms_2 = std::chrono::duration_cast<std::chrono::microseconds>(dur_2).count();
    std::cout << "Classic_parall time: " << ms_2 << std::endl;
//        winograd_result_opt.show();
//        winorad_opt += ms_2;

    auto start_3 = std::chrono::high_resolution_clock::now();
    Matrix<int> winograd_result_parall = Winograd_parall(matr, matr2);
    auto end_3 = std::chrono::high_resolution_clock::now();
    auto dur_3 = end_3 - start_3;
    auto ms_3 = std::chrono::duration_cast<std::chrono::microseconds>(dur_3).count();
    std::cout << "Winograd_parall time: " << ms_3 << std::endl;
    std::cout << std::endl;
//        winograd_result_opt.show();
//        winorad_opt += ms_2;
//    }

//    classic /= 5;
//    winograd /= 5;
//    winorad_opt /= 5;
//    std::cout << std::endl;
//
//    std::cout << "Classic time:  /" << classic << std::endl;
//    std::cout << "Winograd time:  /" << winograd << std::endl;
//    std::cout << "Winograd_opt time:  /" << winorad_opt << std::endl;
}

int main(int argc, const char * argv[]) {
    while (true){
        std::cout << "N: ";
        int n;
        std::cin >> n;
        test(n);
    }

    return 0;
}