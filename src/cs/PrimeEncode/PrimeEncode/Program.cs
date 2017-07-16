using System;
using System.IO;

namespace PrimeEncode
{
    class Program
    {
        static void Main(string[] args)
        {
            var max = int.Parse(args[0]);
            var startT = DateTime.Now;
            var primes = PrimeEncode.GetPrimesBytes(max);
            Console.WriteLine($"Took {DateTime.Now.Subtract(startT).TotalMilliseconds} ms.");
            File.WriteAllBytes("1.bin", primes);
        }
    }
}