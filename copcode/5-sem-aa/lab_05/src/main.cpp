#include <iostream>
#include "Conveyor/Conveyor.h"
tm getTime(unsigned long long &ms)
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration tp = now.time_since_epoch();

    tp -= duration_cast<std::chrono::seconds>(tp);

    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm t = *gmtime(&tt);
    ms = t.tm_min * 60 * 1000 + t.tm_sec * 1000 + static_cast<unsigned long long>(tp / std::chrono::milliseconds(1));
    return t;
}
//#define N 800
int main() {
    Conveyor c;
    task_stats_t stats[8 + 1];
    c.run_par(8, stats);
//    for (int N = 100; N < 1100; N+=100) {
//        task_stats_t stats[N + 1];
//        Conveyor c;
//
//        unsigned long long bp, ep;
//        tm tbp = getTime(bp);
//        c.run_par(N, stats);
//        tm tep = getTime(ep);
//
////        printf("%llu, ", (tep.tm_sec - tbp.tm_sec) * 1000 + ep - bp);
//        long sum_system = 0;
//        long sum_proc = 0;
//        for (int i = 1; i < N + 1; i++)
//        {
//            sum_system += stats[i].system_time;
//            sum_proc += stats[i].proc_time;
//            //printf("task: %d, proc time: %lu; system time: %lu\n", i, stats[i].proc_time, stats[i].system_time);
//        }
//        double avg_queue = (sum_system - sum_proc) / (N * 1.0);
//        printf("%d & %.3lf & %.3lf & %.3lf \\\\\n\\hline\n", N, avg_queue, sum_system / (N * 1.0), sum_proc / (N * 1.0));
//    }
    return 0;
}
//std::cout << "x = [";
//for (int i =100; i < 1100; i+=100)
//std::cout << i << ", ";
//std::cout << "]\ny1 = [";
//for (int N = 100; N < 1100; N+=100) {
//task_stats_t stats[N + 1];
//Conveyor c;
//
//unsigned long long bs, es;
//tm tbs = getTime(bs);
//c.run_seq(N);
//tm tes = getTime(es);
//
//printf("%llu, ", (tes.tm_sec - tbs.tm_sec) * 1000 + es - bs);
//}
//std::cout << "]\ny2 = [";
//for (int N = 100; N < 1100; N+=100) {
//task_stats_t stats[N + 1];
//Conveyor c;
//
//unsigned long long bp, ep;
//tm tbp = getTime(bp);
//c.run_par(N, stats);
//tm tep = getTime(ep);
//
//printf("%llu, ", (tep.tm_sec - tbp.tm_sec) * 1000 + ep - bp);
//}
//std::cout << "]";