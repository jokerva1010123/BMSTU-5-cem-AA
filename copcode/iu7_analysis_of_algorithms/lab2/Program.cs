using System;
using System.Diagnostics;
using System.Linq;


namespace lab2
{
    class Program
    {
        static int [,] Alg_std(int [,] m1, int [,] m2) {
            int m = m1.GetLength(0);
            int q = m2.GetLength(1);
            int n = m2.GetLength(0);
            int[,] res = new int[m, q];

            if (m1.GetLength(1) != n){
                Console.WriteLine("Неправильный размер матрицы");
                return res;
            }


            for (int i = 0; i <  m; i++) // 2+m(2
                for (int j = 0; j < q; j++)  // 2+q(2
                    for (int k = 0; k < n; k++) // 2+k(2
                        res[i, j] += m1[i, k] * m2[k, j]; // 8
            return res;
        }
        static int [,] Alg_vin(int [,] m1, int [,] m2) {
            int m = m1.GetLength(0);
            int q = m2.GetLength(1);
            int n = m2.GetLength(0);

            int[,] res = new int[m, q];

            if (m1.GetLength(1) != n)
            {
                Console.WriteLine("Неправильный размер матрицы");
                return res;
            }

            int [] H = new int[m];
            int [] V = new int[q];

            for (int i = 0; i < m; i++) // 2+m(2
            {
                for (int j = 0; j < n/2; j ++) // 3 + n/2(3
                    H[i] = H[i] + m1[i, 2 * j] * m1[i, 2 * j + 1]; // 12
            }

            for (int i = 0; i < q; i++) // 2+q(2
            {
                for (int j = 0; j < n / 2; j++) // 3+n/2(3
                    V[i] = V[i] + m2[2 * j, i] * m2[2 * j + 1, i]; // 12
            }

            for (int i = 0; i < m; i++)  // 2+m(2
                for (int j = 0; j < q; j++)  // 2+q(2
                {
                    res[i, j] = -H[i] - V[j]; // 7
                    for (int k = 0; k < n/2; k ++)  // 3+n/2(3
                        res[i, j] = res[i, j] + ((m1[i, 2*k] + m2[2 * k + 1, j]) * (m1[i, 2 * k + 1] + m2[2 * k, j])); // 23
                }

            if (n % 2 != 0)  // 2
                for (int i = 0; i < m; i++)  // 2+m(2
                    for (int j = 0; j < q; j++)  // 2+q(2
                        res[i, j] = res[i, j] + m1[i,n - 1] * m2[n - 1,j];  // 13
            return res;
        }
        static int [,] FillMtr(int n, int m) {
            int [,]result = new int[n, m];
            Random rand = new Random();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    result[i, j] = rand.Next(-100, 100);
                    //Console.Write("{0}\t", result[i, j]);
                }
                //Console.WriteLine();
            }
            //Console.WriteLine();
            return result;
        }
        static int[,] Alg_vin_mod(int[,] m1, int[,] m2)
        {
            int m = m1.GetLength(0);
            int q = m2.GetLength(1);
            int n = m2.GetLength(0);

            int[,] res = new int[m, q];

            if (m1.GetLength(1) != n)
            {
                Console.WriteLine("Неправильный размер матрицы");
                return res;
            }

            int[] H = new int[m];
            int[] V = new int[q];

            //int d = q / 2;

            for (int i = 0; i < m; i++)  // 2+m(2
            {
                for (int j = 0; j < n-1; j += 2)  // 3+n/2(3
                    H[i] += m1[i, j] * m1[i, j + 1];  // 8
            }

            for (int i = 0; i < q; i++)  // 2+q(2
                for (int j = 0; j < n-1; j += 2)  // 3+n/2(3
                    V[i] += m2[j, i] * m2[j + 1, i];  // 8


            int nn = n - 1;
            bool remainder = (n%2 == 0);
            for (int i = 0; i < m; i++)  // 2+m(2
                for (int j = 0; j < q; j++)  // 2+q(2
                {
                    res[i, j] = -H[i] - V[j];  // 7
                    for (int k = 0; k < nn; k += 2)  // 2+n/2(2
                        res[i, j] += ((m1[i, k] + m2[k + 1, j]) *
                                      (m1[i, k + 1] + m2[k, j]));  // 16
                    if (!remainder)  // 1
                        res[i, j] += m1[i, nn] * m2[nn, j];  // 8
                }

            return res;
        }
            static void Print_matrix(int [,] mtr, int n, int m) {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                    Console.Write("{0}\t", mtr[i, j]);
                Console.WriteLine();
            }
            Console.WriteLine();
            Console.WriteLine();
        }
        static int Tests(int n1, int m1, int n2, int m2) {

            int [,] mtr1 = FillMtr(n1, m1);
            int[,] mtr2 = FillMtr(n2, m2);

            //Console.WriteLine("\nСтандартный алгоритм:\n");
            DateTime start1 = DateTime.Now;
            for (int i = 0; i < 100; i++)
                Alg_std(mtr1, mtr2);
            DateTime end1 = DateTime.Now;
            //Print_matrix(res, n1, m2);
            TimeSpan time1 = (end1 - start1)/10;
            Console.WriteLine("\nСтандартный алгоритм:\n");
            Console.WriteLine("   {0,-35} {1,20:N0}", "Ticks:\t", time1.Ticks);

            Console.WriteLine("Алгоритм Винограда:\n");
            DateTime start2 = DateTime.Now;
            for (int i = 0; i < 100; i++)
                Alg_vin(mtr1, mtr2);
            DateTime end2 = DateTime.Now;
            //Print_matrix(res, n1, m2);
            TimeSpan time2 = (end2 - start2)/10;
            Console.WriteLine("   {0,-35} {1,20:N0}", "Ticks:\t", time2.Ticks);

            Console.WriteLine("Модифицированный алгоритм Винограда:\n");
            DateTime start3 = DateTime.Now;
            for (int i = 0; i < 100; i++)
                Alg_vin_mod(mtr1, mtr2);
            DateTime end3 = DateTime.Now;
            //Print_matrix(res, n1, m2);
            TimeSpan time3 = (end3 - start3)/10;
            Console.WriteLine("   {0,-35} {1,20:N0}", "Ticks:\t", time3.Ticks);

            return 0;
        }
        static void Main(string[] args)
        {
            while (true)
            {
                Console.WriteLine("n: ");
                int n = Convert.ToInt32(Console.ReadLine());
                Tests(n, n, n, n);
            }
        }
    }
}
