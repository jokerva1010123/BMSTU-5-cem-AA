using System;
using System.Diagnostics;
using System.Linq;

namespace lab4
{
    class Program
    {
        static void Sort_Bin_Insert(int[] arr) {
            int x;
            int left;
            int right;
            int sred;
            int n = arr.Length;
            for (int i = 1; i < n; i++)
            {
                if (arr[i - 1] > arr[i])
                {
                    x = arr[i];
                    left = 0;
                    right = i - 1;
                    do
                    {
                        sred = (left + right) / 2;
                        if (arr[sred] < x)
                            left = sred + 1;
                        else 
                            right = sred - 1;
                    } while (left <= right);
                    for (int j = i - 1; j >= left; j--)
                        arr[j + 1] = arr[j];
                    arr[left] = x;
                }
            }

            //for (int i = 0; i < n; i++)
                //Console.Write("{0}\t", arr[i]);
        }
        static void Counting_Sort(int[] arr, int max) {
            int n = arr.Length;
            int m = max + 1;
            int[] c = new int[m];
            for (int i = 0; i < m; i++)
                c[i] = 0;
            for (int i = 0; i < n; i++)
                c[arr[i]]++;
            int k = 0;
            for (int i = 0; i < m; i++)
                for (int j = 0; j < c[i]; j++) {
                    arr[k] = i;
                    k++;
                }

            //Console.WriteLine();
            //for (int i = 0; i < array.Length; i++)
                //Console.Write("{0}\t", array[i]);
        }
        static void Gnome_Sort(int[] arr) {
            int n = arr.Length;
            int i = 1;
            while (i < n)
            {
                if (i == 0 || arr[i - 1] <= arr[i]){
                    ++i;
                }
                else
                {
                    int temp = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = temp;
                    i--;
                }
            }

            //Console.WriteLine();
            //for (int j = 0; j < n; j++)
            //Console.Write("{0}\t", arr[j]);
        }
        static void Tests(int n){
            int[] arr = new int[n];
            Random rand = new Random();
            for (int i = 0; i < n; i++)
                arr[i] = rand.Next(0, 100000);

            int max = arr[0];

            for (int i = 0; i < n; i++)
                if (arr[i] > max)
                    max = arr[i];

            DateTime start1 = DateTime.Now;
            for (int i = 0; i < 100; i++)
                Sort_Bin_Insert(arr);
            DateTime end1 = DateTime.Now;
            TimeSpan time1 = (end1 - start1) / 100;
            Console.WriteLine("{0, -35} {1,20:N0}", "Ticks:\t", time1.Ticks);

            DateTime start2 = DateTime.Now;
            for (int i = 0; i < 100; i++)
                Counting_Sort(arr, max);
            DateTime end2 = DateTime.Now;
            TimeSpan time2 = (end2 - start2) / 100;
            Console.WriteLine("{0, -35} {1,20:N0}", "Ticks:\t", time2.Ticks);

            DateTime start3 = DateTime.Now;
            for (int i = 0; i < 100; i++)
                Gnome_Sort(arr);
            DateTime end3 = DateTime.Now;
            TimeSpan time3 = (end3 - start3) / 100;
            Console.WriteLine("{0, -35} {1,20:N0}", "Ticks:\t", time3 .Ticks);
        }
        static void Main(string[] args)
        {
            while(true) {
                Console.Write("n: ");
                int n = Convert.ToInt32(Console.ReadLine());
                Tests(n);
            }
        }
    }
}
