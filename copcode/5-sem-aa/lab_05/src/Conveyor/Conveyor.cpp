//
// Created by Екатерина on 12.11.2021.
//

#include "Conveyor.h"
std::mutex mtx;
template <typename type>
void SafeQueue<type>::push(type val)
{
    mtx.lock();
    q.push(val);
    mtx.unlock();
}
template <typename type>
void SafeQueue<type>::pop()
{
    mtx.lock();
    q.pop();
    mtx.unlock();
}
template <typename type>
bool SafeQueue<type>::empty()
{
    bool r;
    mtx.lock();
    r = q.empty();
    mtx.unlock();
    return r;
}
template <typename type>
type SafeQueue<type>::front()
{
    type val;
    mtx.lock();
    val = q.front();
    mtx.unlock();
    return val;
}
void init_stats(size_t task_num, task_stats_t *stats, event_t event, unsigned long long time)
{
    if (event == TASK_1_STARTED) {
        mtx.lock();
        if (task_num == 1) {
            stats[task_num].start_time = time;
        }
        stats[task_num].system_time = stats[1].start_time;
        mtx.unlock();
        stats[task_num].task1_time = time;
    } else if (event == TASK_1_ENDED) {
        stats[task_num].proc_time = time - stats[task_num].task1_time;
    }
    else if (event == TASK_2_STARTED)
    {
        stats[task_num].task2_time = time;
    } else if (event == TASK_2_ENDED) {
        stats[task_num].proc_time += time - stats[task_num].task2_time;
    } else if (event == TASK_3_STARTED)
    {
        stats[task_num].task3_time = time;
    } else if (event == TASK_3_ENDED) {
        stats[task_num].proc_time += time - stats[task_num].task3_time;
        stats[task_num].system_time = time - stats[task_num].system_time;
    }
}
std::string eventToString(event_t &event)
{
    if (event == TASK_1_STARTED)
        return "Part 1 | Start";
    if (event == TASK_1_ENDED)
        return "Part 1 | End";
    if (event == TASK_2_STARTED)
        return "Part 2 | Start";
    if (event == TASK_2_ENDED)
        return "Part 2 | End";
    if (event == TASK_3_STARTED)
        return "Part 3 | Start";
    if (event == TASK_3_ENDED)
        return "Part 3 | End";

}
void log_current_event(size_t task_num, task_stats_t *stats, event_t event)
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration tp = now.time_since_epoch();

    tp -= duration_cast<std::chrono::seconds>(tp);

    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm t = *gmtime(&tt);
    unsigned long long time = t.tm_min * 60 * 1000 + t.tm_sec * 1000 + static_cast<unsigned long long>(tp / std::chrono::milliseconds(1));
    //init_stats(task_num, stats, event, time);
    std::printf("Task №%lu | %s | %02u:%02u:%02u.%3u\n",
                task_num,
                eventToString(event).c_str(),
                t.tm_hour,
                t.tm_min,
                t.tm_sec,
                static_cast<unsigned long long>(tp / std::chrono::milliseconds(1))
    );
}
void Сookies::calcEgg(int n) // fib
{
    int f1 = 1, f2 = 1;

    for (int i = 2; i < n; i++)
    {
        this->eggs = f1 + f2;
        f1 = f2;
        f2 = this->eggs;
    }
}
void Сookies::calcButter(int num, int deg)  // num ^ degree
{
    this->butter = num;
    for (int i = 0; i < deg - 1; i++)
        this->butter *= num;
}
void Сookies::calcFlour(long n)  // factorial
{
    this->flour = 1;
    for (int i = 1; i <= n; i++)
        this->flour *= i;
}
void Conveyor::run_par(size_t count, task_stats_t *stats)
{
    this->stats = stats;
    for (size_t i = 0; i < count; i++)
    {
        std::shared_ptr<Сookies> p(new Сookies);
        cookies.push_back(p);
        q1.push(p);
    }

    this->threads[0] = std::thread(&Conveyor::calcEgg, this);
    this->threads[1] = std::thread(&Conveyor::calcButter, this);
    this->threads[2] = std::thread(&Conveyor::calcFlour, this);

    for (int i = 0; i < 3; i++)
    {
        this->threads[i].join();
    }
}

void Conveyor::run_seq(size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        std::shared_ptr<Сookies> c(new Сookies);
        c->calcEgg(1000000);
        c->calcButter(2, 1000000);
        c->calcFlour(1000000);
    }
}

void Conveyor::calcEgg()
{

    size_t task_num = 1;

    while (!this->q1.empty())
    {
        std::shared_ptr<Сookies> c = q1.front();
        log_current_event(task_num, stats, TASK_1_STARTED);
        c->calcEgg(90000000);
        log_current_event(task_num, stats, TASK_1_ENDED);
        q2.push(c);
        q1.pop();
        task_num++;
    }

}

void Conveyor::calcButter()
{
    size_t task_num = 1;

    do
    {
        if (!this->q2.empty())
        {
            std::shared_ptr<Сookies> c = q2.front();
            log_current_event(task_num, stats, TASK_2_STARTED);
            c->calcButter(2, 90000000);
            log_current_event(task_num, stats, TASK_2_ENDED);


            q3.push(c);
            q2.pop();
            task_num++;
        }
    } while(!q1.empty() || !q2.empty());
}

void Conveyor::calcFlour()
{
    size_t task_num = 1;

    do
    {
        if (!this->q3.empty())
        {
            std::shared_ptr<Сookies> c = q3.front();
            log_current_event(task_num, stats, TASK_3_STARTED);
            c->calcFlour(90000000);
            log_current_event(task_num, stats, TASK_3_ENDED);
            q3.pop();
            task_num++;
        }
    } while (!q1.empty() || !q2.empty() || !q3.empty());
}