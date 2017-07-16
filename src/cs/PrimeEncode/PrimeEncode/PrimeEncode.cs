using System;
using System.Collections.Generic;
using System.Linq;

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
            return (int)(Math.Ceiling((double)((max - 10) / 30) * 30 + 10));
        }

        public static byte[] GetPrimes(int max)
        {
            var r = ExtendRange(max);
            var primes = new List<int>() { 7 };
            var n = 11;

            while (n < r)
            {
                if (IsPrime(n, primes)) primes.Add(n);
                n += 2;
                if (IsPrime(n, primes)) primes.Add(n);
                n += 4;
                if (IsPrime(n, primes)) primes.Add(n);
                n += 2;
                if (IsPrime(n, primes)) primes.Add(n);
                n += 4;
                if (IsPrime(n, primes)) primes.Add(n);
                n += 6;
                if (IsPrime(n, primes)) primes.Add(n);
                n += 2;
                if (IsPrime(n, primes)) primes.Add(n);
                n += 6;
                if (IsPrime(n, primes)) primes.Add(n);
                n += 4;
            }

            return Encode(primes.Skip(1).ToArray());
        }

        public static byte[] GetPrimes(int max, int threadCount)
        {
            var r = ExtendRange(max);
            var primes = new List<int> { 2 };

            for (var i = 3; i <= max; i += 2)
            {
                if (IsPrime(i, primes))
                {
                    primes.Add(i);
                }
            }

            return Encode(primes.Skip(4).ToArray());
        }


    }
}
