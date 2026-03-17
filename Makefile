CXXFLAGS += -std=c++14 -Wall -Wextra -Weffc++

top-vec: main.o
	g++ -o $@ $^

clean:
	rm -rf *.o top-vec
