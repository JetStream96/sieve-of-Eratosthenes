using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace PrimeEncode
{
    public static class PrimeEncode
    {
        private static bool IsPrime(int x, List<int> allPrimes)
        {
            foreach (var i in allPrimes)
            {
                if (x % i == 0)
                {
                    return false;
                }
                else if (i * i > x)
                {
                    break;
                }
            }

            return true;
        }

        private static byte[] Encode(int[] primes)
        {
            if (primes[0] != 11) throw new Exception();

            var len = primes.Length;
            var byteCount = Math.Ceiling((double)((primes[len - 1] - 10) / 30));

            var bytes = new byte[(int)byteCount];
            int[] remainders = { 11, 13, 17, 19, 23, 29, 31, 37 };
            var index = 0;

            for (var i = 0; i < byteCount; i++)
            {
                byte b = 0;
                for (var j = 0; j < 8; j++)
                {
                    if (index == len) break;

                    if (primes[index] == 30 * i + remainders[j])
                    {
                        b |= (byte)(1 << j);
                        index++;
                    }
                }

                bytes[i] = b;
            }

            return bytes;
        }

        private static int ExtendRange(int max)
        {
            if (max < 11) return 40;
            return (int)(Math.Ceiling((max - 10.0) / 30) * 30 + 10);
        }

        private static List<int> GetPrimesInRange(int sectorStart, int sectorCount,
            List<int> allPrimes)
        {
            var n = sectorStart * 30 + 11;
            for (int i = 0; i < sectorCount; i++)
            {
                if (IsPrime(n, allPrimes)) allPrimes.Add(n);
                n += 2;
                if (IsPrime(n, allPrimes)) allPrimes.Add(n);
                n += 4;
                if (IsPrime(n, allPrimes)) allPrimes.Add(n);
                n += 2;
                if (IsPrime(n, allPrimes)) allPrimes.Add(n);
                n += 4;
                if (IsPrime(n, allPrimes)) allPrimes.Add(n);
                n += 6;
                if (IsPrime(n, allPrimes)) allPrimes.Add(n);
                n += 2;
                if (IsPrime(n, allPrimes)) allPrimes.Add(n);
                n += 6;
                if (IsPrime(n, allPrimes)) allPrimes.Add(n);
                n += 4;
            }

            return allPrimes;
        }

        public static byte[] GetPrimesBytes(int max)
        {
            return Encode(GetPrimes(max).Skip(1).ToArray());
        }

        // Primes starting from 11.
        public static List<int> GetPrimes(int max)
        {
            var primes = new List<int>() { 7 };
            return GetPrimesInRange(0, (max - 10) / 30, primes);
        }

        /*
        private static void CombineLists(List<int>[] x,List<int> y,int index,object _lock)
        {
            lock (_lock)
            {
                x[index]=
            }
        }*/
        /*
        private static void AddToList(List<int> primeList, List<int> threadRes,
            int index, object _lock, int chunkSize)
        {
            lock (_lock)
            {
                primeList.AddRange(threadRes);
            }
        }*/

        private static void FillPrimesParallel(List<int> allPrimes, int currentSeg,
            int segCount, object _lock, int maxSegCount)
        {
            var lists = new List<int>[4];

            for (int i = 0; i < 4; i++)
            {
                var t = new Thread(() => ThreadTask(i, currentSeg + i * segCount, segCount,
                    allPrimes, _lock, lists, maxSegCount));
                t.Start();
            }
        }

        private static void ThreadTask(int index, int currentSeg, int segCount,
            List<int> allPrimes, object _lock, List<int>[] lists, int maxSegCount)
        {
            var p = GetPrimesInRange(currentSeg, segCount, allPrimes);

            lock (_lock)
            {
                lists[0] = p;

                if (lists.All(i => i != null))
                {
                    for (int j = 0; j < 4; j++)
                    {
                        allPrimes.AddRange(lists[j]);
                    }

                    FillPrimesParallel(allPrimes, currentSeg + 4 * segCount,
                        segCount, _lock, maxSegCount);
                }
            }
        }

        public static void GetPrimesParallel(int max, Action callback)
        {
            object _lock = new object();

            // Number of bytes to encode.
            const int segCount = 30000;
            const int chunkSize = segCount * 30;

            // Get primes starting from 11.
            var primes = GetPrimes(chunkSize + 10);
            var currentSeg = segCount;
            var maxSegCount = Math.Ceiling((max - 10.0) / 30);

            FillPrimesParallel(primes, currentSeg, segCount, _lock, (int)maxSegCount);
        }

    }
}
