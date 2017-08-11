#pragma once
#include <string>
#include <vector>
#include "global.h"
#include "Wheel.h"

using std::string;
using std::vector;

bool is_prime(int x);
vector<string> to_str_vec(char ** c, int count);
void test_prime(const string& num);
vector<char> get_primes(int max, int wheel_prime_count = 3);
vector<char> get_primes_segmented(int max, 
    int wheel_prime_count = 3, int seg_size=1'000'000);
vector<char> get_init_vec(int max);
void init_vec(vector<char>& is_prime);
int extend_range(int max);
vector<char> get_primes_by_trial(int max);
template <typename T>
bool sequence_equal(vector<T>& x, vector<T>& y);
void set_composite(vector<char>& bytes, int n);
int get_index(int n);
int get_bit(int n);
int first_prime(Wheel& w);
bool is_prime(vector<char> &bytes, int n, vector<int> &wheel_prime);
bool is_prime(vector<char>& bytes, int n);
void set_wheel_multiples(vector<char>& primes, const Wheel &w);

#if DEBUG
void assert(bool x, const string& test_id);
void self_test();
void test_get_primes_by_trial();
void test_get_primes();
void wheel_test();
#endif
