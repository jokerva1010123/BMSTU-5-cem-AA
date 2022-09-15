//
// Created by Екатерина on 12.11.2021.
//

#ifndef SRC_CONVEYOR_H
#define SRC_CONVEYOR_H
#include <thread>
#include <queue>
#include <iostream>
#include <chrono>
#include <mutex>
#define th 8
template <typename type>
class SafeQueue
{
public:
    void push(type val);
    void pop();
    bool empty();
    type front();

private:
    std::queue<type> q;
};
class Сookies
{
public:
    void calcButter(int num, int deg);
    void calcFlour(long n);
    void calcEgg(int n); 
private:
    int eggs;
    int flour;
    int butter;
};
typedef struct
{
    unsigned long long system_time;
    unsigned long long proc_time;
    unsigned long long task1_time;
    unsigned long long task2_time;
    unsigned long long task3_time;
    unsigned long long start_time;
} task_stats_t;
typedef enum
{
    TASK_1_STARTED,
    TASK_1_ENDED,
    TASK_2_STARTED,
    TASK_2_ENDED,
    TASK_3_STARTED,
    TASK_3_ENDED
} event_t;
class Conveyor {
public:
    void run_par(size_t count, task_stats_t *stats);
    void run_seq(size_t count);

private:
    void calcButter();
    void calcFlour();
    void calcEgg();
    std::vector<std::shared_ptr<Сookies>> cookies;
    std::thread threads[th];
    SafeQueue<std::shared_ptr<Сookies>> q1;
    SafeQueue<std::shared_ptr<Сookies>> q2;
    SafeQueue<std::shared_ptr<Сookies>> q3;
    task_stats_t *stats;

};


#endif //SRC_CONVEYOR_H
