CXXFLAGS += -std=c++14 -Wall -Wextra -Weffc++ -MMD


top-vec: main.o
	$(CXX) -o $@ $^

-include main.d

clean:
	$(RM) -rf *.d *.o top-vec
