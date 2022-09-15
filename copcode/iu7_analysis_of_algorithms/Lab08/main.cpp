#include <iostream>

#include "KMP.h"
#include "BM.h"

int main() {
    std::cout << "BM:" << std::endl;
    char txt[] = "ABABABABA";
    char pat[] = "ABA";
    int *arr = (search(txt, pat));
    std::cout << "Pattern found at index = "  << search(txt, pat) << std::endl;


    std::cout << std::endl;
    std::cout << "KMP:" << std::endl;
    char txt1[] = "ABABABABA";
    char pat1[] = "ABA";

    std::cout << "Pattern found at index = "  << KMPSearch(pat1, txt1) << std::endl;

    return 0;
}