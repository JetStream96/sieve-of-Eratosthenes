all:
	g++ -std=c++14 -c src/*.cpp 
	g++ -o bin/prime_gen src/*.o
