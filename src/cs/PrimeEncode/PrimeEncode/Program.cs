using System;
using System.IO;
using System.Linq;
using System.Threading;

namespace PrimeEncode
{
    class Program
    {
        static void Main(string[] args)
        {
            var max = int.Parse(args[0]);
            var startT = DateTime.Now;

            if (args[1] == "-p")
            {
                PrimeEncode.GetPrimesParallel(max, (p) =>
                {
                    var primes = PrimeEncode.Encode(p.Skip(1).ToArray());
                    Console.WriteLine($"Took {DateTime.Now.Subtract(startT).TotalMilliseconds} ms.");
                    File.WriteAllBytes("1.bin", primes);
                });

                while (true)
                {
                    Thread.Sleep(100);
                }
            }
            else
            {
                var primes = PrimeEncode.GetPrimesBytes(max);
                Console.WriteLine($"Took {DateTime.Now.Subtract(startT).TotalMilliseconds} ms.");
                File.WriteAllBytes("1.bin", primes);
            }            
        }
    }
}