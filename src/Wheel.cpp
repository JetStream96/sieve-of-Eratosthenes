#include "Wheel.h"
#include <iostream>

Wheel::Wheel(int prime_count)
{
	this->primes = get_prime_singleton();
	this->prime_count = prime_count;
}

vector<int> get_prime_singleton()
{
	static vector<int> p;
	if (p.empty())
	{
		p = vector<int>({ 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47 });
	}
	return p;
}

int Wheel::get_prime_count() const
{
	return prime_count;
}

int Wheel::get_period()
{
	auto p = get_wheel_primes();
	int period = 1;

	for (int i = 0; i < p.size(); i++)
	{
		period *= p[i];
	}
	return period;
}

vector<int> Wheel::get_wheel_primes() const
{
	static vector<int> p;
	if (p.empty())
	{
		auto s = get_prime_singleton();
		for (int i = 0; i < get_prime_count(); i++)
		{
			p.push_back(s[i]);
		}
	}
	return p;
}

vector<int> Wheel::get_non_spoke()
{
	auto p = get_wheel_primes();
	auto res = vector<int>();
	for (int i = 1; i <= get_period(); i++)
	{
		bool is_spoke = false;
		for (int j = 0; j < p.size(); j++)
		{
			if (i%p[j] == 0)
			{
				is_spoke = true;
				break;
			}
		}
		if (!is_spoke) res.push_back(i);
	}
	return res;
}

Wheel::~Wheel()
{
}
