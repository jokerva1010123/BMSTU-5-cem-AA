#include <bits/stdc++.h>

using namespace std;

struct matrix{
    std::vector<vector<double>> matr;
    int n, m;
};

using matrix_t = struct matrix;

struct matrix_state
{
    bool stage_1;
    bool stage_2;
    bool stage_3;
};

using matrix_state_t = struct matrix_state;

struct result_time
{
    int task;
    int tape;

    double beg;
    double end;

    chrono::time_point<chrono::system_clock> time_begin;
};

using res_time_t = struct result_time;

matrix_t generate_matrix(int n, int m)
{
    matrix_t matrix;
    matrix.n = n;
    matrix.m = m;
    matrix.matr.resize(n);
    for(int i = 0; i < n; i++)
        matrix.matr[i].resize(m);
    for (int i = 0; i < matrix.n; i++)
        for (int j = 0; j < matrix.m; j++)
            matrix.matr[i][j] = rand() % 90 + 10;
    return matrix;
}

matrix_t change_matrix(matrix_t matrix)
{
    int posi = -1, posj = -1;
    double sum = 1.0, average = 1.0, max_value = matrix.matr[0][0];
    for(int i = 0; i < matrix.n; i++)
        for(int j = 0; j < matrix.m; j++)
            sum *= matrix.matr[i][j];
    average = pow(sum, 1.0/(matrix.n * matrix.m));
    for(int i = 0; i < matrix.n; i++)
        for(int j = 0; j < matrix.m; j++)
        {
            max_value = max(max_value, matrix.matr[i][j]);
            if(matrix.matr[i][j] > average)
            {
                if(posi == -1)
                {
                    posi = i;
                    posj = j;
                }
                else if(matrix.matr[i][j] < matrix.matr[posi][posj])
                {
                    posi = i;
                    posj = j;
                }
            }
        }
    if (posi == -1)
        matrix.matr[0][0] = max_value;
    else
        matrix.matr[posi][posj] = max_value;
    return matrix;
}

matrix_t truncate_matrix(matrix_t matrix)
{
    matrix_t tmp_matrix;
    tmp_matrix.n = matrix.m;
    tmp_matrix.m = matrix.n;
    tmp_matrix.matr.resize(tmp_matrix.n);
    for(int i = 0; i < tmp_matrix.n; i++)
        tmp_matrix.matr[i].resize(tmp_matrix.m);
    for (int i = 0; i < tmp_matrix.n; i++)
        for(int j = 0; j < tmp_matrix.m; j++)
            tmp_matrix.matr[i][j] = matrix.matr[j][i];
    return tmp_matrix;
}

matrix_t mul_matrix(matrix_t matrixA, matrix_t matrixB)
{
    matrix_t tmp_matrix;
    tmp_matrix.n = matrixA.n;
    tmp_matrix.m = matrixB.m;
    tmp_matrix.matr.resize(tmp_matrix.n);
    for(int i = 0; i < tmp_matrix.n; i++)
        tmp_matrix.matr[i].resize(tmp_matrix.m);
    for (int i = 0; i < tmp_matrix.n; i++)
        for(int j = 0; j < tmp_matrix.m; j++)
        {
            tmp_matrix.matr[i][j] = 0;
            for(int k = 0; k < matrixA.m; k++)
                tmp_matrix.matr[i][j] = matrixA.matr[i][k] * matrixB.matr[k][j];
        }
    return tmp_matrix;
}

void init_time_result_arr(std::vector<res_time_t> &time_result_arr,
                          std::chrono::time_point<std::chrono::system_clock> time_begin,
                          int cnt_matr, int cnt_threads)
{
    int len = cnt_matr * cnt_threads;
    time_result_arr.resize(len);

    for (int i = 0; i < len; i++)
    {
        res_time_t time_res;
        time_res.time_begin = time_begin;

        time_result_arr[i] = time_res;
    }

}

void print_res_time(std::vector<res_time_t> &time_result_arr, int size_arr)
{
    printf("--------------------------------------------------------"
           "\n  № matrix  |   № step  | time start | time end \n"
           "--------------------------------------------------------\n");

    for (int i = 0; i < size_arr; i++)
    {
        printf("    %3d      |     %2d     |   %.6f   |   %.6f   \n",
                time_result_arr[i].task,
                time_result_arr[i].tape,
                time_result_arr[i].beg,
                time_result_arr[i].end);

        if ((i + 1) % 3 == 0)
        {
            printf("--------------------------------------------------------\n");
        }
    }
}

void save_result(std::vector<res_time_t> &time_result_arr,
                 std::chrono::time_point<std::chrono::system_clock> time_start,
                 std::chrono::time_point<std::chrono::system_clock> time_end,
                 std::chrono::time_point<std::chrono::system_clock> time_begin,
                 int task_num, int numb_stage)
{
    double beg_time = (std::chrono::duration_cast<std::chrono::nanoseconds>
                    (time_start - time_begin).count()) / 1e9;

    double end_time = (std::chrono::duration_cast<std::chrono::nanoseconds>
                    (time_end - time_begin).count()) / 1e9;

    int index = (task_num - 1) * 3 + numb_stage - 1;

    time_result_arr[index].task = task_num;
    time_result_arr[index].tape = numb_stage;
    time_result_arr[index].beg = beg_time;
    time_result_arr[index].end = end_time;
}

