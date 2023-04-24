#include "pipeline.hpp"
#include "matrix.hpp"

using namespace std;

void task1(queue<matrix_t> &q1, queue<matrix_t> &q2)
{
    mutex m;
    
    m.lock();
    matrix_t tmp_matrix = q1.front();
    m.unlock();

    tmp_matrix = change_matrix(tmp_matrix);

    m.lock();
    q2.push(tmp_matrix);
    m.unlock();

    m.lock();
    q1.pop();
    m.unlock();
}

void task2(queue<matrix_t> &q2, queue<matrix_t> &q3)
{
    mutex m;
    
    m.lock();
    matrix_t tmp_matrix = q2.front();
    m.unlock();

    tmp_matrix = truncate_matrix(tmp_matrix);

    m.lock();
    q3.push(tmp_matrix);
    m.unlock();

    m.lock();
    q2.pop();
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

    vector<matrix_state_t> state(cnt);
    for(int i = 0; i < cnt; i++)
    {
        matrix_state_t tmp_state;
        tmp_state.stage_1 = false;
        tmp_state.stage_2 = false;
        tmp_state.stage_3 = false;
        state[i] = tmp_state;
    }
    
    for (int i = 0; i < cnt; i++)
    {
        task1(ref(qA1), ref(qA2));
        task1(ref(qB1), ref(qB2));

        task2(ref(qA2), ref(qA3));
        task2(ref(qB2), ref(qB3));

        task3(ref(qA3), ref(qB3), ref(q_res));
    }
}
