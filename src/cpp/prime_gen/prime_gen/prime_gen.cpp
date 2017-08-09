#include "stdafx.h"
#include "prime_gen.h"
#include <iostream>
#include "global.h"
#include "Wheel.h"
#include <algorithm>

using std::cout;
using std::stoi;
using std::exception;
using std::ceil;
using std::floor;
using std::min;
using std::max;

bool is_prime(int x)
{
	if (x == 2) return true;

	int n = 3;
	while (n*n <= x)
	{
		if (x%n == 0 && x != n) return false;
		n += 2;
	}

	return true;
}

vector<string> to_str_vec(char ** c, int count)
{
	auto res = vector<string>();
	for (int i = 0; i < count; i++)
	{
		res.push_back(string(c[i]));
	}
	return res;
}

void test_prime(const string& num)
{
	try
	{
		auto n = stoi(num);
		cout << (is_prime(n) ? "True" : "False") << "\n";
	}
	catch (const exception&)
	{
		cout << "Input is not a valid integer.\n";
	}
}

/*
	Segmented sieve

	Encode [3, 5, 7, 9, 11, 13, 15, 17] in a single byte.
	First bit is 1 iff 3 is a prime. Second bit is 1 iff 5 is a prime.
	Similar for [19, 21, ..., 33], etc.
*/
vector<char> get_primes(int max, int wheel_prime_count, int seg_size)
{
	int n = extend_range(max);
	int sqrtn = (int)ceil(sqrt(n));
	auto wheel = Wheel(wheel_prime_count);
	auto ns = wheel.get_non_spoke();
	int period = wheel.get_period();
	auto primes = get_init_vec(max);

	for (int i = first_prime(wheel); i <= sqrtn; i += 2)
	{
		if (is_prime(primes, i))
		{
			int j = i*i/period;
			while (j < )
			{

			}
		}
	}

	return primes;
}

int first_prime(Wheel& w)
{
	auto p = w.get_wheel_primes();
	if (p.size() <= 1) return 3;
	return p[p.size() - 1] + 2;
}

vector<char> get_init_vec(int max)
{
	// Extend range so that the final count is divisible by 8.
	int max_e = extend_range(max);

	int byte_count = (int)ceil((max_e - 2.0) / 16);
	auto res = vector<char>(byte_count);
	init_vec(res);
	return res;
}

void init_vec(vector<char>& is_prime)
{
	for (size_t i = 0; i < is_prime.size(); i++)
	{
		is_prime[i] = (char)255;
	}
}

int extend_range(int max)
{
	if (max <= 2) return extend_range(3);
	return (int)(ceil((max - 2.0) / 16) * 16 + 1);
}

vector<char> get_primes_by_trial(int max)
{
	auto res = get_init_vec(max);

	for (int i = 3; i <= extend_range(max); i += 2)
	{
		if (!is_prime(i)) set_composite(res, i);
	}

	return res;
}

template <typename T>
bool sequence_equal(vector<T>& x, vector<T>& y)
{
	int len = x.size();
	if (len != y.size()) return false;
	for (int i = 0; i < len; i++)
	{
		if (x[i] != y[i]) return false;
	}

	return true;
}

bool is_prime(vector<char>& bytes, int n)
{
	int b = get_bit(n);
	int index = get_index(n);
	char c = 1 << (7 - b);
	return (bytes[index] & c) == c;
}

void set_composite(vector<char>& bytes, int n)
{
	int b = get_bit(n);
	int index = get_index(n);
	bytes[index] &= (~(1 << (7 - b)));
}

int get_index(int n)
{
	return (n - 3) / 16;
}

int get_bit(int n)
{
	return ((n - 3) % 16) / 2;
}

#if DEBUG

void assert(bool x, const string& test_id)
{
	if (!x)
	{
		cout << "Test " + test_id + " failed.\n";
	}
}

void self_test()
{
	assert(is_prime(2), "is_prime #0");
	assert(is_prime(3), "is_prime #1");
	assert(is_prime(5), "is_prime #2");
	assert(is_prime(7), "is_prime #3");
	assert(!is_prime(12), "is_prime #4");
	assert(!is_prime(99), "is_prime #5");
	assert(is_prime(101), "is_prime #6");

	assert(extend_range(2) == 17, "extend_range #0");
	assert(extend_range(3) == 17, "extend_range #1");
	assert(extend_range(17) == 17, "extend_range #2");
	assert(extend_range(18) == 17, "extend_range #3");
	assert(extend_range(19) == 33, "extend_range #4");

	test_get_primes_by_trial();
	test_get_primes();
	wheel_test();

	cout << "Self-test finished.";
}

void test_get_primes_by_trial()
{
	auto expected = vector<char>{ (char)237, (char)166 };
	assert(sequence_equal(expected, get_primes_by_trial(33)), "get_primes_by_trial");
}

void test_get_primes()
{
	int n = 1'000'000;
	auto expected = get_primes_by_trial(n);
	assert(sequence_equal(expected, get_primes(n)), "get_primes test");
}

void wheel_test()
{
	auto w = Wheel(3);
	assert(w.get_prime_count() == 3, "wheel_test #0");
	assert(sequence_equal(w.get_wheel_primes(), vector<int>{2, 3, 5}), "wheel_test #1");
	assert(sequence_equal(w.get_non_spoke(),
		vector<int>{1, 7, 11, 13, 17, 19, 23, 29}), "wheel_test #2");
}

#endif