void task1(queue<matrix_t> &qA1, queue<matrix_t> &qA2, queue<matrix_t> &qB1, queue<matrix_t> &qB2)
{
    mutex m;

    m.lock();
    matrix_t tmp_matrixA = qA1.front();
    matrix_t tmp_matrixB = qB1.front();
    m.unlock();

    tmp_matrixA = change_matrix(tmp_matrixA);
    tmp_matrixB = change_matrix(tmp_matrixB);

    m.lock();
    qA2.push(tmp_matrixA);
    qB2.push(tmp_matrixB);
    m.unlock();

    m.lock();
    qA1.pop();
    qB1.pop();
    m.unlock();
}

void task2(queue<matrix_t> &qA2, queue<matrix_t> &qA3, queue<matrix_t> &qB2, queue<matrix_t> &qB3)
{
    mutex m;

    m.lock();
    matrix_t tmp_matrixA = qA2.front();
    matrix_t tmp_matrixB = qB2.front();
    m.unlock();

    tmp_matrixA = truncate_matrix(tmp_matrixA);
    tmp_matrixB = truncate_matrix(tmp_matrixB);

    m.lock();
    qA3.push(tmp_matrixA);
    qB3.push(tmp_matrixB);
    m.unlock();

    m.lock();
    qA2.pop();
    qB2.pop();
    m.unlock();
}

void task3(queue<matrix_t> &qA3, queue<matrix_t> &qB3, queue<matrix_t> &q_res)
{
    mutex m;

    m.lock();
    matrix_t tmp_matrixA = qA3.front();
    matrix_t tmp_matrixB = qB3.front();
    m.unlock();

    matrix_t tmp_matrix = mul_matrix(tmp_matrixA, tmp_matrixB);

    m.lock();
    q_res.push(tmp_matrix);
    m.unlock();

    m.lock();
    qA3.pop();
    qB3.pop();
    m.unlock();
}

void liner(int size, int cnt, bool is_count)
{
    queue<matrix_t> qA1;
    queue<matrix_t> qB1;
    queue<matrix_t> qA2;
    queue<matrix_t> qB2;
    queue<matrix_t> qA3;
    queue<matrix_t> qB3;
    queue<matrix_t> q_res;

    std::chrono::time_point<std::chrono::system_clock> time_start, time_end,
    time_begin = std::chrono::system_clock::now();

    std::vector<res_time_t> time_result_arr;
    init_time_result_arr(time_result_arr, time_begin, cnt, 3);

    for (int i = 0 ; i < cnt; i++)
    {
        matrix_t matrA = generate_matrix(size, size);
        matrix_t matrB = generate_matrix(size, size);
        qA1.push(matrA);
        qB1.push(matrB);
    }

    for (int i = 0; i < cnt; i++)
    {
        time_start = chrono::system_clock::now();
        task1(ref(qA1), ref(qA2), ref(qB1), ref(qB2));
        time_end = std::chrono::system_clock::now();

        save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, i + 1, 1);

        time_start = chrono::system_clock::now();
        task2(ref(qA2), ref(qA3), ref(qB2), ref(qB3));
        time_end = std::chrono::system_clock::now();

        save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, i + 1, 2);

        time_start = chrono::system_clock::now();
        task3(ref(qA3), ref(qB3), ref(q_res));
        time_end = std::chrono::system_clock::now();

        save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, i + 1, 3);
    }

    if(is_count)
    {
        printf("     %4d      |     %4d      |   %.6f  \n",
            size, cnt, time_result_arr[cnt - 1].end);
    }
    else
    {
        print_res_time(time_result_arr, cnt * 3);
    }
}

void parallel_stage_1(queue<matrix_t> &qA1, queue<matrix_t> &qA2, queue<matrix_t> &qB1, queue<matrix_t> &qB2, vector<matrix_state_t> &state, vector<res_time_t> &time_result_arr, bool &qA1_is_empty)
{
    chrono::time_point<chrono::system_clock> time_start, time_end;
    int task_num = 1;
    while(!qA1.empty())
    {
        time_start = chrono::system_clock::now();
        task1(qA1, qA2, qB1, qB2);
        time_end = std::chrono::system_clock::now();
        save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, task_num, 1);
        state[task_num - 1].stage_1 = true;
        task_num ++;
    }
    qA1_is_empty = true;
}

void parallel_stage_2(queue<matrix_t> &qA2, queue<matrix_t> &qA3, queue<matrix_t> &qB2, queue<matrix_t> &qB3, vector<matrix_state_t> &state, vector<res_time_t> &time_result_arr, bool &qA1_is_empty, bool &qA2_is_empty)
{
    chrono::time_point<chrono::system_clock> time_start, time_end;
    int task_num = 1;
    while(1)
    {
        if(qA2.empty() == false)
        {
            if(state[task_num - 1].stage_1 == true)
            {
                time_start = chrono::system_clock::now();
                task2(qA2, qA3, qB2, qB3);
                time_end = std::chrono::system_clock::now();

                save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, task_num, 2);

                state[task_num - 1].stage_2 = true;
                task_num ++;  
            }
        }
        else if(qA1_is_empty)
                break;
    }
    qA2_is_empty = true;
}

