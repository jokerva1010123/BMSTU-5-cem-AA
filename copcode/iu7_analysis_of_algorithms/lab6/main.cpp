#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <unistd.h>
#include <map>
#include <random>
#include <fstream>
#include "Log.h"
#include "Array.h"

#define threads_count 3
#define OBJ_COUNT 1000
#define ARRAY_SIZE 500
#define FIRST_LEVEL 1
#define SECOND_LEVEL 2
#define THIRD_LEVEL 3

using namespace std;

//auto static synchronizedFile = std::make_shared<SynchronizedFile>("log.txt");


int main(int argc, const char * argv[]) {


    std::cout << "Сonveyor" << std::endl;

    auto start1 = std::chrono::high_resolution_clock::now();

    thread threads[threads_count];

    queue<Array> q[threads_count];
    queue<Array> queue1;

    int obj[OBJ_COUNT];
    for(int i = 0; i < OBJ_COUNT; i++) {
        obj[i] = i+1;
    }

    int current_element = 0;

    while (q[2].size() != OBJ_COUNT) {
        if (current_element < OBJ_COUNT) {
            Array array(ARRAY_SIZE, obj[current_element]);
            queue1.push(array);
            current_element++;
        }

        // Level 1
        if (threads[0].joinable())
            threads[0].join();
        if (!queue1.empty() && !threads[0].joinable()) {
            Array front_array = queue1.front();
            queue1.pop();

            auto level1 = [](Array obj, queue<Array> &queue) {
                obj.rand_vec();

                mutex queue_mutex;
                queue_mutex.lock();
                queue.push(obj);
                queue_mutex.unlock();
            };

            threads[0] = thread(level1, front_array, ref(q[0]));
        }

        // Level 2
        if (threads[1].joinable()){
            threads[1].join();
        }
        if (!q[0].empty() && !threads[1].joinable()) {
            Array front_array = q[0].front();
            q[0].pop();

            auto level2 = [](Array obj, queue <Array> &queue) {
                obj.summa();

                mutex queue_mutex;
                queue_mutex.lock();
                queue.push(obj);
                queue_mutex.unlock();
            };

            threads[1] = thread(level2, front_array, ref(q[1]));
        }

        // Level 3
        if (threads[2].joinable()){
            threads[2].join();
        }
        if (!q[1].empty() && !threads[2].joinable()) {
            Array front_array = q[1].front();
            q[1].pop();

            auto level3 = [](Array obj, queue <Array> &queue) {
                string str = "file" + to_string(obj.get_id()) + ".txt";
                obj.print(str);

                mutex queue_mutex;
                queue_mutex.lock();
                queue.push(obj);
                queue_mutex.unlock();
            };

            threads[2] = thread(level3, front_array, ref(q[2]));
        }
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    auto dur1 = end1 - start1;
    auto ms1 = std::chrono::duration_cast<std::chrono::nanoseconds>(dur1).count();
    std::cout << "Time: " << ms1 << std::endl;

    std::cout << "Completed." << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    std::cout << "Simple." << std::endl;
    for (int i = 0; i < OBJ_COUNT; ++i) {
        Array array(ARRAY_SIZE, i);
        array.rand_vec();
        array.summa();
        string str = "file" + to_string(array.get_id()) + ".txt";
        array.print(str);
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    auto dur2 = end2 - start2;
    auto ms2 = std::chrono::duration_cast<std::chrono::nanoseconds>(dur2).count();
    std::cout << "Time: " << ms2 << std::endl;
    std::cout << "Completed." << std::endl;

    return 0;
}
