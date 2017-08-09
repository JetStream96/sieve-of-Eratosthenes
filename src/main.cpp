#include "prime_gen.h"
#include <string>
#include <iostream>
#include "Wheel.h"
#include "global.h"

int main(int argc, char* argv[]) {
	auto arg = to_str_vec(argv, argc);
	
	// First arg is the executable name.
	if (argc == 2) {
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
	}

	return 0;
}