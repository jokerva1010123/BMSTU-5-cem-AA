using System;
using System.Diagnostics;
using System.Threading;
using System.Linq;

namespace test1
{
    class Program
    {
        static int Distance_Lewenstein(string str1, int length1, string str2, int length2, bool T)
        {
            int[,] matrix = new int[length1, length2];
            for (int i = 0; i < length1; i++)
                matrix[i, 0] = i;
            for (int i = 0; i < length2; i++)
                matrix[0, i] = i;

            for (int i = 1; i < length1; i++)
            {
                for (int j = 1; j < length2; j++)
                {
                    int I = matrix[i, j - 1] + 1;  // insert
                    int D = matrix[i - 1, j] + 1;  // delete
                    int R = matrix[i - 1, j - 1] + Match(str1[i - 1], str2[j - 1]);  // replase

                    matrix[i, j] = Math.Min(I, Math.Min(D, R));
                }
            }

            // печать матрицы
            if (T)
            {
                for (int i = 0; i < length1; i++)
                {
                    for (int j = 0; j < length2; j++)
                        Console.Write("{0}\t", matrix[i, j]);
                    Console.WriteLine();
                }
            }
            return matrix[length1 - 1, length2 - 1];
        }


        static int Distance_Damerau_Levenshtein(string str1, int length1, string str2, int length2, bool T)
        {
            int[,] matrix = new int[length1, length2];
            for (int i = 0; i < length1; i++)
                matrix[i, 0] = i;
            for (int i = 0; i < length2; i++)
                matrix[0, i] = i;

            for (int i = 1; i < length1; i++)
            {
                for (int j = 1; j < length2; j++)
                {
                    int I = matrix[i, j - 1] + 1;  // insert
                    int D = matrix[i - 1, j] + 1;  // delete
                    int R = matrix[i - 1, j - 1] + Match(str1[i - 1], str2[j - 1]);  // replase
                    int tmp = Math.Min(I, Math.Min(D, R));

                    if (i > 1 && j > 1 && str1[i - 2] == str2[j-1] && str1[i-1] == str2[j - 2]) {
                        int tmp1 = matrix[i - 2, j - 2] + 1;

                        tmp = Math.Min(tmp, tmp1);
                    }

                    matrix[i, j] = tmp;
                }
            }

            // печать матрицы
            if (T)
            {
                for (int i = 0; i < length1; i++)
                {
                    for (int j = 0; j < length2; j++)
                        Console.Write("{0}\t", matrix[i, j]);
                    Console.WriteLine();
                }
            }
            return matrix[length1 - 1, length2 - 1];
        }

        static int Distance_Lewenstein_recursion(string str1, int length1, string str2, int length2) {

            if (length1 == 0 && length2 == 0)
                return 0;
            if (length1 > 0 && length2 == 0)
                return length1;
            if (length1 == 0 && length2 > 0)
                return length2;

            int I = Distance_Lewenstein_recursion(str1, length1, str2, length2 - 1) + 1;
            int D = Distance_Lewenstein_recursion(str1, length1 - 1, str2, length2) + 1;
            int R = Distance_Lewenstein_recursion(str1, length1-1, str2, length2 - 1)
                + Match(str1[length1-1], str2[length2-1]);

            return Math.Min(I, Math.Min(D, R));
        }


        static int Match(char s1, char s2)
        {
            return s1 == s2 ? 0 : 1;
        }

        private static Random random = new Random();
        public static string RandomString(int length)
        {
            const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            return new string(Enumerable.Repeat(chars, length)
              .Select(s => s[random.Next(s.Length)]).ToArray());
        }

        static void test() {
            Stopwatch stopWatch = new Stopwatch();

            Console.Write("Введите длину слов: ");

            int len = Convert.ToInt32(Console.ReadLine());

            string s1 = RandomString(len);
            string s2 = RandomString(len);

            TimeSpan time2, time3;


            for (int i = 0; i < 100; i++) {
                stopWatch.Start();
                Distance_Lewenstein(s1, s1.Length + 1, s2, s2.Length + 1, false);
                stopWatch.Stop();

                TimeSpan time1 = stopWatch.Elapsed;
                time2 += time1;
            }

            Console.WriteLine("   {0,-35} {1,20:N0}", "Ticks   L  :", time2.Ticks);

            

            for (int i = 0; i < 100; i++)
            {
                stopWatch.Start();
                Distance_Damerau_Levenshtein(s1, s1.Length + 1, s2, s2.Length + 1, false);
                stopWatch.Stop();

                TimeSpan time1 = stopWatch.Elapsed;
                time3 += time1;
            }

            Console.WriteLine("   {0,-35} {1,20:N0}", "Ticks   D-L  :", time3.Ticks);
        }

        static void Input() {
            Stopwatch stopWatch = new Stopwatch();

            Console.WriteLine("Введите первое слово: ");
            string str1 = Console.ReadLine();
            Console.WriteLine("Введите второе слово: ");
            string str2 = Console.ReadLine();
            int result = 0;

            stopWatch.Start();
            result = Distance_Lewenstein(str1, str1.Length + 1, str2, str2.Length + 1, true);
            stopWatch.Stop();
            Console.WriteLine("\n\nРасстояние Левенштейна: {0}", result);
            TimeSpan t1 = stopWatch.Elapsed;
            Console.WriteLine("   {0,-35} {1,20:N0}", "Ticks:", t1.Ticks);
            //Console.Write("{0}\t", result);
            Console.WriteLine();



            stopWatch.Start();
            result = Distance_Damerau_Levenshtein(str1, str1.Length + 1, str2, str2.Length + 1, true);
            stopWatch.Stop();
            Console.WriteLine("\n\nРасстояние Дамерау-Левенштейна: {0}", result);
            //Console.Write("{0}\t", result);
            TimeSpan t2 = stopWatch.Elapsed;
            Console.WriteLine("   {0,-35} {1,20:N0}", "Ticks:", t2.Ticks);
            Console.WriteLine();


            stopWatch.Start();
            result = Distance_Lewenstein_recursion(str1, str1.Length, str2, str2.Length);
            stopWatch.Stop();
            Console.WriteLine("\n\nРасстояние Левенштейна (рекурсивное): {0}", result);
            TimeSpan t3 = stopWatch.Elapsed;
            Console.WriteLine("   {0,-35} {1,20:N0}", "Ticks:", t3.Ticks);
            //Console.Write("{0}\t", result);
            Console.WriteLine();

            //test();
        }

        static void Main(string[] args)
        {
            while (true)
              //Input();
              test();
        }
    }
}
