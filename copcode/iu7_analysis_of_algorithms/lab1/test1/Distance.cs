using System;
namespace test1
{
    public class Distance
    {
        public
        int Distance_Lowenstein(string str1, int length1, string str2, int length2)
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
                    int R = matrix[i - 1, j - 1] + Compare(str1[i - 1], str2[j - 1]);  // replase

                    matrix[i, j] = Math.Min(I, Math.Min(D, R));
                }
            }

            // печать матрицы
            for (int i = 0; i < length1; i++)
            {
                for (int j = 0; j < length2; j++)
                    Console.Write("{0}\t", matrix[i, j]);
                Console.WriteLine();
            }
            return matrix[length1 - 1, length2 - 1];
        }

        static int Distance_Domerau_Levenshtein(string str1, int length1, string str2, int length2)
        {
            return 0;
        }

        static int Compare(char s1, char s2)
        {
            return s1 == s2 ? 0 : 1;
        }
    }
}
