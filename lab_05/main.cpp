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

void liner(int n, int m, int p, int q, int cnt)
{
    queue<matrix_t> qA1;
    queue<matrix_t> qB1;
    queue<matrix_t> qA2;
    queue<matrix_t> qB2;
    queue<matrix_t> qA3;
    queue<matrix_t> qB3;
    queue<matrix_t> q_res;

    for (int i = 0 ; i < cnt; i++)
    {
        matrix_t matrA = generate_matrix(n, m);
        matrix_t matrB = generate_matrix(p, q);
        qA1.push(matrA);
        qB1.push(matrB);
    }

    for (int i = 0; i < cnt; i++)
    {
        task1(ref(qA1), ref(qA2), ref(qB1), ref(qB2));
       // task1(ref(qB1), ref(qB2));
        task2(ref(qA2), ref(qA3), ref(qB2), ref(qB3));
        //task2(ref(qB2), ref(qB3));

        task3(ref(qA3), ref(qB3), ref(q_res));
    }
}

void parallel_stage_1(queue<matrix_t> &qA1, queue<matrix_t> &qA2, queue<matrix_t> &qB1, queue<matrix_t> &qB2, vector<matrix_state_t> &state, bool &qA1_is_empty)
{
    int task_num = 1;
    while(!qA1.empty())
    {
        task1(qA1, qA2, qB1, qB2);
        state[task_num - 1].stage_1 = true;
        task_num ++;
    }
    qA1_is_empty = true;
}

void parallel_stage_2(queue<matrix_t> &qA2, queue<matrix_t> &qA3, queue<matrix_t> &qB2, queue<matrix_t> &qB3, vector<matrix_state_t> &state, bool &qA1_is_empty, bool &qA2_is_empty)
{
    int task_num = 1;
    while(1)
    {
        if(!qA2.empty())
            if(state[task_num - 1].stage_1 == true)
            {
                task2(qA2, qA3, qB2, qB3);
                state[task_num].stage_2 = true;
                task_num ++;
            }
        if(qA2.empty())
            break;
    }
    qA2_is_empty = true;
}

void parallel_stage_3(queue<matrix_t> &qA3, queue<matrix_t> &qB3, queue<matrix_t> &q_res, vector<matrix_state_t> &state, bool &qA2_is_empty, int cnt)
{
    int task_num = 1;
    while(1)
    {
        if(!qA3.empty())
        {
            if(state[task_num - 1].stage_2 = true)
            {
                task3(qA3, qB3, q_res);
                state[task_num - 1].stage_3 = true;
                task_num ++;
            }
        }
        if(qA3.empty())
            break;
    }
}

void parallel(int n, int m, int p, int q, int cnt)
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
        matrix_t matrA = generate_matrix(n, m);
        matrix_t matrB = generate_matrix(p, q);
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

    thread threads[3];

    threads[0] = std::thread(parallel_stage_1, ref(qA1), ref(qA2), ref(qB1), ref(qB2), ref(state), ref(qA1_is_empty));
    threads[1] = std::thread(parallel_stage_2, ref(qA2), ref(qA3), ref(qB2), ref(qB3), ref(state), ref(qA1_is_empty), ref(qA2_is_empty));
    threads[2] = std::thread(parallel_stage_3, ref(qA3), ref(qB3), ref(q_res), ref(state), ref(qA2_is_empty), cnt);

    for (int i = 0; i < 3; i++)
        threads[i].join();
}

int main()
{
    srand(time(nullptr));
    int abc = 400;
    std::chrono::time_point<std::chrono::system_clock> time_begin = std::chrono::system_clock::now();
    liner(abc, abc, abc, abc, abc);
    std::chrono::time_point<std::chrono::system_clock> time_end = std::chrono::system_clock::now();
    cout << (std::chrono::duration_cast<std::chrono::nanoseconds> (time_end - time_begin).count()) / 1e9 << '\n';
    time_begin = std::chrono::system_clock::now();
    parallel(abc, abc, abc, abc, abc);
    time_end = std::chrono::system_clock::now();
    cout << (std::chrono::duration_cast<std::chrono::nanoseconds> (time_end - time_begin).count()) / 1e9 << '\n';
    return 0;
}