void parallel_stage_3(queue<matrix_t> &qA3, queue<matrix_t> &qB3, queue<matrix_t> &q_res, vector<matrix_state_t> &state, vector<res_time_t> &time_result_arr, bool &qA2_is_empty, int cnt)
{
    chrono::time_point<chrono::system_clock> time_start, time_end;
    int task_num = 1;
    while(1)
    {
        if(qA3.empty() == false)
        {
            if(state[task_num - 1].stage_2 == true)
            {
                time_start = chrono::system_clock::now();
                task3(qA3, qB3, q_res);
                time_end = std::chrono::system_clock::now();
                save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, task_num, 3);
                state[task_num - 1].stage_3 = true;
                task_num ++;
            }
        }
        else if(qA2_is_empty)
            break;
    }
}

void parallel(int size, int cnt, bool is_count)
{
    queue<matrix_t> qA1;
    queue<matrix_t> qB1;
    queue<matrix_t> qA2;
    queue<matrix_t> qB2;
    queue<matrix_t> qA3;
    queue<matrix_t> qB3;
    queue<matrix_t> q_res;

    for (int i = 0; i < cnt; i++)
    {
        matrix_t matrA = generate_matrix(size, size);
        matrix_t matrB = generate_matrix(size, size);
        qA1.push(matrA);
        qB1.push(matrB);
    }
    bool qA1_is_empty = false;
    bool qA2_is_empty = false;
    vector<matrix_state_t> state(cnt);
    for (int i = 0; i < cnt; i++)
    {
        matrix_state_t tmp_state;
        tmp_state.stage_1 = false;
        tmp_state.stage_2 = false;
        tmp_state.stage_3 = false;
        state[i] = tmp_state;
    }
    chrono::time_point<std::chrono::system_clock> time_begin = chrono::system_clock::now();
    vector<res_time_t> time_result_arr;
    init_time_result_arr(time_result_arr, time_begin, cnt, 3);
    thread threads[3];
    threads[0] = thread(parallel_stage_1, ref(qA1), ref(qA2), ref(qB1), ref(qB2), ref(state), ref(time_result_arr), ref(qA1_is_empty));
    threads[1] = thread(parallel_stage_2, ref(qA2), ref(qA3), ref(qB2), ref(qB3), ref(state), ref(time_result_arr), ref(qA1_is_empty), ref(qA2_is_empty));
    threads[2] = thread(parallel_stage_3, ref(qA3), ref(qB3), ref(q_res), ref(state), ref(time_result_arr), ref(qA2_is_empty), cnt);
    for (int i = 0; i < 3; i++)
        threads[i].join();
    if(is_count)
        printf("     %4d      |     %4d      |   %.6f  \n",
            size, cnt, time_result_arr[cnt - 1].end);
    else
        print_res_time(time_result_arr, cnt * 3);
}

int read_number_action(int &action)
{
    std::cout <<
            "\nMenu\n\n"
            "\t1. linear\n"
            "\t2. conveyor\n"
            "\t3. time analysis\n"
            "\t0. exit \n\n"
            "\tInput: ";

    int r = scanf("%d", &action);
    return r;
}

void compare_time()
{
    cout << "Tome conveyor\n";
    printf(" Matrix size | Number matrix |  Time end  \n"
           "-----------------------------------------------\n");
    for (int i = 50; i < 2000; i *= 2)
    {
        parallel(100, i, true);
    }
    cout << "Time for linear\n";
    printf(" Matrix size | Number matrix |  Time end  \n"
           "-----------------------------------------------\n");
    for (int i = 50; i < 2000; i *= 2)
    {
        liner(100, i, true);
    }
    cout << "Time conveyor size\n";
    printf(" Matrix size | Number matrix |  Time end  \n"
           "-----------------------------------------------\n");
    for (int i = 20; i < 500; i *= 2)
    {
        parallel(i, 100, true);
    }
    cout << "Time linear size\n";
    printf(" Matrix size | Number matrix |  Time end  \n"
           "-----------------------------------------------\n");
    for (int i = 20; i < 500; i *= 2)
    {
        liner(i, 100, true);
    }

}

int main()
{
    srand(time(nullptr));
    int action = -1;
    while(action)
    {
        int a = read_number_action(action);
        if (a != 1 || (a == 1 && (action < 0 || action > 3)))
        {
            cout << "Input again!\n";
            continue;
        }
        if (action == 1)
        {
            int size, cnt;
            cout << "Input size matrix: ";
            cin >> size;
            cout << "Input number of matrix: ";
            cin >> cnt;
            liner(size, cnt, false);
        }
        else if (action == 2)
        {
            int size, cnt;
            cout << "Input size matrix: ";
            cin >> size;
            cout << "Input number of matrix: ";
            cin >> cnt;
            parallel(size, cnt, false);
        }
        else if (action == 3)
        {
            compare_time();
        }
    }
    return 0;
}
