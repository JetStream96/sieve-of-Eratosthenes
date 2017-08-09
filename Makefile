all:
	mkdir -p bin
	g++ -std=c++14 -c src/*.cpp 
	g++ -o bin/prime_gen *.o

clean:
	rm *.o
	rm bin/prime_gen
