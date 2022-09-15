//
// Created by Мхитарян Виктория on 2018-12-19.
//

#ifndef LAB06_ARRAY_H
#define LAB06_ARRAY_H

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

class Array {
private:
    std::vector<int> array;
    int length;
    int id;

    void timeout() {
        int wait_time = rand()%2000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(wait_time));
    }

public:
    Array(int length, int id) {
        this->length = length;
        this->id = id;
        for (int i = 0; i < length; ++i) {
            array.push_back(0);
        }
    };

    void rand_vec() {
        timeout();

        for (int i = 0; i < length; ++i) {
            array[i] = rand()%1000;
        }
    }

    void summa() {
        timeout();
        int sum = 0;
        for (int i = 0; i < length; i++){
            sum += array[i];
        }
        array[0] = sum;
    }

    void print(std::string file_name) {
        std::ofstream file (file_name);

        timeout();

        file << "Summa: ";
        file << array[0];
        file << "\n";
    }

    int get_id() {
        return id;
    }
};

#endif //LAB06_ARRAY_H
