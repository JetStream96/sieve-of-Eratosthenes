#include "prime_gen.h"
#include <string>
#include <iostream>
#include "Wheel.h"
#include "global.h"
#include <ctime>

using std::cout;

int main(int argc, char *argv[])
{
	auto arg = to_str_vec(argv, argc);
	int start_time = clock();

	// First arg is the executable name.
	if (argc == 2)
	{
#if DEBUG
		if (arg[1] == "test")
		{
			// self-test
			self_test();
		}
#endif
	}
	else if (argc == 3)
	{
		if (arg[1] == "is_prime")
		{
			test_prime(arg[2]);
		}
		else if (arg[1] == "gen")
		{
			auto p = get_primes(1'000'000'000, 3);
			cout << (int)(uint8_t)p[p.size() - 2];
		}
	}

	if(contain<string>(arg, "--time"))
	{
		cout << "Took " << (clock() - start_time)/1000 << " ms\n"; 
	}

	return 0;
}