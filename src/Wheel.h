#pragma once
#include <vector>

using std::vector;

class Wheel
{
private:
    vector<int> primes;
	int prime_count;

public:
	Wheel(int prime_count);
	int get_prime_count() const;
	int get_period();
	vector<int> get_wheel_primes() const;
	vector<int> get_non_spoke();
	~Wheel();
};

vector<int> get_prime_singleton();
